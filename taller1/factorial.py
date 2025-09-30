import time
import sys

# Aumenta el límite de recursión de Python para números grandes.
sys.setrecursionlimit(200000)

def factorial_recursivo(n):
    if n == 0:
        return 1
    else:
        # print(f"Calculando para {n}...") 
        return n * factorial_recursivo(n - 1)

if __name__ == "__main__":
    numero = 100000 

    # --- Medición de tiempo ---
    inicio = time.perf_counter() # Obtiene un tiempo de alta precisión

    try:
        resultado = factorial_recursivo(numero)
        fin = time.perf_counter() # Obtiene el tiempo al finalizar
        
        # print(f"El factorial de {numero} es: {resultado}") # PD: Esto explota con numeros grandes xd
        print(f"Cálculo completado.")
        print(f"El programa en Python tardó: {fin - inicio:0.6f} segundos.")

    except RecursionError:
        print(f"Error: Se ha excedido el límite de recursión para el número {numero}.")
    except Exception as e:
        print(f"Ocurrió un error: {e}")