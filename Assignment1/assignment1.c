#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct node { //학생이름, 과목, 점수를 담는 구조체
	char* name;
	char* subject;
	int score;
	struct node* next;
}Node;

Node* head = NULL; //링크드리스트의 해드

void init_node(); //score.txt에서 정보 읽어오는 함수
void create_linkedlist(char* nm, char* sub, int sc);


int main() {
	init_node();
}
void init_node() {

}

void create_linkedlist(char* nm, char* sub, int sc){


}

