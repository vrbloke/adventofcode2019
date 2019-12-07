#include <stdlib.h>
#include <stdio.h>

/*
    I'm going to construct a tree with up to 36^3 nodes. 
    Each node is going to contain:
    * a pointer to its parent (the body it's orbiting)
    * its name -- a 3-character alphanumeric string
    * pointers to each of its children (gotta figure out how many this will require, how?)
    For every node at the end of a branch, we count the number of nodes until we reach COM.
    The total number of nodes we find is that node's number of orbits.
    We then do the same thing for every node that is one node before the end of a branch, and so on.
    While we do this we remember which nodes have been checked so as not to repeat ourselves.
*/

struct tree
{
    char name[3];
    struct tree *left, *right;
};

struct tree* tree(struct tree* pointer)
{
    struct tree result;
    result.left = NULL;
    result.right = NULL;
    result.name[0] = 0;
    result.name[1] = 0;
    result.name[2] = 0;
    pointer = &result;
    return pointer;
}

int areEqual(char a[3], char b[3])
{
    for(int i = 0; i < 3; i++)
    {
        if(a[i] != b[i]) { return 0; }
    }
    return 1;
}

struct tree* findInTree(char string[3], struct tree *tree)
{
    if(areEqual(string, tree->name)) { return tree; }
    else
    {
        if(!(tree->left || tree->right)) { return NULL; }
        else
        {
            struct tree* result = findInTree(string, tree->right);
            if(result)
            {
                return result;                
            }
            else
            {
                result = findInTree(string, tree->left);
                return result;
            }
            
        }
        
    }
}

void printTree(struct tree* root)
{
    printf("%c%c%c\n", root->name[0], root->name[1], root->name[2]);
    if(root->left) { printTree(root->left); }
    if(root->right) { printTree(root->right); }
}

int main(void) { 

    FILE* in = fopen("input", "r");
    struct tree *body[1377];

    // // //
    //Construct trees for each pointer to point to
    for(int i = 0; i < 1377; i++)
    {
        body[i] = tree(body[i]);
    }

    body[0]->name[0] = 'C';
    body[0]->name[1] = 'O';
    body[0]->name[2] = 'M';

    //Import names
    for(int i = 1; i < 1377; i++)
    {
        fscanf(in, "%*c%*c%*c)%c%c%c\n", &body[i]->name[0],&body[i]->name[1],&body[i]->name[2]);
        printf("%c%c%c\n", body[i]->name[0], body[i]->name[1], body[i]->name[2]);
    }

    fclose(in);
    in = fopen("input", "r");

    //Build relationships
    for(int i = 0; i < 1376; i++)
    {
        char parent_name[3];
        struct tree *parent;
        char child_name[3];
        struct tree *child;

        fscanf(in, "%c%c%c)%c%c%c", parent_name[0], parent_name[1], parent_name[2], child_name[0], child_name[1], child_name[2]);

        for(int i = 0; i < 1377; i++)
        {
            if(areEqual(body[i]->name, parent_name)) { parent = body[i]; break; }
        }

        for(int i = 0; i < 1377; i++)
        {
            if(areEqual(body[i]->name, child_name)) { child = body[i]; break; }
        }

        if(parent->left)
        {
            parent->right = child;
        }
        else
        {
            parent->left = child;
        }
        
    }

    //Print tree left to right
    printTree(body[0]);

    return 0;
}
