#include "Uwg.h"
#include <iostream>
#include <string> 
#include <array>
#include <fstream> 
#include <sstream>
#include <vector>
#include <limits>

using std::string;
using std::array;
using std::vector;

const int infinito = std::numeric_limits<int>::max();

// --- MÉTODOS DA CLASSE VERTICE ---

Vertice::Vertice(int id, string rotulo, int grau) {
    this->id = id;
    this->rotulo = rotulo;
    this->grau = grau;
    this->ancestor = nullptr;
    this->distance = infinito;
    this->known = false;
}


Vertice* Vertice::getAncestor() {
    return ancestor;
}

int Vertice::getDistance() {
    return distance;
}

bool Vertice::getKnown() {
    return known;
}

void Vertice::setAncestor(Vertice* a) {
    ancestor = a;
}

void Vertice::setDistance(int d) {
    distance = d;
}

void Vertice::setKnown(bool info) {
    known = info;
}


// --- MÉTODOS DA CLASSE UWG ---

Uwg::Uwg() {
    nVertices = 0;
    nArestas = 0;
}

int Uwg::qtdVertices() {
    return this->nVertices;
}

int Uwg::qtdArestas() {
    return this->nArestas;
}

int Uwg::grau(int v) {
    return this->verticesList[v].grau;
}

string Uwg::rotulo(int v) {
    return this->verticesList[v].rotulo;
}

vector<Vertice> Uwg::vizinhos(int v) {
    vector<Vertice> vec;
    
    for (int i = 0; i < this->nVertices; i++) {
        if (matrix[v][i] != 0) vec.push_back(verticesList[i]);
    }

    return vec;
}

bool Uwg::haAresta(int u, int v) {
    return (this->matrix[u][v] != 0);
}

int Uwg::peso(int u, int v) {
    return(this->matrix[u][v] != 0) ? matrix[u][v] : infinito;
}

int Uwg::lerArquivo(string path) {
    int vertices;
    std::string line;

    std::ifstream file(path);

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

        verticesList.push_back(Vertice(id, label, 0));
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
        matrix[b-1][a-1] = peso;
        verticesList[a-1].grau++;
        verticesList[b-1].grau++;
        nArestas++;
    }

    file.close();
    return 0;
}
/*
int main() {
    Uwg g;

    // Tenta ler o arquivo de entrada
    string caminhoArquivo = "example-graph.txt";
    if (g.lerArquivo(caminhoArquivo) != 0) {
        std::cout << "Falha ao carregar o arquivo. Verifique se o caminho esta correto.\n";
        return 1;
    }

    std::cout << "\n--- TESTANDO OPERACOES DO GRAFO ---\n\n";

    // 0. Matriz de adjacencia
    for (int i = 0; i < g.nVertices; i++) {
        for (int j = 0; j < g.nVertices; j++) {
            printf(" %d ", g.matrix[i][j]);
        }
        printf("\n");
    }

    // 1. qtdVertices() e qtdArestas()
    std::cout << "Quantidade de vertices: " << g.qtdVertices() << "\n";
    std::cout << "Quantidade de arestas: " << g.qtdArestas() << "\n\n";

    // 2. rotulo(v) e grau(v) para cada vértice
    std::cout << "--- Vertices e Seus Graus ---\n";
    for (int i = 0; i < g.qtdVertices(); i++) {
        std::cout << "Vertice " << i << " -> Rotulo: " << g.rotulo(i) 
                  << " | Grau: " << g.grau(i) << "\n";
    }
    std::cout << "\n";

    // 3. vizinhos(v)
    std::cout << "--- Vizinhos do Vertice 0 ---\n";
    if (g.qtdVertices() > 0) {
        vector<Vertice> viz = g.vizinhos(0);
        std::cout << "Vizinhos de " << g.rotulo(0) << ": ";
        for (const auto& v : viz) {
            std::cout << v.rotulo << " (id: " << v.id << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // 4. haAresta(u, v) e peso(u, v)
    std::cout << "--- Verificacao de Arestas e Pesos ---\n";
    if (g.qtdVertices() >= 2) {
        int u = 0, v = 1;
        std::cout << "Ha aresta entre " << u << " e " << v << "? " 
                  << (g.haAresta(u, v) ? "Sim" : "Nao") << "\n";
        std::cout << "Peso da aresta {" << u << ", " << v << "}: " 
                  << g.peso(u, v) << "\n";
    }

    return 0;
}
*/