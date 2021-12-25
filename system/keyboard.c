#include "include/keyboard.h"
#include "include/common.h"
#include "include/hal.h"
#include "include/heap.h"
#include "include/menu.h"
#include "include/string.h"
#include "include/windows.h"
#include "include/drawing.h"

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
        else if(scanCode == 0x0F || scanCode == 0x8F){ //tab
            //SwichWindow();
        }
        else if(scanCode == 0x38 || scanCode == 0xB8){ //left alt
            /*WindowContext* context = GetSystemContext()->mainWindow->children[GetSystemContext()->mainWindow->childrenCount-1];
            
            WindowContext* bcontext = (WindowContext*)MallocHeap(sizeof(WindowContext));
            MemcpyBuffers((char*)bcontext, (char*)context, sizeof(WindowContext));
            
            char buffer[100];
            FormatString(buffer, "C %u %u %u %u", context->x, context->y, bcontext->x, bcontext->y);
            DrawText(context, 30, 30, buffer, 2, RED, GREYB);

            //CloseWindow(bcontext);
            context->x+=10;
            context->y+=5;
            DrawWindow(context);*/
        }
        kHit++;
    }
    else{
        kHit=0;
    }
}