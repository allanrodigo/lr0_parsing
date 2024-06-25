#include <stdio.h>
#include <string.h>
#include "parser.h"

#define NUM_STATES 15   // Define o número de estados na tabela LR(0)
#define NUM_SYMBOLS 7   // Define o número de símbolos na tabela LR(0)
#define STACK_SIZE 100  // Define o tamanho da pilha


// Declara a tabela LR(0) com ações e estados correspondentes
Action lr_table[NUM_STATES][NUM_SYMBOLS] = {
    //    (        )        x        +        $        E        S
    {{'s', 2}, {' ', 0}, {'s', 3}, {' ', 0}, {' ', 0}, {' ', 0}, {' ', 1}}, // Estado 0
    {{' ', 0}, {' ', 0}, {' ', 0}, {'s', 9}, {'a', 0}, {' ', 0}, {' ', 0}}, // Estado 1 
    {{' ', 0}, {' ', 0}, {'s', 3}, {' ', 0}, {' ', 0}, {' ', 4}, {' ', 5}}, // Estado 2
    {{'r', 2}, {'r', 2}, {'r', 2}, {'r', 2}, {'r', 2}, {' ', 0}, {' ', 0}}, // Estado 3
    {{' ', 0}, {'s', 6}, {' ', 0}, {'s', 9}, {' ', 0}, {' ', 0}, {' ', 0}}, // Estado 4
    {{'r', 3}, {'r', 3}, {'r', 3}, {'r', 3}, {'r', 3}, {' ', 0}, {' ', 0}}, // Estado 5 
    {{'r', 1}, {'r', 1}, {'r', 1}, {'r', 1}, {'r', 1}, {' ', 0}, {' ', 0}}, // Estado 6
    {{' ', 0}, {'r', 3}, {' ', 0}, {' ', 0}, {' ', 0}, {' ', 0}, {' ', 8}}, // Estado 7
    {{'r', 4}, {'r', 4}, {'r', 4}, {'r', 4}, {'r', 4}, {' ', 0}, {' ', 0}},  // Estado 8 
    {{' ', 0}, {' ', 0}, {'s', 3}, {' ', 0}, {' ', 0}, {' ', 0}, {' ', 10}}, // Estado 9 
    {{'r', 4}, {'r', 4}, {'r', 4}, {'r', 4}, {'a', 1}, {' ', 0}, {' ', 0}} // Estado 10 
};

// Função para obter o índice do símbolo na tabela
int get_symbol_index(char symbol) {
    switch (symbol) {
        case '(': return 0;
        case ')': return 1;
        case 'x': return 2;
        case '+': return 3;
        case '$': return 4;
        default: return -1;
    }
}

// Função para obter o índice do não-terminal na tabela
int get_non_terminal_index(char symbol) {
    switch (symbol) {
        case 'E': return 5;
        case 'S': return 6;
        default: return -1;  // Retorna -1 para não-terminais inválidos
    }
}

// Função para verificar se a cadeia pertence à linguagem usando o analisador LR(0)
void parse(const char* input) {
    StackItem stack[STACK_SIZE]; // Declara a pilha
    int top = 0;                 // Inicializa o topo da pilha
    stack[top].state = 0;        // Estado inicial é 0
    stack[top].symbol = '$';     // Símbolo inicial é $

    int i = 0;                   // Índice para percorrer a string de entrada
    char current_symbol = input[i]; // Símbolo atual é o primeiro da entrada

    printf("Iniciando analise sintatica...\n");
    printf("Entrada: %s\n", input);

    while (1) {
        int state = stack[top].state;  // Estado atual do topo da pilha
        int symbol_index = get_symbol_index(current_symbol); // Índice do símbolo atual
        if (symbol_index == -1) {
            printf("Simbolo invalido: %c\n", current_symbol);
            printf("1. <REJEITAR>\n");
            return;
        }
        printf("Estado atual: %d, Simbolo atual: %c, Indice do simbolo: %d\n", state, current_symbol, symbol_index);
        Action action = lr_table[state][symbol_index]; // Obtém a ação da tabela LR(0) para o estado e símbolo atuais

        if (action.action == 's') {
            // Ação de shift: empilha o novo estado e símbolo, avança na entrada
            printf("Acao: shift, Proximo estado: %d\n", action.state);
            top++;
            stack[top].state = action.state;
            stack[top].symbol = current_symbol;
            i++;
            current_symbol = input[i];
        } else if (action.action == 'r') {
            // Ação de reduce: desempilha conforme a regra e empilha o não-terminal correspondente
            printf("Acao: reduce, Regra: %d\n", action.state);
            int num_pop;
            char non_terminal;
            switch (action.state) {
                case 1: num_pop = 3; non_terminal = 'S'; break; // Regra S → (E)
                case 2: num_pop = 1; non_terminal = 'S'; break; // Regra S → x
                case 3: num_pop = 1; non_terminal = 'E'; break; // Regra E → S
                case 4: num_pop = 5; non_terminal = 'E'; break; // Regra E → E + S
                default: num_pop = 0; non_terminal = ' '; break;
            }
            printf("Desempilhando %d simbolos, Empilhando nao-terminal: %c\n", num_pop, non_terminal);
            top -= num_pop; // Desempilha conforme a quantidade de símbolos na regra
            int goto_index = get_non_terminal_index(non_terminal); // Obtém o índice do não-terminal
            int goto_state = lr_table[stack[top].state][goto_index].state; // Estado de destino após a redução
            top++;
            stack[top].state = goto_state; // Empilha o novo estado
            stack[top].symbol = non_terminal; // Empilha o não-terminal
        } else if (action.action == 'a') {
            // Ação de accept: a entrada é aceita
            printf("Acao: accept\n");
            printf("\n\nString is accepted.\n");
            return;
        } else {
            // Qualquer outra ação: rejeita a entrada
            printf("Acao: erro\n");
            printf("2. <REJEITAR>\n");
            return;
        }
    }
}