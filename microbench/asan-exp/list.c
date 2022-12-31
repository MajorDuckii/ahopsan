#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int data;
  int key;
  struct node *next;
} *head = NULL;

void insertFirst(int key, int data)
{
  // create a link
  struct node *link = (struct node *)malloc(sizeof(struct node));

  link->key = key;
  link->data = data;

  // point it to old first node
  link->next = head;

  // point first to new first node
  head = link;
}

// display the list
void printList()
{
  struct node *ptr = head;
  printf("[ ");

  // start from the beginning
  while (ptr != NULL) {
    printf("(%d,%d) ", ptr->key, ptr->data);
    ptr = ptr->next;
  }

  printf(" ]\n");
}

// display the list
void printList2()
{
  struct node *ptr = head;
  printf("[ ");

  // start from the beginning
  while (ptr != NULL && ptr->key != 5) {
    printf("(%d,%d) ", ptr->key, ptr->data);
    ptr = ptr->next->next;
  }

  printf(" ]\n");
}

int main(int argc, char *argv[])
{
  insertFirst(1, 10);
  insertFirst(2, 20);
  insertFirst(3, 30);
  insertFirst(4, 1);
  insertFirst(5, 40);
  insertFirst(6, 56);

  printf("Original List:\n");
  // print list
  printList();

  printf("\nFor IR Observation:\n");
  // print list
  printList2();
  return 0;
}
