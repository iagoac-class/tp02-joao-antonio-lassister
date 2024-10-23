#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

// Funções árvore não balanceada
// Função para criar um novo nó
struct No_bi* novoNo(int valor) {
    struct No_bi* no = malloc(sizeof(struct No_bi));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Função para inserir um nó na árvore binária
struct No_bi* inserir(struct No_bi* no, int valor) {
    // Realiza a inserção padrão
    if (no == NULL)
        return novoNo(valor);

    if (valor < no->valor)
        no->esquerda = inserir(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = inserir(no->direita, valor);

    return no;
}

// Função para encontrar o menor nó da árvore
struct No_bi* noValorMinimo(struct No_bi* no) {
    struct No_bi* atual = no;
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Função para remover um nó
struct No_bi* remover(struct No_bi* raiz, int valor) {
    if (raiz == NULL)
        return raiz;

    if (valor < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = remover(raiz->direita, valor);
    else {
        // Nó com um ou nenhum filho
        if (raiz->esquerda == NULL) {
            struct No_bi* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            struct No_bi* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos
        struct No_bi* temp = noValorMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }

    return raiz;
}

// Funções árvore balanceada
// Função para obter a altura da árvore
int altura(struct No_avl *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

// Função para obter o máximo de dois inteiros
int maximo(int a, int b)
{
    return (a > b)? a : b;
}

// Função para criar um novo nó
struct No_avl* novoNo_AVL(int valor)
{
    struct No_avl* no = malloc(sizeof(struct No_avl));
    no->valor   = valor;
    no->esquerda = NULL;
    no->direita  = NULL;
    no->altura = 1;
    return(no);
}

// Função para rotacionar à direita
struct No_avl *girarDireita(struct No_avl *y)
{
    struct No_avl *x = y->esquerda;
    struct No_avl *T2 = x->direita;

    // Realizar a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualizar as alturas
    y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;

    // Retornar nova raiz
    return x;
}

// Função para rotacionar à esquerda
struct No_avl *girarEsquerda(struct No_avl *x)
{
    struct No_avl *y = x->direita;
    struct No_avl *T2 = y->esquerda;

    // Realizar a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualizar as alturas
    x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;

    // Retornar nova raiz
    return y;
}

// Obter fator de equilíbrio do nó N
int obterEquilibrio(struct No_avl *N)
{
    if (N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita);
}

// Função para inserir um nó
struct No_avl* inserir_AVL(struct No_avl* no, int valor)
{
    // Realiza a inserção padrão
    if (no == NULL)
        return(novoNo_AVL(valor));

    if (valor < no->valor)
        no->esquerda  = inserir_AVL(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = inserir_AVL(no->direita, valor);
    else
        return no;

    // Atualiza a altura
    no->altura = 1 + maximo(altura(no->esquerda), altura(no->direita));

    // Verifica o equilíbrio após a inserção
    int equilibrio = obterEquilibrio(no);

    // Se este nó se tornar desequilibrado, então há 4 casos

    // Caso Esquerda Esquerda
    if (equilibrio > 1 && valor < no->esquerda->valor)
        return girarDireita(no);

    // Caso Direita Direita
    if (equilibrio < -1 && valor > no->direita->valor)
        return girarEsquerda(no);

    // Caso Esquerda Direita
    if (equilibrio > 1 && valor > no->esquerda->valor)
    {
        no->esquerda =  girarEsquerda(no->esquerda);
        return girarDireita(no);
    }

    // Caso Direita Esquerda
    if (equilibrio < -1 && valor < no->direita->valor)
    {
        no->direita = girarDireita(no->direita);
        return girarEsquerda(no);
    }

    return no;
}

// Função para encontrar menor nó da árvore
struct No_avl * noValorMinimo_AVL(struct No_avl* no)
{
    struct No_avl* atual = no;

    while (atual->esquerda != NULL)
        atual = atual->esquerda;

    return atual;
}

// Função para remover um nó
struct No_avl* remover_AVL(struct No_avl* raiz, int valor)
{
    // Realiza a remoção padrão

    if (raiz == NULL)
        return raiz;

    if (valor < raiz->valor)
        raiz->esquerda = remover_AVL(raiz->esquerda, valor);

    else if (valor > raiz->valor)
        raiz->direita = remover_AVL(raiz->direita, valor);

    else
    {
        // Nó com um ou nenhum filho
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL))
        {
            struct No_avl *temp = raiz->esquerda ? raiz->esquerda :
                                                 raiz->direita;

            // Caso sem filhos
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else // Caso com um filho
                *raiz = *temp;
            free(temp);
        }
        else
        {
            // Nó com dois filhos
            struct No_avl* temp = noValorMinimo_AVL(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = remover_AVL(raiz->direita, temp->valor);
        }
    }

    // Se a árvore tinha apenas um nó, então retorna
    if (raiz == NULL)
        return raiz;

    // Atualiza a altura
    raiz->altura = 1 + maximo(altura(raiz->esquerda), altura(raiz->direita));

    // Verifica o equilíbrio após a remoção
    int equilibrio = obterEquilibrio(raiz);

    // Se este nó se tornar desequilibrado, então há 4 casos

    // Caso Esquerda Esquerda
    if (equilibrio > 1 && obterEquilibrio(raiz->esquerda) >= 0)
        return girarDireita(raiz);

    // Caso Esquerda Direita
    if (equilibrio > 1 && obterEquilibrio(raiz->esquerda) < 0)
    {
        raiz->esquerda =  girarEsquerda(raiz->esquerda);
        return girarDireita(raiz);
    }

    // Caso Direita Direita
    if (equilibrio < -1 && obterEquilibrio(raiz->direita) <= 0)
        return girarEsquerda(raiz);

    // Caso Direita Esquerda
    if (equilibrio < -1 && obterEquilibrio(raiz->direita) > 0)
    {
        raiz->direita = girarDireita(raiz->direita);
        return girarEsquerda(raiz);
    }

    return raiz;
}

double arvore_binaria(int instancia_num) {
    double tempo = 0;
    char caminho[20], operacao;
    int valor;
    struct No_bi *raiz = NULL;

    snprintf(caminho, sizeof(caminho), "instancias/%d.txt", instancia_num);
    FILE *file = fopen(caminho, "r");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    while (fscanf(file, "%c %d", &operacao, &valor) != EOF)
    {
        clock_t begin, end;
        switch (operacao)
        {
        case 'I':
            begin = clock();
            raiz = inserir(raiz, valor);
            end = clock();
            break;

        case 'R':
            begin = clock();
            raiz = remover(raiz, valor);
            end = clock();
            break;
        }
        tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    }

    fclose(file);

    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    return (tempo);
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    char caminho[20], operacao;
    int valor;
    struct No_avl *raiz = NULL;

    snprintf(caminho, sizeof(caminho), "instancias/%d.txt", instancia_num);
    FILE *file = fopen(caminho, "r");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    while (fscanf(file, "%c %d", &operacao, &valor) != EOF)
    {
        clock_t begin, end;
        switch (operacao)
        {
        case 'I':
            begin = clock();
            raiz = inserir_AVL(raiz, valor);
            end = clock();
            break;

        case 'R':
            begin = clock();
            raiz = remover_AVL(raiz, valor);
            end = clock();
            break;
        }
        tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    }

    fclose(file);

    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    return (tempo);
}


int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);

    

    
    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}