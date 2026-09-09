#include "Uwg.h"
#include "uwgraph.cpp"
#include "Vertice.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using std::string;
using std::vector;



int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Uso: ./A1_5 <arquivo_do_grafo>\n";
        return 1;
    }

    std::string filePath = argv[1];

    Uwg graph;
    if (graph.lerArquivo(filePath) != 0)
    {
        return 1;
    }

    int n = graph.nVertices;

    // Inicializa a matriz de distâncias com infinito
    vector<vector<double> > dist(n, vector<double>(n, infinito));

    // Configuração inicial da matriz com os pesos diretos das arestas
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (i != j && graph.matrix[i][j] != 0)
            {
                dist[i][j] = graph.matrix[i][j];
            }
        }
    }

    // Laços principais do Floyd-Warshall (Programação Dinâmica: O(V^3))
    // Testa todos os vértices intermediários k entre cada par (i, j)
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d:", graph.verticesList[i].id);
        for (int j = 0; j < n; j++)
        {
            printf("%lld", (long long)dist[i][j]);
            if (j < n - 1)
            {
                printf(",");
            }
        }
        printf("\n");
    }

    fflush(stdout);
    return 0;
}