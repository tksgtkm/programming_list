
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef long ELEM;

#define QUEUE_SIZE 100

ELEM queue[QUEUE_SIZE];
int front;
int rear;

#define next(a) (((a) + 1) % QUEUE_SIZE)

void error(char *s) {
  fprintf(stderr, s);
  exit(1);
}

void init() {
  front = rear = 0;
}

void enqueue(ELEM x) {
  if (next(rear) == front) {
    error("待ち行列がフルなので要素を入れられません\n");
  }
  queue[rear] = x;
  rear = next(rear)
}

ELEM dequeue() {
  ELEM x;
  if (front == rear) {
    error("待ち行列がからなので要素を取り出せません\n");
  }
  x = queue[front];
  front = next(front);
  return x;
}

int empty() {
  return front == rear;
}
