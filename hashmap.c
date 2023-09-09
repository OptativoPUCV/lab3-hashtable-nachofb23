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

long hash(char * key, long capacity) {
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
        return; 
    }

    long index = hash(key, map->capacity);

    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL) {
        index = (index + 1) % map->capacity;
    }

    if (map->buckets[index] != NULL && strcmp(map->buckets[index]->key, key) == 0) {
        return;
    }

    Pair *newPair = (Pair *)malloc(sizeof(Pair));
    if (newPair == NULL) {
        perror("Error al alocar memoria para el nuevo par");
        exit(EXIT_FAILURE);
    }

    newPair->key = strdup(key); 
    newPair->value = value;

    
    map->buckets[index] = newPair;

   
    map->size++;

    map->current = index;
}



void enlarge(HashMap * map) {
    enlarge_called = 1; 


}


HashMap * createMap(long capacity) {
  HashMap* map = (HashMap*)malloc(sizeof(HashMap));

  if (map == NULL) {
      perror("Error al alocar memoria para la tabla de hash");
      exit(EXIT_FAILURE);
    }

  map->buckets = (Pair**)malloc(sizeof(Pair*) * capacity);

  if (map->buckets == NULL) {
        perror("Error al alocar memoria para el arreglo de pares");
        exit(EXIT_FAILURE);
    }

  for (long i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }

  map->capacity = capacity;
  map->size = 0;
  map->current = -1;
  
  return map;
}

void eraseMap(HashMap * map,  char * key) {
  if (map == NULL || key == NULL) {
    return;
  }

  long index = hash(key, map->capacity);

  while (map ->buckets[index] != NULL) {
    if (map->buckets[index]->key != NULL && strcmp(map->buckets[index]->key, key) == 0) {
      free(map->buckets[index]->key);
      map->buckets[index]->key = NULL;
      map->size--;
      return;
    }
    index = (index + 1) % map->capacity;
  }

}

Pair * searchMap(HashMap * map,  char * key) {  
  if (map == NULL || key == NULL) {
    return NULL;
  }

  long index = hash(key, map->capacity);
  

  while (map->buckets[index] != NULL) {
    if (map->buckets[index]->key != NULL && strcmp(map->buckets[index]->key, key) == 0) {
        map->current = index;
        return map->buckets[index];
    }
    index = (index + 1) % map->capacity;
  }
  return NULL;
}

Pair * firstMap(HashMap * map) {
    if (map == NULL) {
    return NULL;
  }

  for (long i = 0; i < map->capacity; i++) {
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      map->current = i;
      return map->buckets[i];
    }
  }
    return NULL;
}

Pair * nextMap(HashMap * map) {
  if (map == NULL) {
    return NULL;
  }

  for (long i = map->current + 1; i < map->capacity; i++) {
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      map->current = 1;
      return map->buckets[i];
    }
  }
    return NULL;
}
