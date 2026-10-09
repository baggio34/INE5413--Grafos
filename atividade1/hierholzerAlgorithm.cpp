#include "Uwg.h"
#include "uwgraph.cpp"
#include "Vertice.h"
#include <queue>
#include <vector>
#include <algorithm> 

using std::vector;


// Estrutura de retorno para encapsular o resultado: 
// indica se o ciclo existe e armazena a sequência de vértices caso exista.
struct returnType {
    bool exist;
    vector<int> ciclo;
};

returnType HierholzerAlgorithm(Uwg* graph) {
    returnType ret;
    ret.exist = true;

    // 1. Grafo vazio
    if (graph->nArestas == 0) {
        ret.exist = true;
        return ret;
    }

    // 2. Condição de Euler: Verificar se todos os vértices têm grau par
    int start_v = -1;
    for (int i = 0; i < graph->nVertices; i++) {
        if (graph->grau(i) % 2 != 0) {
            ret.exist = false;
            return ret;
        }
        if (graph->grau(i) > 0 && start_v == -1) {
            start_v = i; // Define o primeiro vértice conectado como início
        }
    }

    if (start_v == -1) {
        ret.exist = false;
        return ret;
    }

    // 3. Validação de Conexidade (Garante que todas as arestas/vértices com grau > 0 pertencem à mesma componente)
    vector<bool> visited(graph->nVertices, false);
    std::queue<int> q;
    q.push(start_v);
    visited[start_v] = true;
    int visitedCount = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visitedCount++;
        for (int v = 0; v < graph->nVertices; v++) {
            if (graph->haAresta(u, v) && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    int totalVerticesComArestas = 0;
    for (int i = 0; i < graph->nVertices; i++) {
        if (graph->grau(i) > 0) totalVerticesComArestas++;
    }

    // Se houver vértices com arestas que não foram alcançados, o grafo é desconexo
    if (visitedCount != totalVerticesComArestas) {
        ret.exist = false;
        return ret;
    }

    // 4. Algoritmo de Hierholzer iterativo (Pilha)
    vector<int> curr_path;
    vector<int> circuit;
    curr_path.push_back(start_v);

    // Matriz booleana de existência de arestas para "consumir" durante a busca.
    vector<vector<bool> > edges(graph->nVertices, vector<bool>(graph->nVertices, false));
    for (int i = 0; i < graph->nVertices; i++) {
        for (int j = 0; j < graph->nVertices; j++) {
            edges[i][j] = graph->haAresta(i, j);
        }
    }

    while (!curr_path.empty()) {
        int curr_v = curr_path.back();
        bool has_edge = false;

        // Procura a próxima aresta adjacente
        for (int next_v = 0; next_v < graph->nVertices; next_v++) {
            if (edges[curr_v][next_v]) {
                // Remove a aresta (grafo não-dirigido)
                edges[curr_v][next_v] = false;
                edges[next_v][curr_v] = false;
                
                curr_path.push_back(next_v);
                has_edge = true;
                break;
            }
        }

        // Se não houver mais arestas, o vértice atual entra no circuito final
        if (!has_edge) {
            circuit.push_back(graph->verticesList[curr_v].id);
            curr_path.pop_back();
        }
    }

    // 5. Verificação de segurança final de arestas residuais
    for (int i = 0; i < graph->nVertices; i++) {
        for (int j = 0; j < graph->nVertices; j++) {
            if (edges[i][j]) {
                ret.exist = false;
                return ret;
            }
        }
    }

    // O circuito é construído de trás para frente, então o revertemos
    std::reverse(circuit.begin(), circuit.end());
    ret.ciclo = circuit;

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