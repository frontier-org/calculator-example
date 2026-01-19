// Copyright (c) 2026 The Frontier Framework Authors
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

double parseExpr(const char*& p);

double parseFactor(const char*& p) {
    while (*p == ' ') p++;
    if (*p == '(') {
        p++;
        double res = parseExpr(p);
        if (*p == ')') p++;
        return res;
    }
    char* end;
    double res = std::strtod(p, &end);
    p = end;
    return res;
}

double parseTerm(const char*& p) {
    double res = parseFactor(p);
    while (*p == '*' || *p == '/') {
        char op = *p++;
        double next = parseFactor(p);
        if (op == '*') res *= next;
        else if (next != 0) res /= next;
    }
    return res;
}

double parseExpr(const char*& p) {
    double res = parseTerm(p);
    while (*p == '+' || *p == '-') {
        char op = *p++;
        if (op == '+') res += parseTerm(p);
        else res -= parseTerm(p);
    }
    return res;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::string s = argv[1];
    // Limpeza de aspas
    if (s.front() == '"') s = s.substr(1, s.size() - 2);
    const char* p = s.c_str();
    std::cout << std::fixed << std::setprecision(2) << parseExpr(p);
    return 0;
}