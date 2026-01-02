import sys
import math

try:
    # Remove aspas extras se o Frontier as passar
    expr = sys.argv[1].strip('"')
    # Avalia a expressão matemática
    result = eval(expr, {"__builtins__": None}, {
        "math": math, "abs": abs, "round": round
    })
    print(f"{result:.2f}")
except Exception as e:
    print("Error")