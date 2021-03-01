/* Distance Vector Algorithm implementation using Bellman Ford algorithm
 * This program simulates creation of the routing table on different routers in a network
 * Author   -   Anish Sharma
 * Date     -   28-02-2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Representative of a router in the network
typedef struct Router
{
    int *D;
    int *T;
} Router;

int bellman(int index, int n, Router *rt[n])
{
    int changeFlag = 0;
    // For every destination
    for (int v = 0; v < n; v++)
    {
        // For every neighbour
        for (int u = 0; u < n; u++)
        {
            // If no route to destination, skip neighbour
            if (rt[index]->D[u] == INT_MAX || rt[u]->D[v] == INT_MAX)
                continue;
            if (rt[index]->D[v] > rt[index]->D[u] + rt[u]->D[v])
            {
                rt[index]->D[v] = rt[index]->D[u] + rt[u]->D[v];
                rt[index]->T[v] = rt[index]->T[u];
                changeFlag = 1;
            }
        }
    }

    return changeFlag;
}

void main()
{
    // n - number of vertices/routers
    // m - number of links/edges
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

    while (1)
    {
        int change = 0;
        // execute bellman-ford algorithm on each router to calculate distances
        for (int i = 0; i < n; i++)
        {
            change += bellman(i, n, rt);
        }
        // if there were no changes, break the loop
        if (change == 0)
            break;
    }

    // Display results - routing table for each router
    printf("Distance Vector Routing - Using Bellman Ford algorithm\n");
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