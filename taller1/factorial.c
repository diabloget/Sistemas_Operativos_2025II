#include <stdio.h>
#include <time.h>

double factorial_recursivo(int n);

double factorial_recursivo(int n) {
    /*
    Usa 'double' para poder manejar resultados más grandes, aunque con pérdida de precisión.
    */
    if (n == 0) {
        return 1.0;
    } 
    else {
        return (double)n * factorial_recursivo(n - 1);
    }
}

int main() {
    int numero = 10000; 

    // --- Medición de tiempo ---
    clock_t inicio, fin;
    double tiempo_cpu_usado;

    inicio = clock(); // Guarda el tiempo de inicio

    double resultado = factorial_recursivo(numero);
    
    fin = clock(); // Guarda el tiempo de finalización

    // Calcula el tiempo transcurrido en segundos
    tiempo_cpu_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;

    printf("Cálculo completado.\n");
    //printf("El factorial de %d es aproximadamente: %e\n", numero, resultado); // Notación científica
    printf("El programa en C tardó: %f segundos.\n", tiempo_cpu_usado);

    return 0;
}