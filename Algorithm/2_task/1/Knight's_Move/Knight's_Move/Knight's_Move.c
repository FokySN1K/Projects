#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <dos.h> // для sleep()

int** create_massiv_N_N(int N);
void print_massiv_N_N(int** massiv, int N);
void delete_massiv_N_N(int** massiv, int N);
int can_horse_move(int x1, int y1, int x2, int y2);//проверяем возможен ли такой ход
int sum_of_moves(int** massiv, int N, int x1, int y1); // количество ходов из этой клетки
void solution(int** massiv, int N, int x1, int y1, int* horse); // x1 - строка, y1 - столбец
int proverka(int** massiv, int N);
void beatiful_print_moving_from_horse(int** massiv, int N); // просто красивый вывод

int main() {
	setlocale(LC_ALL, "Rus");

	int size_massiv = 8;
	int** massiv = NULL; // таблица, по которой ходит конь
	int horse = 0;

	massiv = create_massiv_N_N(size_massiv);
	
	int x1 = 0, y1 = 0; // надо вводиить вручную
	massiv[x1][y1] = 1;
	horse += 1;

	solution(massiv, size_massiv, x1, y1, &horse);

	
	if (proverka(massiv, size_massiv)) {
		beatiful_print_moving_from_horse(massiv, size_massiv);
		print_massiv_N_N(massiv, size_massiv);
	}
	else {
		printf("К сожалению, произошла ошибка. Получен неправильный массив\n");
	}
	delete_massiv_N_N(massiv, size_massiv);

}


int** create_massiv_N_N(int N) {
	/*
		Я знаю, что в прошлых задачах ступил, можете не напоминать))
		Лучше писать так!
	*/
	int** massiv = (int**)calloc(N, sizeof(int*));
	for (int i = 0; i < N; i++) {
		massiv[i] = (int*)calloc(N, sizeof(int));
	}
	return massiv;
}
void print_massiv_N_N(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%2i ", massiv[i][j]);
		}
		printf("\n");
	}
	printf("......................\n");
}
void delete_massiv_N_N(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		free(massiv[i]);
	}
	free(massiv);
}
int can_horse_move(int x1, int y1, int x2, int y2) {
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	if ( (dx == 1 && dy == 2) || (dx == 2 && dy == 1)) {
		return 1;
	}
	return 0;
}
int sum_of_moves(int** massiv, int N, int x1, int y1) {
	int sum = 0;
	for (int x2 = 0; x2 < N; x2++) {
		for (int y2 = 0; y2 < N; y2++) {
			if (massiv[x2][y2] == 0 && can_horse_move(x1, y1, x2, y2)) {
				sum++;
			}
		}
	}
	if (sum == 0) {
		return 1; // ходов не осталось -> эта клетка последняя незанятая
	}
	else {
		return sum;
	}
}
void solution(int** massiv, int N, int x1, int y1, int* horse) {
	int max = 100000;
	int x3 = 0, y3 = 0;
	int sum = 0;
	for (int x2 = 0; x2 < N; x2++) {
		for (int y2 = 0; y2 < N; y2++) {
			if (can_horse_move(x1, y1, x2, y2)) {
				//printf("%i %i\n", x2, y2);
				if (massiv[x2][y2] != 0) {
					sum = 0;
				}
				else {
					sum = sum_of_moves(massiv, N, x2, y2);
				}
				if (sum < max && sum != 0) { // sum = 0 -> клетка занята
					max = sum;
					x3 = x2;
					y3 = y2;
				}
			}
		}
	}
	//printf("%i %i\n", x3, y3);
	*horse += 1;
	massiv[x3][y3] = *horse;
	//print_massiv_N_N(massiv, N);
	if (*horse != N*N) {
		solution(massiv, N, x3, y3, horse);
	}
}
int proverka(int** massiv, int N) {
	long long unsigned sum = 0;
	long long unsigned total_sum = 0;
	if (N % 2 == 1) {
		sum = (1 + N * N) / 2 * ( N * N);
	}
	else {
		sum = (N * N) / 2 * (N * N + 1);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			total_sum += massiv[i][j];
		}
	}
	if (sum == total_sum) {
		return 1;
	}
	return 0;
}
void beatiful_print_moving_from_horse(int** massiv, int N) {
	for (int index = 1; index <= N * N; index++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%c ", (massiv[i][j] == index) ? ('K') : ('-'));
			}
			printf("\n");
		}
		Sleep(200);
		printf("\033[0d\033[2J"); // сдвиг курсора(имитация "стирания" консоли)
	}
}
