#include "hashmap.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMap HashMap;
int enlarge_called = 0;

struct HashMap {
  Pair **buckets;
  long size;     // cantidad de datos/pairs en la tabla
  long capacity; // capacidad de la tabla
  long current;  // indice del ultimo dato accedido
};

Pair *createPair(char *key, void *value) {
  Pair *new = (Pair *)malloc(sizeof(Pair));
  new->key = key;
  new->value = value;
  return new;
}

long hash(char *key, long capacity) {
  unsigned long hash = 0;
  char *ptr;
  for (ptr = key; *ptr != '\0'; ptr++) {
    hash += hash * 32 + tolower(*ptr);
  }
  return hash % capacity;
}

int is_equal(void *key1, void *key2) {
  if (key1 == NULL || key2 == NULL)
    return 0;
  if (strcmp((char *)key1, (char *)key2) == 0)
    return 1;
  return 0;
}

void insertMap(HashMap *map, char *key, void *value) {

  if (map->size == map->capacity)
    return;

  long pos = hash(key, map->capacity);

  while (map->buckets[pos] != NULL)
    pos = (pos + 1) % map->capacity;

  map->buckets[pos] = createPair(key, value);

  map->size++;
  map->current = pos;
}

void enlarge(HashMap *map) {
  enlarge_called = 1; // no borrar (testing purposes)
}

HashMap *createMap(long capacity) {

  HashMap *hashMap = malloc(sizeof(HashMap));

  hashMap->buckets = malloc(capacity * sizeof(Pair *));
  hashMap->capacity = capacity;
  hashMap->current = -1;
  hashMap->size = 0;

  return hashMap;
}

void eraseMap(HashMap *map, char *key) {}

Pair *searchMap(HashMap *map, char *key) {
  long pos = hash(key, map->capacity);
  map->current = pos;

  bool end = false;
  while (!end)
    {
      if (map->buckets[pos] != NULL)
      {
        if(is_equal(map->buckets[pos]->key, key))
          end = true;
      }
      else
      {
        pos++;
      }
    }

  return map->buckets[pos];
}

Pair *firstMap(HashMap *map) { return NULL; }

Pair *nextMap(HashMap *map) { return NULL; }
