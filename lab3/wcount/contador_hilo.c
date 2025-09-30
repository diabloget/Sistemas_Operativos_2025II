#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>

// Estructura para pasar datos a cada hilo
typedef struct {
    char *buffer;
    long size;
    char *word_to_find;
    int *count;
} ThreadData;

// Función que ejecutará cada hilo
void *count_words(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int local_count = 0;
    char *saveptr;
    char *word;

    // Usamos strtok_r para dividir el buffer en palabras (seguro en hilos)
    word = strtok_r(data->buffer, " \n\r\t.,;:-¡!¿?\"", &saveptr);
    while (word != NULL) {
        if (strcmp(word, data->word_to_find) == 0) {
            local_count++;
        }
        word = strtok_r(NULL, " \n\r\t.,;:-¡!¿?\"", &saveptr);
    }

    *(data->count) = local_count;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <archivo.txt> <palabra> <num_hilos>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *word_to_find = argv[2];
    int num_threads = atoi(argv[3]);

    if (num_threads <= 0) {
        fprintf(stderr, "El número de hilos debe ser mayor que 0.\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Obtener el tamaño del archivo
    struct stat st;
    stat(filename, &st);
    long file_size = st.st_size;

    // Leer todo el archivo en memoria
    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error al reservar memoria");
        fclose(file);
        return 1;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int thread_counts[num_threads];
    long chunk_size = file_size / num_threads;

    for (int i = 0; i < num_threads; i++) {
        long start = i * chunk_size;
        long end = (i == num_threads - 1) ? file_size : (i + 1) * chunk_size;

        // Ajustar inicio hacia el siguiente delimitador si no es el primer hilo
        if (i != 0) {
            while (start < end && strchr(" \n\r\t.,;:-¡!¿?\"", buffer[start]) == NULL) {
                start++;
            }
        }

        long size = end - start;

        // Copiar fragmento al buffer del hilo
        char *thread_buffer = malloc(size + 1);
        if (thread_buffer == NULL) {
            perror("Error al reservar memoria para hilo");
            return 1;
        }

        strncpy(thread_buffer, buffer + start, size);
        thread_buffer[size] = '\0';

        thread_counts[i] = 0;
        thread_data[i].buffer = thread_buffer;
        thread_data[i].size = size;
        thread_data[i].word_to_find = word_to_find;
        thread_data[i].count = &thread_counts[i];

        pthread_create(&threads[i], NULL, count_words, &thread_data[i]);
    }

    int total_count = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_count += thread_counts[i];
        free(thread_data[i].buffer);  // Liberar el buffer copiado
    }

    printf("La palabra '%s' aparece %d veces.\n", word_to_find, total_count);
    free(buffer);
    return 0;
}

