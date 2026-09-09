#include "Uwg.h"
#include "uwgraph.cpp"
#include "Vertice.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <utility>

using std::string;
using std::vector;

void dijkstra(Uwg &graph, int index)
{
    Vertice &s = graph.verticesList[index];
    s.distance = 0;

    // Min-Heap armazenando pares: {distância acumulada, índice do vértice}
    std::priority_queue<std::pair<double, int>, 
                        std::vector<std::pair<double, int>>, 
                        std::greater<std::pair<double, int>>> pq;
    
    pq.push(std::make_pair(0.0, index));

    while (!pq.empty())
    {
        double dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        Vertice &currU = graph.verticesList[u];

        // Ignora se encontrarmos uma entrada desatualizada na fila
        if (dist > currU.distance) continue;
        if (currU.known) continue;
        
        currU.known = true;

        // Relaxamento das arestas vizinhas
        for (int v = 0; v < graph.nVertices; v++)
        {
            if (graph.matrix[u][v] != 0) 
            {
                Vertice &currV = graph.verticesList[v];
                double pesoAresta = graph.matrix[u][v];

                if (!currV.known && currU.distance + pesoAresta < currV.distance)
                {
                    currV.distance = currU.distance + pesoAresta;
                    currV.ancestor = &currU; // Armazena ancestral para reconstrução
                    pq.push(std::make_pair(currV.distance, v));
                }
            }
        }
    }
}

// Reconstrói o caminho percorrido do destino até a origem usando os ancestrais
vector<int> reconstruirCaminho(Vertice *destino)
{
    vector<int> caminho;
    Vertice *atual = destino;

    while (atual != nullptr)
    {
        caminho.push_back(atual->id);
        atual = atual->ancestor;
    }

    std::reverse(caminho.begin(), caminho.end());
    return caminho;
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        std::cout << "Uso: ./A1_4 <arquivo_do_grafo> <vertice_inicial>\n";
        return 1;
    }

    std::string filePath = argv[1];
    int startIndex = std::stoi(argv[2]) - 1;

    Uwg graph;
    if (graph.lerArquivo(filePath) != 0)
    {
        return 1;
    }

    dijkstra(graph, startIndex);

    // Exibe os caminhos e distâncias para todos os vértices
    for (int i = 0; i < graph.nVertices; i++)
    {
        Vertice &destino = graph.verticesList[i];
        vector<int> caminho = reconstruirCaminho(&destino);

        printf("%d: ", destino.id);
        
        // Se o vértice for inalcançável, a distância permanece como infinito
        if (destino.distance >= infinito / 2) {
            printf("Inalcançável; d=INF\n"); 
        } else {
            for (size_t k = 0; k < caminho.size(); k++)
            {
                printf("%d", caminho[k]);
                if (k < caminho.size() - 1)
                {
                    printf(",");
                }
            }
            printf("; d=%lld\n", (long long)destino.distance);
        }
    }

    return 0;
}