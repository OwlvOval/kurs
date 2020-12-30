#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <windows.h>
#include "Header.h"
#include "Header2.h"
FILE* f_output;
FILE* f_input;
int* num;
int** arr;
int** arr1;
int* ar;
int n;
int m;
int main() {
	using namespace std;
	vector<int> ress;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int select, select2;
	printf("Чтобы создать рандомный массив введите 1\n");
	printf("Чтобы открыть массив из файла введите 2\n");
	printf("Чтобы ввести массив вручную введите 3\n");
	printf("Чтобы завершить программу введите 0\n");
	scanf("%d", &select);
	f_output = fopen("out.txt", "w");
	fclose(f_output);
	while (select != 0) {
		f_output = fopen("out.txt", "a");
		if (select == 1) {
			n = 0;
			
			printf("Введите порядок массива\n");
			while (n==0)
			{
				scanf("%d", &n);
				if (n == 0) {
					printf("Порядок массива не может быть равнен нулю\n");
				}
			}

				arr = dynamic(n);
				arr1 = dynamic(n);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j > i) {
						arr[i][j] = rand() % 2;
						arr[j][i] = arr[i][j];
					}
					else if (i == j) arr[i][j] = 0;
				}
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%d ", arr[i][j]);
				}
				printf("\n");
			}
			
			copy(arr1, arr, n);
			fprintf(f_output, "Матрица смежности заданная рандомно: \n");
			print(arr, n);
			m=alg(n, arr);
			if (m == 1) {
				printf("\nЧтобы преобразовать эйлеров путь в цикл, введите один, для выхода введите 0\n");
				scanf("%d", &select2);
				if (select2 == 1) {
					el(n, arr1);
					alg(n, arr1);
				}
			}
		}
		if (select == 2) {
			
			if ((f_input = fopen("in.txt", "r")) == NULL)
			{
				printf("Не удалось открыть файл");
				getchar();
				
			}
			else {
				int k;
				k = in();
				fprintf(f_output, "Матрица смежности считанная из файла: \n");
				print(arr, k);
				for (int i = 0; i < k; i++) {
					for (int j = 0; j < k; j++) {
						printf("%d ", arr[i][j]);
					}
					printf("\n");
				}
				arr1 = dynamic(k);
				copy(arr1, arr, k);
				m = alg(k, arr);
				if (m == 1) {
					printf("\nЧтобы преобразовать эйлеров путь в цикл, введите один, для выхода введите 0\n");
					scanf("%d", &select2);
					if (select2 == 1) {
						el(k, arr1);
						alg(k, arr1);
					}
				}
				fclose(f_input);
			}
			
		}
		if (select == 3) {
			printf("Введите порядок массива\n");
			n = 0;
			while (n == 0)
			{
				scanf("%d", &n);
				if (n == 0) {
					printf("Порядок массива не может быть равнен нулю\n");
				}
			}
			arr = dynamic(n);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("arr[%d][%d]=", i, j);
					scanf("%d", &arr[i][j]);
				}
				
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%d ", arr[i][j]);
				}
				printf("\n");
			}
			arr1 = dynamic(n);
			
			fprintf(f_output, "Матрица смежности заданная вручную: \n");
			print(arr, n);
			copy(arr1, arr, n);
			m = alg(n, arr);
			if (m == 1) {
				printf("\nЧтобы преобразовать эйлеров путь в цикл, введите один, для выхода введите 0\n");
				scanf("%d", &select2);
				if (select2 == 1) {
					el(n, arr1);
					alg(n, arr1);
				}
			}


		}if (select > 3) {
			printf("Данные введены неверно");
		}
		scanf("%d", &select);
	}
}
int in() {
	int m = 0;
	int s = 0, n = 0;
	while ((fscanf_s(f_input, "%d", &s) != EOF)) {
		if (!f_input) break;
		m += 1;
	}
	rewind(f_input); // перематываем файл для повторного чтения
	n = sqrt(m);
	arr = dynamic(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf_s(f_input, "%d", &arr[i][j]);
		}
	}
	return n;
}
void print(int** arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j< n; j++) {
			fprintf(f_output, "%d ", arr[i][j]);
		}
		fprintf(f_output, "\n");
	}

	fclose(f_output);
}
void el(int n, int** arr) {
	int* mas;
	int v1 = -1, v2 = -1;
	mas = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		mas[i] = 0;
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			mas[i] = mas[i] + arr[i][j];

	for (int i = 0; i < n; ++i) {
		if (mas[i] % 2 != 0) {
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
		}
	}
	printf("\n");
	if (arr1[v1][v2] == 0) {
		printf("Эйлеров цикл был получен путём добовления ребра между вершинами %d и %d\n", v1, v2);
		arr1[v1][v2] = 1;
		arr1[v2][v1] = 1;
	}
      else {
		printf("Эйлеров цикл был получен путём удоления ребра между вершинами %d и %d\n", v1, v2);
		arr1[v1][v2] = 0;
		arr1[v2][v1] = 0;
	}
}
void copy(int** arr1, int** arr, int n) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			arr1[i][j] = arr[i][j];
}