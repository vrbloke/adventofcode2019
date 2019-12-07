#include <stdio.h>
#include <stdlib.h>

int areEqual(char a[3], char b[3])
{
    for(int i = 0; i < 3; i++)
    {
        if(a[i] != b[i]) { return 0; }
    }
    return 1;
}

int main()
{
    FILE* in = fopen("input", "r");
    int size = 0;
    char temp[3];
    char trash[3];
    char children[46656][3];
    int children_count[46656];
    int bodies_count = 0;
    int l = 0;

    for(size = 0; fscanf(in, "%*3s)%*3s\n") == 2; size++) {}

    for(int i = 48; i < 91; i++)
    {
        if(i == 58) { i = 65; }
        for(int j = 48; j < 91; j++)
        {
            if(j == 58) { j = 65; }
            for(int k = 48; k < 91; k++)
            {
                if(k == 58) { k = 65; }
                children[l][0] = i;
                children[l][1] = j;
                children[l][2] = k;
                children_count[l] = 0;
                l++;                        
            }
            
        }
    }

    fclose(in);
    in = fopen("input", "r");

    for(int i = 0; i < 1376; i++)
    {
        fscanf(in, "%c%c%c)%c%c%c\n", &temp[0], &temp[1], &temp[2], &trash[0], &trash[1], &trash[2]);

        for(int i =0; i < 3; i++)
        {
            printf("%c", temp[i]);
        }

        printf("\n");

        for(int i = 0; i < 46656; i++)
        {
            if(areEqual(temp, children[i])) { children_count[i]++; }
        }
    }

    for(int i = 0; i < 46656; i++)
    {
        bodies_count += children_count[i];
    }

    int max_children_count = 0;
    for(int i = 0; i < 46656; i++)
    {
        if(children_count[i] > max_children_count) { max_children_count = children_count[i]; }
    }

    for(int i = 0; i < 46656; i++)
    {
        printf("%c%c%c has %d children.\n", children[i][0], children[i][1], children[i][2], children_count[i]);
    }

    printf("There are %d bodies in total. The highest number of children is %d.\n", bodies_count+1, max_children_count);

    return 0;
}
