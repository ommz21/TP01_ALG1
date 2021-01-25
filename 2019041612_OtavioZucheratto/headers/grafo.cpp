#include "grafo.h"

#define INFINITO 1000000

// Implementacao dos metodos da classe Grafo
Grafo::Grafo(int q_centros, int q_postos, int d_temp)
{
    quant_centros = q_centros;
    quant_postos = q_postos;
    // Calculo para verificar quantas arestas serao percorridas sem que a
    // temperatura maxima seja ultrapassada 
    max_arestas = 30 / d_temp;
    // Inicia os alcancados de maneira que os centros de distribuicoes nao sejam contabilizados
    alcancados = -q_centros;
    loop = false;
}
void Grafo::InsereCentros(std::list<int> lista)
{
    centros.push_back(lista);
}
void Grafo::InserePostos(std::list<int> lista)
{
    locais.push_back(lista);
}
void Grafo::CopiaCentros()
{
    // Adiciona todos as listas de adjascencias dos centros no vector locais(depois dos postos)
    for (int i = 0; i < quant_centros; i++)
        locais.push_back(centros.at(i));
}
// Algoritmo BFS simplificado do livro do Nivio Ziviani
void Grafo::VisitaBfs(int vertice_u)
{
    // Cinza significa que esta sendo explorado e distancia do centro eh zero pois o mesmo eh a raiz
    cor.at(vertice_u) = "cinza";
    dist.at(vertice_u) = 0;
    // Fila comeca vazia e enfileira a raiz
    fila = std::queue<int>();
    fila.push(vertice_u);
    while (!fila.empty())
    {
        // Retira um vertice da fila e contabiliza o contador de postos alcancados
        vertice_u = fila.front();
        fila.pop();
        alcancados++;
        // Se o maximo de arestas foi alcancados entao esse caminho se encerra nesse vertice
        if (dist.at(vertice_u) + 1 > max_arestas)
            continue;
        // Percorre todos os vertices adjascentes ao vertice_u e caso o vertice nao tenha sido
        // explorado ainda (branco), o mesmo sera adicionado na fila e ficara cinza
        for (int vertice_v : locais.at(vertice_u))
        {
            if (cor.at(vertice_v) != "branco")
                continue;
            cor.at(vertice_v) = "cinza";
            // Distancia sera a distancia do pai mais um, a distancia sera a do menor caminho
            if (dist.at(vertice_v) >= dist.at(vertice_u) + 1)
                dist.at(vertice_v) = dist.at(vertice_u) + 1;
            // Trata o caso de nao adicionar aresta para o 0 pois essa posicao nao corresponde
            // a nenhum vertice
            if (vertice_v)
                fila.push(vertice_v);
        }
        // Terminou de explorar todos os vertices vizinhos do vertice_u
        cor.at(vertice_u) = "preto";    
    }
}
void Grafo::BuscaEmLargura()
{
    // Inicia todos os vertices com cor branca e distancia muito grande
    for (int i = 0; i <= quant_centros + quant_postos; i++)
    {
        cor.push_back("branco");
        dist.push_back(INFINITO);
    }
    // Chama o BFS para cada centro
    for (int i = quant_postos + 1; i <= quant_postos + quant_centros; i++)
        Grafo::VisitaBfs(i);
}
// Algoritmo DFS simplificado do livro do Nivio Ziviani
void Grafo::VisitaDfs(int vertice_u)
{
    // Utiliza o booleano que indica que existem algum posto percorrido mais de uma vez em uma mesma rota
    if (loop)
        return;
    // Cinza indica vertice que comecou a ser explorado
    cor.at(vertice_u) = "cinza";
    for (int vertice_v : locais.at(vertice_u))
    {
        if (cor.at(vertice_v) == "branco")
            VisitaDfs(vertice_v);
        // Caso encontre um vertice cinza indica que esse vertice pertence ao caminho atual e
        // indica que ele seria percorrido mais de uma vez e portanto o booleano se torna true
        else if (cor.at(vertice_v) == "cinza")
        {
            loop = true;    
            return;
        }
    }
    // Esgotou todos os vertices filhos do vertice_u entao o vertice se torna preto
    cor.at(vertice_u) = "preto";
}
void Grafo::BuscaEmProfundidade()
{
    // Inicializa todos vertices como branco
    for (int i = 0; i <= quant_centros + quant_postos; i++)
        cor.at(i) = "branco";
    // Realiza a busca DFS partindo de todos os centros de distribuicoes
    for (int i = quant_postos + 1; i <= quant_postos + quant_centros; i++)
        Grafo::VisitaDfs(i);
}

void Grafo::ImprimeSaida()
{
    // Imprime a quantidade de postos de vacinacao alcancados
    std::cout << alcancados << std::endl;
    if (!alcancados)
        std::cout << "*";
    // Imprime os indices de todos os postos alcancados
    for (int i = 1; i <= quant_postos + quant_centros; i++)
        if (dist.at(i) > 0 && dist.at(i) < INFINITO)
            std::cout << i << " ";
    std::cout << std::endl;
    // Imprime o indicador de que existe ou nao um posto que foi percorrido mais de uma vez
    // em uma determinada rota
    if (loop)
        std::cout << 1;
    else
        std::cout << 0;
    std::cout << std::endl;
}