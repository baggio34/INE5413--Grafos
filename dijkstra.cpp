#include "Uwg.h"
#include "uwgraph.cpp"
#include "Vertice.h"
#include <queue>
#include <vector>
#include <stack>

using std::vector;

void dijkstra(string path, int index)
{

    Uwg graph;

    graph.lerArquivo(path);
    Vertice &s = graph.verticesList[index];

    s.distance = 0;

    for (int i = 0; i < graph.nVertices; i++)
    {

        double shortestDistance = infinito;
        int lowestRate = -1;

        for (int j = 0; j < graph.nVertices; j++)
        {

            Vertice &current = graph.verticesList[j];

            if (current.known == false)
            {
                if (current.distance < shortestDistance)
                {
                    shortestDistance = current.distance;
                    lowestRate = j;
                }
            }
        }

        if (lowestRate == -1)
        {
            break;
        }

        Vertice &chosen = graph.verticesList[lowestRate];
        chosen.known = true;

        vector<Vertice> neighborhood = graph.vizinhos(chosen.id - 1);

        for (Vertice v : neighborhood)
        {
            Vertice &realV = graph.verticesList[v.id - 1];

            if (realV.known == false)
            {

                double newDistance = chosen.distance + graph.peso(chosen.id - 1, realV.id - 1);

                if (newDistance < realV.distance)
                {

                    realV.distance = newDistance;
                    realV.ancestor = &chosen;
                }
            }

            std::stack<Vertice *> stack;

            Vertice &actual = realV;

            if (actual.ancestor != nullptr)
            {
                stack.push(&actual);
                actual = *actual.ancestor;
            }
            else
            {
                printf ("%d: ", i);
                for (int k = 0; k < stack.size(); k ++) {
                    Vertice& aux = *stack.top();
                    printf("%d, ", aux.id);
                    stack.pop();
                }
            }
        }
    }
}
