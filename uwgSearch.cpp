#include "Uwg.h" 
#include "uwgraph.cpp"
#include <queue>
#include <vector>

using std::vector;

void uwgSearch(string path, int index) {
    Uwg graph;
    std::queue<Vertice*> queue;

    graph.lerArquivo(path);
    Vertice& s = graph.verticesList[index];

    s.known = true;
    s.distance = 0;
    queue.push(&s);

    int currentDistance = 0;
    bool first = true;

    while (!queue.empty()) {
        Vertice* u = queue.front();
        
        if (currentDistance == u->distance) { 
            if (currentDistance != 0) {printf("\n");}
            printf("%d: ", u->distance);
            currentDistance += 1;
            first = true;
        }
        queue.pop();
        
        vector<Vertice> neighborhood = graph.vizinhos(u->id-1);

        for (Vertice v : neighborhood) {
            Vertice& realV = graph.verticesList[v.id - 1];

            if (!realV.known) {
                realV.known = true;
                realV.distance = u->distance + 1;
                realV.ancestor = u;
                queue.push(&realV);
            }
        }

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