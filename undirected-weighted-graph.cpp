// Crie um tipo estruturado de dados ou uma classe que represente um grafo nao-dirigido
// e ponderado G(V, E, w), no qual V ´e o conjunto de v´ertices, E é o conjunto de arestas e w : E → R é a função que
// mapeia o peso de cada aresta {u, v} ∈ E. As operações/méetodos contemplados para o grafo deverão ser:
// • qtdVertices(): retornr a quantidade de vértices;
// • qtdArestas(): retorna a quantidade de arestas;
// • grau(v): retorna o grau do vértice v;
// • rotulo(v): retorna o rótulo do vértice v;
// • vizinhos(v): retorna os vizinhos do vértice v;
// • haAresta(u, v): se {u, v} ∈ E, retorna verdadeiro; se não existir, retorna falso;
// • peso(u, v): se {u, v} ∈ E, retorna o peso da aresta {u, v}; se não existir, retorna um valor infinito positivo1;
// • ler(arquivo)2: deve carregar um grafo a partir de um arquivo no formato especificado ao final deste docu-
// mento.
// IMPORTANTE: As operações/métodos deverão ter complexidade de tempo computacional O(1) quando possível.
// No caso de dúvidas, consulte o professor da disciplina.

#include <iostream>
#include <string> 
#include <array>
#include <fstream> 
#include <sstream>
#include <vector>


using std::string;
using std::array;

class Vertice {      
    public:

};

class Uwg {
    public:
        // métodos e atributos
        int nVertices;

        Uwg();
        int qtdVertices();
        int qtdArestas();
        int grau();
        string rotulo();
        array<Vertice, 999> vizinhos(); //alterar esse 999 depois 
        bool haAresta();
        int peso();
        int lerArquivo();

        std::vector<std::vector<int> > matrix;

};

Uwg::Uwg() {
    nVertices = 0;
}

int Uwg::qtdVertices() {

}

int Uwg::qtdArestas() {

}

int Uwg::grau() {

}

string Uwg::rotulo() {

}

array<Vertice, 999> vizinhos() {       //alterar 999
    
}

bool Uwg::haAresta() {

}

int Uwg::peso() {

}

int Uwg::lerArquivo() {
   int vertices;
   std::string line;

   std::ifstream file("example-graph.txt");

    if (!file.is_open()) {
        std::cerr << "Error, could not open the file." << std::endl;
        return 1;
    }

    // procura *vertices
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string comando;

        ss >> comando;

        if (comando == "*vertices") {
            ss >> vertices;
            this->nVertices = vertices;

            matrix.assign(vertices, std::vector<int>(vertices, 0));
            break;
        }
    }

    // le os n vertices
    for (int i = 0; i < vertices; i++) {
        std::getline(file, line);

        std::stringstream ss(line);

        int id;
        std::string label;

        ss >> id;
        ss >> label;
    }

    // procura *edges
    while (std::getline(file, line)) {
        if (line == "*edges") {
            break;
        }
    }

    // le as arestas
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        int a, b;
        double peso;
        ss >> a >> b >> peso;
        matrix[a-1][b-1] = peso;
        matrix[a-1][b-1] = peso;
    }

    file.close();
    return 0;
}

int main() {
    Uwg graph = Uwg();

    graph.lerArquivo();

    for (int i = 0; i<5; i++) {
        for (int j=0; j<5; j++) {
            printf("%d", graph.matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}