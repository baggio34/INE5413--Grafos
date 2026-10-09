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

// Definição global de infinito para tratamento de arestas inexistentes
const double infinito = std::numeric_limits<double>::infinity();

// --- MÉTODOS DA CLASSE VERTICE ---

Vertice::Vertice(int id, string rotulo, int grau) {
    this->id = id;
    this->rotulo = rotulo;
    this->grau = grau;
    this->ancestor = nullptr;
    this->distance = std::numeric_limits<int>::max(); 
    this->known = false;
}



// --- MÉTODOS DA CLASSE UWG ---

// Construtor padrão
Uwg::Uwg() {
    nVertices = 0;
    nArestas = 0;
}

// Retorna a quantidade total de vértices
int Uwg::qtdVertices() { return this->nVertices; }

// Retorna a quantidade total de arestas
int Uwg::qtdArestas() { return this->nArestas; }

// Retorna o grau de um vértice específico
int Uwg::grau(int v) { return this->verticesList[v].grau; }

// Retorna o rótulo de um vértice específico
string Uwg::rotulo(int v) { return this->verticesList[v].rotulo; }

// Retorna um vetor com os vértices vizinhos
vector<Vertice> Uwg::vizinhos(int v) {
    vector<Vertice> vec;
    vec.reserve(this->grau(v)); // Evita realocações dinâmicas reservando o tamanho exato do grau
    
    for (int i = 0; i < this->nVertices; i++) {
        if (matrix[v][i] != infinito) {
            vec.push_back(verticesList[i]);
        }
    }

    return vec;
}

// Verifica se existe aresta entre os vértices u e v
bool Uwg::haAresta(int u, int v) { return (this->matrix[u][v] != infinito); }

// Retorna o peso da aresta {u, v} ou infinito se ela não existir
double Uwg::peso(int u, int v) { return(this->matrix[u][v] != infinito) ? matrix[u][v] : infinito; }

int Uwg::lerArquivo(string path) {
    int vertices = 0;
    std::string line;

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error, could not open the file." << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        std::stringstream ss(line);
        std::string comando;
        ss >> comando;

        if (comando == "*vertices") {
            ss >> vertices;
            this->nVertices = vertices;
            matrix.assign(vertices, std::vector<double>(vertices, infinito));
            break;
        }
    }

    for (int i = 0; i < vertices; i++) {
        if (!std::getline(file, line)) break;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        std::stringstream ss(line);
        int id;
        string label = "";
        ss >> id;

        size_t firstQuote = line.find('"');
        if (firstQuote != std::string::npos) {
            size_t secondQuote = line.find('"', firstQuote + 1);
            if (secondQuote != std::string::npos) {
                label = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
            } else {
                label = line.substr(firstQuote + 1);
            }
        } else {
            ss >> label;
            if (label.empty()) {
                label = std::to_string(id);
            }
        }

        verticesList.push_back(Vertice(id, label, 0));
    }

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        // Remove espaços à esquerda/direita se necessário ou compara prefixo
        if (line.rfind("*arcs", 0) == 0) {
            break;
        }
    }

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;

        std::stringstream ss(line);
        int a, b;
        double peso;
        
        if (!(ss >> a >> b >> peso)) continue; // Ignora linhas inválidas/vazias
        
        // Grafo não-dirigido: preenche simetricamente
        matrix[a-1][b-1] = peso;
        // matrix[b-1][a-1] = peso;  // descomentar em caso de ser não direcionado
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
        vector<Vertice> viz = g.(0);
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