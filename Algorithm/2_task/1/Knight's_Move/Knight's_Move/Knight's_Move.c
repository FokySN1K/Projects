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
void massiv_N_N_to_null(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			massiv[i][j] = 0;
		}
	}
}
int test_solution(int** massiv, int N) {
	int sum_proverka = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			solution_with_check(massiv, N, i, j);
			sum_proverka += proverka(massiv, N);
			if (!proverka(massiv, N)) {
				printf("%i %i\n", i, j);
			}
			massiv_N_N_to_null(massiv, N);
		}
	}
	return sum_proverka;
}
int solution_with_check(int** massiv, int N, int x1, int y1) {
	int horse = 1;
	massiv[x1][y1] = 1;
	solution(massiv, N, x1, y1, &horse);
	if (proverka(massiv, N)) {
		return 1;
	}
	else {
		// ищем поле, которое будет правильным
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				horse = 1;
				massiv_N_N_to_null(massiv, N);
				massiv[i][j] = 1;
				solution(massiv, N, i, j, &horse);
				if (proverka(massiv, N)) {
					int difference = massiv[x1][y1] - 1;
					// изменяем ходы, как будто мы ходили с заданного поля
					for (int x2 = 0; x2 < N; x2++) {
						for (int y2 = 0; y2 < N; y2++) {
							if (massiv[x2][y2] > difference) {
								massiv[x2][y2] -= difference;
							}
							else {
								massiv[x2][y2] = N*N + massiv[x2][y2] - difference;
							}
						}
					}
					return 1;
				}
			}
		}
		return 0;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");

	int size_massiv = 3;
	int** massiv = NULL; // таблица, по которой ходит конь
	int horse = 1;
	int x1 = 2, y1 = 0;

	massiv = create_massiv_N_N(size_massiv);
	
	//printf("%i", test_solution(massiv, size_massiv));

	if (solution_with_check(massiv, size_massiv, x1, y1)) {
		beatiful_print_moving_from_horse(massiv, size_massiv);
		print_massiv_N_N(massiv, size_massiv);
	}
	else {
		printf("К сожалению, произошла ошибка. Возможно, ответа не существует\n");
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
			printf("%3i ", massiv[i][j]);
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
	return sum;
}
void solution(int** massiv, int N, int x1, int y1, int* horse) {
	int min = 100000;
	int x3 = 0, y3 = 0;
	int sum = 0;
	for (int x2 = 0; x2 < N; x2++) {
		for (int y2 = 0; y2 < N; y2++) {
			if (massiv[x2][y2] == 0 && can_horse_move(x1, y1, x2, y2)) {
				//printf("%i %i\n", x2, y2);
				sum = sum_of_moves(massiv, N, x2, y2);

				if (sum < min) { // sum = 0 -> клетка занята
					min = sum;
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
