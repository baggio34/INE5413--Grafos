#include "Uwg.h" 
#include "uwgraph.cpp"
#include <queue>
#include <vector>

using std::vector;

void uwgSearch(string path, int index) {
    Uwg graph;

    std::queue<Vertice*> queue;

    graph.lerArquivo(path);

    // Ajuste de índice (base-1 do arquivo para base-0 do vetor C++)
    Vertice& s = graph.verticesList[index];

    // Inicialização do vértice de origem
    s.known = true;
    s.distance = 0;
    queue.push(&s);

    int currentDistance = 0;
    bool first = true;

    // Laço principal da BFS (FIFO: First-In, First-Out)
    while (!queue.empty()) {
        Vertice* u = queue.front();
    
        // Controle de níveis: detecta quando mudamos para uma nova distância
        if (currentDistance == u->distance) { 
            if (currentDistance != 0) {printf("\n");}
            printf("%d: ", u->distance);
            currentDistance += 1;
            first = true;
        }
        queue.pop();
        
        // Recupera os vizinhos do vértice atual (convertendo ID para índice 0-based)
        vector<Vertice> neighborhood = graph.vizinhos(u->id-1);

        for (Vertice v : neighborhood) {
            Vertice& realV = graph.verticesList[v.id - 1];

            // Se o vizinho ainda não foi visitado, marca-o e enfileira
            if (!realV.known) {
                realV.known = true;
                realV.distance = u->distance + 1;
                realV.ancestor = u; // Armazena o ancestral para rastreio de caminho se necessário
                queue.push(&realV);
            }
        }

        // Impressão formatada dos vértices pertencentes ao nível atual
        if (first) {
            printf("%d", u->id);
            first = false;
        } else {
            printf(", %d", u->id);
        }
    }

    printf("\n");

} 

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        std::cout << "./main <arquivo_do_grafo> <vertice_inicial>\n";
        return 1; // encerra  se faltar
    }

    std::string filePath = argv[1];

    int startIndex = std::stoi(argv[2]) - 1 ;

    uwgSearch(filePath, startIndex);

    return 0;
}