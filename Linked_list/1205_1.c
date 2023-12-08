#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct node {
	int num;
	struct node* next;
}Node;
Node* head = NULL;

void creaet_node(int n);
void delete_node(int n);
void sort_as();
void sort_ds();
void display_list();
int main() {
	while (1) {
		int num = 0;
		printf("숫자를 입력하세요, 0 입력시 종료\n");
		scanf("%d", &num);
		if (num == 0)
			break;
		creaet_node(num);
		
	}
	while (1) {
		int num = 0;
		printf("삭제할 숫자를 입력하세요, 0 입력시 종료\n");
		scanf("%d", &num);
		if (num == 0)
			break;
		delete_node(num);
	}
	printf("오름차순/ 내림차순 : ");
	char tmp[20];
	scanf("%s", tmp);
	if (strcmp(tmp, "오름차순") == 0) {
		sort_as();
	}
	else {
		sort_ds();
	}
	display_list();
}

void creaet_node(int n) {
	Node* new_node = (struct node*)calloc(sizeof(struct node),1);
	new_node->num = n;
	if (head == NULL) {
		head = new_node;
		return;
	}
	Node* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_node;
}

void sort_as() {
	Node* current, * index;
	int temp;

	if (head == NULL) {
		return;
	}
	else {
		for (current = head; current != NULL; current = current->next) {
			for (index = current->next; index != NULL; index = index->next) {
				if (current->num > index->num) {
					temp = current->num;
					current->num = index->num;
					index->num = temp;
				}
			}
		}
	}

}
void sort_ds() {
	Node* current, * index;
	int temp;

	if (head == NULL) {
		return;
	}
	else {
		for (current = head; current != NULL; current = current->next) {
			for (index = current->next; index != NULL; index = index->next) {
				if (current->num < index->num) {
					temp = current->num;
					current->num = index->num;
					index->num = temp;
				}
			}
		}
	}
}

void display_list() {
	Node* temp = head;
	while (temp != NULL) {
		printf("%d ", temp->num);
		temp = temp->next;
	}
	printf("\n");
}

void delete_node(int n) {
	Node* curr = head;
	Node* prev = NULL;

	while (curr != NULL && curr->num != n) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("Number not found in the list.\n");
		return;
	}

	if (prev == NULL) {
		// If the node to be deleted is the head
		head = curr->next;
	}
	else {
		prev->next = curr->next;
	}

	free(curr);

}
