#include "Uwg.h" 
#include <queue>

void uswSearch(string path, int index) {
    Uwg graph;
    std::queue<Vertice*> queue;

    graph.lerArquivo(path);
    Vertice s = graph.verticesList[index];

    s.known = true;
    s.distance = 0;
    queue.push(&s);

    while (!queue.empty()) {
        Vertice* u = queue.pop();
        
    }

} 