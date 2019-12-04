#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

//Wirecode consists of a direction and an amount
struct wirecode{
        char direction;
        int amount;
    };

//Coordinates relative to origin
 struct point{
        int x, y;
    };

//This time, size corresponds 1:1 to size1, size2
struct point* build_wire(struct wirecode* wirecode, struct point* wire, int size)
{
    wire = (struct point*)malloc((size+1)*sizeof(struct point));
    struct point head = {0, 0};
    wire[0] = head;

    for(int i=1; i < size+1; i++)
    {
        switch(wirecode[i].direction)
        {
            case 'U':
            head.y += wirecode[i].amount;
            wire[i] = head;
            break;

            case 'D':
            head.y -= wirecode[i].amount;
            wire[i] = head;
            break;

            case 'R':
            head.x += wirecode[i].amount;
            wire[i] = head;
            break;

            case 'L':
            head.x -= wirecode[i].amount;
            wire[i] = head;
            break;
        }
    }

    return wire;
}

//Simple function for absolute value
int abs(int a)
{
    if(a < 0) { return -a; }
    else { return a; }
}

//Simple function for minimum
int min(int a, int b)
{
    if(a < b) { return a; }
    else { return b; }
}

//Simple function for maximum
int max(int a, int b)
{
    if(a > b) { return a; }
    else { return b; }
}

struct point intersection_exists(struct point a1, struct point a2, struct point b1, struct point b2, struct point result)
{
    result.x = 0;
    result.y = 0;
    //Segments a1a2, b1b2 must have opposite horizontality
    if((a1.y == a2.y) && (b1.x == b2.x)) // a1a2 is horizontal and b1b2 is vertical
    {
        if((b1.x > min(a1.x,a2.x)) && (b1.x < max(a1.x,a2.x))) 
        { 
            result.x = b2.x; 
            result.y = a2.y;
            return result;
        }
    }

    if((a1.x == a2.x) && (b1.y == b2.y)) // a1a2 is vertical and b1b2 is horizontal
    {
        if((a1.x > min(b1.x,b2.x)) && (a1.x < max(b1.x,b2.x)))
        {
            result.x = a2.x;
            result.y = b2.y;
            return result;
        }
    }
    return result;
}

int main()
{
    // STEP ONE: IMPORT WIRECODES
    FILE* dir1 = fopen("directions_one", "r");
    FILE* dir2 = fopen("directions_two", "r");
    FILE* amm1 = fopen("amounts_one", "r");
    FILE* amm2 = fopen("amounts_two", "r");
    FILE* lin1 = fopen("lines_one", "r");
    FILE* lin2 = fopen("lines_two", "r");

    int size1, size2;

    fscanf(lin1, "%d", &size1);
    fscanf(lin2, "%d", &size2);

    struct wirecode wirecode1[size1];
    struct wirecode wirecode2[size2];

    for(int i = 0; i < size1; i++) { fscanf(dir1, "%c\n", &(wirecode1[i].direction)); fscanf(amm1, "%d\n", &(wirecode1[i].amount)); }
    for(int i = 0; i < size2; i++) { fscanf(dir2, "%c\n", &(wirecode2[i].direction)); fscanf(amm2, "%d\n", &(wirecode2[i].amount)); }

    //Check if imported properly
    printf("Wirecode1:\n");
    for(int i = 0; i <size1; i++) { printf("%c%d\n", wirecode1[i].direction, wirecode1[i].amount); }
    printf("Wirecode2:\n");
    for(int i = 0; i< size2; i++) { printf("%c%d\n", wirecode2[i].direction, wirecode2[i].amount); }

    // STEP TWO: BUILD WIRES
    struct point* wire1 = build_wire(wirecode1, wire1, size1);
    struct point* wire2 = build_wire(wirecode2, wire2, size2);

    //Check if built properly
    for(int i = 0; i < size1; i++) { printf("Point %d in wire 1: %d, %d\n", i, wire1[i].x, wire2[i].y); }
    printf("\n");
    for(int i = 0; i < size2; i++) { printf("Point %d in wire 2: %d %d\n", i, wire2[i].x, wire2[i].y); }
    printf("\n");

    // STEP THREE: COMPARE WIRES
    int minimum_distance = INT_MAX;
    struct point intersection;

    for(int i = 0; i < size1; i++)
    {
        for(int j = 0; j < size2; j++)
        {
            intersection = intersection_exists(wire1[i], wire1[i+1], wire2[j], wire2[j+1], intersection);
            if((intersection.x != 0) && (intersection.y != 0))
            {
                int distance = abs(intersection.x) + abs(intersection.y);
                minimum_distance = min(minimum_distance, distance);
                printf("Intersection found at point %d, %d. Distance: %d\n", intersection.x, intersection.y, distance);
            }
        }
    }

    printf("Minimum distance: %d\n", minimum_distance);

    return 0;
    }
