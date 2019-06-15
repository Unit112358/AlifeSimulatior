#pragma once
#include <cstdlib>

constexpr double attenuation_rate = 0.9;

class Alife
{
private:
	double y, x;
	double velocity_x, velocity_y;
	int energy;
	int size = 10;
	int color;
	int tail_length = 10;
	double tail_x[10];
	double tail_y[10];
	int tail_index = 0;

public:
	Alife(double x, double y) :x(x), y(y), energy(10), color(0), velocity_x(0), velocity_y(0), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {}
	Alife(double x, double y, double velocity_x, double velocity_y) :x(x), y(y), energy(10), color(0), velocity_x(velocity_x), velocity_y(velocity_y), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {}
	//Alife(double x, double y, double color, double velocity_x, double velocity_y) :x(x), y(y), energy(10), color(0), velocity_x(0), velocity_y(0), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {};
	//Alife(double x, double y, int energy, double color, double velocity_x, double velocity_y) :x(x), y(y), energy(energy), color(color), velocity_x(velocity_x), velocity_y(velocity_y), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {}
	~Alife() {};
	void update();
	void move();
	void draw();
	void setColor(int color);
	void addForce(double x, double y);
	double getVelocityX();
	double getVelocityY();
	double getX();
	double getY();
};

#include "alife.cpp"