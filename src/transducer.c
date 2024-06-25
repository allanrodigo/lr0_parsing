
#include <stdio.h>
#include <string.h>
#include "transducer.h"


// Função para verificar se o caractere pertence ao alfabeto permitido
int is_valid_char(char c) {
    // Verifica se o caractere é uma letra minúscula, '+' ou '(', ')' ou espaço
    return (c >= 'a' && c <= 'z') || c == '+' || c == '(' || c == ')' || c == ' ';
}

// Função para processar a cadeia de entrada
void process_input(const char *input, char *output) {
    int i = 0, j = 0;               // Inicializa índices para percorrer input e output
    int in_alpha_sequence = 0;      // Flag para indicar se estamos em uma sequência de letras alfabéticas

    // Itera sobre cada caractere da entrada até encontrar o terminador de string
    while (input[i] != '\0') {
        printf("Processando caractere: %c (indice %d)\n", input[i], i);
        // Verifica se o caractere atual é válido
        if (!is_valid_char(input[i])) {
            // Se não for válido, imprime "<REJEITAR>" e sinaliza a rejeição com uma string vazia
            printf("Caractere invalido encontrado: %c\n", input[i]);
            printf("\n<REJEITAR>\n\n");
            output[0] = '\0'; // Sinaliza rejeição
            return;
        }

        // Ignora espaços na entrada
        if (input[i] == ' ') {
            i++;            // Move para o próximo caractere
            continue;       // Volta ao início do loop
        }

        // Se o caractere for uma letra minúscula
        if (input[i] >= 'a' && input[i] <= 'z') {
            // Se não estivermos em uma sequência alfabética, insere 'x' na saída
            if (!in_alpha_sequence) {
                printf("Inicio de uma sequencia alfabetica detectada (indice %d)\n", i);
                output[j++] = 'x';
                in_alpha_sequence = 1;  // Marca que estamos em uma sequência alfabética
            }
        } else {
            // Se não for uma letra minúscula, copia o caractere para a saída
            printf("Caractere nao alfabetico copiado para a saida: %c (indice %d)\n", input[i], i);
            output[j++] = input[i];
            in_alpha_sequence = 0;  // Reseta a flag de sequência alfabética
        }
        i++;    // Move para o próximo caractere da entrada
    }
    output[j] = '\0';  // Finaliza a string de saída
    printf("Processamento concluido. Saida: %s\n", output);
}