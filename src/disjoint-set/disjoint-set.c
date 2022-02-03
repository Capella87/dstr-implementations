#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* init_set(const int size)
{
    int* new_set = (int*)malloc(sizeof(int) * size);
    if (!new_set) return NULL;
    memset((void*)new_set, -1, sizeof(int) * size);

    return new_set;
}

int find_set(int* set, const int num)
{
    if (set[num] < 0) return num; // root;
    else return set[num] = find_set(set, set[num]);
}

void union_set(int* set, const int a, const int b) // based on union-by-height;
{
    int a_root = find_set(set, a);
    int b_root = find_set(set, b);

    if (a_root == b_root) return;

    if (set[b_root] < set[a_root]) // b_root is bigger;
        set[a_root] = b_root;
    else // a_root is bigger than b_root or equal
    {
        if (set[a_root] == set[b_root]) set[a_root]--;
        set[b_root] = a_root;
    }

    return;
}

int main(void)
{
    int n, command, t_a, t_b;

    scanf("%d", &n);
    int* set = init_set(n);
    while (scanf("%d", &command) != EOF)
    {
        switch (command)
        {
        case 1: // Union
            scanf("%d %d", &t_a, &t_b);
            union_set(set, t_a, t_b);
            break;

        case 2: // Find
            scanf("%d", &t_a);
            printf("root of %d : %d\n", t_a, find_set(set, t_a));
            break;
        }
    }

    free(set);
    return 0;
}

/*
Input:
100
1 1 2
1 1 3
2 1
2 2
2 3
1 4 5
2 4
2 5
2 6
1 1 4
2 1
2 2
2 3
2 4
2 5
2 6

Output:
root of 1 : 1
root of 2 : 1
root of 3 : 1
root of 4 : 4
root of 5 : 4
root of 6 : 6
root of 1 : 1
root of 2 : 1
root of 3 : 1
root of 4 : 1
root of 5 : 1
root of 6 : 6
*/