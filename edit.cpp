#include "DxLib\DxLib.h"
#include "utils.hpp"
#include "alife.hpp"
#include <vector>
#include <map>
#include <cmath>

int fontSize = 20;

/*
enum
{
	IMM = 0,
	RAX,
	RBX,
	RCX,
	RDX,
	EXIT,
	NOP,
	MOV,
	ADD,
	SUB,
	MUL,
	DIV,
	AND,
	OR,
	XOR,
	INC,
	DEC,
	CMP,
	LOOP,
	JMP,
	ZJ,
	NZJ,
	SJ,
	NSJ,
	POP,
	PUSH,
	RET,
	ADDFRC,
	GETNEAR,
	GETNUM,
	GETDIST,
	GETVEC,
	GETCLR,
	BITE,
	DIVISION,	
	N_OP
};
*/

TCHAR operationStrings[][20] = 
{
	"Immidiate",
	"RAX",
	"RBX",
	"RCX",
	"RDX",
	"Exit",
	"No-opration",
	"Move",
	"Add",
	"Substract",
	"Multiplicate",
	"Divite",
	"And",
	"Or",
	"Xor",
	"Increment",
	"Decrement",
	"Compare",
	"Loop",
	"Jamp",
	"Zero jamp",
	"Non-zero jamp",
	"Sign jamp",
	"Non-sign jamp",
	"Pop",
	"Push",
	"Return",
	"Add force",
	"Get near",
	"Get number",
	"Get distance",
	"Get vector",
	"Get color",
	"Bite",
	"Duplicate"
};

int edit();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);       // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定

    edit();

    WaitKey();
    DxLib_End();
}

int drawBattleField()
{
    int Mouse_X, Mouse_Y;
    int input;
    static int forcusedId = -1;

    DrawBox(0, 0, 180, 600, GetColor(255, 0, 0), 0);
    DrawBox(720, 0, 900, 600, GetColor(0, 0, 255), 0);

    GetMousePoint(&Mouse_X, &Mouse_Y);
    input = GetMouseInput();
    
    if(input & MOUSE_INPUT_LEFT)
    {
        if(0 <= Mouse_X && Mouse_X <= 180 || 720 <= Mouse_X && Mouse_X <= WINDOW_WIDTH)
        {
            bool update = false;
            for(auto ite : Alife::alife_list)
            {
                int x = ite.second->getX() - Mouse_X;
                int y = ite.second->getY() - Mouse_Y;
                int d = ite.second->getSize();
                if(x * x + y * y <= 4 * d * d)
                {
                    forcusedId = ite.second->getId();
                    update = true;
                }
            }
            if(!update && 0 <= Mouse_Y && Mouse_Y <= WINDOW_HEIGHT)
            {
                Alife *tmp = new Alife(Mouse_X, Mouse_Y);
                forcusedId = tmp->getId();
                if(Mouse_X <= 180)
                {
                    tmp->setTeam(0);
                    tmp->setColor(GetColor(255, 0, 0));
                }
                else
                {
                    tmp->setTeam(1);
                    tmp->setColor(GetColor(0, 0, 255));
                }
            }
        }
    }

    if(CheckHitKey(KEY_INPUT_D))
    {
        if(forcusedId != -1 && Alife::alife_list.count(forcusedId) != 0)
        {
            Alife* p = Alife::alife_list[forcusedId];
            Alife::alife_list.erase(forcusedId);
            delete p;
            forcusedId = -1;
        }
    }

    for(auto ite : Alife::alife_list)
    {
        Alife* p = ite.second;
        p->draw();
        if(p->getId() == forcusedId)
            DrawCircle(p->getX(), p->getY(), p->getSize() + 5, GetColor(255, 255, 255), 0);
    }

    return forcusedId;
}

bool drawMem(int forcusedId, int operation)
{
    static int scrl = 0;
    
    static int l = WINDOW_WIDTH / 5;
    static int r = WINDOW_WIDTH / 2;
    static int border = 2;

    static const int box_width = 135;
    static const int box_height = 40;
    static const int box_border = 5;

    static const int mem_height = 40;

    static int forcusedMem = -1;
    static int mem_lim[2] = {80, 80};

    static int prevId = -1;

    static std::map<int, std::vector<byte>> mem_list;

    int dscrl = GetMouseWheelRotVol();
    int input = GetMouseInput();
    int mouse_X, mouse_Y;
    GetMousePoint(&mouse_X, &mouse_Y);

    if(prevId != forcusedId)
    {
        prevId = forcusedId;
        forcusedMem = -1;
    }

    if(forcusedId != -1)
    {
        if(mem_list.count(forcusedId) == 0)mem_list[forcusedId] = std::vector<byte>({NOP});

        //DrawBox(181, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, GetColor(255,255,0), 1);

        scrl -= 2 * dscrl;
        if(scrl < 0)scrl = 0;
        if(scrl > std::max(0, (int)(mem_list[forcusedId].size()) * box_height - WINDOW_HEIGHT)) scrl = std::max(0, (int)(mem_list[forcusedId].size()) * box_height - WINDOW_HEIGHT);

        if(input & MOUSE_INPUT_LEFT && l + box_border <= mouse_X && mouse_X <= l + box_width - box_border && WINDOW_HEIGHT - box_height + box_border <= mouse_Y && mouse_Y <= WINDOW_HEIGHT - box_border)
        {
            if(mem_list[forcusedId].size())
            {
                mem_list[forcusedId].pop_back();
                mem_lim[Alife::alife_list[forcusedId]->getTeam()]++;
                if(forcusedMem >= mem_list[forcusedId].size())forcusedMem = -1;
            }
        }
        else if(input & MOUSE_INPUT_LEFT && l + box_width + box_border <= mouse_X && mouse_X <= r - box_border && WINDOW_HEIGHT - box_height + box_border <= mouse_Y && mouse_Y <= WINDOW_HEIGHT - box_border)
        {
            if(mem_lim[Alife::alife_list[forcusedId]->getTeam()] != 0)
            {
                mem_list[forcusedId].push_back(NOP);
                mem_lim[Alife::alife_list[forcusedId]->getTeam()]--;
            }
        }
        else if(input & MOUSE_INPUT_LEFT && l + border <= mouse_X && mouse_X <= r - border && border <= mouse_Y && mouse_Y <= WINDOW_HEIGHT)
        {
            forcusedMem = (mouse_Y - border) / mem_height;
            if(forcusedMem >= mem_list[forcusedId].size())forcusedMem = -1;
        }

        //draw mem
        for(int i = 0; i < (int)(mem_list[forcusedId].size()); i++)
        {
            byte crr = mem_list[forcusedId][i];
            int width = GetDrawStringWidth(operationStrings[crr], strlen(operationStrings[crr]));
            DrawBox(l + border, -scrl + i * mem_height + border, r - border, -scrl + (i + 1) * mem_height - border, GetColor(255,255,255),0);
            if(forcusedMem == i)DrawBox(l + border, -scrl + i * mem_height + border, r - border, -scrl + (i + 1) * mem_height - border, GetColor(0,255,0),0);
            DrawString((l + r - width) / 2, -scrl + i * mem_height + (mem_height - fontSize) / 2, operationStrings[crr], GetColor(255,255,255), GetColor(255,255,255));
        }
    }

    if(forcusedMem != -1)mem_list[forcusedId][forcusedMem] = operation;

    //draw - +
    DrawBox(l + box_border, WINDOW_HEIGHT - box_height + box_border, l + box_width - box_border, WINDOW_HEIGHT - box_border, GetColor(0,0,255), 1);
    DrawBox(l + box_width + box_border, WINDOW_HEIGHT - box_height + box_border, r - box_border, WINDOW_HEIGHT - box_border, GetColor(255,0,0), 1);
    DrawString(l + box_width / 2, WINDOW_HEIGHT - box_height / 2, "+", 0xffffff);

    return false;
}

int edit()
{
    /*
    int in_time = 100;
    for(int i = 1; i <= in_time; i++)
    {
        ClearDrawScreen();
        DrawBox(180 * i / in_time - 179, 0, 180 * i / in_time, WINDOW_HEIGHT, GetColor(255, 0, 0), 0);
        DrawBox(WINDOW_WIDTH - 180 * i / in_time, 0, WINDOW_WIDTH + 180 - 180 * i / in_time, WINDOW_HEIGHT, GetColor(0, 0, 255), 0);
        ScreenFlip();
    }
    */

    while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_Z) == 0)
    {
        int forcusedId = drawBattleField();
        
        int operation/* = drawOperation()*/ = 0;

        bool isFinish = drawMem(forcusedId, operation);
    }
}