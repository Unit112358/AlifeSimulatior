#include "cpu.hpp"

CPU* new_cpu()
{
    CPU *p = (CPU*)malloc(sizeof(CPU));
    memset(p, 0, sizeof(CPU));

    return p;
}

int mov_rr(CPU* cpu)
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *(byte*)RESISTER(cpu, dst) = *RESISTER(cpu, src);

    return 3;
}

int mov_ri(CPU* cpu)
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *(byte*)RESISTER(cpu, dst) = src;

    return 3;
}

int add_rr(CPU* cpu)
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *RESISTER(cpu, dst) = *RESISTER(cpu, dst) + *RESISTER(cpu, src);

    return 3;
}
int add_ri(CPU* cpu)
{
    byte dst, src;

    dst = cpu->rip[1];
    src = cpu->rip[2];

    *RESISTER(cpu, dst) = *RESISTER(cpu, dst) + src;

    return 3;
}

int inc(CPU* cpu)
{
    byte dst;
    dst = cpu->rip[1];

    *RESISTER(cpu, dst) += 1;

    return 2;
}

int dec(CPU* cpu)
{
    byte dst;
    dst = cpu->rip[1];

    *RESISTER(cpu, dst) -= 1;

    return 2;
}

int loop(CPU* cpu)
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

int jmp(CPU* cpu)
{
    byte dst;
    dst = cpu->rip[1];

    return (signed char)dst;
}

int syscall(CPU* cpu)
{
    #ifndef _WIN64
    cpu->rax += 0x200000;
    #endif
    asm volatile
    (
        "syscall"
        ".intel_syntax noprefix\n"
        : "=a"(cpu->rax)
        : "a"(cpu->rax),
          "b"(cpu->rax),
          "c"(cpu->rcx),
          "d"(cpu->rdx),
          "S"(cpu->rsi),
          "D"(cpu->rdi)
    );
}