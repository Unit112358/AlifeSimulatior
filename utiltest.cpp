
#include <stdio.h>
#include <stdlib.h>
// #include <iostream>

typedef int int32;
typedef long long int int64;
#define LOWINT64(a) (int32)((a)&0xffffffff)
#define HIINT64(a) (int32)(((a)&0xffffffff00000000)>>32)

typedef unsigned char byte;

typedef union _int64toByteArray
{
    int64 i64;
    byte byteArray[8];
}i64toByteArray;

#define COMMA ,
#define CONCAT3(a,b,c) a##b##c
// #define i2b(a) CONCAT3(((a)&0xff),COMMA,CONCAT3(((a)&0xff00),COMMA,CONCAT3()))

using namespace std;

byte mem[] = {0x12, 0x34, 0x56, 0x78, 0xaa, 0xbb, 0xcc, 0xdd};

int main()
{
    int64 a = 0xaabbccdd11223344;
    i64toByteArray b;
    b.i64 = a;
    byte mem2[] = {}

    printf("0x%x\n", HIINT64(a));
    printf("0x%x\n", LOWINT64(a));

    printf("%d\n", *(int*)(mem+0));
    // 0x78563412
    printf("%d\n", (int)0x78563412);
    printf("%d\n", *(int*)(mem+4));
    printf("%d\n", (int)0xddccbbaa);

    for(int i = 0; i< 8; i++)
    {
        printf("0x%x\n", b.byteArray[i]);
    }
    printf("0x%llx\n", *(int64*)(b.byteArray));
    system("pause");

    return 0;
}