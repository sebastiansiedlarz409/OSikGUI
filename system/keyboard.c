#include "keyboard.h"
#include "common.h"
#include "hal.h"
#include "menu.h"
#include "windows.h"
#include "drawing.h"

#include <stdint.h>

uint8_t kHit = 0;

const char scanCodeCh[] = {
   0, 0, '1', '2', //empty, esc
   '3', '4', '5', '6',
   '7', '8', '9', '0',
   '-', '=', 0, '\t', //backspace
   'q', 'w', 'e', 'r',
   't', 'y', 'u', 'i',
   'o', 'p', '[', ']',
   0,  0, 'a', 's', //enter, lctrl
   'd', 'f', 'g', 'h',
   'j', 'k', 'l', ';',
   '\'', '`', 0, '\\', //lshift
   'z', 'x', 'c', 'v',
   'b', 'n', 'm', ',',
   '.', '/', 0, '*', //rshift
   0, ' ', 0, 0, //lalt, CL, F1
   0, 0, 0, 0, //F2, F3, F4, F5
   0, 0, 0, 0, //F6, F7, F8, F9
   0, 0, 0, '7', //F10, number_lock, scroll_lock
   '8', '9', '-', '4',
   '5', '6', '+', '1',
   '2', '3', 0, '.',
   0, 0, 0, 0, //empty, empty, empty, F11
   0, 0, 0, 0, //F12, empty, empty, empty
   //asd
   0, 0, '1', '2', //empty, esc
   '3', '4', '5', '6',
   '7', '8', '9', '0',
   '-', '=', 0, '\t', //backspace
   'q', 'w', 'e', 'r',
   't', 'y', 'u', 'i',
   'o', 'p', '[', ']',
   0,  0, 'a', 's', //enter, lctrl
   'd', 'f', 'g', 'h',
   'j', 'k', 'l', ';',
   '\'', '`', 0, '\\', //lshift
   'z', 'x', 'c', 'v',
   'b', 'n', 'm', ',',
   '.', '/', 0, '*', //rshift
   0, ' ', 0, 0, //lalt, CL, F1
   0, 0, 0, 0, //F2, F3, F4, F5
   0, 0, 0, 0, //F6, F7, F8, F9
   0, 0, 0, '7', //F10, number_lock, scroll_lock
   '8', '9', '-', '4',
   '5', '6', '+', '1',
   '2', '3', 0, '.',
   0, 0, 0, 0, //empty, empty, empty, F11
   0, 0, 0, 0, //F12, empty, empty, empty
};

char GetChar(uint8_t scanCode)
{
    if(scanCode >= 0x81)
        scanCode -= 0x24;

    return scanCodeCh[scanCode];
}

void KeyboardHandler(void){
    uint8_t scanCode;
    PortInByte(0x60, &scanCode);

    if(!kHit){
        if(scanCode == 0x01 || scanCode == 0x81){ //esc
            //close actually open window
            CloseWindow(GetSystemContext()->mainWindow->children[GetSystemContext()->mainWindow->childrenCount-1]);
        }
        else if(scanCode == 0x0F || scanCode == 0x8F){
            SwichWindow();
        }
        kHit++;
    }
    else{
        kHit=0;
    }
}