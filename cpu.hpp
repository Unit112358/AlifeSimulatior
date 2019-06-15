
#pragma once

#include <stdlib.h>
#include <string.h>

typedef long long int int64;
typedef int int32;
typedef short int16;
typedef char int8;
typedef unsigned char byte;

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
    byte* rip;

    int64 flags;

    int64 stack[10];
}CPU;

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
    RIP,
    FLAGS
} resister;

CPU* new_cpu();

typedef enum _instruction
{
    EXIT = (byte)-1,
    MOV_RR = 0,
    MOV_RI,
    ADD_RR,
    ADD_RI,
    SUB,
    MUL,
    DIV,
    AND,
    OR,
    XOR,
    INC,
    DEC,
    LOOP,
    JMP,
    ZJ,
    NZJ,
    POP,
    PUSH,
    SYSCALL
} instruction;

int mov_rr(CPU* cpu);
int mov_ri(CPU* cpu);
int add_rr(CPU* cpu);
int add_ri(CPU* cpu);
int inc(CPU* cpu);
int dec(CPU* cpu);
int loop(CPU* cpu);
int jmp(CPU* cpu);

int syscall(CPU* cpu);
int syscall(CPU* cpu);


#include "cpu.cpp"