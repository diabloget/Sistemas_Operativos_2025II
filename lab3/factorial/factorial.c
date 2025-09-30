#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long double factorial(int n) {
    // Imprime un punto para ralentizar la ejecución (para que no explote xd).
    //printf("Sistemas ");
    //printf("Operativos ");
    //fflush(stdout); // Forza la impresión inmediata del punto.
    
    usleep(100);
    
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        return 1;
    }
    
    int num = atoi(argv[1]);
    printf("\nCalculando el factorial de %d...\n", num);
    long double result = factorial(num);
    printf("\nEl cálculo ha terminado.\n");
    // El resultado será 'inf' para números muy grandes.
    printf("Resultado (simbólico): %Lf\n", result); 
    
    return 0;
}
