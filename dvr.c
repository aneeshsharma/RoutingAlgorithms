/* Distance Vector Algorithm implementation using Bellman Ford algorithm
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

void bellman(Router *rt, int index, int n, int w[n][n])
{
    for (int j = 0; j < n; j++)
    {
        if (index == j)
        {
            rt->D[j] = 0;
        }
        else
        {
            rt->D[j] = INT_MAX;
        }
        rt->T[j] = -1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                if (w[u][v] == INT_MAX)
                    continue;
                int weight = w[u][v];
                if (rt->D[u] != INT_MAX && rt->D[u] + weight < rt->D[v])
                {
                    rt->D[v] = rt->D[u] + weight;
                    if (u != index)
                        rt->T[v] = u;
                }
            }
        }
    }

    printf("Dest\tDist\tVia\n");
    for (int i = 0; i < n; i++)
    {
        if (rt->T[i] == -1)
            printf("%d\t%d\t-\n", i, rt->D[i]);
        else
            printf("%d\t%d\t%d\n", i, rt->D[i], rt->T[i]);
    }
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
    Router rt[n];
    for (int i = 0; i < n; i++)
    {
        rt[i].D = malloc(n * sizeof(int));
        rt[i].T = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                rt[i].D[j] = 0;
            else
                rt[i].D[j] = INT_MAX;
        }

    for (int i = 0; i < n; i++)
    {
        printf("--------------\n");
        printf("For Router %d\n", i);
        // execute bellman-ford algorithm on each router to calculate distances
        bellman(&rt[i], i, n, w);
    }
}