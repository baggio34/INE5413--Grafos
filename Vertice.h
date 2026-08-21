class Vertice {
    public:
        string rotulo;
        int id;
        int grau;
        Vertice* ancestor;
        int distance;
        bool known;

        Vertice();
        Vertice* getAncestor();
        int getDistance();
        bool getKnown();
        void setAncestor(Vertice* a);
        void setDistance(int d);
        void setKnown(bool info);
}