## General info
It is simple operating system for x86 CPUs. This time the main goal was draw window based UI.
	
## Details
What works (or works in some part):
* Boot (Real Mode > Protected Mode > Long Mode)
* VESA Graphic Mode (1600x1200 256 colors)
* Drawing
    * Windows (window with title bar)
    * Text Fields
    * Buttons with label
    * Progress bars
    * Basic shapes such as circles, rectangles, lines
* Each window and window element has own context structure so OS can manage it
* Window focus swiching and closing
* System place in memory at 0x800000 struct with API so it can be used in external apps
* System contains PE file loader so its posible to write external apps base on API
* Interrupts
* Keyboard (keys are catch to STDIN and what happends depends on active app)
* Heap
* BSOD :D

Memory map is available in memmap.txt and here below screenshot. Whole system use 130 pages(2MB each). Every page is map 1:1 expect last two.

## Requirements
* GCC 64bits
* NASM
* Python 3
* QEMU

All this stuff should be added to PATH so that the build script can execute.

## Run
To run this project:

```
$ git clone [...]
$ python build.py
```

## How it looks like?

<img src="https://github.com/sebastiansiedlarz409/OsikGUI/blob/master/s1.png"/>
<img src="https://github.com/sebastiansiedlarz409/OSikGUI/blob/master/s2.png"/>
<img src="https://github.com/sebastiansiedlarz409/OSikGUI/blob/master/s3.png"/>


## Memory map

```
//OSIK MAP MEMORY ADDRESSES TO VIRTUAL MEMORY ADDRESSES 1:1

TOTAL MEMORY: 128*2MB+4MB

------------------ 0x00007C00 (F) //bios boot entry point
|                |
|   bootsector   |
|                |
------------------ 0x00010000 (F) //bootloader is loaded here
|                |
|   bootloader   |
|       +        |
|     kernel     |
|     image      |
|       +        |
|      apps      |
|     images     |
|                |
------------------ 0x003FFE00 (V) //app table
------------------ 0x00400000 (V) //kernel base address
|                |
|     kernel     |
|                |
|                |
------------------ 0x00600000 (V) //heap
|                |
|     heap       |
|                |
|                |
------------------ 0x00800000 (V) //system api
|                |
|   system api   |
|                |
|                |
------------------ 0x00A00000 (V) //stack
|                |
|     stack      |
|                |
-----------------| 0x01000000 (V) //apps (+0x00200000 for every app)
|                |
|      apps      |
|                |
~~~~~~~~~~~~~~~~~~
|                |
|                |
------------------ 0x10000000 (V) //video ram
|                |
|   video ram    |
|                |
|                |
------------------ 0x10400000 (V) //end of ram
```