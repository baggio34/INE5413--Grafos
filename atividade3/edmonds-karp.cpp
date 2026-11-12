#include "Uwg.h"
#include "uwgraph.cpp"
#include "Vertice.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


vector<Vertice> edmondsBfs(Uwg* graph, Vertice s, Vertice t) {
    std::queue<Vertice> queue;


    for (Vertice& v : graph->verticesList) {
        v.known = false;
        v.ancestor = nullptr;
    }

    graph->verticesList[s.id - 1].known = true;

    queue.push(s);

    while (!queue.empty()) {
        Vertice u = queue.front();
        queue.pop();
        
        for (Vertice viz : graph->vizinhosSaintes(u.id - 1)) {
            Vertice& v = graph->verticesList[viz.id - 1];

            if (!v.known && graph->matrix[u.id - 1][v.id - 1] != 0) {
                v.known = true;
                v.ancestor = &graph->verticesList[u.id - 1];
                queue.push(v);

                vector<Vertice> p;

                if (t.id == v.id) {
                    p.push_back(v);
                    Vertice w = v;

                    while (w.id != s.id) {
                        w = *w.ancestor;
                        p.insert(p.begin(), w);
                    }

                    return p;
                }
                
            }
        }
    }
        
    return vector<Vertice>();
        
}

double edmondsKarp(Uwg* graph, int s, int t) {
   for (int i = 0; i < graph->nVertices; i++) {
        for (int j = 0; j < graph->nVertices; j++) {
            if (graph->matrix[i][j] != infinito && graph->matrix[j][i] == infinito) graph->matrix[j][i] = 0;
        }
    }

    double F = 0;
    vector<Vertice> p = edmondsBfs(graph, graph->verticesList[s - 1], graph->verticesList[t - 1]);

    while (!p.empty()) {
        double fp = infinito;
        for (size_t i = 0; i + 1 < p.size(); i++) {
            fp = std::min(fp, graph->matrix[p[i].id - 1][p[i + 1].id - 1]);
        }

        F += fp;

        for (size_t i = 0; i + 1 < p.size(); i++) {
            graph->matrix[p[i].id - 1][p[i + 1].id - 1] -= fp;
            graph->matrix[p[i + 1].id - 1][p[i].id - 1] += fp;
        }

        p = edmondsBfs(graph, graph->verticesList[s - 1], graph->verticesList[t - 1]);
    }

    return F;
}


int main(int argc, char* argv[]) {
    Uwg g;
    if (g.lerArquivo(argv[1]) != 0) return 1;

    std::cout << (long long) edmondsKarp(&g, std::stoi(argv[2]), std::stoi(argv[3])) << std::endl;
    return 0;
}