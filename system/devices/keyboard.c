#include "../include/keyboard.h"
#include "../include/common.h"
#include "../include/hal.h"
#include "../include/heap.h"
#include "../include/menu.h"
#include "../include/string.h"
#include "../include/windows.h"
#include "../include/drawing.h"
#include "../include/streams.h"
#include "../include/loader.h"

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
   '2', '3', '0', '.',
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
   '2', '3', '0', '.',
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

    //if app grabs all keys without esc and tab
    if(GetSystemContext()->currentWindow->keys == 1 && scanCode != 0x01 && scanCode != 0x81 && scanCode != 0x0f && scanCode != 0x8f){
        if(kHit==1){
            kHit=0;    
            //test stdin
            if(GetSystemContext()->GetInStreamSize()<100)
                GetSystemContext()->PushInStream(GetChar(scanCode));
        }
        else{
            kHit++;
        }
    }

    //here goes only some functional keys
    if(scanCode == 0x81){ //esc release
        //close actually open window
        if(GetSystemContext()->currentWindow!=NULL)
            CloseWindow(GetSystemContext()->currentWindow);
    }
    else if(scanCode == 0x01){ //esc pushed

    }
    else if(scanCode == 0x1C){ //enter pushed

    }
    else if(scanCode == 0x9C){ //enter release

    }
    else if(scanCode == 0x1D){ //left control pushed

    }
    else if(scanCode == 0x9D){ //left control release

    }
    else if(scanCode == 0x2A){ //left shift pushed

    }
    else if(scanCode == 0xAA){ //left shift release

    }
    else if(scanCode == 0x36){ //right shift pushed

    }
    else if(scanCode == 0xB6){ //right shift release

    }
    else if(scanCode == 0x38){ //left alt pushed

    }
    else if(scanCode == 0xB8){ //left alt release

    }
    else if(scanCode == 0x0F){ //tab pushed
        //SwichWindow();
    }
    else if(scanCode == 0x8F){ //tab release
        SwichWindow();
    }
    else if(scanCode == 0x3A){ //caps pushed
        //SwichWindow();
    }
    else if(scanCode == 0xBA){ //caps release
        
    }
    else if(scanCode == 0x3B){ //f1 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xBB){ //f1 release
        
    }
    else if(scanCode == 0x3C){ //f2 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xBC){ //f2 release
        
    }
    else if(scanCode == 0x3D){ //f3 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xBD){ //f3 release
        
    }
    else if(scanCode == 0x3E){ //f4 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xBE){ //f4 release
        
    }
    else if(scanCode == 0x3F){ //f5 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xBF){ //f5 release
        
    }
    else if(scanCode == 0x40){ //f6 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xC0){ //f6 release
        
    }
    else if(scanCode == 0x41){ //f7 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xC1){ //f7 release
        
    }
    else if(scanCode == 0x42){ //f8 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xC2){ //f8 release
        
    }
    else if(scanCode == 0x43){ //f9 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xC3){ //f9 release
        
    }
    else if(scanCode == 0x44){ //f10 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xC4){ //f10 release
        
    }
    else if(scanCode == 0x57){ //f11 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xD7){ //f11 release
        
    }
    else if(scanCode == 0x58){ //f12 pushed
        //SwichWindow();
    }
    else if(scanCode == 0xD8){ //f12 release
        
    }
    else if(scanCode == 0x45){ //numlock pushed
        //SwichWindow();
    }
    else if(scanCode == 0xC5){ //numlock release
        
    }
    else if(scanCode == 0x46){ //scroll lock pushed
        //SwichWindow();
    }
    else if(scanCode == 0xC6){ //scroll lock release
        
    }
    /*else if(scanCode == 0x4F){ //numpad 1 pushed

    }
    else if(scanCode == 0xCF){ //numpad 1 release
        //RunApp(LoadApp(0));
    }
    else if(scanCode == 0x50){ //numpad 2 pushed
        
    }
    else if(scanCode == 0xD0){ //numpad 2 release
        //RunApp(LoadApp(1));
    }
    else if(scanCode == 0x51){ //numpad 3 pushed
        
    }
    else if(scanCode == 0xD1){ //numpad 3 release
        //RunApp(LoadApp(2));
    }
    else if(scanCode == 0x4C){ //numpad 5 pushed
        
    }
    else if(scanCode == 0xCC){ //numpad 5 release
        //RunApp(LoadApp(3));
    }*/
    else{

    }
}