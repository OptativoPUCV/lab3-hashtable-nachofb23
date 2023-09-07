#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  if (map == NULL || key == NULL) {
        return; // Verificación de seguridad
    }

    // Calcular el índice usando la función hash
    unsigned long index = hash(key) % map->capacity;

    // Buscar una casilla disponible para insertar el par
    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL) {
        // Si la casilla está ocupada, avanza circularmente
        index = (index + 1) % map->capacity;
    }

    // Si la clave ya existe, no insertarla nuevamente
    if (map->buckets[index] != NULL && strcmp(map->buckets[index]->key, key) == 0) {
        return;
    }

    // Crear un nuevo par clave-valor
    Pair *newPair = (Pair *)malloc(sizeof(Pair));
    if (newPair == NULL) {
        perror("Error al alocar memoria para el nuevo par");
        exit(EXIT_FAILURE);
    }

    newPair->key = strdup(key); // Duplicar la clave
    newPair->value = value;

    // Insertar el par en la casilla encontrada
    map->buckets[index] = newPair;

    // Actualizar la variable size
    map->size++;

    // Actualizar el índice current
    map->current = index;
}



void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap* map = (HashMap*)malloc(sizeof(HashMap));

    if (map == NULL) {
        perror("Error al alocar memoria para la tabla de hash");
        exit(EXIT_FAILURE);
    }

    // Alocar memoria para el arreglo de punteros a pares
    map->buckets = (Pair**)malloc(sizeof(Pair*) * capacity);

    if (map->buckets == NULL) {
        perror("Error al alocar memoria para el arreglo de pares");
        exit(EXIT_FAILURE);
    }

    // Inicializar las entradas de la tabla
    for (long i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }

    // Establecer la capacidad de la tabla y otras propiedades
    map->capacity = capacity;
    map->size = 0;
    map->current = -1;

    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
