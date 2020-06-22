#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNSIGNED_MAX 4294967295

typedef struct edge {
  char name[100];
  unsigned cost;
  struct edge *next;
} Edge;

typedef struct node {
  char name[100];
  char prev[100];
  unsigned cost;
  Edge *edge;
} Node;

void swap(Node *S, int i, int j) {
  Node node = S[i];

  S[i] = S[j];
  S[j] = node;
}

void update(Node *S, int i) {
  while (i > 0) {
    if (S[i].cost < S[(i - 1) / 2].cost) {
      swap(S, i, (i - 1) / 2);
      i = (i - 1) / 2;
    }
    else
      break;
  }
}

void insert(Node *S, int *size, Node node) {
  S[*size] = node;
  update(S, *size);
  (*size)++;
}

Node delete(Node *S, int *size) {
  Node node = S[0];
  int i = 0;

  (*size)--;
  S[0] = S[*size];
  while (2 * i + 1 < *size) {
    if (2 * i + 2 < *size && S[2 * i + 2].cost < S[i].cost && S[2 * i + 2].cost <= S[2 * i + 1].cost) {
      swap(S, i, 2 * i + 2);
      i = 2 * i + 2;
    }
    else if (S[2 * i + 1].cost < S[i].cost) {
      swap(S, i, 2 * i + 1);
      i = 2 * i + 1;
    }
    else
      break;
  }
  return node;
}

void dijkstra(Node *S, int size, char *end) {
  Node node, reached[1000];
  Edge *edge;
  int i;
  int count = 0;
  char prev[100];
  char route[1000][100];
  int len = 1;

  while (size) {
    node = delete(S, &size);
    reached[count++] = node;
    edge = node.edge;
    while (edge != NULL) {
      for (i = 0; i < size; i++) {
	if (strcmp(S[i].name, edge->name) == 0) {
	  if (node.cost + edge->cost < S[i].cost) {
	    strcpy(S[i].prev, node.name);
	    S[i].cost = node.cost + edge->cost;
	    update(S, i);
	  }
	  break;
	}
      }
      edge = edge->next;
    }
  }
  for (i = 0; i < count; i++) {
    if (strcmp(reached[i].name, end) == 0) {
      strcpy(prev, reached[i].prev);
      break;
    }
  }
  if (strcmp(prev, "") == 0)
    printf("(no route)\n");
  else {
    strcpy(route[0], end);
    while (strcmp(prev, "") != 0) {
      strcpy(route[len], prev);
      len++;
      for (i = 0; i < count; i++) {
	if (strcmp(reached[i].name, prev) == 0) {
	  strcpy(prev, reached[i].prev);
	  break;
	}
      }
    }
    for (i = len - 1; i >= 0; i--)
      printf("%s\n", route[i]);
  }
}

int main(void) {
  FILE *fp;
  char name1[100], name2[100], end[100];
  Node S[1000];
  Node node;
  unsigned cost;
  int size = 2;
  int i;
  Edge *edge;

  fp = fopen("graph.txt", "r");
  fscanf(fp, "%s", name1);
  strcpy(node.name, name1);
  strcpy(node.prev, "");
  node.cost = 0;
  node.edge = NULL;
  S[0] = node;
  fscanf(fp, "%s", end);
  strcpy(node.name, end);
  strcpy(node.prev, "");
  node.cost = UNSIGNED_MAX;
  node.edge = NULL;
  S[1] = node;
  while (fscanf(fp, "%s%s%u", name1, name2, &cost) == 3) {
    edge = malloc(sizeof(Edge));
    if (edge == NULL)
      exit(1);
    strcpy(edge->name, name2);
    edge->cost = cost;
    for (i = 0; i < size; i++) {
      if (strcmp(S[i].name, name1) == 0) {
	edge->next = S[i].edge;
	S[i].edge = edge;
	break;
      }
      if (i == size - 1) {
	edge->next = NULL;
	strcpy(node.name, name1);
	strcpy(node.prev, "");
	node.cost = UNSIGNED_MAX;
	node.edge = edge;
	insert(S, &size, node);
	break;
      }
    }
    for (i = 0; i < size; i++) {
      if (strcmp(S[i].name, name2) == 0)
	break;
      if (i == size - 1) {
	strcpy(node.name, name2);
	strcpy(node.prev, "");
	node.cost = UNSIGNED_MAX;
	node.edge = NULL;
	insert(S, &size, node);
	break;
      }
    }
  }
  fclose(fp);
  dijkstra(S, size, end);

  return 0;
}
