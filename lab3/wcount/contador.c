#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <archivo.txt> <palabra>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *word_to_find = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int count = 0;
    char buffer[1024];

    // Leemos palabra por palabra del archivo
    while (fscanf(file, "%1023s", buffer) == 1) {
        if (strcmp(buffer, word_to_find) == 0) {
            count++;
        }
    }

    fclose(file);

    printf("La palabra '%s' aparece %d veces.\n", word_to_find, count);

    return 0;
}
