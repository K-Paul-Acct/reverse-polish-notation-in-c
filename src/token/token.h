#ifndef SRC_TOKEN_TOKEN_H_
#define SRC_TOKEN_TOKEN_H_

#define NUMBER 0
#define VARIABLE 1
#define FUNCTION 2
#define OPERATOR 3
#define PARENTHESIS 4

#define LEFT 5
#define RIGHT 6

#define NEGATE '~'
#define SIN '@'
#define COS '#'
#define TAN '$'
#define COT '%'
#define ARCSIN '^'
#define ARCCOS '&'
#define ARCTAN '*'
#define ARCCOT '('
#define EXP ')'
#define LN '-'
#define SQRT '_'
#define FACT '!'

typedef struct token {
    int type;
    union {
        double value;
        char symbol;
    };
} t_token;

t_token *token_create_number(double value);
t_token *token_create_variable(char symbol);
t_token *token_create_function(char symbol);
t_token *token_create_operator(char symbol);
t_token *token_create_parenthesis(char symbol);
void token_destroy(t_token *token);

int is_operator(char c);
int operator_get_associativity(t_token *self);
int operator_compare_precedence(t_token *operator_1, t_token *operator_2);
t_token *operator_apply_unary(t_token *self, t_token *operand);
t_token *operator_apply_binary(t_token *self, t_token *operand_1, t_token *operand_2);

#endif  // SRC_TOKEN_TOKEN_H_
