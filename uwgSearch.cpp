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

    vector<vector<int>> levels;
    levels.push_back({s.id});


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
                
                if (levels.size() <= (size_t)realV.distance) {
                    levels.resize(realV.distance + 1);
                }
                levels[realV.distance].push_back(realV.id);
            }
        }

    }
    for (size_t d = 0; d < levels.size(); ++d) {
        if (!levels[d].empty()) {
            printf("%zu: ", d);
            for (size_t i = 0; i < levels[d].size(); ++i) {
                printf("%d%s", levels[d][i], (i == levels[d].size() - 1) ? "" : " ");
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