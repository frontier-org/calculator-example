// Copyright (c) 2026 The Frontier Framework Authors
// SPDX-License-Identifier: Apache-2.0 OR MIT

package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"unicode"
)

type Parser struct {
	expr string
	pos  int
}

func (p *Parser) parseExpression() float64 {
	result := p.parseTerm()
	for p.pos < len(p.expr) {
		op := p.expr[p.pos]
		if op != '+' && op != '-' {
			break
		}
		p.pos++
		if op == '+' {
			result += p.parseTerm()
		} else {
			result -= p.parseTerm()
		}
	}
	return result
}

func (p *Parser) parseTerm() float64 {
	result := p.parseFactor()
	for p.pos < len(p.expr) {
		op := p.expr[p.pos]
		if op != '*' && op != '/' {
			break
		}
		p.pos++
		if op == '*' {
			result *= p.parseFactor()
		} else {
			div := p.parseFactor()
			if div != 0 {
				result /= div
			}
		}
	}
	return result
}

func (p *Parser) parseFactor() float64 {
	p.skipSpaces()
	if p.pos < len(p.expr) && p.expr[p.pos] == '(' {
		p.pos++ // pula (
		result := p.parseExpression()
		if p.pos < len(p.expr) && p.expr[p.pos] == ')' {
			p.pos++ // pula )
		}
		return result
	}

	start := p.pos
	for p.pos < len(p.expr) && (unicode.IsDigit(rune(p.expr[p.pos])) || p.expr[p.pos] == '.') {
		p.pos++
	}
	
	val, _ := strconv.ParseFloat(p.expr[start:p.pos], 64)
	p.skipSpaces()
	return val
}

func (p *Parser) skipSpaces() {
	for p.pos < len(p.expr) && p.expr[p.pos] == ' ' {
		p.pos++
	}
}

func main() {
	if len(os.Args) < 2 {
		return
	}

	// Limpa a expressão de aspas extras enviadas pelo IPC
	input := strings.Trim(os.Args[1], "\"")
	
	parser := &Parser{expr: input, pos: 0}
	fmt.Printf("%.2f", parser.parseExpression())
}