#include "data_io.h"

t_token *scan_number(char *c);
t_token *scan_function(char *c);

void print_plane(int plane[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c", plane[i][j] ? '*' : ' ');
        }
        ptintf("\n");
    }
}

t_list *tokenize_input() {
    t_queue *output_queue = queue_create();
    t_operator *operator;
    t_operand *operand;
    t_token *token, *last_token = NULL;
    char c;
    int is_first = 1, scan = 1;
    do {
        if (scan) {
            c = getchar();
        }
        scan = 1;
        operator = NULL;
        operand = NULL;
        if (c == ' ') {
            continue;
        } else if ('0' <= c && c <= '9') {
            operand = scan_number(&c);
            scan = 0;
        } else if (c == 'x') {
            operand = operand_create(VARIABLE, 'x');
        } else if (c == '-' && (token_is_l_parenthesis(last_token) || is_first ||
                                token_is_binary_operator(last_token))) {
            operator = operator_create(FUNCTION, c);
        } else if (is_operator(c)) {
            operator = operator_create(OPERATOR, c);
        } else if (c == '(') {
            operator = operator_create(L_PARENTHESIS, c);
        } else if (c == ')') {
            operator = operator_create(R_PARENTHESIS, c);
        } else if (c != '\n') {
            operator = scan_function(&c);
            scan = 0;
        } else {
            break;
        }
        if (operator == NULL && operand == NULL) {
            while (!queue_is_empty(output_queue)) {
                token_destroy((t_token *)queue_dequeue(output_queue));
            }
            queue_destroy(output_queue);
            output_queue = NULL;
            c = '\n';
        } else {
            token = token_create(operator, operand);
            queue_enqueue(output_queue, token);
            last_token = token;
        }
        is_first = 0;
    } while (c != '\n');
    return output_queue;
}

t_token *scan_function(char *c) {
    t_operator *operator = NULL;
    char func[8] = {0};
    int index = 1, exit = 0;
    func[0] = *c;
    while (!exit) {
        *c = getchar();
        if (*c != '\n' && index < 7) {
            func[index++] = *c;
        }
        if (*c == '(' || index > 5) {
            exit = 1;
        }
    }
    if (*c == '(') {
        char func_letter = '\0';
        if (strcmp("sin(", func) == 0) {
            func_letter = 's';  // 's' for sin
        } else if (strcmp("cos(", func) == 0) {
            func_letter = 'c';  // 'c' for cos
        } else if (strcmp("tan(", func) == 0) {
            func_letter = 't';  // 't' for tan
        } else if (strcmp("ctg(", func) == 0) {
            func_letter = 'o';  // 'o' for cot
        } else if (strcmp("sqrt(", func) == 0) {
            func_letter = 'q';  // 'q' for sqrt
        } else if (strcmp("ln(", func) == 0) {
            func_letter = 'l';  // 'l' for ln
        }
        if (func_letter != '\0') {
            operator = operator_create(FUNCTION, func_letter);
        }
    }
    return operator;
}

t_token *scan_number(char *c) {
    t_operand *operand = NULL;
    int points_counter = 0, exit = 0;
    double number = 0;
    t_stack *before_point_stack = stack_create();
    t_stack *after_point_stack = stack_create();
    while (!exit) {
        if (*c == '.') {
            points_counter++;
        } else if (*c >= '0' && *c <= '9') {
            if (points_counter == 1) {
                int *digit = (int *)malloc(sizeof(int));
                *digit = *c - '0';
                stack_push(after_point_stack, digit);
            } else if (points_counter == 0) {
                int *digit = (int *)malloc(sizeof(int));
                *digit = *c - '0';
                stack_push(before_point_stack, digit);
            } else {
                exit = 1;
            }
        } else {
            exit = 1;
        }
        if (!exit) {
            *c = getchar();
        }
    }
    for (int i = 0; !stack_is_empty(before_point_stack); ++i) {
        int *digit = (int *)stack_pop(before_point_stack);
        number += pow(10, i) * *digit;
        free(digit);
    }
    for (int i = -after_point_stack->count; !stack_is_empty(after_point_stack); ++i) {
        int *digit = (int *)stack_pop(after_point_stack);
        number += pow(10, i) * *digit;
        free(digit);
    }
    if (points_counter < 2) {
        operand = operand_create(NUMBER, number);
    }
    stack_destroy(before_point_stack);
    stack_destroy(after_point_stack);
    return operand;
}

void print_parsing_error() {
    printf("An error occurred while parsing.\n");
}
