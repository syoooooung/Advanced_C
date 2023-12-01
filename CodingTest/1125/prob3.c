#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>



struct snack {
	char* name; //
	int num; //스낵  수
	int id;
	int quan; //남은 수
	int sel_count; //팔린 수
	int price; //가격
};
struct drink {
	char* name;
	int num;
	int id;
	int quan;
	int sel_count; //팔린 수
	int price;
};
struct menu {
	struct drink* drin;
	struct snack* snac;
};

struct menu m;
int drink_num = 0;
int snack_num = 0;

struct menu us_m;

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
			if (input_id > drink_num || (*(m.drin + input_id)).quan == 0) {
				printf("주문이 불가한 id입니다.\n");
				continue;
			}
			(*(m.drin + input_id)).sel_count++;
			(*(m.drin + input_id)).quan--;
		}
		else if (input_ob == 2) { // 간식 선택
			print_snack();

			printf("원하시는 메뉴의 번호를 입력하세요. : ");
			int input_id = 0;
			scanf("%d", &input_id);
			if (input_id > snack_num || (*(m.snac + input_id)).quan == 0) {
				printf("주문이 불가한 id입니다.\n");
				continue;
			}
			(*(m.snac + input_id)).sel_count++;
			(*(m.snac + input_id)).quan--;
		}
		else {
			break;
		}


	}
	print_receip();

}

void print_snack() {
	printf("메뉴 번호  메뉴이름      가격  재고량\n");
	for (int i = 0; i < snack_num; i++) {
		if ((*(m.snac + i)).quan == 0)
			continue;
		printf("%d\t%s  %d  %d\n", (*(m.snac + i)).id, (*(m.snac + i)).name, (*(m.snac + i)).price, (*(m.snac + i)).quan);

	}
}
void print_drink() {
	printf("메뉴 번호  메뉴이름      가격  재고량\n");
	for (int i = 0; i < drink_num; i++) {
		if ((*(m.drin + i)).quan == 0)
			continue;
		printf("%d\t%s  %d  %d\n", (*(m.drin + i)).id, (*(m.drin + i)).name, (*(m.drin + i)).price, (*(m.drin + i)).quan);

	}
}
void print_receip() {
	FILE* fwp;
	fwp = fopen("receipt.txt", "w");
	printf("\n======총 주문 내역=====\n\n");
	fprintf(fwp,"\n======총 주문 내역=====\n\n");
	int total_price = 0;
	for (int i = 0; i < snack_num; i++) {
		if ((*(m.snac + i)).sel_count == 0)
			continue;
		printf("%s : %d개\n", (*(m.snac + i)).name, (*(m.snac + i)).sel_count);
		fprintf(fwp,"%s : %d개\n", (*(m.snac + i)).name, (*(m.snac + i)).sel_count);
		total_price += (*(m.snac + i)).price * (*(m.snac + i)).sel_count;
		
	}
	for (int i = 0; i < drink_num; i++) {
		if ((*(m.drin + i)).sel_count == 0)
			continue;
		printf("%s : %d개\n", (*(m.drin + i)).name, (*(m.drin + i)).sel_count);
		fprintf(fwp, "%s : %d개\n", (*(m.drin + i)).name, (*(m.drin + i)).sel_count);
		total_price += (*(m.drin + i)).price * (*(m.drin + i)).sel_count;
	}
	printf("총 가격 : %d\n", total_price);
	fprintf(fwp,"총 가격 : %d\n", total_price);
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
	frp = fopen("drink2.txt", "r");
	m.drin = malloc(sizeof(struct drink) * 1);
	int Is_fir = 0;
	while (1) {
		if (Is_fir == 0) {
			char trash[30];
			fscanf(frp, "%[^\n]\n", trash);
		
			Is_fir = 1;
			continue;
		}
		if (feof(frp))
			break;

		char imsi[50];
		int pr = 0, cn=0;
		fscanf(frp, "%[^\t]\t%d", imsi,&pr);
		fscanf(frp, "\t%d\n", &cn);
		

		int siz = strlen(imsi);
		m.drin = realloc(m.drin, sizeof(struct drink) * (drink_num + 1));
		(*(m.drin + drink_num)).name = (char*)malloc(sizeof(char) * siz + 1);
		strcpy((*(m.drin + drink_num)).name, imsi);
		//printf("%s\n", (*(drin + drink_num)).name);
		(*(m.drin + drink_num)).id = drink_num;
		(*(m.drin + drink_num)).sel_count = 0;
		(*(m.drin + drink_num)).quan = cn;
		(*(m.drin + drink_num)).price = pr;

		drink_num++;
	}
}

void reset_snack_menu() {
	FILE* frp;
	frp = fopen("snack2.txt", "r");
	m.snac = malloc(sizeof(struct snack) * 1);
	int Is_fir = 0;
	while (1) {
		if (Is_fir == 0) {
			char trash[30];
			fscanf(frp, "%[^\n]\n", trash);
			Is_fir = 1;
			continue;
		}
		if (feof(frp))
			break;
		char imsi[50];
		int pr = 0, cn = 0;
		fscanf(frp, "%[^\t]\t%d", imsi, &pr);
		fscanf(frp, "\t%d\n", &cn);
		
		int siz = strlen(imsi);
		m.snac = realloc(m.snac, sizeof(struct snack) * (snack_num + 1));
		(*(m.snac + snack_num)).name = malloc(sizeof(char) * siz + 1);
		strcpy((*(m.snac + snack_num)).name, imsi);
		(*(m.snac + snack_num)).id = snack_num;
		(*(m.snac + snack_num)).sel_count = 0;
		(*(m.snac + snack_num)).quan = cn;
		(*(m.snac + snack_num)).price = pr;
		snack_num++;
	}
}
