#include <stdio.h>
#include <string.h>
#include "transducer.h"
#include "parser.h"


int main() {
    char input[100];            // Declaração de um array de caracteres para armazenar a entrada do usuário
    char processed_input[100];  // Declaração de um array de caracteres para armazenar a entrada processada

    // Solicita ao usuário para digitar uma cadeia de entrada
    printf("Digite a cadeia de entrada: ");
    fgets(input, 100, stdin);   // Lê a entrada do usuário (até 100 caracteres) e armazena no array 'input'

    // Remove o caractere de nova linha ('\n') que o fgets adiciona no final da entrada
    input[strcspn(input, "\n")] = '\0';

    // Processa a entrada para remover espaços e substituir letras minúsculas por 'x'
    process_input(input, processed_input);

    // Se a entrada processada for válida (não vazia), continua com o parsing
    if (processed_input[0] != '\0') {
        // Adiciona um marcador de fim ('$') no final da entrada processada
        strcat(processed_input, "$");
        // Chama a função de parsing com a entrada processada
        parse(processed_input);
    }

    return 0; // Termina o programa com sucesso
}