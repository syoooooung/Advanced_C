#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>



struct snack {
	char* name; //
	int num; //스낵  수
	int id;
	int sel_count; //팔린 수
};
struct drink {
	char* name;
	int num;
	int id;
	int sel_count; //팔린 수
};

struct drink* drin;
struct snack* snac;
int drink_num = 0;
int snack_num = 0;


int check_ID(char* id); //관리자라면 0 서비스모드라면 1
void reset_drink_menu(); // 음료 초기ㅗ하
void reset_snack_menu(); //간식 초기화
void service_mode();
void print_snack();
void print_drink();
void print_receip(); //사용자 주문 내용 출력
int main() {
	char who[20];
	int who_result = 0;
	while (1) {
		printf("Mode Select (admin or user) :");
		scanf("%s", who);
		who_result = check_ID(who);
		if (who_result == 0) { // 관리자 모드
			printf("Admin mode\n");
			break;
		}
		else if (who_result == 1) {
			printf("User mode\n");
			service_mode();
			break;
		}
		else {
			printf("Error : Wrong Input!\n");
		}
	}
	

}

void service_mode() { // 주문 받는 함수
	reset_drink_menu(); 
	reset_snack_menu();
	
	while (1) {
		int input_ob = 0;
		printf("음료수는 1, 스낵은 2, 주문 종료시 0을 입력하세요 : ");
		scanf("%d", &input_ob);
		if (input_ob == 1) { //음료 선택
			print_drink();

			printf("원하시는 메뉴의 번호를 입력하세요. : ");
			int input_id = 0;
			scanf("%d", &input_id);
			(*(drin + input_id)).sel_count++;
		}
		else if (input_ob == 2) { // 간식 선택
			print_snack();

			printf("원하시는 메뉴의 번호를 입력하세요. : ");
			int input_id = 0;
			scanf("%d", &input_id);
			(*(snac + input_id)).sel_count++;
		}
		else {
			break;
		}
		
		
	}
	print_receip();
	
}

void print_snack() {
	printf("메뉴 번호  메뉴이름\n");
	for (int i = 0; i < snack_num; i++) {
		printf("%d\t%s\n", (*(snac + i)).id, (*(snac + i)).name);

	}
}
void print_drink() {
	printf("메뉴 번호  메뉴이름\n");
	for (int i = 0; i < drink_num; i++) {
		printf("%d\t%s\n", (*(drin + i)).id, (*(drin + i)).name);

	}
}
void print_receip() {
	printf("\n======총 주문 내역=====\n\n");
	for (int i = 0; i < snack_num; i++) {
		if ((*(snac + i)).sel_count == 0)
			continue;
		printf("%s : %d개\n", (*(snac + i)).name,(*(snac + i)).sel_count );

	}
	for (int i = 0; i < drink_num; i++) {
		if ((*(drin + i)).sel_count == 0)
			continue;
		printf("%s : %d개\n", (*(drin + i)).name,(*(drin + i)).sel_count);

	}
}

int check_ID(char* id) {
	if (strcmp(id, "admin") == 0) {
		return 0;
	}
	else if (strcmp(id, "user") == 0) {
		return 1;
	}
	else {
		return 2;
	}
	return 2;
}

void reset_drink_menu() {
	FILE* frp;
	frp = fopen("drink1.txt", "r");
	drin = malloc(sizeof(struct drink) * 1);
	int Is_fir = 0;
	while (1) {
		if (Is_fir == 0) {
			char trash[10];
			fscanf(frp, "%s\n", trash);
			Is_fir = 1;
			continue;
		}
		if (feof(frp))
			break;
		
		char imsi[50];
		fscanf(frp,"%s\n", imsi);
		
		
		int siz = strlen(imsi);
		drin = realloc(drin, sizeof(struct drink) * (drink_num +1));
		(*(drin + drink_num)).name =(char*) malloc(sizeof(char) * siz + 1);
		strcpy((*(drin + drink_num)).name, imsi);
		//printf("%s\n", (*(drin + drink_num)).name);
		(*(drin + drink_num)).id = drink_num;
		(*(drin + drink_num)).sel_count = 0;
		
		drink_num++;
	}
}

void reset_snack_menu() {
	FILE* frp;
	frp = fopen("snack1.txt", "r");
	snac = malloc(sizeof(struct snack) * 1);
	int Is_fir = 0;
	while (1) {
		if (Is_fir == 0) {
			char trash[10];
			fscanf(frp, "%s\n", trash);
			Is_fir = 1;
			continue;
		}
		if (feof(frp))
			break;
		
		char imsi[50];
		fscanf(frp,"%s\n", imsi);
		int siz = strlen(imsi);
		snac = realloc(snac, sizeof(struct snack) *( snack_num + 1));
		(*(snac + snack_num)).name = malloc(sizeof(char) * siz + 1);
		strcpy((*(snac + snack_num)).name, imsi);
		(*(snac + snack_num)).id = snack_num;
		(*(snac + snack_num)).sel_count =0 ;
		snack_num++;
	}
}
