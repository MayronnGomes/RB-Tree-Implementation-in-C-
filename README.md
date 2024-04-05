<h1>RB Tree Implementation in C</h1>

Este é um exemplo de implementação de uma Árvore Rubro-Negra em C. A Árvore Rubro-Negra é uma árvore de busca binária balanceada, onde cada nó possui uma cor (vermelho ou preto) e segue algumas propriedades para manter o balanceamento e garantir a eficiência das operações de inserção, remoção e busca.

<h2>Estrutura de Dados</h2>

O código contém a seguinte estrutura de dados para os nós da Árvore Rubro-Negra:
```
typedef struct No{
    int chave;
    char cor;
    struct No *pai, *esq, *dir;
}no;
```

- chave: Valor inteiro armazenado no nó.
- cor: Cor do nó (vermelho 'R' ou preto 'N').
- pai: Ponteiro para o nó pai.
- esq: Ponteiro para o filho esquerdo do nó.
- dir: Ponteiro para o filho direito do nó.

<h2>Funções Principais</h2>

- **void InserirRN(int chave, no ptraiz) :
Esta função insere um novo elemento na Árvore Rubro-Negra.

- **void RemoverRN(int chave, no ptraiz) :
Esta função remove um elemento da Árvore Rubro-Negra.

- no Buscar(int chave, no pt) :
Esta função busca um elemento na Árvore Rubro-Negra.

- **void E_RN(no *x, bool *e_RN)** :
Esta função verifica se a árvore é uma Árvore RB válida.

<h2>Compilação e Execução</h2>

Para compilar o código, você pode usar um compilador C como o GCC:
```
gcc main.c -o arvore_rubro_negra
```

Em seguida, execute o programa:
```
./arvore_rubro_negra
```
O programa contém testes automáticos para inserção, remoção e verificação da propriedade da Árvore Rubro-Negra.

<h2>Notas</h2>

- Este código foi testado com chaves aleatórias para demonstrar o funcionamento da Árvore Rubro-Negra.
- Certifique-se de ter um ambiente de desenvolvimento C configurado para compilar e executar o código.
