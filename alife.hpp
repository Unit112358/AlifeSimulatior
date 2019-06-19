#pragma once
#include <vector>
#include <map>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include "utils.hpp"
#include "DxLib\Dxlib.h"
#include <iostream>
#include <fstream>
#include <cmath>

// utilに移す
typedef unsigned int uint;
typedef long long int int64;
typedef int int32;
typedef short int16;
typedef char int8;
typedef unsigned char byte;

using namespace std;
// using byte = unsigned char;

typedef union _flags
{
	int64 i64;
	struct
	{
		bool zero : 1;
		bool sign : 1;
		unsigned : 0;
	} f;
} flags;

// CPU構造体の定義
typedef struct _cpu
{
    int64 rax;
    int64 rbx;
    int64 rcx;
    int64 rdx;
    int64 rsi;
    int64 rdi;

    int64 rbp;
    int64 rsp;

	int64 r9;
	int64 r10;
	int64 r11;

    byte* rip;

    flags flags;

    int64 stack[10];
}CPU;

// レジスタ参照のマクロ
#define RESISTER(cpu, resister) (((int64*)cpu)+resister)
typedef enum _resister
{
    RAX = 0,
    RBX,
    RCX,
    RDX,
    RSI,
    RDI,
    RBP,
    RSP,
	R9,
	R10,
	R11,
    RIP,
    FLAGS
} resister;

// CPU構造体のコンストラクタ
CPU* new_cpu();

// バイトコード
typedef enum _instruction
{
    EXIT = 0,
    MOV_RR,
    MOV_RI,
    ADD_RR,
    ADD_RI,
    SUB,
    MUL,
    DIV,
    AND_RR,
    OR,
    XOR,
    INC,
    DEC,
	CMP_RR,
    LOOP,
    JMP,
    ZJ,
    NZJ,
    POP,
    PUSH,
    SYSCALL,
	ADDFRC_II,
	ADDFRC_R,
	GETNEAR,
	GETNUM_I,
	GETNUM_R,
	GETDIST_R,
	GETVEC_R,
	BITE
} instruction;

constexpr double attenuation_rate = 0.995;
const int tail_length = 10;

class Alife
{
private:
	double x, y;
	double s_v_x, s_v_y;
	double v_x, v_y;
	int energy = 10;
	int size = 5;
	int color;
	double tail_x[tail_length];
	double tail_y[tail_length];
	int tail_index = 0;
	int id;

public:
	Alife(double x, double y) :x(x), y(y), energy(10), color(0), s_v_x(0), s_v_y(0), v_x(0), v_y(0), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y }
	{
		//if(!num) alife_list = new vector<Alife*>{this};
		cpu = new_cpu();
		id = num++;
		alife_list[id] = this;
	}
	Alife(double x, double y, double velocity_x, double velocity_y) :x(x), y(y), energy(10), color(0), s_v_x(velocity_x), s_v_y(velocity_y), v_x(0), v_y(0), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y }
	{
		//if(!num) alife_list = new vector<Alife*>{this};
		cpu = new_cpu();
		id = num++;
		alife_list[id] = this;
	}
	//Alife(double x, double y, double color, double velocity_x, double velocity_y) :x(x), y(y), energy(10), color(0), velocity_x(0), velocity_y(0), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {};
	//Alife(double x, double y, int energy, double color, double velocity_x, double velocity_y) :x(x), y(y), energy(energy), color(color), velocity_x(velocity_x), velocity_y(velocity_y), tail_x{ x,x,x,x,x,x,x,x,x,x }, tail_y{ y,y,y,y,y,y,y,y,y,y } {}
	~Alife() {free(mem);free(cpu);};
	bool update();
	void move();
	void draw();
	void setColor(int color);
	void addForce(double x, double y);
	double getVelocityX();
	double getVelocityY();
	double getX() const {return x;}
	double getY() const {return y;}
	static void setFps(int a);
	static int fps; 		// frame per second
	static double spf; 		// second per frame
	static int num;
	int getId() {return id;}
	static map<int, Alife *> alife_list;


	// CPU関連
	CPU *cpu;
	byte *mem;

	void setMem(byte*, uint size);

	void fetch(); 			// バイトコードをメモリから一つとる関数
	void decode(); 			// バイトコードから命令にデコードする関数
	void execute();			// 命令を実行する関数
	void act();				// 上３つ分の関数

	// 命令群
	int mov_rr();	// レジスタにレジスタから値をコピーする
	int mov_ri();	// レジスタに即値を代入する
	int add_rr();
	int add_ri();
	int and_rr();
	int inc();
	int dec();
	int cmp_rr();
	int loop();
	int jmp();
	int zj();
	int nzj();

	int syscall();

	int addfrc_ii();
	int addfrc_r();
	int getnear();
	int getnum_i();
	int getnum_r();
	int getdist_r();
	int getvec_r();
	int bite();
};

int Alife::fps = 60;
double Alife::spf = 1./60;
int Alife::num = 0;
map<int, Alife*> Alife::alife_list;

#include "alife.cpp"