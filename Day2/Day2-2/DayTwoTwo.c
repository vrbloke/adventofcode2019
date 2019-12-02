#include<stdio.h>
#include<stdlib.h>

int main(){

    int head = 0;
    int size = 0;
    int add_a = 0;
    int add_b = 0;
    int add_c = 0;
    int noun = 0;
    int verb = 0;
    FILE* in = fopen("input","r");

    //There are no comments throughout this because I'm tired and wanna move on.

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
    int *refresh = (int*)malloc(size*sizeof(int));
    for(int i = 0; i < size; i++)
    {
        refresh[i] = code[i];
    }

        for(int i = 0; i < 100; i++)
        {
            for(int j = 0; j < 100; j++)
            {
                for(int k = 0; k < size; k++)
                {
                    code[k] = refresh[k];
                }
                code[1] = i;
                code[2] = j;

                printf("\n");

                //Resolve code:
                for(head = 0; head < size; head+=4)
                {
                    //  Opcode 99: Termination
                    if(code[head] == 99)
                    {
                        if(code[0] == 19690720) { noun = code[1]; verb = code[2]; }
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

            }
        }

    for(int i = 0; i < size; i++) { printf("%d, ", code[i]); }
    printf("\n\n\n\n");
    printf("RESULT: %d", 100*noun+verb);

    return 0;
}
