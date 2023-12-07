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
void create_linkedlist(char* nm, char* sub, int sc); //1차원 링크드리스트에 노드 추가 시 호출
void create_2D_linked(char* nm, char* sub, int sc); //2차원 링크드리스트에 노드 추가 시 호출
void print_before_sort(); //초기 1차원 링크드리스트 출력
void print_after_sort(); //재정렬 후 1차원 링크드 리스트 출력
void pirnt_2d_linked(); //2차원 링크드리스트 출력
void re_sort();  //재정렬
void insertion_sort(int num); //insertion sort

int main() {
	init_node();
	print_before_sort();
	re_sort();
	print_after_sort();
	pirnt_2d_linked();
}
void init_node() {
	FILE* frp;
	frp = fopen("score.txt", "r"); //score.txt를 read권한으로 연다
	int is_fir = 0;
	while (!feof(frp)) {
		if (is_fir == 0) { //첫줄은 저장하지 않는다
			char trash[30];
			fscanf(frp, "%[^\n]\n", trash);
			is_fir = 1;
			continue;
		}
		char imsi_name[15];
		char imsi_sub[20];
		int sc;
		fscanf(frp, "%[^\t]\t%s", imsi_name, imsi_sub);
		fscanf(frp, "\t%d\n", &sc); //이름, 과목, 점수를 읽어옴

		create_linkedlist(imsi_name, imsi_sub, sc); //1차원 링크드리스트에 해당 정보를 저장할 노드 추가
		create_2D_linked(imsi_name, imsi_sub, sc); //2차원 링크드리스트에 해당 정보를 저장할 노드 추가

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
		new_node->is_head = 1;
		return;
	}
	Node2* pre_node = NULL;
	Node2* curr_node = head2;
	while (curr_node != NULL) {
		int cmp_result = strcmp(curr_node->name, new_node->name);
		if (cmp_result > 0) { //newnode를 currnode 위에 넣어줘야해
			//새로운 줄 생기는 거니까
			new_node->is_head = 1;
			if (pre_node == NULL){ //만약 해드 앞에 넣어줘야하는 거라면
				head2 = new_node; //새로운 노드가 head가 된다
				new_node->down = curr_node;
				return;
			}
			new_node->down = curr_node;
			pre_node->down = new_node;
			
			return;
		}
		else if (cmp_result == 0) {//이미 같은 이름이 있음!
			//과목명 비교 시작
			
			while (curr_node != NULL) {
				if (strcmp(curr_node->subject, new_node->subject) >= 0) {
					if (curr_node->is_head == 1) { 
						if (pre_node == NULL) { //넣어야할 부분이 해드라면
							curr_node->is_head = 0;
							new_node->is_head = 1;
							head2 = new_node;
							new_node->down = curr_node->down; //currnode는 newnode의 next가되고 newnode에 down을넘겨준다
							new_node->next = curr_node;
							
							return;
						}
						curr_node->is_head = 0;
						new_node->is_head = 1; //새로운 노드가 head가 된다.
						new_node->down = curr_node->down; 
						pre_node->down = new_node;
						new_node->next = curr_node;
						
						return;
					}
					pre_node->next = new_node; //prenode와 currnode 사이에 newnode 넣어줌
					new_node->next = curr_node;
					
					return;
				}
				pre_node = curr_node;
				curr_node = curr_node->next;
			}
			pre_node->next = new_node;
			
			return;
		}


		pre_node = curr_node;
		curr_node = curr_node->down; //아래 노드로 넘어가기

	}
	pre_node->down = new_node; //newnode는 마지막노드가된다
	new_node->is_head = 1;
	return;
}
void pirnt_2d_linked() {
	FILE* fwp;
	fwp = fopen("record.txt", "a"); //record.txt에 이어쓰기
	Node2* curr = head2;
	while (curr->down != NULL) { 
		Node2* tmp = curr;
		while (curr->next != NULL) { //그 행을 출력
			printf("(%s, %s, %d)->", curr->name, curr->subject, curr->score); 
			fprintf(fwp,"(%s, %s, %d)->", curr->name, curr->subject, curr->score); //학생이름, 과목명, 점수를 순서로 출력
			curr = curr->next;
		}
		printf("(%s, %s, %d)\n", curr->name, curr->subject, curr->score);
		printf("  |\n  V\n");
		fprintf(fwp,"(%s, %s, %d)\n", curr->name, curr->subject, curr->score); //그행의 마지막 노드 출력
		fprintf(fwp,"  |\n  V\n");
		curr = tmp;
		curr = curr->down;
	}
	while (curr->next != NULL) { //그 행을 출력
		printf("(%s, %s, %d)->", curr->name, curr->subject, curr->score);
		fprintf(fwp,"(%s, %s, %d)->", curr->name, curr->subject, curr->score); //학생이름, 과목명, 점수를 순서대로 출력
		curr = curr->next;
	}
	printf("(%s, %s, %d)\n", curr->name, curr->subject, curr->score);
	fprintf(fwp,"(%s, %s, %d)\n", curr->name, curr->subject, curr->score); //최종 마지막 노드 출력
	fclose(fwp);
}
void create_linkedlist(char* nm, char* sub, int sc){
	Node* new_node =(struct node*) calloc(sizeof(struct node),1); //새로운 노드 생성
	new_node->name = malloc(sizeof(struct node) * strlen(nm));
	new_node->subject = malloc(sizeof(struct node) * strlen(sub)); //메모리 동적할당
	strcpy(new_node->name, nm);
	strcpy(new_node->subject, sub); //정보저장해주기
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
					if (pre_node == NULL) { //만약 head뒤에 새로운 노드가들어가야한다면
						head = new_node; //새로운 노드가 head가된다.
						new_node->next = curr_node;
						return;
					}
					pre_node->next = new_node; //prenode와 currnode 사이에 newnode를 넣어준다
					new_node->next = curr_node;
					return;
				}
				if (strcmp(curr_node->subject, new_node->subject) >= 0) { //newnode가 currnode과목명보다 우선순위를 가진다면
					if (pre_node == NULL) {
						head = new_node;
						new_node->next = curr_node; //newnode의 currnode전 노드는 newnode
						return;
					}
					pre_node->next = new_node; //prenode와 currnode 사이에 newnode를 넣어줌
					new_node->next = curr_node;
					return;
				}
				pre_node = curr_node;
				curr_node = curr_node->next;
				
			}
			pre_node->next = new_node;
			return;

		}
	}
	if (pre_node == NULL) {
		head = new_node;
		return;
	}
	pre_node->next = new_node; //newnode는 리스트의 마지막자리에 들어간다.
	return;
}

void print_before_sort() {
	FILE* fwp;
	fwp = fopen("record.txt", "w");
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
			fprintf(fwp, "%s 학생의 평균 점수 : %.2lf\n\n", curr->name, ((result / div) * 100) / 100);
			printf("%s 학생의 평균 점수 : %.2lf\n\n", curr->name, ((result / div)*100)/100);
			result = 0.0;
			div = 0;
			curr = curr->next;
			break;
		}
		if (strcmp(curr->name, curr->next->name) != 0) {
			result += curr->score;
			div++;
			fprintf(fwp, "%s 학생의 평균 점수 : %.2lf\n\n", curr->name, ((result / div) * 100) / 100);
			printf( "%s 학생의 평균 점수 : %.2lf\n\n", curr->name, ((result / div) * 100) / 100);
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
	fwp = fopen("record.txt", "a");
	Node* curr = head;
	fprintf(fwp, "\n\n이름\t과목\t점수\n");
	
	float result = 0.0;
	float result2 = 0.0;
	int div = 0;
	int div2 = 0;
	while (curr != NULL) {
		fprintf(fwp, "%s\t%s\t%d\n", curr->name, curr->subject, curr->score);
		if (curr->next == NULL) {
			result += curr->score;
			if (curr->score > 60) {
				result2 += curr->score;
				div2++;
			}
			div++;
			fprintf(fwp, "%s 과목의 평균 점수 : %.2lf\n", curr->subject, ((result / div)*100)/100);
			fprintf(fwp, "%s 과목의 평균 점수(60점 이하 제외) : ", curr->subject);
			if (div2 == 0) {
				fprintf(fwp, "XX\n\n");
			}
			else {
				fprintf(fwp, "%.2lf\n\n", ((result2 / div2) * 100) / 100);
			}
			result = 0.0;
			result2 = 0.0;
			div = 0;
			div2 = 0;
			curr = curr->next;
			break;
		}
		if (strcmp(curr->subject, curr->next->subject) != 0) {
			result += curr->score;
			if (curr->score > 60) {
				result2 += curr->score;
				div2++;
			}
			div++;
			fprintf(fwp, "%s 과목의 평균 점수 : %.2lf\n", curr->subject, ((result / div) * 100) / 100);
			fprintf(fwp, "%s 과목의 평균 점수(60점 이하 제외) : ", curr->subject);
			if (div2 == 0) {
				fprintf(fwp, "XX\n\n");
			}
			else {
				fprintf(fwp, "%.2lf\n\n", ((result2 / div2) * 100) / 100);
			}
			result = 0.0;
			result2 = 0.0;
			div = 0;
			div2 = 0;
			curr = curr->next;
			continue;
		}
		result += curr->score;
		if (curr->score > 60) {
			result2 += curr->score;
			div2++;
		}
		div++;
		curr = curr->next;
	}

	fclose(fwp);
	return;
}
