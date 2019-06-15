#include "DxLib\DxLib.h"
//#include "CPU.cpp"
#include "alife.h"
#include <math.h>
#include <iostream>

// �ｿｽv�ｿｽ�ｿｽ�ｿｽO�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ WinMain �ｿｽ�ｿｽ�ｿｽ�ｿｽn�ｿｽﾜゑｿｽﾜゑｿｽ
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetGraphMode(1280, 1024, 16);
	if (DxLib_Init() == -1)		// �ｿｽc�ｿｽw�ｿｽ�ｿｽ�ｿｽC�ｿｽu�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	{
		return -1;			// �ｿｽG�ｿｽ�ｿｽ�ｿｽ[�ｿｽ�ｿｽ�ｿｽN�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ迺ｼ�ｿｽ�ｿｽ�ｿｽﾉ終�ｿｽ�ｿｽ
	}

	/*
	DrawPixel(320, 240, GetColor(255, 255, 255));	// �ｿｽ_�ｿｽ�ｿｽﾅゑｿｽ
	DrawString(200, 100, "Hello World!", GetColor(0xFF, 0xA5, 0));	// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾅゑｿｽ
	DrawString(250, 100, "Hello UnIt", GetColor(0xff, 0xff, 0xff));
	DrawString(200, 150, "Hello Chocobo", GetColor(0xFF, 0xA5, 0));
	*/

	/*
	DrawPixel(0, 0, GetColor(255, 255, 255));	// �ｿｽ_�ｿｽ�ｿｽﾅゑｿｽ
	DrawPixel(1, 0, GetColor(255, 255, 255));	// �ｿｽ_�ｿｽ�ｿｽﾅゑｿｽ
	DrawPixel(2, 0, GetColor(255, 255, 255));	// �ｿｽ_�ｿｽ�ｿｽﾅゑｿｽ
	DrawPixel(3, 0, GetColor(255, 255, 255));	// �ｿｽ_�ｿｽ�ｿｽﾅゑｿｽ
	*/

	Alife sample1(500, 500, 10, 0), sample2(600, 600, -10, 0);
	sample1.setColor(GetColor(0, 0, 255));
	sample2.setColor(GetColor(255, 0, 0));

	while (CheckHitKeyAll() == 0)
	{	
		ClearDrawScreen();
	
		/*
		double velocity_x = sample1.getVelocityX(), velocity_y = sample1.getVelocityY();
		sample1.addForce(-velocity_y / 30.0, velocity_x / 30.0);
		sample1.update();
		*/

		double x1 = sample1.getX(), y1 = sample1.getY();
		double x2 = sample2.getX(), y2 = sample2.getY();

		double k = pow(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)), 2.0) / 10000;
		
		sample1.addForce((x2 - x1) / 60.0 / k, (y2 - y1) / 60.0 / k);
		sample2.addForce((x1 - x2) / 60.0 / k, (y1 - y2) / 60.0 / k);

		sample1.update();
		sample2.update();

		ScreenFlip();
	}

	WaitKey();				// �ｿｽL�ｿｽ[�ｿｽ�ｿｽ�ｿｽﾍ待ゑｿｽ

	DxLib_End();				// �ｿｽc�ｿｽw�ｿｽ�ｿｽ�ｿｽC�ｿｽu�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽg�ｿｽp�ｿｽﾌ終�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ

	return 0;				// �ｿｽ\�ｿｽt�ｿｽg�ｿｽﾌ終�ｿｽ�ｿｽ 
}
