#include<stdlib.h>
#include<stdio.h>

struct wirecode{
    char direction;
    int amount;
};

int wire_len(struct wirecode* wire)
{
    int len = 0;
    for(int i = 0; i<301; i++)
    {
        len += wire[i].amount;
    }
    return len;
}

int main()
{
    //We start by importing 4 arrays:
    //Two arrays of directions: D, U, R, L
    //Two arrays of amounts: integers

    FILE* dir1 = fopen("directions_one", "r");
    FILE* dir2 = fopen("directions_two", "r");
    FILE* amm1 = fopen("amounts_one", "r");
    FILE* amm2 = fopen("amounts_two", "r");

    //Inputs are all the same size: 301 lines, which we know through the external program
    //used to separate them

    struct wirecode wirecode1[301], wirecode2[301];

    for(int i = 0; i < 301; i++)
    {
        fscanf(dir1, "%c\n", &(wirecode1[i].direction));
        fscanf(amm1, "%d\n", &(wirecode1[i].amount));
        fscanf(dir2, "%c\n", &(wirecode2[i].direction));
        fscanf(amm2, "%d\n", &(wirecode2[i].amount));
    }

    fclose(dir1);
    fclose(dir2);
    fclose(amm1);
    fclose(amm2);

    printf("%d", wire_len(wirecode1));
    printf("%d", wire_len(wirecode2));

    return 0;
}

