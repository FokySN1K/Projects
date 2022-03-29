﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BIG long long unsigned 
#define MOD 524288 //2**19 // модуль от числа
#define POWER 13 // степень числа





BIG get_hash(char* string); // хеш от подстроки
void search_pattern_in_text(char* FILE_WAY, char* STRING); 


int main() {
	char* FILE_WAY = "C:/Yaroslav/Projects/Algorithm/2_task/3/EXAMPLE.txt";
	char* STRING = "Now we study at the same university And thou";//подстрока


	search_pattern_in_text(FILE_WAY, STRING);
	

}

BIG get_hash(char* string) {
	BIG len_string = strlen(string);
	BIG result = 0;
	for (BIG i = 0; i < len_string; i++) {
		result = (result * POWER + string[i]) % MOD;
	}
	return result;
}
void search_pattern_in_text(char* FILE_WAY, char* STRING) {
	freopen(FILE_WAY, "r", stdin);
	
	int c;
	BIG len_STRING = strlen(STRING);
	BIG HASH_STRING = get_hash(STRING);
	char* additional_string = (char*)calloc(len_STRING + 1, sizeof(char));
	fgets(additional_string, len_STRING + 1, stdin);
	BIG additional_hash = get_hash(additional_string);

	BIG MAX_POWER = 1;
	for (BIG i = 1; i < len_STRING; i++) {
		MAX_POWER = (MAX_POWER * POWER) % MOD;
	}
	//printf("%s", additional_string);
	for (BIG i = 0; (c = getchar()) != EOF; i++) {
		if (HASH_STRING == additional_hash) {
			if (!strcmp(STRING, additional_string)) {
				printf("%llu\n", i); // индекс вхождения
			}
		}
		
		// сначала меняем хеш дополнительной строки
		// потом саму строку
		additional_hash = ((additional_hash - additional_string[0]*MAX_POWER)*POWER + c) % MOD;
		if (additional_hash < 0) {
			additional_hash += MOD;
		}
		for (BIG j = 0; j < len_STRING - 1; j++) {
			additional_string[j] = additional_string[j + 1];
		}
		////////////
		////////////  !!!!!!!!!!!!! ГДЕ-ТО ЗДЕСЬ ОШИБКА !!!!!!!!!!
		////////////
		additional_string[len_STRING - 1] = c;
		//printf("%c", c);
		printf("%s!\n", additional_string);
	}

	fclose(stdin);
}
