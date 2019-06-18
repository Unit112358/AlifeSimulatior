#include "alife.hpp"

#define ALIFEDEBUG

#ifdef ALIFEDEBUG
const char* filename = "alife_log.txt";
std::ofstream ofs(filename);
#endif

CPU* new_cpu()
{
    CPU *p = (CPU*)malloc(sizeof(CPU));
    memset(p, 0, sizeof(CPU));

    return p;
}

void Alife::update()
{
	v_x *= attenuation_rate;
	v_y *= attenuation_rate;
	s_v_x *= attenuation_rate;
	s_v_y *= attenuation_rate;

	act();
	move();
	draw();
}

void Alife::move()
{
	x += getVelocityX();
	y += getVelocityY();

	//超えた分を引いてるだけだからあまりに飛びすぎるとバグる
	//かなり速度が速くなってもバグらなかったからとりあえずこのまま
	if(x < 0)
	{
		x *= -1;
		s_v_x *= -1;
		v_x *= -1;
	}
	if(x > WINDOW_WIDTH)
	{
		x = WINDOW_WIDTH - (x - WINDOW_WIDTH);
		s_v_x *= -1;
		v_x *= -1;
	}
	if(y < 0)
	{
		y *= -1;
		s_v_y *= -1;
		v_y *= -1;
	}
	if(y > WINDOW_HEIGHT)
	{
		y = WINDOW_HEIGHT - (y - WINDOW_HEIGHT);
		s_v_y *= -1;
		v_y *= -1;
	}
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
		DrawCircle(tail_x[index], tail_y[index], size - i, color, 1);
	}
}

inline int Alife::getVelocityX() { return s_v_x + v_x * spf; }

inline int Alife::getVelocityY() { return s_v_y + v_y * spf; }

void Alife::setFps(int a)
{
	fps = a;
	spf = 1./a;
}

void Alife::setMem(byte* mem, uint size)
{
	byte* tmp = (byte*)malloc(size);
	memcpy(tmp, mem, size);
	this->mem = tmp;
	cpu->rip = tmp;
}

void Alife::act()
{
	#ifdef ALIFEDEBUG
	ofs << (int)(*cpu->rip) << std::endl;
	#endif

	int next = 1;
	switch(*cpu->rip)
	{
		case EXIT:
		// 終了処理
			break;
		case MOV_RR:
			next = mov_rr();
			break;
		case MOV_RI:
			next = mov_ri();
			break;
		case ADD_RR:
			next = add_rr();
			break;
		case ADD_RI:
			next = add_ri();
			break;
		case AND_RR:
			next = and_rr();
			break;
		case INC:
			next = inc();
			break;
		case DEC:
			next = dec();
			break;
		case LOOP:
			next = loop();
			break;
		case JMP:
			next = jmp();
			break;
		case ADDFRC_II:
			next = addfrc_ii();
			break;
		case ADDFRC_R:
			next = addfrc_r();
			break;
		case GETNEAR:
			next = getnear();
			break;
		case GETNUM_I:
			next = getnum_i();
			break;
		case GETVEC_R:
			next = getvec_r();
			break;
		default:
			next = 1;
			break; 
	}
	#ifdef ALIFEDEBUG
	ofs << (int)(*cpu->rip) << std::endl;
	#endif

	cpu->rip += next;
}

int Alife::mov_rr()
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *(byte*)RESISTER(cpu, dst) = *RESISTER(cpu, src);

    return 3;
}

int Alife::mov_ri()
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *(byte*)RESISTER(cpu, dst) = src;

    return 3;
}

int Alife::add_rr()
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *RESISTER(cpu, dst) = *RESISTER(cpu, dst) + *RESISTER(cpu, src);

	if(*RESISTER(cpu, dst) == 0)
		cpu->flags.f.zero = 1;
	else
		cpu->flags.f.zero = 0;

	return 3;
}
int Alife::add_ri()
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *RESISTER(cpu, dst) = *RESISTER(cpu, dst) + src;

	if(*RESISTER(cpu, dst) == 0)
		cpu->flags.f.zero = 1;
	else
		cpu->flags.f.zero = 0;

    return 3;
}

int Alife::and_rr()
{
	byte dst, src;
	dst = cpu->rip[1];
	src = cpu->rip[2];

	*RESISTER(cpu, dst) = *RESISTER(cpu, dst) & *RESISTER(cpu, src);

	if(*RESISTER(cpu, dst) == 0)
		cpu->flags.f.zero = 1;
	else
		cpu->flags.f.zero = 0;

	return 3;
}

int Alife::inc()
{
    byte dst;
    dst = cpu->rip[1];

    *RESISTER(cpu, dst) += 1;

	if(*RESISTER(cpu, dst) == 0)
		cpu->flags.f.zero = 1;
	else
		cpu->flags.f.zero = 0;

    return 2;
}

int Alife::dec()
{
    byte dst;
    dst = cpu->rip[1];

    *RESISTER(cpu, dst) -= 1;

	if(*RESISTER(cpu, dst) == 0)
		cpu->flags.f.zero = 1;
	else
		cpu->flags.f.zero = 0;

    return 2;
}

int Alife::loop()
{
    byte dst;

    dst = cpu->rip[1];

    if(cpu->rcx)
    {
        cpu->rcx--;
        return (signed char)dst;
    }
    return 2;
}

int Alife::jmp()
{
    byte dst;
    dst = cpu->rip[1];

    return (signed char)dst;
}

int Alife::zj()
{
	byte dst;
	dst = cpu->rip[1];
	
	if(cpu->flags.f.zero)
		return (signed char)dst;
	return 2;
}
int Alife::nzj()
{
	byte dst;
	dst = cpu->rip[1];
	
	if(!cpu->flags.f.zero)
		return (signed char)dst;
	return 2;
}

int Alife::syscall()
{
    #ifndef _WIN64
    cpu->rax += 0x200000;
    #endif
    asm volatile
    (
        "syscall"
        // ".intel_syntax noprefix\n"
        : "=a"(cpu->rax)
        : "a"(cpu->rax),
          "b"(cpu->rax),
          "c"(cpu->rcx),
          "d"(cpu->rdx),
          "S"(cpu->rsi),
          "D"(cpu->rdi)
    );
}


inline void Alife::addForce(int accelaration_x, int accelaration_y)
{
	v_x += accelaration_x;
	v_y += accelaration_y;
}


int Alife::addfrc_ii()
{
	byte x, y;

	x = cpu->rip[1];
	y = cpu->rip[2];

	addForce(x, y);

	return 3;
}

int Alife::addfrc_r()
{
	int64 vec;

	vec = *RESISTER(cpu, cpu->rip[1]);

	#ifdef ALIFEDEBUG
	ofs << "vec: " << vec << std::endl;
	ofs << "x: " << vec_x(vec) << " y: " << vec_y(vec) << std::endl;
	#endif

	addForce(vec_x(vec), vec_y(vec));

	return 2;
}

int Alife::getnear()
{
	int id = -1;
	uint min_dist = (uint)-1;
	for(Alife* p : alife_list)
	{
		if(p->id == this->id) continue;
		uint dist = (uint)((x - p->x) * (x - p->x) + (y - p->y) * (y - p->y));
		if(min_dist > dist)
		{
			id = p->id;
			min_dist = dist;
		}
	}

	cpu->rax = id;
	return 1;
}

int Alife::getnum_i()
{
	int num = -1;
	int dist = cpu->rip[1];

	for(Alife* p : alife_list)
		if((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y) <= dist * dist)
			num++;
			
	cpu->rax = num;

	return 2;
}

int Alife::getvec_r()
{
	int id = *RESISTER(cpu, cpu->rip[1]);
	if(id < 0 || alife_list.size() <= id) id = this->id;
	int64 x = alife_list[id]->x - this->x;
	int y = alife_list[id]->y - this->y;

	cpu->rax = (x << 32) | y;

	return 2;
}