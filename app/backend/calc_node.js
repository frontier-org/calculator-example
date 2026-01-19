// Copyright (c) 2026 The Frontier Framework Authors
// SPDX-License-Identifier: Apache-2.0 OR MIT

require('vm');

try {
    let expr = process.argv[2];
    // Remove aspas se presentes
    expr = expr.replace(/^"|"$/g, '');
    
    // Executa o cálculo de forma segura
    const result = Number(Function('"use strict";return (' + expr + ')')());
    console.log(result.toFixed(2));
} catch (e) {
    console.log("Error");
}