#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


int check_ID(char* id); //관리자라면 0 서비스모드라면 1
int main() {
	char who[20];
	while (1) {
		printf("Mode Select (admin or user) :");
		scanf("%s", who);
		int who_result = check_ID(who);
		if (who_result == 0) { // 관리자 모드
			printf("Admin mode\n");
			break;
		}
		else if (who_result == 1) {
			printf("User mode\n");
			break;
		}
		else {
			printf("Error : Wrong Input!\n");
		}
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
