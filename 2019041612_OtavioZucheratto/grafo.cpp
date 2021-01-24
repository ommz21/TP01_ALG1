#include "grafo.h"

#define INFINITO 1000000

/*Implementacao dos metodos da classe Grafo*/
Grafo::Grafo(int q_centros, int q_postos, int d_temp)
{
    quant_centros = q_centros;
    quant_postos = q_postos;
    max_arestas = 30 / d_temp;
    alcancados = -q_centros;
    loop = false;
}
void Grafo::InsereCentros(std::vector<int> lista)
{
    centros.push_back(lista);
}
void Grafo::InserePostos(std::vector<int> lista)
{
    locais.push_back(lista);
}
void Grafo::CopiaCentros()
{
    for (int i = 0; i < quant_centros; i++)
        locais.push_back(centros.at(i));
}
void Grafo::ImprimeGrafo()
{
    for(int i = 1; i <= quant_postos + quant_centros; i++)
    {
        std::cout << "Local " << i << ": ";
        for (auto v : locais.at(i))
            std::cout << v <<" ";
        std::cout << std::endl;
    }
}
void Grafo::VisitaBfs(int vertice_u)
{
    int vertice_v;
    cor.at(vertice_u) = "cinza";
    dist.at(vertice_u) = 0;
    fila = std::queue<int>();
    fila.push(vertice_u);
    while (!fila.empty())
    {
        vertice_u = fila.front();
        fila.pop();
        alcancados++;
        if (dist.at(vertice_u) + 1 > max_arestas)
            continue;
        for (int vertice_v : locais.at(vertice_u))
        {
            if (cor.at(vertice_v) != "branco")
                continue;
            cor.at(vertice_v) = "cinza";
            if (dist.at(vertice_v) >= dist.at(vertice_u) + 1)
                dist.at(vertice_v) = dist.at(vertice_u) + 1;
            if (vertice_v)
                fila.push(vertice_v);
        }
        cor.at(vertice_u) = "preto";    
    }
}
void Grafo::BuscaEmLargura()
{
    for (int i = 0; i <= quant_centros + quant_postos; i++)
    {
        cor.push_back("branco");
        dist.push_back(INFINITO);
    }
    for (int i = quant_postos + 1; i <= quant_postos + quant_centros; i++)
        Grafo::VisitaBfs(i);
}
void Grafo::VisitaDfs(int vertice_u)
{
    int vertice_v;
    if (loop)
        return;
    cor.at(vertice_u) = "cinza";
    for (int vertice_v : locais.at(vertice_u))
    {
        if (cor.at(vertice_v) == "branco")
            VisitaDfs(vertice_v);
        else if (cor.at(vertice_v) == "cinza")
        {
            loop = true;    
            return;
        }
    }
    cor.at(vertice_u) = "preto";
}
void Grafo::BuscaEmProfundidade()
{
    for (int i = 0; i <= quant_centros + quant_postos; i++)
        cor.at(i) = "branco";
    for (int i = quant_postos + 1; i <= quant_postos + quant_centros; i++)
        Grafo::VisitaDfs(i);
}
void Grafo::ImprimeSaida()
{
    std::cout << alcancados << std::endl;
    if (!alcancados)
        std::cout << "*";
    for (int i = 1; i <= quant_postos + quant_centros; i++)
        if (dist.at(i) > 0 && dist.at(i) < INFINITO)
            std::cout << i << " ";
    std::cout << std::endl;
    if (loop)
        std::cout << 1;
    else
        std::cout << 0;
}