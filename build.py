import os
import subprocess
from glob import glob

image = []

cmds = []
obj_cmds = []

obj_files = []

gcc_flags = "-std=c11 -nostdlib -masm=intel -Wall -Wextra -mgeneral-regs-only -c -ggdb -O0"
ld_flags = "--image-base 0x400000 -entry=KERN_Start -s"
asm_flags = "-masm=intel -c"

dirs = [d for d in os.listdir("system") if os.path.isdir(os.path.join("system", d))]

#compile *.c
for d in dirs:
    for fname in glob(f"system\{d}\*.c"):
        binary = f"{fname.split('.')[0]}.o"
        obj_files.append(binary)
        obj_cmds.append([f"gcc {fname} {gcc_flags} -o {binary}"])

#compile *.s
for d in dirs:
    for fname in glob(f"system\{d}\*.s"):
        binary = f"{fname.split('.')[0]}.obj"
        obj_files.append(binary)
        obj_cmds.append([f"gcc {fname} {asm_flags} -o {binary}"])

# compile *.c in main kernel directory
for fname in glob("system\*.c"):
    binary = f"{fname.split('.')[0]}.o"
    obj_files.append(binary)
    obj_cmds.append([f"gcc {fname} {gcc_flags} -o {binary}"])

# compile *.s in main kernel directory
for fname in glob("system\*.s"):
    binary = f"{fname.split('.')[0]}.obj"
    obj_files.append(binary)
    obj_cmds.append([f"gcc {fname} {asm_flags} -o {binary}"])

for cmd in obj_cmds:
    result = subprocess.check_output(cmd[0], shell=True)
    print(f"Execute: {cmd[0]}")
    if result:
        print(result)
    print()

#link everything
cmds = [
    ["nasm boot\\bootsector.asm", "boot\\bootsector"],
    ["nasm boot\\bootloader.asm", "boot\\bootloader"],
    [f"ld {(' '.join(obj_files))} {ld_flags} -o system\kernel.exe", "system\kernel.exe"],
]

for cmd in cmds:
    result = subprocess.check_output(cmd[0], shell=True)
    print(f"Execute: {cmd[0]}")
    if result:
        print(result)
    print()

padding = 0
stage2_size = os.stat(cmds[1][1]).st_size
kernel_size = os.stat(cmds[2][1]).st_size
sectors = (stage2_size + kernel_size) / 512
p = 0

if (sectors - int(sectors)) != 0:
    padding= 512 - ((stage2_size + kernel_size) % 512)

print(f"Images sizes: {stage2_size} {kernel_size} {padding} {sectors}")

if sectors > 255:
    raise("Image is to large...")

with open(cmds[0][1], "rb+") as stage1:
    data = stage1.read()
    index = data.index(b"\xb0\x97\x90\x90")
    data = bytearray(data)
    data[index+1] = int(sectors)
    stage1.seek(0)
    stage1.write(data)
    print("Stage1 fixed")

for file in cmds:
    if file[1] is not None:
        with open(file[1],"rb") as f:
            image.append(f.read())

print("Add padding...")
while padding:
    p+=1
    image.append(b"\0")
    padding-=1

sectors = (stage2_size + kernel_size + p) / 512
if p > 0:
    print(f"Images sizes: {stage2_size} {kernel_size} {padding} {sectors}")

#make image
with open("floppy.bin", "wb") as f:
    for b in image:
        f.write(b)

subprocess.call("runqemu.bat")