#include "DxLib\DxLib.h"
#include "utils.hpp"
#include "title.cpp"

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
	"Duplicate"
};

int fontSize = 	18;

int DrawOperations()
{
	static int scrl = 0;

	static const int l = WINDOW_WIDTH / 2;
	static const int r = WINDOW_WIDTH - WINDOW_WIDTH / 5;
	static const int border = 2;

	static const int box_height = 40;


	// Global
	static int d_scrl;
	static int mouseX, mouseY;
	static int mouseClick = 0;
	d_scrl = GetMouseWheelRotVol();
	GetMousePoint(&mouseX, &mouseY);
	if (GetMouseInput())
		mouseClick++;
	else
		mouseClick = 0;

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();FILE* out = 0; freopen_s( &out, "CON", "w", stdout );
	printf("Program has started.\n");

	ChangeWindowMode(true);
	SetGraphMode(900, 600, 16);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定
	
	GetMouseWheelRotVol();

	int selectedOperation;

	if(title(WINDOW_WIDTH, WINDOW_HEIGHT) != 0)
		exit(0);

	SetFontSize(fontSize);

	int op;

	while (ProcessMessage() == 0)
	{	
		ClearDrawScreen();

		op = DrawOperations();
		if(op > 0)
			printf("%s\n", operationStrings[op]);
		else if(op < 0)
			printf("%d\n", ~op);

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}
