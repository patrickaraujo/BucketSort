#include <stdio.h>
#include <stdlib.h>

#define TAM 5  // Tamanho máximo de elementos em cada balde

// Estrutura do balde
struct balde {
    int qtd;
    int valores[TAM];
};

// Função auxiliar: Insertion Sort
void insertionSort(int *V, int N) {
    int i, j, aux;
    for (i = 1; i < N; i++) {
        aux = V[i];
        for (j = i; (j > 0) && (aux < V[j - 1]); j--) {
            V[j] = V[j - 1];
        }
        V[j] = aux;
    }
}

// Função principal: Bucket Sort
void bucketSort(int *V, int N) {
    int i, j, maior, menor, nroBaldes, pos;
    struct balde *bd;

    // Encontra maior e menor valor do vetor
    maior = menor = V[0];
    for (i = 1; i < N; i++) {
        if (V[i] > maior) maior = V[i];
        if (V[i] < menor) menor = V[i];
    }

    // Calcula número de baldes e aloca memória
    nroBaldes = (maior - menor) / TAM + 1;
    bd = (struct balde *) malloc(nroBaldes * sizeof(struct balde));

    // Inicializa os baldes
    for (i = 0; i < nroBaldes; i++)
        bd[i].qtd = 0;

    // Distribui os elementos nos baldes
    for (i = 0; i < N; i++) {
        pos = (V[i] - menor) / TAM;
        bd[pos].valores[bd[pos].qtd] = V[i];
        bd[pos].qtd++;
    }

    // Ordena os baldes e copia para o vetor original
    pos = 0;
    for (i = 0; i < nroBaldes; i++) {
        insertionSort(bd[i].valores, bd[i].qtd);
        for (j = 0; j < bd[i].qtd; j++) {
            V[pos] = bd[i].valores[j];
            pos++;
        }
    }

    free(bd);
}

// Função para imprimir o vetor
void imprimeVetor(int *V, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
}

// Exemplo de uso
int main() {
    int vetor[] = {23, 4, 67, -8, 21, 12, 5, 9, 3, 45};
    int N = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original:\n");
    imprimeVetor(vetor, N);

    bucketSort(vetor, N);

    printf("Vetor ordenado com Bucket Sort:\n");
    imprimeVetor(vetor, N);

    return 0;
}
