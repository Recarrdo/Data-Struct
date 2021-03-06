#include <stdio.h>
#define MAXNODE 100

struct Node
{
	int data;
	Node* prev;
	Node* next;
}node[MAXNODE];

int arr_idx;
Node* head, * tail;

Node* myalloc()
{
	return &node[arr_idx++];
}


void init()
{
	arr_idx = 0;
	head = myalloc();
	tail = myalloc();
	head->next = tail;
	tail->prev = head;
}

void addtoHead(int data)
{
	Node* pp = myalloc();
	pp->data = data;
	pp->next = head->next;
	head->next = pp;
	pp->prev = pp->next->prev;
	pp->next->prev = pp;
}

void addtoTail(int data)
{
	Node* pp = myalloc();
	pp->data = data;
	pp->prev = tail->prev;
	tail->prev = pp;
	pp->next = pp->prev->next;
	pp->prev->next = pp;
}

void search(int data)
{
	for (Node* pp = head->next; pp != tail; pp = pp->next)
	{
		if(pp->data == data)
		{
			printf("find: %d\n", data);
			break;
		}
	}
}

void delNode(int data)
{
	for (Node* pp = head->next; pp != tail; pp = pp->next)
	{
		if (pp->data == data)
		{
			pp->next->prev = pp->prev;
			pp->prev->next = pp->next;
			break;
		}
	}
}

void printall()
{
	for (Node* pp = head->next; pp != tail; pp = pp->next)
	{
		printf("%d ", pp->data);
	}
	printf("\n");
}

int main(void)
{
	init();
	char val;
	int num;

	while (1)
	{
		printf("add to Head: H\n");
		printf("add to Tail: T\n");
		printf("add to Delete: D\n");
		fflush(stdin);
		scanf_s(" %c", &val);
		

		switch (val)
		{
			case 'H':
			{
				printf("plz enter number that you want");
				scanf_s("%d", &num);
				addtoHead(num);
				printall();
				break;
			}
			case 'T':
			{
				printf("plz enter number that you want");
				scanf_s("%d", &num);
				addtoTail(num);
				printall();
				break;
			}
			case 'D':
			{
				printf("plz enter number that you want to delete");
				scanf_s("%d", &num);
				delNode(num);
				printall();
				break;
			}
			default:
				break;
			}
	}

	return 0;
}