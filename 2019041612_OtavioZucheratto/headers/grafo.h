#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

// Assinatura dos atributos e metodos da classe Grafo
class Grafo
{
    public:
        Grafo(int q_centros, int q_postos, int d_temp);
        void InsereCentros(std::list<int> lista);
        void InserePostos(std::list<int> lista);
        void CopiaCentros();
        void ImprimeGrafo();
        void BuscaEmLargura();
        void BuscaEmProfundidade();
        void ImprimeSaida();
        
    private:
        void VisitaBfs(int vertice_u);
        void VisitaDfs(int vertice_u);
        int quant_centros, quant_postos, max_arestas, alcancados;
        bool loop;
        std::vector<std::list<int> > centros;
        std::vector<std::list<int> > locais;
        std::vector<std::string> cor;
        std::vector<int> dist;
        std::queue<int> fila;
        
};

#endif /* GRAFO_H */