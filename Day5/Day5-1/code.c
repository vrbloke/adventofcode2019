#include <stdlib.h>
#include <stdio.h>

/*
    Each cell of code can now be many characters long. 
    I can't define a single width to fit them all.
    Instead: I can introduce an extra step (slowing down the code) splitting the code cells 
    into arrays of single digits (using the floor division method, with extra checking for 
    relevant zeroes).
    Once code is split into an array, it can be evaluated: I should only need one array
    at a time, so this can be a single variable.
    Code in general should still be stored as a 1D array, only temporarily split for interpretation.
*/

//pow function to make things easier in one part
int pow(int base, int exponent)
{
    int temp = 1;
    for(int i = 0; i < exponent; i++)
    {
        temp *= base;
    }
    return temp;
}

int main()
{
    //Import code.
    FILE* in = fopen("input", "r");
    int size = 0; //Measures number of code cells
    int head = 0; //Code address pointer
    int head_jump = 0; //Determines how far head needs to jump after executing instruction.
    int* instruction_array;

    for(size = 0; fscanf(in, "%d,", &head) == 1; size++) {}
    fclose(in);

    int* code = (int*)malloc(size*sizeof(int));
    in = fopen("input", "r");
    for(int i = 0; i < size; i++)
    {
        fscanf(in, "%d,", &(code[i]));
    }

    //Resolve code.
    //Head doesn't move a static amount. This will be determined by type of instruction detected.
    
    for(head = 0; head < size; head += head_jump)
    {
        //Start by dissasembling current input.
        int value = code[head]; //Numerical value of current code cell.
        int number_of_digits = 0; //Number of digits in current code cell.
        int last_digit = 0; //Last digit in current code cell; the opcode.
        int temp = 0; //Used for whatever.

        //Identify last digit to determine how big the array should be.
        last_digit = value % 10;
        switch(last_digit)
        {
            case 9:
            number_of_digits = 2;
            head_jump = 1;
            break;

            case 1:
            case 2:
            case 7:
            case 8:
            number_of_digits = 5;
            head_jump = 4; //Might as well set this now.
            break;

            case 3:
            case 4:
            number_of_digits = 3;
            head_jump = 2;
            break;

            case 5:
            case 6:
            number_of_digits = 4;
            head_jump = 3;
            break;

            default:
            head_jump = 1;
            break;
        }

        instruction_array = (int*)malloc(number_of_digits*sizeof(int));

        //Dissasembly
        temp = value;
        for(int i = number_of_digits-1; i >= 0; i--)
        {
            instruction_array[i] = temp % 10;
            temp /= 10;
        }

        //Interpretation
        int a;
        int b;
        switch(last_digit)
        {
            //instruction_array[2] == 1 -> Immediate mode. Else position mode.
            case 1: //Addition
            a = instruction_array[2] ? code[head+1] : code[code[head+1]];
            b = instruction_array[1] ? code[head+2] : code[code[head+2]];
            code[code[head+3]] = a+b;
            break;

            case 2: //Multiplication
            a = instruction_array[2] ? code[head+1] : code[code[head+1]];
            b = instruction_array[1] ? code[head+2] : code[code[head+2]];
            code[code[head+3]] = a*b;
            break;

            case 3: //Input
            printf("Input: ");
            scanf("%d", &code[code[head+1]]);
            break;

            case 4: //Output
            printf("%d\n", code[code[head+1]]);
            break;

            case 5: //Jump-if-true
            a = instruction_array[1] ? code[head+1] : code[code[head+1]]; //1
            b = instruction_array[0] ? code[head+2] : code[code[head+2]]; //9
            head = a ? b : head; //9
            head_jump = a ? 0 : 3; //0
            break;

            case 6: //Jump-if-false
            a = instruction_array[1] ? code[head+1] : code[code[head+1]]; //0
            b = instruction_array[0] ? code[head+2] : code[code[head+2]]; //9
            head = a ? head : b; //9
            head_jump = a ? 3 : 0; //0
            break;

            case 7: //Less than
            a = instruction_array[2] ? code[head+1] : code[code[head+1]];
            b = instruction_array[1] ? code[head+2] : code[code[head+2]];
            code[code[head+3]] = a < b ? 1 : 0;
            break;

            case 8:
            a = instruction_array[2] ? code[head+1] : code[code[head+1]];
            b = instruction_array[1] ? code[head+2] : code[code[head+2]];
            code[code[head+3]] = a == b ? 1 : 0;
            break;

            case 9:
            printf("Terminating.\n");
            return 0;

            default:
            printf("Wrong opcode encountered. Exiting...\n");
            return -1;
        }    

        free(instruction_array);
    }

    return 0;
}
