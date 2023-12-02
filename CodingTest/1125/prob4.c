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
struct menu { //가게 정보
	struct drink* drin;
	struct snack* snac;
	int current_cost; //보유금
	int zero_cnt; //재고량이 0인 메뉴 개수
};

struct company {
	struct drink* drin;
	struct snack* snac;
	int price;
	int quan;
};

struct menu m;
struct company c11;
struct company coup;
struct company gmar;

int drink_num = 0;
int snack_num = 0;
int c11_num = 0;
int coup_num = 0;
int gmar_num = 0;
struct menu us_m;

int check_ID(char* id); //관리자라면 0 서비스모드라면 1
void reset_drink_menu(); // 음료 초기ㅗ하
void reset_snack_menu(); //간식 초기화
void reset_company();
void service_mode();
void print_snack();
void print_drink();
void print_receip(); //사용자 주문 내용 출력

void admin_mode(); // 현재 재고량 확인.
void order_print(); //재고 주문 결과 출력
int find_company();
void check_zero();
int main() {
	char who[20];
	int who_result = 0;
	m.current_cost = 30000;
	while (1) {
		printf("Mode Select (admin or user) :");
		scanf("%s", who);
		who_result = check_ID(who);
		if (who_result == 0) { // 관리자 모드
			printf("Admin mode\n");
			admin_mode();
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
void admin_mode() {
	//현재 재고량 확인 후
	// 주문 대상 외부회사 선정
	// 주문 수행 시 우리의 재고량은 상승시키고 보유금은 감소시킴
	reset_company();
	while (1) { //3개보다 작을 시 exit
		service_mode();
		
		check_zero();
		if (m.zero_cnt < 3)
			break;
		find_company();
		order_print();
	}
}
void order_print() {
	print_snack();
	print_drink();
	printf("현재 보유금 : %d\n", m.current_cost);
}
int find_company() {
	struct menu need;
	int Is_full = 0;
	need.drin = malloc(sizeof(struct drink) * 1);
	need.snac = malloc(sizeof(struct snack) * 1);
	int need_drink = 0;
	int need_snack = 0;
	/*
	for (int i = 0; i < snack_num; i++) {
		if ((*(m.snac + i)).quan == 0) {
			need.snac = realloc(need.snac, sizeof(struct snack) * (need_snack + 1));
			int siz = strlen((*(m.snac + i)).name);
			*(need.snac + need_snack)->name = malloc(sizeof(char) * siz +1);
			strcpy(*(need.snac + need_snack)->name, (*(m.snac + i)).name);
			need_snack++;
		}
	}
	for (int i = 0; i < drink_num; i++) {
		if ((*(m.drin + i)).quan == 0) {
			need.drin = realloc(need.drin, sizeof(struct drink) * (need_drink + 1));
			int siz = strlen((*(m.drin + i)).name);
			*(need.drin + need_drink)->name = malloc(sizeof(char) * siz + 1);
			strcpy(*(need.drin + need_drink)->name, (*(m.drin + i)).name);
			need_drink++;
		}
	}*/

	int c1 = 0, cp = 0, gm = 0;
	int cfull = 0, cpfull = 0, gmfull = 0; //0이면 모든 재고 있음 , 1이면 모자람
	for (int i = 0; i < snack_num; i++) {
		
		if ((*(m.snac + i)).quan == 0) {
			for (int j = 0; j < coup_num; j++) {
				if (strcmp((*(m.snac + i)).name, (*(coup.drin + j)).name) == 0){
					int cal_num = 0;
					if ((*(coup.drin + j)).quan >= 5) {
						cal_num = 5;
						//(*(coup.drin + j)).quan -= 5;
					}
					else {
						cal_num = (*(coup.drin + j)).quan;
						//(*(coup.drin + j)).quan -= cal_num;
					}
					cp += cal_num * (*(coup.drin + j)).price;
				}
			}
			//
			for (int j = 0; j < c11_num; j++) {
				if (strcmp((*(m.snac + i)).name, (*(c11.drin + j)).name) == 0) {
					int cal_num = 0;
					if ((*(c11.drin + j)).quan >= 5) {
						cal_num = 5;
						//(*(c11.drin + j)).quan -= 5;
					}
					else {
						cal_num = (*(c11.drin + j)).quan;
						//(*(c11.drin + j)).quan -= cal_num;
					}
					c1 += cal_num * (*(c11.drin + j)).price;
				}
			}
			//
			for (int j = 0; j < c11_num; j++) {
				if (strcmp((*(m.snac + i)).name, (*(gmar.drin + j)).name) == 0) {
					int cal_num = 0;
					if ((*(gmar.drin + j)).quan >= 5) {
						cal_num = 5;
						//(*(gmar.drin + j)).quan -= 5;
					}
					else {
						cal_num = (*(gmar.drin + j)).quan;
						//(*(gmar.drin + j)).quan -= cal_num;
					}
					gm += cal_num * (*(gmar.drin + j)).price;
				}
			}

		}
	}
	for (int i = 0; i < drink_num; i++) {
		if ((*(m.drin + i)).quan == 0) {
			for (int j = 0; j < coup_num; j++) {
				if (strcmp((*(m.drin + i)).name, (*(coup.drin + j)).name) == 0) {
					int cal_num = 0;
					if ((*(coup.drin + j)).quan >= 5) {
						cal_num = 5;
						//(*(coup.drin + j)).quan -= 5;
					}
					else {
						cal_num = (*(coup.drin + j)).quan;
						//(*(coup.drin + j)).quan -= cal_num;
					}
					cp += cal_num * (*(coup.drin + j)).price;
				}
			}
			//
			for (int j = 0; j < c11_num; j++) {
				if (strcmp((*(m.drin + i)).name, (*(c11.drin + j)).name) == 0) {
					int cal_num = 0;
					if ((*(c11.drin + j)).quan >= 5) {
						cal_num = 5;
						//(*(c11.drin + j)).quan -= 5;
					}
					else {
						cal_num = (*(c11.drin + j)).quan;
						//(*(c11.drin + j)).quan -= cal_num;
					}
					c1 += cal_num * (*(c11.drin + j)).price;
				}
			}
			//
			for (int j = 0; j < c11_num; j++) {
				if (strcmp((*(m.drin + i)).name, (*(gmar.drin + j)).name) == 0) {
					int cal_num = 0;
					if ((*(gmar.drin + j)).quan >= 5) {
						cal_num = 5;
						//(*(gmar.drin + j)).quan -= 5;
					}
					else {
						cal_num = (*(gmar.drin + j)).quan;
						//(*(gmar.drin + j)).quan -= cal_num;
					}
					gm += cal_num * (*(gmar.drin + j)).price;
				}
			}

		}
	}
	int tota = 0;
	int who_min = 0; //0은 쿠팡 ,1 은 11 . 2 gmark
	if (gm <= c1 && gm < cp) {
		who_min = 2;
		tota = gm;
	}
	else if (c1 <= gm && c1 <= cp) {
		who_min = 1;
		tota = c1;
	}
	else if (cp <= c1 && cp <= gm) {
		who_min = 0;
		tota = cp;
	}

	
	for (int i = 0; i < snack_num; i++) {

		if ((*(m.snac + i)).quan == 0) {
			if (who_min == 0) {
				for (int j = 0; j < coup_num; j++) {
					if (strcmp((*(m.snac + i)).name, (*(coup.drin + j)).name) == 0) {
						int cal_num = 0;
						if ((*(coup.drin + j)).quan >= 5) {
							cal_num = 5;
							(*(coup.drin + j)).quan -= 5;
						}
						else {
							cal_num = (*(coup.drin + j)).quan;
							(*(coup.drin + j)).quan -= cal_num;
						}
						cp += cal_num * (*(coup.drin + j)).price;
					}
				}
			}
			//
			else if (who_min == 1) {
				for (int j = 0; j < c11_num; j++) {
					if (strcmp((*(m.snac + i)).name, (*(c11.drin + j)).name) == 0) {
						int cal_num = 0;
						if ((*(c11.drin + j)).quan >= 5) {
							cal_num = 5;
							(*(c11.drin + j)).quan -= 5;
						}
						else {
							cal_num = (*(c11.drin + j)).quan;
							(*(c11.drin + j)).quan -= cal_num;
						}
						c1 += cal_num * (*(c11.drin + j)).price;
					}
				}
			}
			//
			else {
				for (int j = 0; j < c11_num; j++) {
					if (strcmp((*(m.snac + i)).name, (*(gmar.drin + j)).name) == 0) {
						int cal_num = 0;
						if ((*(gmar.drin + j)).quan >= 5) {
							cal_num = 5;
							(*(gmar.drin + j)).quan -= 5;
						}
						else {
							cal_num = (*(gmar.drin + j)).quan;
							(*(gmar.drin + j)).quan -= cal_num;
						}
						gm += cal_num * (*(gmar.drin + j)).price;
					}
				}
			}

		}
	}
	for (int i = 0; i < drink_num; i++) {
		if ((*(m.drin + i)).quan == 0) {
			if (who_min == 0) {
				for (int j = 0; j < coup_num; j++) {
					if (strcmp((*(m.drin + i)).name, (*(coup.drin + j)).name) == 0) {
						int cal_num = 0;
						if ((*(coup.drin + j)).quan >= 5) {
							cal_num = 5;
							(*(coup.drin + j)).quan -= 5;
						}
						else {
							cal_num = (*(coup.drin + j)).quan;
							(*(coup.drin + j)).quan -= cal_num;
						}
						cp += cal_num * (*(coup.drin + j)).price;
					}
				}
			}
			//
			else if (who_min == 1) {
				for (int j = 0; j < c11_num; j++) {
					if (strcmp((*(m.drin + i)).name, (*(c11.drin + j)).name) == 0) {
						int cal_num = 0;
						if ((*(c11.drin + j)).quan >= 5) {
							cal_num = 5;
							(*(c11.drin + j)).quan -= 5;
						}
						else {
							cal_num = (*(c11.drin + j)).quan;
							(*(c11.drin + j)).quan -= cal_num;
						}
						c1 += cal_num * (*(c11.drin + j)).price;
					}
				}
			}
			//
			else {
				for (int j = 0; j < c11_num; j++) {
					if (strcmp((*(m.drin + i)).name, (*(gmar.drin + j)).name) == 0) {
						int cal_num = 0;
						if ((*(gmar.drin + j)).quan >= 5) {
							cal_num = 5;
							(*(gmar.drin + j)).quan -= 5;
						}
						else {
							cal_num = (*(gmar.drin + j)).quan;
							(*(gmar.drin + j)).quan -= cal_num;
						}
						gm += cal_num * (*(gmar.drin + j)).price;
					}
				}
			}

		}
	}
	m.current_cost -= tota;
}

void check_zero() {
	m.zero_cnt = 0;
	for (int i = 0; i < snack_num; i++) {
		if ((*(m.snac + i)).quan == 0)
			m.zero_cnt++;
	}
	for (int i = 0; i < drink_num; i++) {
		if ((*(m.drin + i)).quan == 0)
			m.zero_cnt++;
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
			m.current_cost += (*(m.drin + input_id)).price;
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
			m.current_cost += (*(m.snac + input_id)).price;
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
	fprintf(fwp, "\n======총 주문 내역=====\n\n");
	int total_price = 0;
	for (int i = 0; i < snack_num; i++) {
		if ((*(m.snac + i)).sel_count == 0)
			continue;
		printf("%s : %d개\n", (*(m.snac + i)).name, (*(m.snac + i)).sel_count);
		fprintf(fwp, "%s : %d개\n", (*(m.snac + i)).name, (*(m.snac + i)).sel_count);
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
	fprintf(fwp, "총 가격 : %d\n", total_price);
	fclose(fwp);
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
		int pr = 0, cn = 0;
		fscanf(frp, "%[^\t]\t%d", imsi, &pr);
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
	fclose(frp);
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
	fclose(frp);
}


void reset_company() {
	FILE* frp;
	frp = fopen("coupang.txt", "r");
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
		coup.drin = realloc(coup.drin, sizeof(struct snack) * (coup_num + 1));
		(*(coup.drin + coup_num)).name = malloc((sizeof(char) * siz + 1));
		strcpy((*(coup.drin + coup_num)).name, imsi);
		(*(coup.drin + coup_num)).quan = cn;
		(*(coup.drin + coup_num)).price = pr;
		coup_num++;
	}
	fclose(frp);

	frp = fopen("11st.txt", "r");
	Is_fir = 0;
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
		c11.drin = realloc(c11.drin, sizeof(struct drink) * (c11_num + 1));
		int siz = strlen(imsi);
		(*(c11.drin + coup_num)).name = malloc((sizeof(char) * siz + 1));
		strcpy((*(c11.drin + coup_num)).name, imsi);
		(*(c11.drin + coup_num)).quan = cn;
		(*(c11.drin + coup_num)).price = pr;
		c11_num++;
	}
	fclose(frp);

	frp = fopen("gmarket.txt", "r");
	Is_fir = 0;
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
		gmar.drin = realloc(gmar.drin, sizeof(struct drink) * (gmar_num + 1));
		int siz = strlen(imsi);
		(*(gmar.drin + coup_num)).name = malloc((sizeof(char) * siz + 1));
		strcpy((*(gmar.drin + coup_num)).name, imsi);
		(*(gmar.drin + coup_num)).quan = cn;
		(*(gmar.drin + coup_num)).price = pr;
		gmar_num++;
	}
	
	fclose(frp);
}
