#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct node {
	char* name;
	int num;
	struct node* next;
}Node;
Node* head = NULL;

void creaet_node(int n, char* nm);
void delete_node(int n);
void sort_as();
void sort_ds();
void display_list();
int main() {
	FILE* frp;
	frp = fopen("drink.txt", "r");
	while (!feof(frp)) {
		char tmp[20];
		int num = 0;
		fscanf(frp, "%[^\t]\t%d\n", tmp, &num);
		creaet_node(num, tmp);
	}


	display_list();
}

void creaet_node(int n, char* nm) {
	Node* new_node = (struct node*)calloc(sizeof(struct node), 1);
	new_node->num = n;
	new_node->name = (char*)malloc(sizeof(struct node) * strlen(nm));
	strcpy(new_node->name, nm);
	if (head == NULL) {
		head = new_node;
		return;
	}
	Node* curr = head;
	Node* pre = NULL;
	while (curr != NULL) {
		if (curr->num > new_node->num) {
			if (pre == NULL) {
				head = new_node;
				new_node->next = curr;
				return;
			}
			pre->next = new_node;
			new_node->next = curr;
			return;
		}
		else if (curr->num == new_node->num) {
			while (curr != NULL) {
				if (curr->num != new_node->num) {
					if (pre == NULL) {
						head = new_node;
						new_node->next = curr;
						return;
					}
					pre->next = new_node;
					new_node->next = curr;
				}
				if (strcmp(curr->name, new_node->name) > 0) {
					if (pre == NULL) {
						head = new_node;
						new_node->next = curr;
						return;
					}
					pre->next = new_node;
					new_node->next = curr;
					return;
				}
				pre = curr;
				curr = curr->next;
			}
			return;
		}
		pre = curr;
		curr = curr->next;
	}
	if (pre == NULL) {
		head = new_node;
	}
	pre->next = new_node;
	//curr->next = new_node;
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
		printf("(%d, %s)", temp->num, temp->name);
		temp = temp->next;
		if (temp != NULL)
			printf(" -> ");
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
