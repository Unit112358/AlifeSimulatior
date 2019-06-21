#include "DxLib\DxLib.h"
#include "utils.hpp"
#include "alife.hpp"
#include <vector>
#include <map>
#include <cmath>

int fontSize = 18;

int d_scrl;
int mouseX, mouseY;
int mouseClick = 0;

enum
{
	OP_IMM = 0,
	OP_RAX,
	OP_RBX,
	OP_RCX,
	OP_RDX,
	OP_EXIT,
	OP_NOP,
	OP_MOV,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_INC,
	OP_DEC,
	OP_CMP,
	OP_LOOP,
	OP_JMP,
	OP_ZJ,
	OP_NZJ,
	OP_SJ,
	OP_NSJ,
	OP_POP,
	OP_PUSH,
	OP_RET,
	OP_ADDFRC,
	OP_GETNEAR,
	OP_GETNUM,
	OP_GETDIST,
	OP_GETVEC,
	OP_GETCLR,
	OP_BITE,
	OP_DIVISION,
    OP_GENERATE,	
	N_OP
};

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
	"Duplicate",
    "Generate"
};

int edit();

int drawBattleField()
{
    static int forcusedId = -1;

    DrawBox(0, 0, 180, 600, GetColor(255, 0, 0), 0);
    DrawBox(720, 0, 900, 600, GetColor(0, 0, 255), 0);
    
    if(mouseClick == 1)
    {
        if(0 <= mouseX && mouseX <= 180 || 720 <= mouseX && mouseX <= WINDOW_WIDTH)
        {
            bool update = false;
            for(auto ite : Alife::alife_list)
            {
                int x = ite.second->getX() - mouseX;
                int y = ite.second->getY() - mouseY;
                int d = ite.second->getSize();
                if(x * x + y * y <= 4 * d * d)
                {
                    forcusedId = ite.second->getId();
                    update = true;
                }
            }
            if(!update && 0 <= mouseY && mouseY <= WINDOW_HEIGHT)
            {
                Alife *tmp = new Alife(mouseX, mouseY);
                forcusedId = tmp->getId();
                if(mouseX <= 180)
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

    static std::map<int, std::vector<int>> mem_list;


    if(prevId != forcusedId)
    {
        prevId = forcusedId;
        forcusedMem = -1;
    }

    if(forcusedId != -1)
    {
        if(mem_list.count(forcusedId) == 0)mem_list[forcusedId] = std::vector<int>({OP_NOP});

        //DrawBox(181, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, GetColor(255,255,0), 1);

        if(l <= mouseX && mouseX <= r && 0 <= mouseY && mouseY <= WINDOW_HEIGHT)
            scrl -= 2 * d_scrl;
        if(scrl < 0)scrl = 0;
        if(scrl > std::max(0, (int)(mem_list[forcusedId].size()) * box_height - WINDOW_HEIGHT)) scrl = std::max(0, (int)(mem_list[forcusedId].size()) * box_height - WINDOW_HEIGHT);

        if(mouseClick == 1 && l + box_border <= mouseX && mouseX <= l + box_width - box_border && WINDOW_HEIGHT - box_height + box_border <= mouseY && mouseY <= WINDOW_HEIGHT - box_border)
        {
            if(mem_list[forcusedId].size())
            {
                mem_list[forcusedId].pop_back();
                mem_lim[Alife::alife_list[forcusedId]->getTeam()]++;
                if(forcusedMem >= mem_list[forcusedId].size())forcusedMem = -1;
            }
        }
        else if(mouseClick == 1 && l + box_width + box_border <= mouseX && mouseX <= r - box_border && WINDOW_HEIGHT - box_height + box_border <= mouseY && mouseY <= WINDOW_HEIGHT - box_border)
        {
            if(mem_lim[Alife::alife_list[forcusedId]->getTeam()] != 0)
            {
                mem_list[forcusedId].push_back(NOP);
                mem_lim[Alife::alife_list[forcusedId]->getTeam()]--;
            }
        }
        else if(mouseClick == 1 && l + border <= mouseX && mouseX <= r - border && border <= mouseY && mouseY <= WINDOW_HEIGHT)
        {
            forcusedMem = (mouseY + scrl) / mem_height;
            if(forcusedMem >= mem_list[forcusedId].size())forcusedMem = -1;
        }

        //draw mem
        for(int i = 0; i < (int)(mem_list[forcusedId].size()); i++)
        {
            int crr = mem_list[forcusedId][i];
            TCHAR tmpstr[20];
            if(crr < 0)
                sprintf(tmpstr, "%d", ~crr);
            TCHAR* str;
            if(crr < 0)
                str = tmpstr;
            else
                str = operationStrings[crr];
            
            int width = GetDrawStringWidth(str, strlen(str));
            DrawBox(l + border, -scrl + i * mem_height + border, r - border, -scrl + (i + 1) * mem_height - border, GetColor(255,255,255),0);
            if(forcusedMem == i)DrawBox(l + border, -scrl + i * mem_height + border, r - border, -scrl + (i + 1) * mem_height - border, GetColor(0,255,0),0);
            DrawString((l + r - width) / 2, -scrl + i * mem_height + (mem_height - fontSize) / 2, str, GetColor(255,255,255), GetColor(255,255,255));
        }
    }

    if(operation != 0 && forcusedMem != -1)mem_list[forcusedId][forcusedMem] = operation;

    //draw - +
    DrawBox(l + box_border, WINDOW_HEIGHT - box_height + box_border, l + box_width - box_border, WINDOW_HEIGHT - box_border, GetColor(0,0,255), 1);
    DrawBox(l + box_width + box_border, WINDOW_HEIGHT - box_height + box_border, r - box_border, WINDOW_HEIGHT - box_border, GetColor(255,0,0), 1);
    // DrawString(l + box_width / 2, WINDOW_HEIGHT - box_height / 2, "+", 0xffffff);

    if(CheckHitKey(KEY_INPUT_RETURN))return true;
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
        d_scrl = GetMouseWheelRotVol();
        GetMousePoint(&mouseX, &mouseY);
        if(GetMouseInput() && MOUSE_INPUT_LEFT)
            mouseClick++;
        else
            mouseClick = 0;
        
        int forcusedId = drawBattleField();
        
        int operation/* = drawOperation()*/ = 0;

        bool isFinish = drawMem(forcusedId, operation);
    }
}

int drawOperations()
{
	static int scrl = 0;

	static const int l = WINDOW_WIDTH / 2;
	static const int r = WINDOW_WIDTH - WINDOW_WIDTH / 5;
	static const int border = 2;

	static const int box_height = 40;


	// Global
	// static int d_scrl;
	// static int mouseX, mouseY;
	// static int mouseClick = 0;
	// d_scrl = GetMouseWheelRotVol();
	// GetMousePoint(&mouseX, &mouseY);
	// if (GetMouseInput())
	// 	mouseClick++;
	// else
	// 	mouseClick = 0;

	if(mouseX > l && mouseX < r)//?&& mouseY > 0 && mouseY < WINDOW_HEIGHT)
		scrl -= 2 * d_scrl;
	if(scrl < 0) scrl = 0;
	if(scrl > N_OP * box_height - WINDOW_HEIGHT) scrl = N_OP * box_height - WINDOW_HEIGHT;

	DrawBox(l, 0, r, WINDOW_HEIGHT, 0x42A0A0, 1);

	for(int i = 0; i < N_OP; i++)
	{
		int width = GetDrawStringWidth(operationStrings[i], strlen(operationStrings[i]));
		DrawBox(l + border, -scrl + border, r - border, -scrl + (i + 1) * box_height - border ,0xA042A0, 0);
		DrawString((l + r - width) / 2, -scrl + i * box_height + (box_height - fontSize) / 2, operationStrings[i], GetColor(0xff, 0, 0), 0xA0A042);
	}

	if(mouseX > l && mouseX < r)
	{
		if(mouseClick == 1)
		{
			int ret = (scrl + mouseY) / box_height;
			if(ret == 0)
			{
				//数値を読む関数を呼ぶ
				SetFontSize(64);
				ret = KeyInputNumber(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 64, 255, -128, 1);
				SetFontSize(fontSize);
				if(ret == 256) return 0;
				if(ret == -129) return 0;
				return ~(byte)ret;
			}
			return ret;
		}
	}

	return 0;
}
