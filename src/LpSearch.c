/*****************************************************************************

    LpSearch - DICIONÁRIO DE PALAVRAS E FRASES
    
    DESENVOLVIDO POR:
    
        Peterson Daronch de Bem
        Laisa Fernochio Ribeiro
        
    PUC MINAS - CAMPUS POÇOS DE CALDAS - 08, MAY, 2016

*****************************************************************************/

/*****************************************************************************
  
    INCLUSÃO DE BIBLIOTECAS E DEFINIÇÃO DE DIRETIVAS
  
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>

#define TAMANHO_MAXIMO_TEXTO 60
#define TAMANHO_MAXIMO_DESCRICAO 255

/******************************************************************************

    DECLARAÇÕES E PREPARAÇÕES INICIAIS

******************************************************************************/

//Estrutura de uma vertice
struct Vertice
{
    char chrLetra;
    char chrDescricao[TAMANHO_MAXIMO_DESCRICAO + 1];
    int intFimDePalavra;
    struct Aresta *arestas;
};

//Estrutura de uma lista de arestas
struct Aresta
{
    struct Vertice *vrtDestino;
    struct Aresta *arsProxima, *arsAnterior;
};

//Esturura de uma texto
struct Texto
{
    char chrTexto[TAMANHO_MAXIMO_TEXTO + 1];
    char chrDescricao[TAMANHO_MAXIMO_DESCRICAO + 1];
    struct Texto *txtProximo, *txtAnterior;
};

//Vertice raiz
struct Vertice *vrtRaiz = NULL;

//Prototipos de funções da interface
void menu();
void busca();
void cadastros();
int cadastroDeTexto();
int cadastroDeDescricao(struct Texto *);
int confirmacao(char []);
int excluir();
void sair();

//Prototipos de funções do grafo
int prepararVertice(struct Vertice **, char, char[], int);
int adicionarAresta(struct Vertice **, struct Vertice **);
int adicionarTextoNoGrafo(char [], char [], struct Vertice **);
int existeIdentificadorInformadoNoGrafo(char [], struct Vertice **);
int buscarComplementosDoPrefixo(char [], char [], struct Vertice **, struct Texto **);
int excluirTextoDoGrafo(char [], struct Vertice **);
void limparGrafo(struct Vertice **);

//Prototipos de funções da lista de textos
int prepararTexto(struct Texto **, char [], char []);
void limparListaDeTextosEncontrados(struct Texto **);
int adicionarTextoNaLista(struct Texto **, char [], char []);

//Prototipos de funções da manipulação de arquivos
int adicionarInformacaoNoDicionario(struct Texto *);
void atualizarGrafoComDadosDoDicionario();
void excluirInformacaoDoDicionario(char []);

//Prototipos de funções genéricas
void adicionaCaractere(int, char [], int);
int getch();

//Ponto de partida
int main(int argc, char *argv[])
{
    struct Texto *txt = NULL; //REMOVER ISTO <-----------------
    
    //Aloca o nó raiz e exibe o menu
    if (prepararVertice(&vrtRaiz, '\0', "\0", 0))
    {
        //Busca dados do Dicionario e adiciona ao grafo
        atualizarGrafoComDadosDoDicionario();
        
        //Chama o menu principal
        menu();
    }
    else
        printf("\n\tFalha na inicializacao do programa!\n\n");
    
    //Trata saida do sistema
    sair();
    
    //Encerra a execução
    return 0;
}

/**********************************************************************************
 
    INTERFACE COM O USUÁRIO 
    
**********************************************************************************/

//Exibe as opções do sistema ao usuário
void menu()
{
    int intOpcaoSelecionada = 0, intComando = 0;
    char *chrPosicao = NULL;
    
    while (intComando != -1)
    {
        //Limpa tela
        system("clear");
        
        //Imprime o titulo do programa
        printf("\n\n\tLpSearch - Dicionario de significados -> Menu:\n\n");
        
        //Imprime informações
        printf("\t[SETAS] - Posicionar [ENTER] - Confirmar [CTRL + F] - Fechar/Voltar\n\n\n\n");
        
        //Remove cursor atual
        if (chrPosicao != NULL)
            free(chrPosicao);
        
        //Realoca duas vezes a quantidade de opções do menu de memoria para posicionar cursor
        chrPosicao = (char *) malloc(2*(3));
        
        //Trata falha
        if (chrPosicao == NULL)
        {
            printf("\t\tFalha na geração do menu, programa sera fechado!\n\n");
            break;
        }
        
        //Preenche as posições do vetor com espaços em branco
        memset(chrPosicao, ' ', sizeof(chrPosicao));
        
        //Posiciona o cursor
        switch (intOpcaoSelecionada)
        {
            case 0:
                chrPosicao[0] = '[';
                chrPosicao[3] = ']';
                break;
            case 1:
                chrPosicao[1] = '[';
                chrPosicao[4] = ']';
                break;
            case 2:
                chrPosicao[2] = '[';
                chrPosicao[5] = ']';
                break;
        }
        
        //Imprime menu na saida padrão
        printf
        (
            "\t\t%c Busca %c\n\n"
            "\t\t%c Cadastros %c\n\n"
            "\t\t%c Sair %c\n\n\n\n",
            chrPosicao[0], chrPosicao[3], 
            chrPosicao[1], chrPosicao[4], 
            chrPosicao[2], chrPosicao[5]
        );
        
        //Aguarda o próximo comando
        intComando = getch();
        
        //Trata o comando
        switch (intComando)
        {
            case 300: if (intOpcaoSelecionada > 0) intOpcaoSelecionada--; break;
            case 301: if (intOpcaoSelecionada < 2) intOpcaoSelecionada++; break;
            case 6: intComando = -1; break;
            case 10: 
                switch (intOpcaoSelecionada) 
                {
                    case 0: busca(); break;
                    case 1: cadastros(); break;
                    case 2: intComando = -1; break;
                }
                break;
        }
    }
}

//Busca no grafo atraves de identificadores fornecidos pelo usuario na entrada padrão
void busca()
{
    int intComando = 0, intCaractereTemporario = 0, intEncontrados = 0;
    char chrTexto[TAMANHO_MAXIMO_TEXTO + 1];
    struct Texto *txtEncontrados = NULL;
    
    //Limpa o vetor que carrega o texto
    memset(chrTexto, '\0', sizeof(chrTexto));
    
    while (intComando != -1)
    {
        //Limpa tela
        system("clear");
        
        //Imprime o titulo do programa
        printf("\n\n\tLpSearch - Dicionario de significados -> Menu -> Busca\n\n");
        
        //Imprime rodapé
        printf("\t[SETAS] - Percorre textos encontrados [CTRL + F] - Fechar/Voltar\n\n");
        
        //Imprime complementos encontrados e seus significados
        printf("\tEncontrados [%d]\n\n", intEncontrados);
        if (txtEncontrados != NULL)
        {
            //Escreve atual
            printf
            (
                "\t\t%s:\n\n\t\t\t%s\n", 
                txtEncontrados->chrTexto, 
                txtEncontrados->chrDescricao
            );
            
            //Se possivel escreve o proximo
            if (txtEncontrados->txtProximo != NULL)
                printf
                (
                    "\n\t\t%s:\n\n\t\t\t%s", 
                    txtEncontrados->txtProximo->chrTexto, 
                    txtEncontrados->txtProximo->chrDescricao
                );
        }
        else
            printf("\t\tNenhum por enquanto.");
        
        //Imprime informação ao usuário
        printf("\n\n\n\tDigite o Identificador: \n\n\t\t%s", chrTexto);
        
        //Aguarda o próximo comando ou caractere
        intCaractereTemporario = getch();
        
        //Trata o comando
        switch (intCaractereTemporario)
        {
            case 300: //Movimenta lista de encontrados para cima com SETA PARA CIMA
                
                //Realiza o mocimento se possivel
                if (txtEncontrados != NULL && txtEncontrados->txtAnterior != NULL)
                    txtEncontrados = txtEncontrados->txtAnterior;
                
            break;
            case 301: //Movimenta lista de encontrados para baixo com SETA PARA BAIXO
                
                if (txtEncontrados != NULL && txtEncontrados->txtProximo != NULL)
                    txtEncontrados = txtEncontrados->txtProximo;
                
            break;
            case 302: case 303: break; //Não faz nada
            case 6: intComando = -1; break;
            default:
                
                //Adiciona novo caractere digitado
                adicionaCaractere(intCaractereTemporario, chrTexto, TAMANHO_MAXIMO_TEXTO);
                
                //Limpa lista de complementos
                if (txtEncontrados != NULL)
                    limparListaDeTextosEncontrados(&txtEncontrados);
                
                //Busca complementos para o texto que está sendo digitado
                if (chrTexto[0] != '\0')
                    intEncontrados = buscarComplementosDoPrefixo(chrTexto, "\0", &vrtRaiz, &txtEncontrados);
                else
                {
                    txtEncontrados = NULL;
                    intEncontrados = 0;
                }
        }
    }
}

//Gerenciamento dos cadastrosde Textos
void cadastros()
{
    int intOpcaoSelecionada = 0, intComando = 0;
    char *chrPosicao = NULL;
    
    while (intComando != -1)
    {
        //Limpa tela
        system("clear");
        
        //Imprime o titulo do programa
        printf("\n\n\tLpSearch - Dicionario de significados -> Menu -> Cadastros:\n\n");
        
        //Imprime informações
        printf("\t[SETAS] - Posicionar [ENTER] - Confirmar [CTRL + F] - Fechar/Voltar\n\n\n\n");
        
        //Remove cursor atual
        if (chrPosicao != NULL)
            free(chrPosicao);
        
        //Realoca duas vezes a quantidade de opções do menu de memoria para posicionar cursor
        chrPosicao = (char *) malloc(2*(3));
        
        //Trata falha
        if (chrPosicao == NULL)
        {
            printf("\t\tFalha na geração do menu, programa sera fechado!\n\n");
            break;
        }
        
        //Preenche as posições do vetor com espaços em branco
        memset(chrPosicao, ' ', sizeof(chrPosicao));
        
        //Posiciona o cursor
        switch (intOpcaoSelecionada)
        {
            case 0:
                chrPosicao[0] = '[';
                chrPosicao[3] = ']';
                break;
            case 1:
                chrPosicao[1] = '[';
                chrPosicao[4] = ']';
                break;
            case 2:
                chrPosicao[2] = '[';
                chrPosicao[5] = ']';
                break;
        }
        
        //Imprime menu na saida padrão
        printf
        (
            "\t\t%c Adicionar %c\n\n"
            "\t\t%c Excluir %c\n\n"
            "\t\t%c Voltar ao Menu %c\n\n\n\n",
            chrPosicao[0], chrPosicao[3], 
            chrPosicao[1], chrPosicao[4], 
            chrPosicao[2], chrPosicao[5]
        );
        
        //Aguarda o próximo comando
        intComando = getch();
        
        //Trata o comando
        switch (intComando)
        {
            case 300: if (intOpcaoSelecionada > 0) intOpcaoSelecionada--; break;
            case 301: if (intOpcaoSelecionada < 2) intOpcaoSelecionada++; break;
            case 6: intComando = -1; break;
            case 10: 
                switch (intOpcaoSelecionada) 
                {
                    case 0: while(cadastroDeTexto()); break;
                    case 1: while(excluir()); break;
                    case 2: intComando = -1; break;
                }
                break;
        }
    }
}

//Cadastra um Texto e seu significado
int cadastroDeTexto()
{
    int intComando = 0, intCaractereTemporario = 0, intErro = 0;
    struct Texto txtCadastro;
    
    //Limpa o vetor que carrega o texto
    memset(txtCadastro.chrTexto, '\0', sizeof(txtCadastro.chrTexto));
    
    while (intComando != -1)
    {
        //Limpa tela
        system("clear");
        
        //Imprime o titulo do programa
        printf("\n\n\tLpSearch - Dicionario de significados -> Menu -> Cadastro de Texto\n\n");
        
        //Imprime rodapé
        printf("\t[ENTER] - Confirmar [CTRL + F] - Fechar/Voltar\n\n");
        
        //Exibe erro
        switch (intErro)
        {
            case 1: printf("\n\t\tIdentificacao, preenchimento obrigatorio!"); break;
            case 2: printf("\n\t\tIdentificacao informada ja esta em uso!"); break;
        }
        
        //Solicita um identificador
        printf("\n\n\n\n\tDigite o Identificador: \n\n\t\t%s", txtCadastro.chrTexto);
        
        //Aguarda o próximo comando ou caractere
        intCaractereTemporario = getch();
        
        //Trata o comando
        switch (intCaractereTemporario)
        {
            case 300: break; //Seta para cima
            case 301: break; //Seta para baixo
            case 302: case 303: break; //Não faz nada
            case 6: intComando = -1; break; //Saida com CTRL+F
            case 10: //Cadastrar com ENTER
                
                //Reseta erro pro padrão
                intErro = 0;
                
                //Verifica preenchimento
                if (strcmp(txtCadastro.chrTexto, "") == 0)
                {
                    intErro = 1;
                    break;
                }
                    
                //Verifica ambiguidade
                if (existeIdentificadorInformadoNoGrafo(txtCadastro.chrTexto, &vrtRaiz))
                {
                    intErro = 2;
                    break;
                }
                
                //Solicita descrição para o identificador
                if (cadastroDeDescricao(&txtCadastro))
                {
                    //Persiste informações
                    adicionarInformacaoNoDicionario(&txtCadastro);
                    
                    //Adiciona no grafo
                    adicionarTextoNoGrafo(txtCadastro.chrTexto, txtCadastro.chrDescricao, &vrtRaiz);
                    
                    //Verifica se o usuário quer cadastrar mais um texto
                    if (confirmacao("Continuar cadastrando?"))
                        return 1;
                    
                    //Sinaliza encerramento do cadastro
                    intComando = -1;
                }
                
            break;
            default: adicionaCaractere(intCaractereTemporario, txtCadastro.chrTexto, TAMANHO_MAXIMO_TEXTO);
        }
    }
    
    //Encerra
    return 0;
}

int cadastroDeDescricao(struct Texto *txtCadastro)
{
    int intComando = 0, intCaractereTemporario = 0, intErro = 0;
    
    //Limpa o vetor que carrega o texto
    memset(txtCadastro->chrDescricao, '\0', sizeof(txtCadastro->chrDescricao));
    
    while (intComando != -1)
    {
        //Limpa tela
        system("clear");
        
        //Imprime o titulo do programa
        printf("\n\n\tLpSearch - Dicionario de significados -> Menu -> Cadastro de Descrição\n\n");
        
        //Imprime rodapé
        printf("\t[ENTER] - Confirmar [CTRL + F] - Fechar/Voltar\n\n");
        
        //Exibe erro
        switch (intErro)
        {
            case 1: printf("\n\t\tDescricao, preenchimento obrigatorio!"); break;
        }
        
        //Solicita uma Descricao
        printf("\n\n\n\n\tDigite uma descricao para %s: \n\n\t\t%s", txtCadastro->chrTexto, txtCadastro->chrDescricao);
        
        //Aguarda o próximo comando ou caractere
        intCaractereTemporario = getch();
        
        //Trata o comando
        switch (intCaractereTemporario)
        {
            case 300: case 301: case 302: case 303: break; //Não faz nada
            case 6: intComando = -1; //Saida com CTRL+F
            case 10: //Cadastrar com ENTER
                
                //Verifica preenchimento
                if (strcmp(txtCadastro->chrDescricao, "") == 0)
                {
                    intErro = 1;
                    break;
                }
                
                //Encerra com sucesso
                return 1;
                
            default: adicionaCaractere(intCaractereTemporario, txtCadastro->chrDescricao, TAMANHO_MAXIMO_DESCRICAO);
        }
    }
    
    //Encerra sem sucesso
    return 0;
}

//Verifica se o usuario quer continuar cadastrando
int confirmacao(char chrMensagem[])
{
    int intOpcaoSelecionada = 0, intComando = 0;
    char *chrPosicao = NULL;
    
    while (intComando != -1)
    {
        //Limpa tela
        system("clear");
        
        //Imprime o titulo do programa
        printf("\n\n\tLpSearch - Dicionario de significados -> Menu -> Cadastros:\n\n");
        
        //Imprime informações
        printf("\t[SETAS] - Posicionar [ENTER] - Confirmar [CTRL + F] - Fechar/Voltar\n\n\n\n");
        
        //Remove cursor atual
        if (chrPosicao != NULL)
            free(chrPosicao);
        
        //Realoca duas vezes a quantidade de opções do menu de memoria para posicionar cursor
        chrPosicao = (char *) malloc(2*(2));

        //Trata falha
        if (chrPosicao == NULL)
        {
            printf("\t\tFalha na geração do menu, programa sera fechado!\n\n");
            break;
        }
        
        //Preenche as posições do vetor com espaços em branco
        memset(chrPosicao, ' ', sizeof(chrPosicao));
        
        //Posiciona o cursor
        switch (intOpcaoSelecionada)
        {
            case 0:
                chrPosicao[0] = '[';
                chrPosicao[2] = ']';
                break;
            case 1:
                chrPosicao[1] = '[';
                chrPosicao[3] = ']';
                break;
        }
        
        //Imprime menu na saida padrão
        printf
        (
            "\t%s\n\n\n"
            "\t\t%c Sim %c\n\n"
            "\t\t%c Nao %c\n\n",
            chrMensagem,
            chrPosicao[0], chrPosicao[2], 
            chrPosicao[1], chrPosicao[3]
        );
        
        //Aguarda o próximo comando
        intComando = getch();
        
        //Trata o comando
        switch (intComando)
        {
            case 300: if (intOpcaoSelecionada > 0) intOpcaoSelecionada--; break;
            case 301: if (intOpcaoSelecionada < 1) intOpcaoSelecionada++; break;
            case 6: intComando = -1; break;
            case 10: 
                switch (intOpcaoSelecionada) 
                {
                    case 0: return 1;
                    case 1: return 0;
                }
                break;
        }
    }
}

//Exclui um texto e sua descrição do grafo e do dicionario
int excluir()
{
    int intComando = 0, intCaractereTemporario = 0, intErro = 0;
    char chrTexto[TAMANHO_MAXIMO_TEXTO + 1];
    
    //Limpa o vetor que carrega o texto
    memset(chrTexto, '\0', sizeof(chrTexto));
    
    while (intComando != -1)
    {
        //Limpa tela
        system("clear");
        
        //Imprime o titulo do programa
        printf("\n\n\tLpSearch - Dicionario de significados -> Menu -> Exluir\n\n");
        
        //Imprime rodapé
        printf("\t[ENTER] - Confirmar [CTRL + F] - Fechar/Voltar\n\n");
        
        //Exibe erro
        switch (intErro)
        {
            case 1: printf("\n\t\tIdentificacao, preenchimento obrigatorio!"); break;
            case 2: printf("\n\t\tIdentificacao nao encontrada!"); break;
        }
        
        //Solicita um identificador
        printf("\n\n\n\n\tDigite o Identificador: \n\n\t\t%s", chrTexto);
        
        //Aguarda o próximo comando ou caractere
        intCaractereTemporario = getch();
        
        //Trata o comando
        switch (intCaractereTemporario)
        {
            case 300: case 301: case 302: case 303: break; //Não faz nada
            case 6: intComando = -1; break; //Saida com CTRL+F
            case 10: //Cadastrar com ENTER
                
                //Reseta erro pro padrão
                intErro = 0;
                
                //Verifica preenchimento
                if (strcmp(chrTexto, "") == 0)
                {
                    intErro = 1;
                    break;
                }
                 
                //Verifica existencia
                if(!existeIdentificadorInformadoNoGrafo(chrTexto, &vrtRaiz))
                {
                    intErro = 2;
                    break;
                }
                
                //Exclui do dicionario
                excluirInformacaoDoDicionario(chrTexto);
                
                //Exclui do grafo
                excluirTextoDoGrafo(chrTexto, &vrtRaiz);
                
                //Verifica se o usuário quer excluir mais um texto
                if (confirmacao("Continuar exclusoes?"))
                    return 1;
                
                //Sinaliza encerramento do cadastro
                intComando = -1;
            
            break;
            default: adicionaCaractere(intCaractereTemporario, chrTexto, TAMANHO_MAXIMO_TEXTO);
        }
    }
    
    //Encerra
    return 0;
}

//Realiza os tratamentos necessários antes da saida do sistema
void sair()
{
    //Limpa o grafo
    limparGrafo(&vrtRaiz);
}

/**********************************************************************************
 
    FUNÇÕES DO GRAFO
    
***********************************************************************************/

//Cria uma vertice
int prepararVertice(struct Vertice **vertice, char chrLetra, char chrDescricao[], int intFimDePalavra)
{
    //Aloca memoria para vertice
    *vertice = (struct Vertice *) malloc(sizeof(struct Vertice));
    
    //Alimenta suas propriedades
    if (*vertice != NULL)
    {
        (*vertice)->chrLetra        = chrLetra;
        (*vertice)->intFimDePalavra = intFimDePalavra;
        (*vertice)->arestas         = NULL;
        strcpy((*vertice)->chrDescricao, chrDescricao);
        
        //Encerra com sucesso
        return 1;
    }
    
    //Encerra sem sucesso
    return 0;
}

//Adiciona uma aresta entre uma vertice origem e destino
int adicionarAresta(struct Vertice **vrtPai, struct Vertice **vrtFilho)
{
    struct Aresta *aresta, *arsAux;
    
    //Aloca memoria para aresta
    aresta = (struct Aresta *) malloc(sizeof(struct Aresta));
    
    //Se tudo estiver ok
    if (aresta != NULL && *vrtPai != NULL && vrtFilho != NULL)
    {
        
        //Alimenta as propriedades da aresta
        aresta->arsProxima  = NULL;
        aresta->arsAnterior = NULL;
        aresta->vrtDestino  = *vrtFilho;
        
        //Faz a ligação
        if ((*vrtPai)->arestas != NULL)
        {
            //Busca a ultima aresta da lista
            arsAux = (*vrtPai)->arestas;
            while (arsAux->arsProxima != NULL)
                arsAux = arsAux->arsProxima;
            
            //Adiciona a nova aresta
            arsAux->arsProxima = aresta;
            aresta->arsAnterior = arsAux;
        }
        else
            (*vrtPai)->arestas = aresta;
        
        //Encerra com sucesso
        return 1;
    }
    
    //Encerra sem sucesso
    return 0;
}

//Adiciona um texto (palavra ou frase) no grafo
int adicionarTextoNoGrafo(char chrTexto[], char chrDescricao[], struct Vertice **vrtBase)
{
    struct Aresta *arsAux;
    struct Vertice *vrtAux;
    
    //Se chegar ao fim do texto então encerra
    if (chrTexto[0] == '\0')
        return 1;
    
    //Pega lista de arestas do vertice
    arsAux = (*vrtBase)->arestas;
    
    //Procura a primeira letra do texto
    while (arsAux != NULL)
    {
        //Se encontrar então chama recursivamente a função para tratar a próxima letra
        if (arsAux->vrtDestino->chrLetra == chrTexto[0])
        {
            //Verifica se a palvra já está inteira dentro do grafo
            if (chrTexto[1] == '\0')
            {
                //Adiciona descrição
                strcpy(arsAux->vrtDestino->chrDescricao, chrDescricao);
                
                //Marca vertice como contendo fim de palavra
                arsAux->vrtDestino->intFimDePalavra = 1;
            }
            
            //Chama a função recursivamente para a vertice adjacente
            return adicionarTextoNoGrafo(&chrTexto[1], chrDescricao, &(arsAux->vrtDestino));
        }
        
        //Move para próxima aresta da lista
        arsAux = arsAux->arsProxima;
    }
    
    //Caso não encontre a letra, então adiciona nova vertice
    if (prepararVertice(&vrtAux, chrTexto[0], ((chrTexto[1] == '\0') ? chrDescricao : "\0"), ((chrTexto[1] == '\0') ? 1 : 0)))
    {
        //Adiciona ligação até a nova vertice
        adicionarAresta(vrtBase, &vrtAux);
        
        //Chama recursivamente a função para tratar a próxima letra
        return adicionarTextoNoGrafo(&chrTexto[1], chrDescricao, &vrtAux);
    }
    
    //Se chegar aqui encerra retornando falha
    return 0;
}

//Verifica se existe um Texto especifico no grafo
int existeIdentificadorInformadoNoGrafo(char chrTexto[], struct Vertice **vrtBase)
{
    struct Aresta *arsAux;
    
    //Se encontrar o final do grafo intão retorna falha
    if (*vrtBase == NULL)
        return 0;
    
    //Pega a lista de arestas do vertice
    arsAux = (*vrtBase)->arestas;
    
    //Procura a primeira letra do texto
    while (arsAux != NULL)
    {
        //Verifica letra do vertice
        if (arsAux->vrtDestino->chrLetra == chrTexto[0])
            return existeIdentificadorInformadoNoGrafo(&chrTexto[1], &(arsAux->vrtDestino));
        
        //Move para próxima aresta da lista
        arsAux = arsAux->arsProxima;        
    }
    
    //Retorna sucesso se o texto for encontrado
    return (chrTexto[0] == '\0' && (*vrtBase)->intFimDePalavra);
}

//Busca todas as frases que completam o prefixo informado e suas descrições
int buscarComplementosDoPrefixo(char chrTexto[], char chrBuff[], struct Vertice **vrtBase, struct Texto **txtEncontrados)
{
    struct Aresta *arsAux;
    struct Texto **txtAux, *txtTemp;
    char chrAux[TAMANHO_MAXIMO_TEXTO + 1];
    int intPalavrasEncontradas = 0;
    
    //Se o vertice for nulo então retorna
    if (*vrtBase == NULL)
        return 0;
    
    //Armazena texto temporario
    strcpy(chrAux, chrBuff);
    
    //Pega lista de arestas do vertice
    arsAux = (*vrtBase)->arestas;
    
    //Procura a primeira letra do texto
    while (arsAux != NULL)
    {
        //Adiciona novo caractere
        sprintf(chrAux, "%s%c", chrAux, arsAux->vrtDestino->chrLetra);
        
        //Direciona busca do próximo caractere
        if (chrTexto[0] != '\0')
        {
            if (arsAux->vrtDestino->chrLetra == chrTexto[0])
            {   
                intPalavrasEncontradas += buscarComplementosDoPrefixo
                (
                    &chrTexto[1], 
                    chrAux,
                    &(arsAux->vrtDestino),
                    txtEncontrados
                );
            }
        }
        else
            intPalavrasEncontradas += buscarComplementosDoPrefixo("\0", chrAux, &(arsAux->vrtDestino), txtEncontrados);
        
        //Retrocede a sequencia de caracteres
        strcpy(chrAux, chrBuff);
        
        //Move para a próxima aresta da lista
        arsAux = arsAux->arsProxima;
    }
    
    //Adiciona texto encontrado na lista
    if 
    (
        chrTexto[0] == '\0' && 
        (*vrtBase)->intFimDePalavra &&
        adicionarTextoNaLista(txtEncontrados, chrAux, (*vrtBase)->chrDescricao)
    )
        intPalavrasEncontradas++;
    
    //Retorna quantidade de palavras encontradas
    return intPalavrasEncontradas;
}

//Exclui um Texto do grafo atraves de seu identificador
int excluirTextoDoGrafo(char chrTexto[], struct Vertice **vrtBase)
{
    struct Aresta *arsAux, *arsTemp;
    
    //Ao chegar no final do texto
    if (chrTexto[0] == '\0')
    {
        //Remove a marcação de fim de Texto
        (*vrtBase)->intFimDePalavra = 0;
        
        //Remove este caractere (vertice) do grafo
        if ((*vrtBase)->arestas == NULL)
        {   
            //Libera a memoria
            free(*vrtBase);
            *vrtBase = NULL;
            
            //Retorna aviso de exclusão da vertice realizada
            return 1;
        }
        
        //Retorna aviso de exclusão da vertice não realizada
        return 0;
    }
    
    //Pega a lista de arestas 
    arsAux = (*vrtBase)->arestas;
    
    //Percorre a lista de arestas
    while (arsAux != NULL)
    {
        //Verifica letra da vertice destino da aresta e exclui a aresta caso a vertice tenha sido excluida
        if (arsAux->vrtDestino->chrLetra == chrTexto[0] && excluirTextoDoGrafo(&chrTexto[1], &(arsAux->vrtDestino)))            
        {
            //Armazena aresta atual temporariamente
            arsTemp = arsAux;
            
            //Altera ligação na lista
            if (arsAux->arsAnterior == NULL)
                (*vrtBase)->arestas = arsAux->arsProxima;
            else
                (arsAux->arsAnterior)->arsProxima = arsAux->arsProxima;
            
            //Move para a próxima aresta da lista
            arsAux = arsAux->arsProxima;
            
            //Libera memória da aresta atual
            free(arsTemp);
            arsTemp = NULL;
        }
        else //Apenas move para próxima aresta da lista
            arsAux = arsAux->arsProxima;
    }
    
    //Exclui esta letra (vertice) do grafo
    if (!((*vrtBase)->intFimDePalavra) && (*vrtBase)->arestas == NULL && *vrtBase != vrtRaiz)
    {
        //Libera a memória
        free(*vrtBase);
        *vrtBase = NULL;
        
        //Retorna aviso de exclusão da vertice realizada
        return 1;
    }
    
    //Retorna aviso de exclusão da vertice não realizada
    return 0;
}

//Limpa todos os dados do grafo, deixando ele branco
void limparGrafo(struct Vertice **vrtBase)
{
    struct Aresta **arsAux, **arsTemp;
    
    if (*vrtBase != NULL)
    {       
        //Pega a lista de arestas do vertice
        arsAux = &((*vrtBase)->arestas);
        
        //Percorre a lista de arestas
        while (*arsAux != NULL)
        {
            //Armazena posição atual na lista
            arsTemp = arsAux;
            
            //Entra na vertice destino da aresta atual
            limparGrafo(&((*arsAux)->vrtDestino));
            
            //Move para próxima aresta da lista
            arsAux = &((*arsAux)->arsProxima);
            
            //Exclui aresta
            free((*arsTemp));
            *arsTemp = NULL;
        }
        
        //Exclui a vertice
        free(*vrtBase);
        *vrtBase = NULL;
    }
}

/**********************************************************************************
 
    FUNÇÕES DA LISTA DE TEXTOS
    
***********************************************************************************/

//Prepara Texto
int prepararTexto(struct Texto **texto, char chrTexto[], char chrDescricao[])
{
    
    //Aloca memoria para texto
    *texto = (struct Texto *) malloc(sizeof(struct Texto));
    
    //Alimenta suas propriedades
    if (*texto != NULL)
    {
        strcpy((*texto)->chrTexto, chrTexto);
        strcpy((*texto)->chrDescricao, chrDescricao);
        (*texto)->txtProximo  = NULL;
        (*texto)->txtAnterior = NULL;
        
        //Encerra com sucesso
        return 1;
    }
    
    //Encerra sem sucesso
    return 0;
    
}

//Limpar a lista de textos encontrados
void limparListaDeTextosEncontrados(struct Texto **txtEncontrados)
{
    if (*txtEncontrados != NULL)
    {   
        //Percorre até o último texto da lista
        limparListaDeTextosEncontrados(&((*txtEncontrados)->txtProximo));
        
        //Exclui o texto
        free(*txtEncontrados);
        *txtEncontrados = NULL;
    }
}

//Adiciona um novo texto e sua descrição na lista
int adicionarTextoNaLista(struct Texto **txtEncontrados, char chrAux[], char chrDescricao[])
{
    struct Texto **txtAux, *txtTemp;
    
    //Pega lista de textos encontrados
    txtAux = txtEncontrados;
    
    //Aloca espaço para o novo texto
    if (*txtAux != NULL)
    {
        //Move até o último texto atual da lista
        while ((*txtAux)->txtProximo != NULL)
            txtAux = &((*txtAux)->txtProximo);
        
        //Adiciona o novo texto
        if (prepararTexto(&txtTemp, chrAux, chrDescricao))
        {
            (*txtAux)->txtProximo = txtTemp;
            txtTemp->txtAnterior = (*txtAux);
            
            //retorna sucesso
            return 1;
        }
    }
    else if (prepararTexto(txtAux, chrAux, chrDescricao))
        return 1;
    
    //Retorna falha na inserção do novo texto
    return 0;
}

/**********************************************************************************
 
    FUNÇÕES PARA MANIPULAÇÃO DE ARQUIVOS
    
***********************************************************************************/

//Gravar uma nova informação no arquivo dicionario
int adicionarInformacaoNoDicionario(struct Texto *txtInformacoes)
{
    FILE *arquivo;
    
    //Abre e/ou cria arquivo
    arquivo = fopen("Dicionario.lp", "a");
    
    //Adiciona as informações ao final do arquivo
    if (arquivo != NULL)
    {
        //Escreve no arquivo os dados
        fwrite(txtInformacoes, sizeof(struct Texto) - (sizeof(struct Texto *) * 2), 1, arquivo);
        
        //Fecha o arquivo
        fclose(arquivo);
        
        //Retorna sucesso
        return 1;
    }
    
    //Retorna falha
    return 0;
}

//Carrega as informações do arquivo dicionario para a estrutura de dados
void atualizarGrafoComDadosDoDicionario()
{
    FILE *arquivo;
    struct Texto txtAux;
    
    //Abre o arquivo
    arquivo = fopen("Dicionario.lp", "r");
    
    //Adiciona as informações do dicionario no grafo
    if (arquivo != NULL)
    {
        //Percorre todas as informações e as adiciona no grafo
        while ((fread(&txtAux, sizeof(struct Texto) - (sizeof(struct Texto *) * 2), 1, arquivo)) > 0)
            adicionarTextoNoGrafo(txtAux.chrTexto, txtAux.chrDescricao, &vrtRaiz);
        
        //Fecha o arquivo
        fclose(arquivo);
    }
}

//Exclui uma informação do dicionario
void excluirInformacaoDoDicionario(char chrTexto[])
{
    FILE *arquivo;
    struct Texto *txtTextos = NULL, *txtTemp, *txtPosicao, txtAux;
    
    //Abre arquivo original
    arquivo = fopen("Dicionario.lp", "r");
    
    //Copia todo o conteudo do arquivo para a memória
    if (arquivo != NULL)
    {
        //Percorre o arquivo buscando as informações
        while ((fread(&txtAux, sizeof(struct Texto) - (sizeof(struct Texto *) * 2), 1, arquivo)) > 0)
        {
            //Configura lista e adiciona os textos encontrados nela
            if (strcmp(txtAux.chrTexto, chrTexto) != 0)
            {
                if (txtTextos == NULL)
                    prepararTexto(&txtTextos, txtAux.chrTexto, txtAux.chrDescricao);
                else if (prepararTexto(&txtTemp, txtAux.chrTexto, txtAux.chrDescricao))
                    {
                        //Posiciona no inicio da lista
                        txtPosicao = txtTextos;
                        
                        //Percorre até o última nó da lista
                        while (txtPosicao->txtProximo != NULL)
                            txtPosicao = txtPosicao->txtProximo;
                        
                        //Adiciona novo nó
                        txtPosicao->txtProximo = txtTemp;
                    }
            }
            
            //Desaponta
            txtTemp = NULL;
        }
        
        //Fecha o arquivo
        fclose(arquivo);
        
        //Sobrescreve o arquivo original com um novo
        arquivo = fopen("Dicionario.lp", "w");
        
        //Fecha o arquivo
        fclose(arquivo);
        
        //Posiciona no inicio da lista de Textos
        txtPosicao = txtTextos;
        
        //Percorre a lista copiando tudo para o novo Dicionario
        while (txtPosicao != NULL)
        {
            //Adiciona no dicionario
            adicionarInformacaoNoDicionario(txtPosicao);
            
            //Move para o próximo nó
            txtPosicao = txtPosicao->txtProximo;
        }
        
        //Desaloca a memória da lista de Textos
        while (txtTextos != NULL)
        {   
            //Posiciona no inicio da lista
            txtTemp = txtTextos;
            
            //Lista passa a ter um novo nó inicial
            txtTextos = txtTextos->txtProximo;
            
            //Remove o nó inicial atual
            free(txtTemp);
        }
        
    }
}

/**********************************************************************************
 
    FUNÇÕES GENÉRICAS
    
***********************************************************************************/

//Trata um caractere e adiciona como próximo caractere de um vetor
void adicionaCaractere(int intCaractereTemporario, char chrFrase[], int intTamanhoDoTexto)
{
    int intPosicao = 0;
    
    //Posiciona na proxima posição do vetor
    while (chrFrase[intPosicao] != '\0' && intPosicao < intTamanhoDoTexto)
        intPosicao ++;
    
    //Trata o caracter digitado
    if ((intCaractereTemporario == 127 || intCaractereTemporario == 8) && intPosicao > 0)
        intPosicao--;
    else if (intPosicao < intTamanhoDoTexto)
    {
        if (intCaractereTemporario > 31 && intCaractereTemporario < 200 && intCaractereTemporario != 126 && intCaractereTemporario != 127 && intCaractereTemporario != 8)
        {
            chrFrase[intPosicao] = intCaractereTemporario;
            intPosicao++;
        }
    }
    
    chrFrase[intPosicao] = '\0';
}

//função getch para captura de teclas
int getch()
{
    int buf=0;
    struct termios old={0};
    
    //Limpa a saida padrão
    fflush(stdout);
    
    //Busca dados do terminal
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    
    //Configura flags
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    
    //Atribui novos dados ao terminal
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    
    //Lê o caractere
    if(read(0,&buf,1)<0)
        perror("read()");
    
    //Altera flags
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    
    //Atribui novas flags ao terminal
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    
    //Trata tecla de escape
    if (buf == 27)
    {
        buf = fgetc(stdin);
        {
            switch(buf)
            {
                case 91:
                    buf = fgetc(stdin);
                    switch (buf)
                    {
                        case 65: buf = 300; break; //Seta para cima 
                        case 66: buf = 301; break; //Seta para baixo
                        case 67: buf = 302; break; //Seta para direita
                        case 68: buf = 303; break; //Seta para esquerda
                    }
                    break;
            }
        }
    }
    
    //Retorna o caractere
    return buf;
}