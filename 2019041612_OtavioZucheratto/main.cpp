#include "grafo.h"
#include <iomanip>
#include <sstream>

int main()
{
    // Declaracao das variaveis para lidar com a entrada do programa
    int quant_centros, quant_postos, delta_temp, posto_adj;
    std::string linha, texto_posto;
    std::istringstream stream;
    
    // Leitura da quantidade de centros de distribuicoes e postos de vacinacao 
    // alem do acrecimo de temperatura por aresta percorrida
    std::cin >> quant_centros >> quant_postos >> delta_temp;
    // Limpa a entrada padrao
    std::cin.clear();
    std::cin.ignore(10000,'\n');
    
    // Constroi o grafo
    Grafo cidade(quant_centros, quant_postos, delta_temp);
    
    // Le e armazena os vertices adjascentes aos centros de distribuicoes
    for (int i = 0; i < quant_centros; i++)
    {
        getline(std::cin, linha);
        std::vector<int> lista_adj;
        stream = std::istringstream(linha);
        while(stream >> texto_posto)
        {
            posto_adj = std::stoi(texto_posto);
            lista_adj.push_back(posto_adj);
        }
        cidade.InsereCentros(lista_adj);
    }
    
    // Coloca 
    cidade.InserePostos(std::vector<int>());
    for (int i = 0; i < quant_postos; i++)
    {
        getline(std::cin, linha);
        std::vector<int> lista_adj;
        stream = std::istringstream(linha);
        while(stream >> texto_posto)
        {
            posto_adj = std::stoi(texto_posto);
            lista_adj.push_back(posto_adj);
        }
        cidade.InserePostos(lista_adj);
    }
    
    cidade.CopiaCentros();
    
    cidade.ImprimeGrafo();

    cidade.BuscaEmLargura();
    cidade.BuscaEmProfundidade();
    cidade.ImprimeSaida();
    
    return 0;
}