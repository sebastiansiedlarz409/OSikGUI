import os
import struct
import subprocess
from glob import glob

def saveImage(name, data):
    #make image
    with open(name, "wb") as f:
        for b in data:
            f.write(b)
    print(f"Saved image: {name}")

def getSubdirs(name, subdirs):
    dirs = [d for d in os.listdir(name) if os.path.isdir(os.path.join(name, d))]
    for el in dirs:
        subdirs.append(f"{name}\{el}")
    
    for el in dirs:
        getSubdirs(f"{name}\{el}", subdirs)

def buildApps():
    apps = ["welcome"]

    for app in apps:
        buildApp(app)

def buildApp(name):
    print(f"BUILD {name.upper()}")
    print()

    gcc_cmds = []
    obj_files = []

    gcc_flags = "-std=c11 -nostdlib -masm=intel -Wall -Wextra -mgeneral-regs-only -c -ggdb -O0"
    ld_flags = "--image-base 0xA00000 -entry=APP_Start -s"

    dirs = [f"apps\\{name}"]
    getSubdirs(f"apps\\{name}", dirs)
    
    #compile system
    #grab *.c
    for d in dirs:
        for fname in glob(f"{d}\*.c"):
            binary = f"{fname.split('.')[0]}.o"
            obj_files.append(binary)
            gcc_cmds.append([f"gcc {fname} {gcc_flags} -o {binary}"])

    #compile to object files
    for cmd in gcc_cmds:
        result = subprocess.check_output(cmd[0], shell=True)
        print(f"Execute: {cmd[0]}")
        if result:
            print(result)
        print()

    link = f"ld {(' '.join(obj_files))} {ld_flags} -o apps\{name}\{name}"
    result = subprocess.check_output(link, shell=True)
    print(f"Execute: {link}")
    if result:
        print(result)
    print()

def buildSystem():
    print("BUILD OSikGUI")
    print()

    #floppy image
    image = []

    gcc_cmds = []
    obj_files = []

    nasm_cmds = []
    boot_files = []

    files = ["boot\\bootsector","boot\\bootloader","system\kernel","apps\welcome\welcome"]

    #flags
    gcc_flags = "-std=c11 -nostdlib -masm=intel -Wall -Wextra -mgeneral-regs-only -c -ggdb -O0"
    ld_flags = "--image-base 0x400000 -entry=KERN_Start -s"
    asm_flags = "-masm=intel -c"

    #get all subdirectories
    dirs = ["boot","system"]
    getSubdirs("system", dirs)

    #compile bootloader
    #grab *.asm
    for d in dirs:
        for fname in glob(f"{d}\*.asm"):
            binary = fname.split('.')[0]
            boot_files.append(binary)
            nasm_cmds.append([f"nasm {fname}"])

    #compile
    for cmd in nasm_cmds:
        result = subprocess.check_output(cmd[0], shell=True)
        print(f"Execute: {cmd[0]}")
        if result:
            print(result)
        print()
    
    #compile system
    #grab *.c
    for d in dirs:
        for fname in glob(f"{d}\*.c"):
            binary = f"{fname.split('.')[0]}.o"
            obj_files.append(binary)
            gcc_cmds.append([f"gcc {fname} {gcc_flags} -o {binary}"])

    #grab *.s
    for d in dirs:
        for fname in glob(f"{d}\*.s"):
            binary = f"{fname.split('.')[0]}.obj"
            obj_files.append(binary)
            gcc_cmds.append([f"gcc {fname} {asm_flags} -o {binary}"])

    #compile to object files
    for cmd in gcc_cmds:
        result = subprocess.check_output(cmd[0], shell=True)
        print(f"Execute: {cmd[0]}")
        if result:
            print(result)
        print()

    #link
    link = f"ld {(' '.join(obj_files))} {ld_flags} -o {files[2]}"
    result = subprocess.check_output(link, shell=True)
    print(f"Execute: {link}")
    if result:
        print(result)
    print()

    padding = 0
    bootloader_size = os.stat(files[1]).st_size
    system_size = 0
    for i in range(2, len(files)):
        system_size += os.stat(files[i]).st_size
    sectors = (bootloader_size + system_size) / 512

    if (sectors - int(sectors)) != 0:
        padding = 512 - ((bootloader_size + system_size) % 512)

    print(f"Bootloader size: {bootloader_size} B\nSystem size: {system_size} B\nPadding: {padding} B\nSectors: {sectors}")

    if sectors > 255:
        exit("Image is to large! Exit")

    with open(files[0], "rb+") as bsec:
        data = bsec.read()
        index = data.index(b"\xb0\x97\x90\x90")
        data = bytearray(data)
        data[index+1] = int(sectors)
        bsec.seek(0)
        bsec.write(data)
        print("Bootsector fixed")

    for file in files:
        if file is not None:
            with open(file,"rb") as f:
                image.append(f.read())

    apps_ptr = len(image[0])+len(image[1])

    print(f"Apps table offset: {hex(apps_ptr)}")
    print("Image generated")

    print(f"Add padding: {padding} B")
    
    sectors = (bootloader_size + system_size + padding) / 512

    print(f"Sectors after adding padding: {sectors}")

    while padding:
        image.append(b"\0")
        padding-=1

    image[1] = image[1][:-8]
    image.insert(2, struct.pack("<q", len(image[1]) + len(image[2]) + 8 ))
    saveImage("floppy.bin", image)

buildApps()
buildSystem()

print("Booting system...")
subprocess.call("runqemu.bat")