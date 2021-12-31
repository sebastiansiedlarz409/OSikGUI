#include "include/menu.h"
#include "include/common.h"
#include "include/drawing.h"
#include "include/string.h"
#include "include/heap.h"
#include "include/windows.h"

void DrawUI(void){
    ClearFullScreen();

    //create main system window
    WindowContext* context;
    if(GetSystemContext()->window!=0){
        context = CreateWindowContext(NULL, 0, 0, 1600, 960, "Desktop", GREY3, GREY1, WHITE, NULL, NULL, NULL, NULL);
        DrawWindow(context);
        GetSystemContext()->mainWindow = context;

    }
    else{
        context = CreateWindowContext(NULL, 0, 0, 1600, 960, "BSOD", GREY3, GREY1, WHITE, NULL, NULL, NULL, NULL);
        DrawWindow(context); //BSOD
        GetSystemContext()->mainWindow = context;
    }
}

void SwichWindow(void){
    if(GetSystemContext()->mainWindow->childrenCount<=1)
        return;

    UnMarkWindow(GetSystemContext()->currentWindow, 1);

    for(int32_t i = GetSystemContext()->currentWindowIndex==0 ? MAX_CHILDREN-1 : GetSystemContext()->currentWindowIndex ;i>=0;i--){

        if(GetSystemContext()->mainWindow->children[i] != NULL){
            if(GetSystemContext()->mainWindow->children[i] != GetSystemContext()->currentWindow){
                GetSystemContext()->currentWindow = GetSystemContext()->mainWindow->children[i];
                GetSystemContext()->currentWindowIndex = i;
                MarkWindow(GetSystemContext()->currentWindow, 1);
                break;
            }
        }

    }
}