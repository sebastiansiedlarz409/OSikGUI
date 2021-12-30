#include "../../system/include/api.h"

SystemAPI* api;

uint8_t p = 0;
uint8_t win = 0;
char marks[] = {0,0,0,0,0,0,0,0,0};

void DrawMark(WindowContext* context);
void DrawField(WindowContext* context);

void Reset(void){
    api->MemsetBuffer(marks, 0, 9);
}

void CheckWin(WindowContext* context){
    uint16_t sx = context->position.sx;
    uint16_t sy = context->position.sy+25+1;
    uint16_t ex = context->position.ex;
    uint16_t ey = context->position.ey;

    if(marks[0]==marks[1] && marks[1]==marks[2] && marks[2] != 0){
        api->DrawWLine(sx+2, sy+105, ex-2, sy+105, 20, MAGENTA);
        win = 1;
    }
    if(marks[3]==marks[4] && marks[4]==marks[5] && marks[5] != 0){
        api->DrawWLine(sx+2, sy+335, ex-2, sy+335, 20, MAGENTA);
        win = 1;
    }
    if(marks[6]==marks[7] && marks[7]==marks[8] && marks[8] != 0){
        api->DrawWLine(sx+2, sy+565, ex-2, sy+565, 20, MAGENTA);
        win = 1;
    }

    if(marks[0]==marks[3] && marks[3]==marks[6] && marks[6] != 0){
        api->DrawWLine(sx+85, sy+2, sx+85, ey-2, 20, MAGENTA);
        win = 1;
    }
    if(marks[1]==marks[4] && marks[4]==marks[7] && marks[7] != 0){
        api->DrawWLine(sx+275, sy+2, sx+275, ey-2, 20, MAGENTA);
        win = 1;
    }
    if(marks[2]==marks[5] && marks[5]==marks[8] && marks[8] != 0){
        api->DrawWLine(sx+465, sy+2, sx+465, ey-2, 20, MAGENTA);
        win = 1;
    }

    if(marks[0]==marks[4] && marks[4]==marks[8] && marks[8] != 0){
        api->DrawWLine(sx+12, sy+25, ex-12, ey-25, 20, MAGENTA); 
        win = 1;
    }
    if(marks[6]==marks[4] && marks[4]==marks[2] && marks[2] != 0){
        api->DrawWLine(sx+12, ey-25, ex-12, sy+25, 20, MAGENTA); 
        win = 1;
    }
}

void DrawMark(WindowContext* context){
    uint16_t sx = context->position.sx;
    uint16_t sy = context->position.sy+25;

    if(marks[0]=='X'){
        uint16_t ssx = 20;
        uint16_t ssy = 40;
        uint16_t eex = 150;
        uint16_t eey = 170;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[1]=='X'){
        uint16_t ssx = 210;
        uint16_t ssy = 40;
        uint16_t eex = 340;
        uint16_t eey = 170;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[2]=='X'){
        uint16_t ssx = 400;
        uint16_t ssy = 40;
        uint16_t eex = 530;
        uint16_t eey = 170;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[3]=='X'){
        uint16_t ssx = 20;
        uint16_t ssy = 270;
        uint16_t eex = 150;
        uint16_t eey = 400;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[4]=='X'){
        uint16_t ssx = 210;
        uint16_t ssy = 270;
        uint16_t eex = 340;
        uint16_t eey = 400;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[5]=='X'){
        uint16_t ssx = 400;
        uint16_t ssy = 270;
        uint16_t eex = 530;
        uint16_t eey = 400;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[6]=='X'){
        uint16_t ssx = 20;
        uint16_t ssy = 500;
        uint16_t eex = 150;
        uint16_t eey = 630;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[7]=='X'){
        uint16_t ssx = 210;
        uint16_t ssy = 500;
        uint16_t eex = 340;
        uint16_t eey = 630;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    if(marks[8]=='X'){
        uint16_t ssx = 400;
        uint16_t ssy = 500;
        uint16_t eex = 530;
        uint16_t eey = 630;
        api->DrawWLine(sx+ssx,sy+ssy,sx+eex,sy+eey,20,RED);

        api->DrawWLine(sx+ssx,sy+eey,sx+eex,sy+ssy,20,RED);
    }
    //----------
    if(marks[0]=='O'){
        uint16_t ssx = 85;
        uint16_t ssy = 105;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[1]=='O'){
        uint16_t ssx = 275;
        uint16_t ssy = 105;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[2]=='O'){
        uint16_t ssx = 465;
        uint16_t ssy = 105;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[3]=='O'){
        uint16_t ssx = 85;
        uint16_t ssy = 335;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[4]=='O'){
        uint16_t ssx = 275;
        uint16_t ssy = 335;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[5]=='O'){
        uint16_t ssx = 465;
        uint16_t ssy = 335;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[6]=='O'){
        uint16_t ssx = 85;
        uint16_t ssy = 565;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[7]=='O'){
        uint16_t ssx = 275;
        uint16_t ssy = 565;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    if(marks[8]=='O'){
        uint16_t ssx = 465;
        uint16_t ssy = 565;

        api->DrawWCircle(sx+ssx,sy+ssy, 50, 70, DARKGREEN, GREYE);
    }
    
}

void tttWindowInputHandle(WindowContext* context){
    uint8_t value = api->GetSystemContext()->PopInSteam();
    
    if(value == '7'){
        //1
        if(marks[0] != 0){
            return;
        }
        if(p==0){
            marks[0] = 'O';
            p = 1;
        }
        else{
            marks[0] = 'X';
            p = 0;
        }
    }
    else if(value == '8'){
        //2
        if(marks[1] != 0){
            return;
        }
        if(p==0){
            marks[1] = 'O';
            p = 1;
        }
        else{
            marks[1] = 'X';
            p = 0;
        }
        
    }
    else if(value == '9'){
        //3
        if(marks[2] != 0){
            return;
        }
        if(p==0){
            marks[2] = 'O';
            p = 1;
        }
        else{
            marks[2] = 'X';
            p = 0;
        }
        
    }
    else if(value == '4'){
        //4
        if(marks[3] != 0){
            return;
        }
        if(p==0){
            marks[3] = 'O';
            p = 1;
        }
        else{
            marks[3] = 'X';
            p = 0;
        }
        
    }
    else if(value == '5'){
        //5
        if(marks[4] != 0){
            return;
        }
        if(p==0){
            marks[4] = 'O';
            p = 1;
        }
        else{
            marks[4] = 'X';
            p = 0;
        }
        
    }
    else if(value == '6'){
        //6
        if(marks[5] != 0){
            return;
        }
        if(p==0){
            marks[5] = 'O';
            p = 1;
        }
        else{
            marks[5] = 'X';
            p = 0;
        }
        
    }
    else if(value == '1'){
        //7
        if(marks[6] != 0){
            return;
        }
        if(p==0){
            marks[6] = 'O';
            p = 1;
        }
        else{
            marks[6] = 'X';
            p = 0;
        }
        
    }
    else if(value == '2'){
        //8
        if(marks[7] != 0){
            return;
        }
        if(p==0){
            marks[7] = 'O';
            p = 1;
        }
        else{
            marks[7] = 'X';
            p = 0;
        }
        
    }
    else if(value == '3'){
        //9
        if(marks[8] != 0){
            return;
        }
        if(p==0){
            marks[8] = 'O';
            p = 1;
        }
        else{
            marks[8] = 'X';
            p = 0;
        }
        
    }
    else{
        return;
    }

    DrawMark(context);
    CheckWin(context);

    if(win == 1){
        api->RefreshPartOfScreen(context->position.sx, context->position.sy, context->position.ex, context->position.ey);
        api->WaitSeconds(2);
        Reset();
        DrawMark(context);
        api->DrawRectangle(context->position.sx+2, context->position.sy+25, context->position.ex-2, context->position.ey-2, 
                        context->theme.background, context->theme.background);
        DrawField(context);
        win = 0;
    }
    
    api->RefreshPartOfScreen(context->position.sx, context->position.sy, context->position.ex, context->position.ey);
}

void DrawField(WindowContext* context){
    //550 w
    //670 h

    uint16_t sx = context->position.sx;
    uint16_t ex = context->position.ex;
    uint16_t sy = context->position.sy+25; //skip titlebar
    uint16_t ey = context->position.ey;

    //horizontal
    api->DrawWLine(sx, sy+220, ex-1, sy+220, 20, BRIGHTBLUE);
    api->DrawWLine(sx, sy+450, ex-1, sy+450, 20, BRIGHTBLUE);

    //vertical
    api->DrawWLine(sx+180, sy, sx+180, ey-1, 20, BRIGHTBLUE);
    api->DrawWLine(sx+370, sy, sx+370, ey-1, 20, BRIGHTBLUE);
}

void APP_Start(){
    api = (SystemAPI*)0x800000;

    api->FlushInStream();

    WindowContext* tttWindowContext = api->CreateWindowContext(
        api->GetSystemContext()->mainWindow,
        450, 230, 1000, 925, "Tic Tac Toe", DODGERBLUE, GREYE, BLACK, tttWindowInputHandle
    );
    api->DrawWindow(tttWindowContext);

    DrawField(tttWindowContext);

    api->RefreshScreen();
}