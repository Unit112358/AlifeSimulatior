#include "alife.h"
#include "DxLib.h"
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
	x += velocity_x;
	y += velocity_y;
}

void Alife::addForce(double accelaration_x, double accelaration_y)
{
	velocity_x += accelaration_x;
	velocity_y += accelaration_y;
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

double Alife::getVelocityX() { return velocity_x; }

double Alife::getVelocityY() { return velocity_y; }

double Alife::getX() { return x; }

double Alife::getY() { return y; }