#include "alife.h"
#include "DxLib\Dxlib.h"
#include "iostream"

void Alife::update()
{
	/*
	velocity_x *= attenuation_rate;
	velocity_y *= attenuation_rate;
	*/
	move();
	draw();
}

void Alife::move()
{
	x += getVelocityX();
	y += getVelocityY();
}

void Alife::addForce(double accelaration_x, double accelaration_y)
{
	v_x += accelaration_x;
	v_y += accelaration_y;
}

void Alife::setColor(int color)
{
	this->color = color;
}

void Alife::draw()
{
	(++tail_index) %= tail_length;
	tail_x[tail_index] = x;
	tail_y[tail_index] = y;

	for (int i = 0, index = tail_index; i < tail_length; i++, index = (index - 1 + tail_length) % tail_length)
	{
		DrawCircle((int)tail_x[index], (int)tail_y[index], size - i, color, 1);
	}
}

inline double Alife::getVelocityX() { return s_v_x + v_x * spf; }

inline double Alife::getVelocityY() { return s_v_y + v_y * spf; }

void Alife::setFps(int a)
{
	fps = a;
	spf = 1./a;
}