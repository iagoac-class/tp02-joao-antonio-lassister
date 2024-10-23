#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui
// Estrutura de um nó da árvore binária
struct No_bi {
    int valor;
    struct No_bi *esquerda;
    struct No_bi *direita;
};
// Estrutura de um nó da árvore AVL
struct No_avl
{
    int valor;
    struct No_avl *esquerda;
    struct No_avl *direita;
    int altura;
};

// Funções árvore binária
struct No_bi* novoNo(int valor);
struct No_bi* inserir(struct No_bi* no, int valor);
struct No_bi* noValorMinimo(struct No_bi* no);
struct No_bi* remover(struct No_bi* raiz, int valor);

// Funções árvore AVL
int altura(struct No_avl *N);
int maximo(int a, int b);
struct No_avl* novoNo_AVL(int valor);
struct No_avl *girarDireita(struct No_avl *y);
struct No_avl *girarEsquerda(struct No_avl *x);
int obterEquilibrio(struct No_avl *N);
struct No_avl* inserir_AVL(struct No_avl* no, int valor);
struct No_avl * noValorMinimo_AVL(struct No_avl* no);
struct No_avl* remover_AVL(struct No_avl* raiz, int valor);

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES