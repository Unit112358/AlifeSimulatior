#pragma once
#include <cstdlib>

constexpr double attenuation_rate = 0.9;

class Alife
{
private:
	double y, x;
	double s_v_x, s_v_y;
	double v_x, v_y;
	int energy;
	int size = 10;
	int color;
	int tail_length = 10;
	double tail_x[10];
	double tail_y[10];
	int tail_index = 0;

public:
	Alife(double x, double y) :x(x), y(y), energy(10), color(0), s_v_x(0), s_v_y(0), v_x(0), v_y(0), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {}
	Alife(double x, double y, double velocity_x, double velocity_y) :x(x), y(y), energy(10), color(0), s_v_x(velocity_x), s_v_y(velocity_y), v_x(0), v_y(0), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {}
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
	double getX() const {return x;}
	double getY() const {return y;}
	static void setFps(int a);
	static int fps;
	static double spf;
};

int Alife::fps = 60;
double Alife::spf = 1./60;

#include "alife.cpp"