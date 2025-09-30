import sys
import time

# a ver si no explota el bicho
sys.setrecursionlimit(40000)

def factorial_recursivo(n):
    # Imprime un punto para ralentizar la ejecución y ver el progreso.
    # El flush=True fuerza a que se imprima de inmediato.
    #print(".", end="", flush=True) 
    
    if n <= 1:
        return 1
    else:
        return n * factorial_recursivo(n - 1)

if __name__ == "__main__":
    # Terminal
    if len(sys.argv) != 2:
        print(f"Uso: python3 {sys.argv[0]} <numero>")
        sys.exit(1)
    
    try:
        numero = int(sys.argv[1])
        
        print(f"\nCalculando el factorial de {numero}...")
        inicio = time.perf_counter()
        
        resultado = factorial_recursivo(numero)
        
        fin = time.perf_counter()
        print("\nCálculo completado.")
        print(f"El programa en Python tardó: {fin - inicio:0.6f} segundos.")

    except RecursionError:
        print(f"\nError: Se ha excedido el límite de recursión para el número {numero}.")
        print("Prueba con un número más pequeño (ej. 20000).")
    except ValueError:
        print("Por favor, introduce un número entero válido.")
    except Exception as e:
        print(f"Ocurrió un error: {e}")
