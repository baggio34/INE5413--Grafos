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

using std::string;
using std::array;

class Vertice {      
    public:

};

class Uwg {
    public:
        // métodos e atributos
        int qtdVertices();
        int qtdArestas();
        int grau();
        string rotulo();
        array<Vertice, 999> vizinhos(); //alterar esse 999 depois 
        bool haAresta();
        int peso();
        void lerArquivo();
};

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

void Uwg::lerArquivo() {

}