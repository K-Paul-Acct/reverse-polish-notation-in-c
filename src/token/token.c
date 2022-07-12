#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "token.h"
#include "../algorithms/algorithms.h"

t_token *token_create() {
    return (t_token *)malloc(sizeof(t_token));
}

t_token *token_create_number(double value) {
    t_token *token = token_create();
    token->type = NUMBER;
    token->value = value;
    return token;
}

t_token *token_create_variable(char symbol) {
    t_token *token = token_create();
    token->type = VARIABLE;
    token->symbol = symbol;
    return token;
}

t_token *token_create_function(char symbol) {
    t_token *token = token_create();
    token->type = FUNCTION;
    token->symbol = symbol;
    return token;
}

t_token *token_create_operator(char symbol) {
    t_token *token = token_create();
    token->type = OPERATOR;
    token->symbol = symbol;
    return token;
}

t_token *token_create_parenthesis(char symbol) {
    t_token *token = token_create();
    token->type = PARENTHESIS;
    token->symbol = symbol;
    return token;
}

void token_destroy(t_token *token) {
    free(token);
}

int is_operator(char c) {
    return strchr("+-*/^", c) != NULL;
}

int operator_get_associativity(t_token *self) {
    int associativity = LEFT;
    if (self->symbol == '^') {
        associativity = RIGHT;
    }
    return associativity;
}

int operator_get_precedence(t_token *operator) {
    int presedence = 8;
    if (operator->type == PARENTHESIS) {
        presedence = 0;
    } else if (operator->type == FUNCTION) {
        presedence = 1;
    } else if (operator->symbol == '^') {
        presedence = 2;
    } else if (operator->symbol == '*' || operator->symbol == '/') {
        presedence = 3;
    } else if (operator->symbol == '+' || operator->symbol == '-') {
        presedence = 4;
    }
    return presedence;
}

int operator_compare_precedence(t_token *operator_1, t_token *operator_2) {
    return operator_get_precedence(operator_2) - operator_get_precedence(operator_1);
}

t_token *operator_apply_unary(t_token *self, t_token *operand) {
    double result, argument = operand->value;
    switch (self->symbol) {
    case NEGATE:
        result = -argument;
        break;
    case SIN:
        result = sin(argument);
        break;
    case COS:
        result = cos(argument);
        break;
    case TAN:
        result = tan(argument);
        break;
    case COT:
        result = 1 / tan(argument);
        break;
    case ARCSIN:
        result = asin(argument);
        break;
    case ARCCOS:
        result = acos(argument);
        break;
    case ARCTAN:
        result = atan(argument);
        break;
    case ARCCOT:
        result = atan(1 / argument);
        break;
    case EXP:
        result = exp(argument);
        break;
    case LN:
        result = log(argument);
        break;
    case SQRT:
        result = sqrt(argument);
        break;
    case FACT:
        result = factorial(argument);
        break;
    default:
        break;
    }
    return token_create_number(result);
}

t_token *operator_apply_binary(t_token *self, t_token *operand_1, t_token *operand_2) {
    double result, argument_1 = operand_1->value, argument_2 = operand_2->value;
    switch (self->symbol) {
    case '+':
        result = argument_1 + argument_2;
        break;
    case '-':
        result = argument_1 - argument_2;
        break;
    case '*':
        result = argument_1 * argument_2;
        break;
    case '/':
        result = argument_1 / argument_2;
        break;
    case '^':
        result = pow(argument_1, argument_2);
        break;
    default:
        break;
    }
    return token_create_number(result);
}
