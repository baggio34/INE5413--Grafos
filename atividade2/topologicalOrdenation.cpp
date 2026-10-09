#include "Uwg.h"
#include "uwgraph.cpp"
#include "Vertice.h"
#include <iostream>
#include <vector>
#include <algorithm>



using namespace std;

vector<string> topologicalOrdenation (Uwg* graph);
void DfsVisitOT(Uwg* graph, Vertice* v, int* time, vector<string>* Olist);

vector<string> topologicalOrdenation (Uwg* graph) {
    for (Vertice &v : graph->verticesList) {
        v.known = false;
        v.time = int(infinito);
        v.distance = int(infinito);
    }

    int time = 0;
    vector<string> Olist;

    for (Vertice &u : graph->verticesList) {
        if (!u.known) {
            DfsVisitOT(graph, &u, &time, &Olist);
        }
    }

    reverse(Olist.begin(), Olist.end());
    return Olist;
}


void DfsVisitOT(Uwg* graph, Vertice* v, int* time, vector<string>* Olist) {
    v->known = true;
    (*time)++;
    v->time = *time;

    int i = v - &graph->verticesList[0];
    for (int j = 0; j < graph->nVertices; j++) {
        if (graph->haAresta(i, j) && !graph->verticesList[j].known) {
            DfsVisitOT(graph, &graph->verticesList[j], time, Olist);
        }
    }

    (*time)++;
    Olist->push_back(v->rotulo);

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

    vector<string> ordenatedVector = topologicalOrdenation(&graph);

    for (size_t i = 0; i < ordenatedVector.size(); i++) {
        cout << ordenatedVector[i];
        if (i + 1 < ordenatedVector.size()) cout << " , ";
    }
    cout << endl;

    return 0;
}