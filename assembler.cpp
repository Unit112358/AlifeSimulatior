#include "edit.cpp"
#include "utils.hpp"
#include "alife.hpp"
#include <vector>

void Alife::setMem(std::vector<byte> v)
{
	byte* tmp = (byte*)malloc(v.size());
	for(int i = 0; i < v.size(); i++)
        tmp[i] = v[i];
	this->mem = tmp;
	cpu->rip = tmp;
	memsize = v.size();
}

std::vector<byte> assembly(std::vector<int> v)
{
    std::vector<byte> ret;

    for(int i = 0;i < v.size(); i++)
    {
        if(v[i] < 0)
        {
            ret.push_back((byte)v[i]);
            continue;
        }
        switch(v[i])
        {
            byte pushee;
            case OP_RAX:
                pushee = RAX;
                break;
            case OP_RBX:
                pushee = RBX;
                break;
            case OP_RCX:
                pushee = RCX;
                break;
            case OP_RDX:
                pushee = RDX;
                break;
            case OP_EXIT:
                pushee = EXIT;
                break;
            case OP_NOP:
                pushee = NOP;
                break;
            case OP_MOV:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(v[i+2] < 0)
                    pushee = MOV_RI;
                else if(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX)
                    pushee = MOV_RR;
                else
                    goto error;
                break;
            case OP_ADD:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(v[i+2] < 0)
                    pushee = ADD_RI;
                else if(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX)
                    pushee = ADD_RR;
                else
                    goto error;
                break;
            case OP_SUB:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(v[i+2] < 0)
                    pushee = SUB_RI;
                else if(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX)
                    pushee = SUB_RR;
                else
                    goto error;
                break;
            case OP_MUL:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(v[i+2] < 0)
                    pushee = MUL_RI;
                else if(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX)
                    pushee = MUL_RR;
                else
                    goto error;
                break;
            case OP_DIV:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(v[i+2] < 0)
                    pushee = DIV_RI;
                else if(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX)
                    pushee = DIV_RR;
                else
                    goto error;
                break;
            case OP_AND:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(!(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX))
                    goto error;
                pushee = AND_RR;
                break;
            case OP_OR:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(!(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX))
                    goto error;
                pushee == OR_RR;
                break;
            case OP_XOR:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(!(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX))
                    goto error;
                pushee = XOR_RR;
                break;
            case OP_INC:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                pushee = INC;
                break;
            case OP_DEC:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                pushee = DEC;
                break;
            case OP_CMP:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                if(!(v[i+2] >= OP_RAX && v[i+2] <= OP_RDX))
                    goto error;
                pushee = CMP_RR;
                break;
            case OP_LOOP:
                if(!(v[i+1] < 0))
                    goto error;
                pushee = LOOP;
                break;
            case OP_JMP:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                pushee = JMP;
                break;
            case OP_ZJ:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                pushee = ZJ;
                break;
            case OP_NZJ:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                pushee = NZJ;
                break;
            case OP_SJ:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                pushee = SJ;
                break;
            case OP_NSJ:
                if(!(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX))
                    goto error;
                pushee = NSJ;
                break;
            case OP_POP:
                pushee = NOP;
                break;
            case OP_PUSH:
                pushee = NOP;
                break;
            case OP_RET:
                pushee = RET;
                break;
            case OP_ADDFRC:
                if(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX)
                    pushee = ADDFRC_R;
                else if (v[i+1] < 0 && v[i+2] < 0)
                    pushee = ADDFRC_II;
                else
                    goto error;
                break;
            case OP_GETNEAR:
                pushee = GETNEAR;
                break;
            case OP_GETNUM:
                if(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX)
                    pushee = GETNUM_R;
                else if(v[i+1] < 0)
                    pushee = GETNUM_I;
                else
                    goto error;
                break;
            case OP_GETDIST:
                if(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX)
                    pushee = GETDIST_R;
                else
                    goto error;
                break;
            case OP_GETVEC:
                if(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX)
                    pushee = GETVEC_R;
                else
                    goto error;
                break;
            case OP_GETCLR:
                if(v[i+1] >= OP_RAX && v[i+1] <= OP_RDX)
                    pushee = GETCOLOR_R;
                else
                    goto error;
                break;          
            case OP_BITE:
                pushee = BITE;
                break;
            case OP_DIVISION:
                if(v[i+1] < 0)                
                    pushee = DIVISION_I;
                else
                    pushee = DIVISION;                    
                break;                            
            case OP_GENERATE:
                pushee = GENERATE;
                break;       
            default:
                printf("eeeee\n");
                exit(0);
            ret.push_back(pushee);
        }
    }
    return ret;

    error:
    printf("syntax error\n");
    exit(0);
    return ;
}