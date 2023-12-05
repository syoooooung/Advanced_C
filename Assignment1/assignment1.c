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

typedef struct node_2d { //2차원 학생이름, 과목, 점수를 담는 구조체
	char* name;
	char* subject;
	int score;
	struct node_2d* next;
	struct node_2d* down;
	int is_head; //해당 줄의 해드라면 1, 아니라면 0
}Node2;

Node* head = NULL; //링크드리스트의 해드
Node* head2 = NULL;
int node_cnt = 0;

void init_node(); //score.txt에서 정보 읽어오는 함수
void create_linkedlist(char* nm, char* sub, int sc);
void create_2D_linked(char* nm, char* sub, int sc);
void print_before_sort();
void print_after_sort();
void pirnt_2d_linked();
void re_sort();
void insertion_sort(int num);
int main() {
	init_node();
	print_before_sort();
	re_sort();
	print_after_sort();
	pirnt_2d_linked();
}
void init_node() {
	FILE* frp;
	frp = fopen("score.txt", "r");
	int is_fir = 0;
	while (!feof(frp)) {
		if (is_fir == 0) {
			char trash[30];
			fscanf(frp, "%[^\n]\n", trash);
			is_fir = 1;
			continue;
		}
		char imsi_name[15];
		char imsi_sub[20];
		int sc;
		fscanf(frp, "%[^\t]\t%s", imsi_name, imsi_sub);
		fscanf(frp, "\t%d\n", &sc);

		create_linkedlist(imsi_name, imsi_sub, sc);
		create_2D_linked(imsi_name, imsi_sub, sc);
		node_cnt++;

	}
}
void create_2D_linked(char* nm, char* sub, int sc) {
	Node2* new_node = (struct node_2d*)calloc(sizeof(struct node_2d), 1);
	new_node->name = malloc(sizeof(struct node_2d) * strlen(nm));
	new_node->subject = malloc(sizeof(struct node_2d) * strlen(sub));
	strcpy(new_node->name, nm);
	strcpy(new_node->subject, sub);
	new_node->score = sc;
	new_node->next = NULL;
	new_node->down = NULL;
	new_node->is_head = 0;
	if (head2 == NULL) { //만약 리스트가 비어있다면
		head2 = new_node;
		return;
	}
	Node2* pre_node = NULL;
	Node2* curr_node = head2;
	while (curr_node != NULL) {
		int cmp_result = strcmp(curr_node->name, new_node->name);
		if (cmp_result > 0) { //newnode를 currnode 위에 넣어줘야해
			//새로운 줄 생기는 거니까
			new_node->is_head = 1;
			if (pre_node == NULL) {
				head2 = new_node;
				new_node->down = curr_node;
				return;
			}
			pre_node->down = new_node;
			new_node->down = curr_node;
			return;
		}
		else if (cmp_result == 0) {//이미 같은 이름이 있음!
			//과목명 비교 시작
			while (curr_node != NULL) {
				if (strcmp(curr_node->subject, new_node->subject) >= 0) {
					if (curr_node->is_head == 1) {
						if (pre_node == NULL) {
							curr_node->is_head = 0;
							new_node->is_head = 1;
							head2 = new_node;
							new_node->down = curr_node->down;
							return;
						}
						curr_node->is_head = 0;
						new_node->is_head = 1;
						pre_node->down = new_node;
						new_node->down = curr_node->down;
						return;
					}
					pre_node->next = new_node;
					new_node->next = curr_node;
					return;
				}
				pre_node = curr_node;
				curr_node = curr_node->next;
			}
			pre_node->next = curr_node;
			return;
		}


		pre_node = curr_node;
		curr_node = curr_node->down;

	}
	pre_node->down = new_node;
	new_node->is_head = 1;
	return;
}
void pirnt_2d_linked() {
	Node2* curr = head2;
	while (curr->down != NULL) {
		while (curr->next != NULL) {
			printf("(%s, %s, %d)->", curr->name, curr->subject, curr->score);
			curr = curr->next;
		}
		printf("(%s, %s, %d)\n", curr->name, curr->subject, curr->score);
		printf("  |\n  V\n");
		curr = curr->down;
		
	}
	printf("(%s, %s, %d)\n", curr->name, curr->subject, curr->score);
}
void create_linkedlist(char* nm, char* sub, int sc){
	Node* new_node =(struct node*) calloc(sizeof(struct node),1);
	new_node->name = malloc(sizeof(struct node) * strlen(nm));
	new_node->subject = malloc(sizeof(struct node) * strlen(sub));
	strcpy(new_node->name, nm);
	strcpy(new_node->subject, sub);
	new_node->score = sc;
	new_node->next = NULL;
	if (head == NULL) { //만약 리스트가 비어있다면
		head = new_node;
		return;
	}
	Node* pre_node = NULL;
	Node* curr_node = head;
	while (curr_node != NULL) {
		int cmp_result = strcmp(curr_node->name, new_node->name);
		if (cmp_result  < 0) { //다음 노드로 넘어가야한다면
			pre_node = curr_node;
			curr_node = curr_node->next;
			continue;
		}
		else if (cmp_result > 0) { // newnode 현 노드보다 앞에 있어야해!
			if (pre_node == NULL) { //newnode가 head가 될 경우
				head = new_node;
				new_node->next = curr_node;
				return;
			}
			new_node->next = curr_node;
			pre_node->next = new_node;
			return;
		}
		else { // newnode랑 currnode의 학생 이름이 같다면
			//과목 이름 기준으로 비교해서 넣기
			while (curr_node != NULL) {
				if (strcmp(curr_node->name, new_node->name) != 0) { //만약 다음 학생 까지 넘어가면
					if (pre_node == NULL) {
						head = new_node;
						new_node->next = curr_node;
						return;
					}
					pre_node->next = new_node;
					new_node->next = curr_node;
					return;
				}
				if (strcmp(curr_node->subject, new_node->subject) >= 0) {
					if (pre_node == NULL) {
						head = new_node;
						new_node->next = curr_node;
						return;
					}
					pre_node->next = new_node;
					new_node->next = curr_node;
					return;
				}
				pre_node = curr_node;
				curr_node = curr_node->next;
				
			}
			return;

		}
	}
	if (pre_node == NULL) {
		head = new_node;
		printf("엥????????????????????????????????????????????????????\n");
		return;
	}
	pre_node->next = new_node;
	return;
}

void print_before_sort() {
	FILE* fwp;
	fwp = fopen("recored.txt", "w");
	Node* curr = head;
	fprintf(fwp, "이름\t과목\t점수\n");
	printf("이름\t과목\t점수\n");
	float result = 0.0;
	int div = 0;
	while (curr != NULL) {
		fprintf(fwp,"%s\t%s\t%d\n", curr->name, curr->subject, curr->score);
		printf( "%s\t%s\t%d\n", curr->name, curr->subject, curr->score);
		if (curr->next == NULL) {
			result += curr->score;
			div++;
			fprintf(fwp, "%s 학생의 평균 점수 : %lf\n\n", curr->name, result / div);
			printf("%s 학생의 평균 점수 : %lf\n\n", curr->name, result / div);
			result = 0.0;
			div = 0;
			curr = curr->next;
			break;
		}
		if (strcmp(curr->name, curr->next->name) != 0) {
			result += curr->score;
			div++;
			fprintf(fwp, "%s 학생의 평균 점수 : %lf\n\n", curr->name, result/div);
			printf( "%s 학생의 평균 점수 : %lf\n\n", curr->name, result / div);
			result = 0.0;
			div = 0;
			curr = curr->next;
			continue;
		}
		result += curr->score;
		div++;
		curr = curr->next;
	}
	
	fclose(fwp);
	return;
}

void re_sort() {
	for (int i = 0; i < node_cnt; i++) {
		insertion_sort(i);
	}
}

void insertion_sort(int num) {
	Node* key_node = head; //insert할 노드
	
	for (int i = 0; i < num; i++) {
		if (key_node == NULL) {
			return;
		}
		key_node = key_node->next;
	}
	if (key_node == NULL) {
		return;
	}
	Node* curr_node = head;
	Node* pre_node = NULL;
	for (int i = 0; i < num; i++) {
		if (strcmp(curr_node->subject, key_node->subject) > 0) { //여기에 insert
			char tmp[30];
			strcpy(tmp, curr_node->name);
			strcpy(curr_node->name,key_node->name );
			strcpy(key_node->name, tmp);
			strcpy(tmp, curr_node->subject);
			strcpy(curr_node->subject, key_node->subject);
			strcpy(key_node->subject, tmp);
			int tmp2 = curr_node->score;
			curr_node->score = key_node->score;
			key_node->score = tmp2;

			
		}
		else if(strcmp(curr_node->subject, key_node->subject) == 0) { //과목이름이 같다면 이름을 비교
			if (strcmp(curr_node->name, key_node->name) > 0) {
				char tmp[30];
				strcpy(tmp, curr_node->name);
				strcpy(curr_node->name, key_node->name);
				strcpy(key_node->name, tmp);
				strcpy(tmp, curr_node->subject);
				strcpy(curr_node->subject, key_node->subject);
				strcpy(key_node->subject, tmp);
				int tmp2 = curr_node->score;
				curr_node->score = key_node->score;
				key_node->score = tmp2;
			}
			if (strcmp(curr_node->next->name, curr_node->name) != 0) {
				char tmp[30];
				strcpy(tmp, curr_node->next->name);
				strcpy(curr_node->next->name, key_node->name);
				strcpy(key_node->name, tmp);
				strcpy(tmp, curr_node->next->subject);
				strcpy(curr_node->next->subject, key_node->subject);
				strcpy(key_node->subject, tmp);
				int tmp2 = curr_node->next->score;
				curr_node->next->score = key_node->score;
				key_node->score = tmp2;
			}
		}
		pre_node = curr_node;
		curr_node = curr_node->next;

	}
}


void print_after_sort() {
	FILE* fwp;
	fwp = fopen("recored.txt", "a");
	Node* curr = head;
	fprintf(fwp, "이름\t과목\t점수\n");
	printf( "이름\t과목\t점수\n");
	float result = 0.0;
	int div = 0;
	while (curr != NULL) {
		fprintf(fwp, "%s\t%s\t%d\n", curr->name, curr->subject, curr->score);
		if (curr->next == NULL) {
			result += curr->score;
			div++;
			fprintf(fwp, "%s 과목의 평균 점수 : %lf\n\n", curr->subject, result / div);
			result = 0.0;
			div = 0;
			curr = curr->next;
			break;
		}
		if (strcmp(curr->subject, curr->next->subject) != 0) {
			result += curr->score;
			div++;
			fprintf(fwp, "%s 과목의 평균 점수 : %lf\n\n", curr->subject, result / div);
			result = 0.0;
			div = 0;
			curr = curr->next;
			continue;
		}
		result += curr->score;
		div++;
		curr = curr->next;
	}

	fclose(fwp);
	return;
}
