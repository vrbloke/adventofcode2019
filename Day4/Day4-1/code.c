#include <stdlib.h>
#include <stdio.h>

int check_number(int num)
{
    int number[6];
    number[0] = num / 100000;
    num -= number[0]*100000;
    number[1] = num / 10000;
    num -= number[1]*10000;
    number[2] = num / 1000;
    num -= number[2]*1000;
    number[3] = num / 100;
    num -= number[3]*100;
    number[4] = num / 10;
    num -= number[4]*10;
    number[5] = num;


    int last_digit = number[0];
    int repeat_present = 0;
    for(int i=1; i<6; i++)
    {
        if(number[i] < last_digit) { return 0; }
        if(number[i] == last_digit) { repeat_present = 1; }
        last_digit = number[i];
    }
    if(repeat_present) { return 1; }
    else { return 0; }
}

int main()
{
    FILE* in = fopen("input", "r");
    int min, max;
    fscanf(in, "%d-%d", &min, &max);

    printf("Value for 111111: %d\n", check_number(111111));
    printf("Value for 223450: %d\n", check_number(223450));
    printf("Value for 123789: %d\n", check_number(123789));

    int matches = 0;

    for(int i = min; i <= max; i++)
    {
        if(check_number(i)){ printf("Match found: %d\n", i); matches++; }
    }

    printf("Total matches: %d\n", matches);

    return 0;
}

