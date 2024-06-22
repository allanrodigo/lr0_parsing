#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char action; // 's' for shift, 'r' for reduce, 'a' for accept
    int state;
} Action;

typedef struct {
    int state;
    char symbol;
} StackItem;

void parse(const char *input);
int get_non_terminal_index(char symbol);
int get_symbol_index(char symbol);

#endif // PARSER_H
