#include "Header.h"
#include "Header2.h"
using namespace std;
FILE* f_output1;
int** dynamic(int count) // Создание динамического массива.
{

	int** mass;
	mass = (int**)malloc(count * sizeof(int*));
	for (int i = 0; i < count; i++)
		mass[i] = (int*)malloc(count * sizeof(int));
	return mass;
}
int alg(int n, int** arr) {
	int m = 0;
	f_output1 = fopen("out.txt", "a");
	vector<int> deg(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			deg[i] += arr[i][j];

	int first = 0;
	while (!deg[first])  ++first;

	int v1 = -1, v2 = -1;
	bool bad = false;
	for (int i = 0; i < n; ++i)
		if (deg[i] & 1)
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;

	if (v1 != -1)
		++arr[v1][v2], ++arr[v2][v1];

	stack<int> st;
	st.push(first);
	vector<int> res;
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i = 0; i < n; ++i)
			if (arr[v][i])
				break;
		if (i == n)
		{
			res.push_back(v);
			st.pop();
		}
		else
		{
			--arr[v][i];
			--arr[i][v];
			st.push(i);
		}
	}

	if (v1 != -1)
		for (size_t i = 0; i + 1 < res.size(); ++i)
			if (res[i] == v1 && res[i + 1] == v2 || res[i] == v2 && res[i + 1] == v1)
			{
				vector<int> res2;
				for (size_t j = i + 1; j < res.size(); ++j)
					res2.push_back(res[j]);
				for (size_t j = 1; j <= i; ++j)
					res2.push_back(res[j]);
				res = res2;
				break;
			}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (arr[i][j])
				bad = true;

	if (bad) {
		puts("-1");
		fprintf(f_output1, "В матрице нет ни Эйлерова цикл, ни Эйлерова пути\n");
		fprintf(f_output1, "______________________________________________________\n");
		
	}
	else {
		
		if (res[0] == res[res.size()-1]) {
			printf("В матрице есть Эйлеров цикл\n ");
			fprintf(f_output1, "В матрице есть Эйлеров цикл\n");
		}
		else {
			printf("В матрице нет Эйлерова цикл, но есть Эйлеров путь\n");
			fprintf(f_output1, "В матрице нет Эйлерова цикла, но есть Эйлеров путь\n");
			m = 1;
		}
		for (size_t i = 0; i < res.size(); ++i) {

			printf("%d ", res[i] + 1);
			fprintf(f_output1, "%d ", res[i] + 1);

			
		}
		printf("\n");
		fprintf(f_output1, "\n\n\n");
		fprintf(f_output1, "______________________________________________________\n");

	}
	fclose(f_output1);
	return m;
}