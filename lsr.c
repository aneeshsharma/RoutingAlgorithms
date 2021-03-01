/* Link State Routing implementation using Dijkstra's algorithm
 * Author   -   Anish Sharma
 * Date     -   28-02-2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Router
{
    int *D;
    int *T;
} Router;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int checkInside(int size, int N[size], int v)
{
    for (int i = 0; i < size; i++)
    {
        if (v == N[i])
            return 1;
    }
    return 0;
}

int dijkstra(int index, int n, Router *rt[n])
{
    int changeFlag = 0;
    int N[n], size;

    N[0] = index;
    size = 1;
    // While not every node is in N
    while (size < n)
    {
        // Find w not in N such that D(w) is min
        int _min = INT_MAX;
        int w = -1;
        for (int i = 0; i < n; i++)
            if (!checkInside(size, N, i))
            {
                if (rt[index]->D[i] < _min)
                {
                    _min = rt[index]->D[i];
                    w = i;
                }
            }

        // Add w to N
        N[size] = w;
        size++;

        // For all neighbours of w not in N, update D
        for (int v = 0; v < n; v++)
        {
            if (rt[w]->D[v] != INT_MAX && !checkInside(size, N, v))
            {
                if (rt[index]->D[v] > rt[index]->D[w] + rt[w]->D[v])
                {
                    rt[index]->D[v] = rt[index]->D[w] + rt[w]->D[v];
                    rt[index]->T[v] = rt[index]->T[w];
                }
            }
        }
    }

    return changeFlag;
}

void main()
{
    int n, m;

    // Take input for number of vertices and number of links
    scanf("%d %d", &n, &m);

    // Initialize weights
    int w[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                w[i][j] = 0;
            else
                w[i][j] = INT_MAX;
        }
    }

    // Input all the links
    for (int i = 0; i < m; i++)
    {
        int u = 0, v = 0, _w = 0;
        scanf("%d %d %d", &u, &v, &_w);
        w[u][v] = _w;
        w[v][u] = _w;
    }

    // initialize Vector table for all routers
    Router *rt[n];
    for (int i = 0; i < n; i++)
    {
        rt[i] = (Router *)malloc(sizeof(Router));
        rt[i]->D = malloc(n * sizeof(int));
        rt[i]->T = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            rt[i]->D[j] = w[i][j];
            rt[i]->T[j] = j;
        }

    // execute dijstra's algorithm on each router to calculate distances
    for (int i = 0; i < n; i++)
    {
        dijkstra(i, n, rt);
    }

    // Display results
    printf("Link State Routing - Using Dijkstra's algorithm\n");
    printf("Calculated distances and predecessors -\n");
    for (int i = 0; i < n; i++)
    {
        printf("--------------\n");
        printf("For Router %d\n", i);
        printf("Dest\tDist\tVia\n");
        for (int j = 0; j < n; j++)
        {
            if (rt[i]->T[j] == j)
                printf("%d\t%d\t-\n", j, rt[i]->D[j]);
            else
                printf("%d\t%d\t%d\n", j, rt[i]->D[j], rt[i]->T[j]);
        }
    }
}