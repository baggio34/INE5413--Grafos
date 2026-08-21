#ifndef UWG_H
#define UWG_H


#include <vector>
#include <iostream>
#include <string>
#include "Vertice.h" 


using std::string;
using std::vector;

class Uwg {
    public:
        int nVertices;
        std::vector<Vertice> verticesList;
        int nArestas;
        std::vector<std::vector<double> > matrix;


        Uwg();
        int qtdVertices();
        int qtdArestas();
        int grau(int v);
        string rotulo(int v);
        vector<Vertice> vizinhos(int v); 
        bool haAresta(int u, int v);
        double peso(int u, int v);
        int lerArquivo(string path);
};

#endif