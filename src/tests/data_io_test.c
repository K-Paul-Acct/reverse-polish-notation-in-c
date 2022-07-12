#include <stdio.h>
#include "../data_io/data_io.h"
#include "../token/token.h"
#include "../data_structures/list.h"

void tokenize_input_test();
void scan_number_test();
void scan_function_test();

int main() {
    tokenize_input_test();
    // scan_number_test();
    return 0;
}

void tokenize_input_test() {
    t_list *tokens = tokenize_input();
    if (tokens != NULL) {
        print_tokens(tokens);
        list_destroy(tokens);
    } else {
        printf("Error: tokenize_input() returned NULL\n");
    }
}

void scan_number_test() {
    char c = getchar();
    t_token *token = scan_number(&c);
    if (token != NULL) {
        printf("scan_number() returned token with value %lf\n", token->value);
        token_destroy(token);
    } else {
        printf("Error: scan_number() returned NULL\n");
    }
}
