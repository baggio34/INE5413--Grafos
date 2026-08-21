#include "Uwg.h" 
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

    printf("0: %d\n", s.id);

    while (!queue.empty()) {
        Vertice* u = queue.front();
        vector<int> ids;
        queue.pop();
        
        vector<Vertice> neighborhood = graph.vizinhos(u->id-1);

        for (Vertice v : neighborhood) {
            Vertice& realV = graph.verticesList[v.id - 1];

            if (!realV.known) {
                realV.known = true;
                realV.distance = u->distance + 1;
                realV.ancestor = u;
                queue.push(&realV);
                ids.push_back(realV.id);
            }
        }

        if (!ids.empty()) {

            printf("%d: ", u->distance+1);
            for (size_t i = 0; i < ids.size(); ++i) {
                printf("%d%s", ids[i], (i == ids.size() - 1) ? "" : " ");
            }
            printf("\n");
        }
    }

} 

int main() {
    std::string filePath = "example-graph.txt";
    int startIndex = 0;

    uwgSearch(filePath, startIndex);

    return 0;
}