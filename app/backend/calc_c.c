// Copyright (c) 2026 The Frontier Framework Authors
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Simple Math Parser in C
const char *expression;

double parse_expression();

double parse_factor() {
    while (isspace(*expression)) expression++;

    if (*expression == '(') {
        expression++; // skip (
        double result = parse_expression();
        if (*expression == ')') expression++; // skip )
        return result;
    }

    char *end;
    double result = strtod(expression, &end);
    expression = end;
    return result;
}

double parse_term() {
    double result = parse_factor();
    while (isspace(*expression)) expression++;

    while (*expression == '*' || *expression == '/') {
        char op = *expression++;
        if (op == '*') result *= parse_factor();
        else {
            double div = parse_factor();
            if (div != 0) result /= div;
        }
        while (isspace(*expression)) expression++;
    }
    return result;
}

double parse_expression() {
    double result = parse_term();
    while (isspace(*expression)) expression++;

    while (*expression == '+' || *expression == '-') {
        char op = *expression++;
        if (op == '+') result += parse_term();
        else result -= parse_term();
        while (isspace(*expression)) expression++;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    expression = argv[1];
    double final_result = parse_expression();

    // Print to stdout for Frontier to catch
    printf("%.2f", final_result);

    return 0;
}