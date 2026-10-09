#ifndef VERTICE_H
#define VERTICE_H


#include <string>
using std::string;

class Vertice {
    public:
        string rotulo;
        int id;
        int grau;
        Vertice* ancestor;
        int distance;
        bool known;
        int time;


        Vertice(int id, string rotulo, int grau);
};

#endif