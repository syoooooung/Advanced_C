#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>



struct libr {
	int id;
	char* name;
	int num;
};
struct libr lib[40];
struct storage {
	int id;
	char* name;
	int num;
};
struct Node {
	int data;
	struct Node* next;
	struct Node* pv;
	struct libr library;
	struct storage stor;
};

struct Node* book_head = NULL;
struct Node* stor_head = NULL;

struct Node* create_node(int data) {
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

struct Node* insert_booknode(struct Node** head, int data, struct libr inlib) {
	struct Node* new_node = create_node(data);
	new_node->library = inlib;
	if (*head == NULL) {
		*head = new_node;
	}
	else {
		struct Node* temp = *head;
		struct Node* iamprev = *head;
		while (temp->next != NULL) {
			iamprev = temp;
			temp = temp->next;
		}
		temp->next = new_node;
		new_node->pv = temp;
	}

	return head;
}

struct Node* insert_storagenode(struct Node** head, int data, struct storage st) {
	struct Node* new_node = create_node(data);
	new_node->stor = st;
	if (*head == NULL) {
		*head = new_node;
	}
	else {
		struct Node* temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_node;
		new_node->pv = temp;
	}
	return head;
}

struct Node* delete_node(struct Node* head, int target) {
	struct Node* current = head;
	struct Node* prev = NULL;
	printf("삭제 시작\n");
	if (current != NULL && current->data == target) { //첫번째노드삭제
		head = current->next;

		free(current);
		return;
	}
	while (current != NULL && current->data != target) {
		prev = current;
		current = current->next;
	}
	if (current == NULL) {
		printf("삭제할 노드가 없습니다\n");
		return;
	}
	prev->next = current->next;
	current->next->pv = prev;
	printf("해당 노드를 삭제했습니다\n");
	free(current);
}

void print_list(struct Node* head) {
	struct Node* current = head;
	while (current != NULL) {
		printf("%d", current->data);
		if (current->next != NULL)
			printf(" ->");
		current = current->next;
	}
	printf("\n");
}

struct storage Storage[100];
int line = 0, line2 = 0;;
void initial_booklist(); //보유 도서 현황을 초기화
int manage_booklist(int id); //사용자 요청에 따라 보유도서 현황 업데이트
void print_booklist();
void admin_check();
void storage_check();
void update_book();
void print_storage();
int main(int argc, char* argv[]) {
	int Is_manage = 0;

	if (strcmp(argv[1], "관리자") == 0)
		Is_manage = 1;

	if (Is_manage) {
		admin_check();
	}
	initial_booklist();
	print_booklist();
	if (Is_manage) {
		int serv = 0;
		printf("\n.\n.\n도서 업데이트\n.\n.\n");
		storage_check();
		update_book();
		print_booklist();
		print_storage();
		printf("서비스 모드로 전환하려면 0을 종료하려면 1을 입력하세요");
		scanf("%d", &serv);
		if (serv == 1)
			return 0;
		printf("\n====서비스 모드로 전환합니다.====\n");
	}
	int input_id = 0;
	while (1) {
		if (input_id == -1)
			print_booklist();

		printf("원하는 id를 입력하세요(-1 입력시 list 제공 ,-2 입력시 종료) : ");
		scanf("%d", &input_id);
		if (input_id == -2)
			break;
		manage_booklist(input_id);

	}
}
void update_book() {
	for (int i = 0; i < line; i++) {
		if (lib[i].num == 0) {
			lib[i].num = 3;
			for (int j = 0; j < line2; j++) {
				if (strcmp(lib[i].name, Storage[j].name) == 0) {
					Storage[j].num -= 3;
					if (Storage[j].num == 0)
						delete_node(stor_head, Storage[j].id);
				}
			}
		}
	}
}
void print_storage() {
	FILE* fwp;
	fwp = fopen("storage.txt", "w");
	for (int i = 0; i < line2; i++) {
		fprintf(fwp, "%s\t%d\n", Storage[i].name, Storage[i].num);
	}
	fclose(fwp);
}
int manage_booklist(int id) {
	if (id > line || id < 0) {
		printf("보유하지 않은 도서 id 입니다\n");
		return 0;
	}
	else if (lib[id].num <= 0) {
		printf("해당 도서는 모두 대여되었습니다.\n");
		return 0;
	}
	else {
		printf("해당 도서는 대여가 가능합니다.\n");
		lib[id].num -= 1;
		printf("대여가 완료됐습니다.\n");
		if (lib[id].num <= 0) {
			delete_node(book_head, id);
		}
		return 1;
	}
}
void admin_check() {
	char* tmp = NULL, * tmp2 = NULL;
	char* id = NULL;
	char* passwd = NULL;
	FILE* frp;
	frp = fopen("admin_auth.txt", "r");
	char imsi[100];
	int size = 0;
	fgets(imsi, 100, frp);
	size = strlen(imsi);
	id = (char*)malloc((sizeof(char) * size) - 3);
	int i = 0;
	for (i = 0; i < size - 4; i++)
		imsi[i] = imsi[i + 4];
	imsi[i - 1] = NULL;
	for (; i < size; i++)
		imsi[i] = NULL;
	strcpy(id, imsi);
	fgets(imsi, 100, frp);
	size = strlen(imsi);
	for (i = 0; i < size - 4; i++)
		imsi[i] = imsi[i + 4];
	imsi[i] = '\0';
	for (; i < size; i++)
		imsi[i] = NULL;

	passwd = (char*)malloc((sizeof(char) * size) - 3);
	strcpy(passwd, imsi);
	//printf("%s/%s", id, passwd);
	fclose(frp);
	while (1) {
		char tmp_id[20];
		char tmp_passwd[20];
		printf("id를 입력하세요 :");
		scanf("%s", tmp_id);
		printf("비밀번호를 입력하세요 :");
		scanf("%s", tmp_passwd);
		if (strcmp(id, tmp_id) == 0 && strcmp(passwd, tmp_passwd) == 0) {
			printf("\n=====관리자 모드로 진입합니다====\n");
			break;
		}
		printf("해당하는 정보가 없습니다. 다시 입력해주세요\n");
	}


}
void storage_check() {
	char* p[20];
	char* word[19];
	char imsi[100];
	int i, size = 0;
	FILE* rfp;
	rfp = fopen("storage.txt", "r");
	for (i = 0; i < 100; i++) {
		int n = 0;
		fscanf(rfp, "%[^\t]\t%d\n", imsi, &n);

		size = strlen(imsi);
		char numbertmp[3] = { 0, };

		Storage[i].num = n;
		Storage[i].name = (char*)malloc((sizeof(char) * size) - 2);

		strcpy(Storage[i].name, imsi);

		Storage[i].id = i;
		if (stor_head == NULL) {
			stor_head = create_node(i);
			stor_head->stor = Storage[i];
		}
		else {
			insert_storagenode(&stor_head, i, Storage[i]);

		}

		if (feof(rfp))
			break;
		line2++;
	}
	fclose(rfp);

}
void initial_booklist() {
	char* p[20];
	char* word[19];
	char imsi[100];
	int i, size = 0;
	FILE* rfp;
	rfp = fopen("books.txt", "r");
	for (i = 0; i < 40; i++) {
		int n = 0;
		fscanf(rfp, "%[^\t]\t%d\n", imsi, &n);
		size = strlen(imsi);

		lib[i].num = n;
		lib[i].name = (char*)malloc((sizeof(char) * size) - 1);

		strcpy(lib[i].name, imsi);

		lib[i].id = i;
		if (book_head == NULL) {
			book_head = create_node(i);
			book_head->library = lib[i];
		}
		else {
			insert_booknode(&book_head, i, lib[i]);
		}

		if (feof(rfp))
			break;
		line++;
	}
	fclose(rfp);

}

void print_booklist() {
	struct Node* current = book_head;

	while (current != NULL) {
		printf("%s // ", current->library.name);
		printf("id: %d  // 보유 권수 : %d\n", current->library.id, current->library.num);
		current = current->next;
	}
}
