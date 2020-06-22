#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bstnode {
  char word[100];
  char tango[100];
  struct bstnode *left;
  struct bstnode *right;
} Node;

void InsertBstreeMember(Node **p_bstree, char* word, char* tango) {
  Node *p, *node;
  int cmp;

  p = malloc(sizeof(Node));
  if (p == NULL)
    exit(1);
  else {
    strcpy(p->word, word);
    strcpy(p->tango, tango);
    p->left = NULL;
    p->right = NULL;
    if (*p_bstree == NULL)
      *p_bstree = p;
    else {
      node = *p_bstree;
      while (1) {
	cmp = strcmp(word, node->word);
	if (cmp == 0) {
	  strcpy(node->tango, tango);
	  free(p);
	  break;
	}
	else if (cmp < 0) {
	  if (node->left == NULL) {
	    node->left = p;
	    break;
	  }
	  else
	    node = node->left;
	}
	else {
	  if (node->right == NULL) {
	    node->right = p;
	    break;
	  }
	  else
	    node = node->right;
	}
      }
    }
  }
}

void DeleteBstreeMember(Node **p_bstree, char* word) {
  Node *upper_node = NULL;
  Node *node = *p_bstree;
  Node *left_max_upper_node, *left_max_node;
  int upper_cmp = 0;
  int cmp;

  while (node != NULL) {
    cmp = strcmp(word, node->word);
    if (cmp == 0) {
      if (node->left != NULL && node->right != NULL) {
	left_max_upper_node = node;
	left_max_node = node->left;
	while (left_max_node->right != NULL) {
	  left_max_upper_node = left_max_node;
	  left_max_node = left_max_node->right;
	}
	if (upper_node != NULL) {
	  if (upper_cmp < 0)
	    upper_node->left = left_max_node;
	  else
	    upper_node->right = left_max_node;
	}
	else
	  *p_bstree = left_max_node;
	if (left_max_upper_node != node) {
	  left_max_upper_node->right = left_max_node->left;
	  left_max_node->left = node->left;
	}
	left_max_node->right = node->right;
      }
      else if (node->left != NULL) {
	if (upper_node != NULL) {
	  if (upper_cmp < 0)
	    upper_node->left = node->left;
	  else
	    upper_node->right = node->left;
	}
	else
	  *p_bstree = node->left;
      }
      else {
	if (upper_node != NULL) {
	  if (upper_cmp < 0)
	    upper_node->left = node->right;
	  else
	    upper_node->right = node->right;
	}
	else
	  *p_bstree = node->right;
      }
      free(node);
      break;
    }
    else {
      upper_node = node;
      upper_cmp = cmp;
      if (cmp < 0)
	node = node->left;
      else
	node = node->right;
    }
  }
}

void SearchBstreeMember(Node *bstree, char* word) {
  Node *node = bstree;
  int cmp;

  while (1) {
    if (node == NULL) {
      printf("(not found)\n");
      break;
    }
    cmp = strcmp(word, node->word);
    if (cmp == 0) {
      printf("%s\n", node->tango);
      break;
    }
    else if (cmp < 0)
      node = node->left;
    else
      node = node->right;
  }
}

int main(void) {
  char command[100] = {0};
  char word[100] = {0};
  char tango[100] = {0};
  Node *bstree = NULL;

  while (1) {
    scanf("%s", command);
    if (strcmp(command, "insert") == 0) {
      scanf("%s", word);
      scanf("%s", tango);
      InsertBstreeMember(&bstree, word, tango);
    }
    else if (strcmp(command, "delete") == 0) {
      scanf("%s", word);
      DeleteBstreeMember(&bstree, word);
    }
    else if (strcmp(command, "search") == 0) {
      scanf("%s", word);
      SearchBstreeMember(bstree, word);
    }
    else if (strcmp(command, "quit") == 0)
      break;
  }

  return 0;
}
