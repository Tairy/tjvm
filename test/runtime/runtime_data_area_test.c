//
// Created by tairy on 2020/11/17.
//
#include "stdio.h"
#include "runtime/local_vars.h"
#include "runtime/operand_stack.h"

void test_local_vars() {
    struct local_vars *local_vars = new_local_vars(100);
    set_int(local_vars, 0, 1222);
    set_int(local_vars, 1, -100);
    set_long(local_vars, 2, 2997924580);
    set_long(local_vars, 4, -2997924580);

    for (int i = 0; i < 2; i++) {
        printf("index: %d, get_int: %d\n", i, get_int(local_vars, i));
    }

    printf("get_long: %ld\n", get_long(local_vars, 2));
    printf("get_long: %ld\n", get_long(local_vars, 4));

    set_float(local_vars, 6, 3.1415926);
    printf("get_float: %.8f\n", get_float(local_vars, 6));

    set_double(local_vars, 8, 2.71828182845);
    printf("get_double: %.12lf\n", get_double(local_vars, 8));
}

void test_operand_stack() {
    struct operand_stack *operand_stack = new_operand_stack(100);

    push_int(operand_stack, 1222);
    printf("pop_int: %d\n", pop_int(operand_stack));

    push_int(operand_stack, -100);
    printf("pop_int: %d\n", pop_int(operand_stack));

    push_long(operand_stack, 2997924580);
    printf("pop_long: %ld\n", pop_long(operand_stack));

    push_float(operand_stack, 3.1415926);
    printf("pop_float: %.8f\n", pop_float(operand_stack));

    push_double(operand_stack, 2.71828182845);
    printf("pop_double: %.12lf\n", pop_double(operand_stack));
}

int main() {
    test_local_vars();
    test_operand_stack();
    return 0;
}

