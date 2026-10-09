#include "Uwg.h"
#include "uwgraph.cpp"
#include "Vertice.h"
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
// para usar a mesma biblioteca de grafos não direcionados desenvolvida anteriormente
// a interpretação será que a célula [i, j] representa um arco saindo de i para j

Uwg* Dfs(Uwg* graph);
void DfsVisit(Uwg* graph, Vertice* vertice, int* time, vector<int>* scc = nullptr);
Uwg* AltDfs(Uwg* graph);


Uwg KosarajuSahir(Uwg* graph) {
    Dfs(graph);

    Uwg transpostGraph = *graph;

    for (int i = 0; i < graph->nVertices; i++) {
        for (int j = 0; j < graph->nVertices; j++) {
            transpostGraph.matrix[j][i] = graph->matrix[i][j];
        }
    }

   AltDfs(&transpostGraph);

   return transpostGraph;
}


Uwg* Dfs(Uwg* graph) {
    for (Vertice &v : graph->verticesList) {
        v.known = false;
        v.distance = int(infinito);
        v.time = int(infinito);
        v.ancestor = nullptr;
    }

    int time = 0;

    for (Vertice &u : graph->verticesList) {
        if (!u.known) {
            DfsVisit(graph, &u, &time);
        }
    }

    return graph;
}


void DfsVisit(Uwg* graph, Vertice* vertice, int* time, vector<int>* scc) {
    vertice->known = true;
    (*time)++;

    if (scc != nullptr) scc->push_back(vertice->id);

    int u_idx = -1;
    for (int i = 0; i < graph->nVertices; i++) {
        if (graph->verticesList[i].id == vertice->id) {
            u_idx = i;
            break;
        }
    }


    for (int v_idx = 0; v_idx < graph->nVertices; v_idx++) {
        if (graph->matrix[u_idx][v_idx] != infinito) {
            Vertice &v = graph->verticesList[v_idx];

            if (!v.known) {
                v.ancestor = vertice;
                DfsVisit(graph, &v, time, scc);
            }
        }
    }


    (*time)++;
    vertice->time = *time;
}

Uwg* AltDfs(Uwg* graph) {
    for (Vertice &v : graph->verticesList) {
        v.known = false;
        v.distance = int(infinito);
        v.ancestor = nullptr;
    }

    int time = 0;

    vector<Vertice*> vec;
 
    for (Vertice &u : graph->verticesList) {
        vec.push_back(&u);
    }

    std::sort(vec.begin(), vec.end(), [](Vertice*a, Vertice* b) {
        return a->time > b->time;
    });



    for (Vertice* u : vec) {
        if (!u->known) {
            vector<int> scc;
            DfsVisit(graph, u, &time, &scc);
            
            std::sort(scc.begin(), scc.end());
            
            for (size_t k = 0; k < scc.size(); k++) {
                cout << scc[k] << (k == scc.size() - 1 ? "" : ",");
            }
            cout << endl;
        }
    }


    return graph;
}

int main(int argc, char *argv[])
{


    if (argc < 2) {
        cout << "Erro: Arquivo nao fornecido." << endl;
        return 1;
    }
    std::string filePath = argv[1];

    Uwg graph;
    if (graph.lerArquivo(filePath) != 0)
    {
        return 1;
    }

    KosarajuSahir(&graph);

    return 0;
}