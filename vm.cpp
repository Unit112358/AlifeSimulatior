
// 　　　　　　　　　　　　　　　　　 　 　 　 　 ＿＿＿　　　　　　　　　,/ヽ 
// 　　　　　　　　　　　　　 ,. -‐ ￣￣｀ ￣ ´ 　 　 　 ￣￣￣￣｀ヽ._,{ ､,i ! 
// 　　　　　　　　　　__.. -/ 　 　 　 ,..　　　　　　　　　　　 /　　　　　　　　｀ヽ､ 
// 　　　　　 , -‐ ,.´-─./　　 　 ／:. . .　　　　　 　 　 　 / ..__ ／　!　　 　 ｀ヽ ヽ　　　 　　∧,,∧ 
// 　　　 ／,.-‐´　　_r‐'　　　_,ノ: : : : : : : . . . . . . . . . . .（＿　 ｀丶､ヽ､ 　 ､__,ｽ ,） 　　　c(´=ω=｀)っ
// ~~￣/(三,. -‐ ´ /　 ,.-‐ ´￣￣￣￣￣￣￣￣￣￣￣￣｀丶　l￣￣￣￣￣￣￣￣￣￣￣￣￣￣ 
// ~￣i　lﾞ´ ￣￣ /　,/ ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣ し,j￣￣￣￣￣￣￣￣￣￣￣￣￣￣ 
// 　. l.　!　　　　 /　/ 
// 　. !　|　　　　(, ,,/ 
// 　　! ,j　　
// 　　ゝ､ﾉ


// 　　　　　　　　　　　　　　　　　　　_,,..．='~1 
// 　　　　　　　　　　 _,.､='＂~~,才＜／彡　 } 
// 　　　　　　　　 ,.=ﾞー- 　▼　　````.X彡-ﾅ 
// 　　　　　_,,.::=7;;;.〃　　　 人　 .〟二二キ二　　
// 　 _,.．='´~こ/;;;´,,..　　 -ｲ　.`'''´ 　 　 　Ｙ 
// .<　二二＝ｵ;;,,..-´　　　　　　　　　　　　 } 
// 　乂　.二=壬　 ／　　　　　　　　　　　　/ 
// 　　 ゝ､,,,,,..ｷ;／　　　　　　　　　,.．--．/ 
// 　　　　　　ゞi　　　　　　　　 ,／　　　　 ＼ 
// 　　　　　　　 ＼　　　　_,,,,,__.ﾚ 　　 　　 　 i 
// 　　　　　　　　　＼,.／　　　 ゝ_r_,.イﾞ　　　! 
// 　　　　　　　　　　 /　　　　　￤　　　　　　 ＼　　　　　,. ､ 
// 　　　　　　　　　　 {　　　 ゝJ┘　　　　　 　　 .>-､,　/6 ６∂ 
// 　　　　　　　　　　 ＼　　　　　　　　　　　　　　　　 ﾞ'i　.ω } 
// 　　　　　　　　　　　　ﾞキ　　　　　　　　　　　　　　　i　　　/ 
// 　　　　　　　　　　　　　ｷ　　　　　　　　　　　　　　 i　 　 / 
// 　　　　　　　　　　　　　 ｷ;;　　　　　　　　　　　　　　　　/ 
// 　　　　　　　　　　　　　 ﾒﾞﾞ　　　　　　　　　　　　　　 ,,ノ 
// 　　　　　　　　　　　　　{キ;. 　　　　　　　　　　　　　ノ 
// 　　　　　　　　　　　　　ｷ≠　　　　　　　　　r=ｫ'匕ゝ､＿　　,,...., 
// 　　　　　　　　　　　　　　Ｙ.--''''''''　　　　 ノ弋≠ ≠;≠ｷ千;;彡ﾞ 
// 　　　　　　　　　　　　　 iﾞ　o　３　　　　,.）　　　`'''…ー'''''´´ 
// 　　　　　　　　　　　　　（__　8　,..〟'''´´ 
// 　　　　　　　　　　　　　　ゝ-'''´ 



#include <stdio.h>
#include "cpu.hpp"

byte mem[] = {MOV_RI, RCX, 5, DEC, RAX, LOOP, -2, EXIT, EXIT, EXIT};

int main()
{
    CPU *cpu = new_cpu();
    cpu->rip = mem;

    while(1)
    {
        int next;
        switch(*cpu->rip)
        {
            case MOV_RR:
                next = mov_rr(cpu);
                break;
            case MOV_RI:
                next = mov_ri(cpu);
                break;
            case ADD_RR:
                next = add_rr(cpu);
                break;
            case ADD_RI:
                next = add_ri(cpu);
                break;
            case INC:
                next = inc(cpu);
                break;
            case DEC:
                next = dec(cpu);
                break;
            case LOOP:
                next = loop(cpu);
                break;
            case JMP:
                next = jmp(cpu);
                break;
            case EXIT:
                goto loop_end;
            default:
                goto loop_end;
        }
        cpu->rip += next;
        printf("rax: %3lld\n", cpu->rax);
        printf("rdx: %3lld\n", cpu->rdx);
    }
    loop_end:

    return 0; 
}
