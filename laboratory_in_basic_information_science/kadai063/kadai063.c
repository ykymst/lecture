#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 30

typedef struct lnode {
  char word[100];
  char tango[100];
  struct lnode *next;
} Node;

unsigned CalcHashValue(char *word) {
  int i;
  unsigned value = 0;

  for (i = 0; i < strlen(word); i++)
    value += word[i];
  return value % HASHSIZE;
}

void InsertHashMember(Node **hashtable, char* word, char* tango) {
  Node *p, *node;
  const unsigned value = CalcHashValue(word);

  p = malloc(sizeof(Node));
  if (p == NULL)
    exit(1);
  else {
    strcpy(p->word, word);
    strcpy(p->tango, tango);
    p->next = NULL;
    node = hashtable[value];
    if (node == NULL)
      hashtable[value] = p;
    else {
      while (1) {
	if (strcmp(node->word, word) == 0) {
	  strcpy(node->tango, tango);
	  free(p);
	  break;
	}
	if (node->next == NULL) {
	  node->next = p;
	  break;
	}
	node = node->next;
      }
    }
  }
}

void DeleteHashMember(Node **hashtable, char* word) {
  Node *prev_node, *node;
  const unsigned value = CalcHashValue(word);

  prev_node = hashtable[value];
  if (prev_node != NULL) {
    if (strcmp(prev_node->word, word) == 0) {
      hashtable[value] = prev_node->next;
      free(prev_node);
    }
    else {
      node = prev_node->next;
      while (node != NULL) {
	if (strcmp(node->word, word) == 0) {
	  prev_node->next = node->next;
	  free(node);
	  break;
	}
	prev_node = node;
	node = node->next;
      }
    }
  }
}

void SearchHashMember(Node **hashtable, char* word) {
  Node *node = hashtable[CalcHashValue(word)];

  while (1) {
    if (node == NULL) {
      printf("(not found)\n");
      break;
    }
    if (strcmp(node->word, word) == 0) {
      printf("%s\n", node->tango);
      break;
    }
    node = node->next;
  }
}

int main(void) {
  char command[100] = {0};
  char word[100] = {0};
  char tango[100] = {0};
  Node *hashtable[HASHSIZE] = {NULL};

  while (1) {
    scanf("%s", command);
    if (strcmp(command, "insert") == 0) {
      scanf("%s", word);
      scanf("%s", tango);
      InsertHashMember(hashtable, word, tango);
    }
    else if (strcmp(command, "delete") == 0) {
      scanf("%s", word);
      DeleteHashMember(hashtable, word);
    }
    else if (strcmp(command, "search") == 0) {
      scanf("%s", word);
      SearchHashMember(hashtable, word);
    }
    else if (strcmp(command, "quit") == 0)
      break;
  }

  return 0;
}
