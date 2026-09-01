#include "Uwg.h" 
#include "uwgraph.cpp"
#include "Vertice.h"
#include <queue>
#include <vector>

using std::vector;

struct returnType
{
    bool exist;
    vector<int> ciclo;
};

returnType SearchSubCicle(Uwg& G, Vertice v, vector<vector<double> >& C);


returnType HierholzerAlgorithm(Uwg* graph) {
    returnType finalValues;
    std::vector<std::vector<double> > matr;

    matr.assign(graph->nVertices, std::vector<double>(graph->nVertices, 0));

    // nˆ2 T-T
    // preencher a matriz
    for (int i = 0; i < graph->nVertices; i++) {
        for (int j = 0; j < graph->nVertices; j++) {
            if (graph->matrix[i][j] != 0) matr[i][j] = 1; else matr[i][j] = 0;
        }
    }
    // grafo vazio
    if (graph->nArestas == 0) {
        finalValues.exist = true;
        return finalValues;
    }

    Vertice initialVertice(999, "v", 0);
    // escolher o vértice inicial conectado
    for (int i = 0; i < graph->nVertices; i++) {
        if (graph->grau(i) > 0) {
            initialVertice = graph->verticesList[i];
            break;
        }
    }

    returnType returned = SearchSubCicle(*graph, initialVertice, matr);


    returnType ret;
    ret.exist = false;

    if (returned.exist == false) {
        return ret;
    }

    for (int i = 0; i < graph->nVertices; i++) {
        for (int j = 0; j < graph->nVertices; j++) {
            if(matr[i][j] != 0) return ret;
        }
    }

    return returned;
}

returnType SearchSubCicle(Uwg& G, Vertice v, vector<vector<double> >& C) {
    returnType ret;
    ret.exist = true;
    ret.ciclo.push_back(v.id);
    size_t arestaCoord[2];

    Vertice temp = v;
    bool finded = false;

    while (!finded) {
        bool edge_found = false;
        for (size_t i = 0; i < G.nVertices; i++) {
            if (C[v.id - 1][i] > 0) {
                arestaCoord[0] = v.id - 1;
                arestaCoord[1] = i;
                edge_found = true;
                break;
            }
        }
        if (!edge_found) {
            ret.exist = false;
            ret.ciclo.clear();
            return ret;
        }

        C[arestaCoord[0]][arestaCoord[1]]--;
        C[arestaCoord[1]][arestaCoord[0]]--;

        v = G.verticesList[arestaCoord[1]];
        ret.ciclo.push_back(v.id);

        if (v.id == temp.id) finded = true;
    }

    for (size_t i = 0; i < ret.ciclo.size(); i++) {
        int x_id = ret.ciclo[i];
        int x_matrix_idx = x_id - 1;

        bool hasRemainingEdge = false;
        for (int j = 0; j < G.nVertices; j++) {
            if (C[x_matrix_idx][j] > 0) {
                hasRemainingEdge = true;
                break;
            }
        }

        if (hasRemainingEdge) {
            returnType sub_ret = SearchSubCicle(G, G.verticesList[x_matrix_idx], C);

            if (!sub_ret.exist) {
                ret.exist = false;
                ret.ciclo.clear();
                return ret;
            }

            ret.ciclo.erase(ret.ciclo.begin() + i);
            ret.ciclo.insert(ret.ciclo.begin() + i, sub_ret.ciclo.begin(), sub_ret.ciclo.end());

        }
    }

    return ret;

}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: ./A1_3 <arquivo_do_grafo>\n";
        return 1;
    }

    std::string filePath = argv[1];
    Uwg graph;

    if (graph.lerArquivo(filePath) != 0) {
        return 1; 
    }

    returnType result = HierholzerAlgorithm(&graph);

    
    if (!result.exist) {
        std::cout << "0\n";
    } 
    else {
        std::cout << "1\n";
        for (size_t i = 0; i < result.ciclo.size(); i++) {
            std::cout << result.ciclo[i];
            
            if (i < result.ciclo.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "\n";
    }

    return 0;
}