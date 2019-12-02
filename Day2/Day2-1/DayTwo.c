#include<stdio.h>
#include<stdlib.h>

int main(){

    int head = 0;
    int size = 0;
    int add_a = 0;
    int add_b = 0;
    int add_c = 0;
    FILE* in = fopen("input","r");

    //Read size of input code (could do this manually but why?)
    while(fscanf(in, "%d,", &head) != EOF)
    {
        size++;
    }

    fclose(in);
    in = fopen("input", "r");

    int *code = (int*)malloc(size*sizeof(int));
    for(int i = 0; i < size; i++)
    {
        fscanf(in, "%d,", code+i);
    }

    //Resolve code:
    for(head = 0; head < size; head+=4)
    {
        //  Opcode 99: Termination
        if(code[head] == 99)
        {
            break;
        }
        //  Opcode 1: Addition
        else if(code[head] == 1)
        {
            add_a = code[head+1];
            add_b = code[head+2];
            add_c = code[head+3];

            code[add_c] = code[add_a] + code[add_b];
        }
        //  Opcode 2: Multiplication
        else if(code[head] == 2)
        {
            add_a = code[head+1];
            add_b = code[head+2];
            add_c = code[head+3];

            code[add_c] = code[add_a] * code[add_b];
        }
        else
        {
            printf("Wrong opcode\n");
            break;
        }
        
    }

    for(int i = 0; i < size; i++) { printf("%d, ", code[i]); }

    return 0;
}
