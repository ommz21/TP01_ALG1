#include "headers/grafo.h"
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
        std::list<int> lista_adj;
        stream = std::istringstream(linha);
        while(stream >> texto_posto)
        {
            posto_adj = std::stoi(texto_posto);
            lista_adj.push_back(posto_adj);
        }
        cidade.InsereCentros(lista_adj);
    }
    
    // Insere uma lista vazia na posicao zero para que os indices dos
    // postos sejam os mesmos do numero indicado ao pela entrada do programa
    cidade.InserePostos(std::list<int>());
    
    // Insere todos as arestas adjascentes aos postos de vacinacao de maneira que
    // locais[i] = vertices adjascentes ao posto i
    for (int i = 0; i < quant_postos; i++)
    {
        getline(std::cin, linha);
        std::list<int> lista_adj;
        stream = std::istringstream(linha);
        while(stream >> texto_posto)
        {
            posto_adj = std::stoi(texto_posto);
            lista_adj.push_back(posto_adj);
        }
        cidade.InserePostos(lista_adj);
    }
    
    // Insere os centros de distribuicoes nas posicoes apos todos os postos de vacinacao
    cidade.CopiaCentros();
    
    // Chama o BFS para contabilzar todos os postos de vacinacao alcancados por todas as rotas
    cidade.BuscaEmLargura();

    // Chama o DFS para determinar se existe alguma rota que passe pelo mesmo posto
    // de vacinacao mais de uma vez durante a mesma rota
    cidade.BuscaEmProfundidade();

    // Exibe na tela todas as informacoes coletadas pelo programa
    cidade.ImprimeSaida();
    
    return 0;
}