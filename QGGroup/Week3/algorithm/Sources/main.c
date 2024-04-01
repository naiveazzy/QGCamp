#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "../Headers/header.h"

int main() {

	menu();

	return 0;

	return 0;
}

/*
	菜单，负责选择和调用函数
*/
void menu() {
	while (1) {
		for (int i = 0; i < 8; i++) {
			puts(ch_menu[i]);
		}

		char key = getchar();

		switch (key) {
		case 'A':
		case 'a': {
			clock_t usedoftime[3][5];
			GenerateAndSort(usedoftime[0], NULL, 10000);
			GenerateAndSort(usedoftime[1], NULL, 50000);
			GenerateAndSort(usedoftime[2], NULL, 200000);

			printf("Sort\data\t%d\t%d\t%d\n", 10000, 50000, 200000);
			printf("InsertSort:\t%dms\t%dms\t%dms\n", usedoftime[0][0], usedoftime[1][0], usedoftime[2][0]);
			printf("MergeSort:\t%dms\t%dms\t%dms\n", usedoftime[0][1], usedoftime[1][1], usedoftime[2][1]);
			printf("QuickSort:\t%dms\t%dms\t%dms\n", usedoftime[0][2], usedoftime[1][2], usedoftime[2][2]);
			printf("CountSort:\t%dms\t%dms\t%dms\n", usedoftime[0][3], usedoftime[1][3], usedoftime[2][3]);
			printf("RadixCountSort:\t%dms\t%dms\t%dms\n", usedoftime[0][4], usedoftime[1][4], usedoftime[2][4]);

			break;
		}
		case 'B':
		case 'b': {
			clock_t alloftime[5];
			memset(alloftime, 0, 5 * sizeof(clock_t));
			clock_t usedoftime[5];
			int* data = (int*)malloc(100 * sizeof(int));
			GenerateRandomData(data, 100, 32767);
			for (int i = 0; i < 100000; i++) {
				GenerateAndSort(usedoftime, data, 100);
				for (int j = 0; j < 5; j++) alloftime[j] += usedoftime[j];
			}

			printf("Sort\data\t%d*%d\n", 100000, 100);
			printf("InsertSort:\t%dms\n", alloftime[0]);
			printf("MergeSort:\t%dms\n", alloftime[1]);
			printf("QuickSort:\t%dms\n", alloftime[2]);
			printf("CountSort:\t%dms\n", alloftime[3]);
			printf("RadixCountSort:\t%dms\n", alloftime[4]);
			free(data);

			break;
		}
		case 'C':
		case 'c': {
			int num = 0;
			int ERROR = 0;
			printf("Please enter the number of data:");
			scanf("%d", &num);
			int* data = (int*)malloc(num * sizeof(int));
			GenerateRandomData(data, num, 32767);

			char key;
			printf("A.InsertSort\n");
			printf("B.MergeSort\n");
			printf("C.QuickSort\n");
			printf("D.CountSort\n");
			printf("E.RadixCountSort\n");
			printf("Please enter the way to sort:");
			getchar();
			scanf("%c", &key);

			switch (key) {
			case 'A':
			case 'a': {
				InsertSort(data, num);
				break;
			}
			case 'B':
			case 'b': {
				MergeSort(data, 0, num - 1);
				break;
			}
			case 'C':
			case 'c': {
				QuickSort(data, 0, num - 1);
				break;
			}
			case 'D':
			case 'd': {
				CountSort(data, 0, num - 1);
				break;
			}
			case 'E':
			case 'e': {
				RadixCountSort(data, num);
				break;
			}
			default: {
				ERROR = 1;
				break;
			}
			}

			if (ERROR == 1) break;

			FILE* fp = fopen("output.txt", "w+");
			for (int i = 0; i < num; i++) {
				fprintf(fp, "%d ", data[i]);
			}
			printf("File saved.");

			fclose(fp);
			free(data);
			break;
		}

		case 'D':
		case 'd': {
			FILE* fp = fopen("input.txt", "r+");
			if (fp == NULL) {
				printf("No File! Please create a file named input.txt");
				break;
			}
			int length = 100000;
			int* data = (int*)malloc(length * sizeof(int));
			int num = 0;
			while (!feof(fp)) {
				if (num == length) {
					length += 100000;
					data = (int*)realloc(data, length * sizeof(int));
				}
				fscanf(fp, "%d ", &data[num++]);
 			}
			fclose(fp);

			char key;
			printf("A.InsertSort\n");
			printf("B.MergeSort\n");
			printf("C.QuickSort\n");
			printf("D.CountSort\n");
			printf("E.RadixCountSort\n");
			printf("Please enter the way to sort:");
			getchar();
			scanf("%c", &key);

			switch (key) {
			case 'A':
			case 'a': {
				InsertSort(data, num);
			}
			case 'B':
			case 'b': {
				MergeSort(data, 0, num - 1);
			}
			case 'C':
			case 'c': {
				QuickSort(data, 0, num - 1);
			}
			case 'D':
			case 'd': {
				CountSort(data, 0, num - 1);
			}
			case 'E':
			case 'e': {
				RadixCountSort(data, num);
			}
			}

			fp = fopen("output.txt", "w+");
			for (int i = 0; i < num; i++) {
				fprintf(fp, "%d ", data[i]);
			}
			printf("File saved.");

			fclose(fp);
			free(data);
			break;
		}
		case 'E':
		case 'e': {
			FILE* fp = fopen("input.txt", "r+");
			if (fp == NULL) {
				printf("No File! Please create a file named input.txt");
				break;
			}
			int length = 100000;
			int* data = (int*)malloc(length * sizeof(int));
			int num = 0;
			while (!feof(fp)) {
				if (num == length) {
					length += 100000;
					data = (int*)realloc(data, length * sizeof(int));
				}
				fscanf(fp, "%d ", &data[num++]);
			}
			fclose(fp);

			ColorSort(data, num);

			fp = fopen("output.txt", "w+");
			for (int i = 0; i < num; i++) {
				fprintf(fp, "%d ", data[i]);
			}
			printf("File saved.");

			fclose(fp);
			free(data);
			break;
		}
		case 'F':
		case 'f': {

			FILE* fp = fopen("input.txt", "r+");
			if (fp == NULL) {
				printf("No File! Please create a file named input.txt");
				break;
			}
			int length = 100000;
			int* data = (int*)malloc(length * sizeof(int));
			int num = 0;
			while (!feof(fp)) {
				if (num == length) {
					length += 100000;
					data = (int*)realloc(data, length * sizeof(int));
				}
				fscanf(fp, "%d ", &data[num++]);
			}
			fclose(fp);

			getchar();
			printf("Please enter A:");
			int seq;
			scanf("%d", &seq);
			
			int ans;
			FindtheSEQofData(data, 0, num - 1, seq - 1, &ans);
			printf("ANS: %d\n", ans);
			break;
		}
		default: break;
		}
		getchar();
	}
}


/*
	生成数据并返回用时
*/
Status GenerateAndSort(clock_t* usedoftime, int* data, int length) {
	
	// 如果没有输入数据则新建
	int isdatanull = 0;
	if (data == NULL) {
		data = (int*)malloc(length * sizeof(int));
		GenerateRandomData(data, length, 7355608);
		isdatanull = 1;
	}
	
	// 逐个排序并返回结果
	for (int i = 0; i < 5; i++) {
		clock_t before = clock();
		switch (i) {
		case 0: {
			InsertSort(data, length);
			break;
		}
		case 1: {
			MergeSort(data, 0, length - 1);
			break;
		}
		case 2: {
			QuickSort(data, 0, length - 1);
			break;
		}
		case 3: {
			CountSort(data, length);
			break;
		}
		case 4: {
			RadixCountSort(data, length);
			break;
		}
		default: break;
		}
		clock_t after = clock();

		usedoftime[i] = after - before;
	}

	if (isdatanull == 1) {
		free(data);
	}
}

/*
	生成随机数据
*/
Status GenerateRandomData(int* data, int length, int max) {
	srand(time(NULL));

	if (max <= 32767) {
		for (int i = 0; i < length; i++) {
			data[i] = rand();
			srand(rand());
		}
		return SUCCESS;
	}

	for (int i = 0; i < length; i++) {
		data[i] = rand();
		srand(rand());
		data[i] *= rand();
		data[i] %= max;
		srand(rand());
	}

	return SUCCESS;
}


Status InsertSort(int* num, int length) {

	// 健壮性
	if (num == NULL || length == 0) return ERROR;

	// i定义每次开始往前插入的位置
	for (int i = 1; i < length; i++) {

		// j从i的位置开始往前插入
		for (int j = i; j > 0; j--) {

			//不断将num[j-1]与num[j]进行交换，直到遇到num[j-1]<[j]
			if (num[j - 1] >= num[j]) {

				// 交换num[j-1]与num[j]
				SwapNum(num + j - 1, num + j);
			}
			else {
				break;
			}
		}
	}

	return SUCCESS;
}


Status MergeSort(int* num, int begin, int end) {

	// 健壮性
	if (num == NULL) return ERROR;

	if (begin > end) return ERROR;

	// 如果只需排序一个数字，直接返回
	if (begin == end) return SUCCESS;

	// 如果需要排序两个数字，判断大小交换并返回
	if (end - begin == 1) {
		if (num[begin] > num[end]) {
			SwapNum(num + begin, num + end);
		}

		return SUCCESS;
	}

	// 如果需要排序三个数字及以上
	// 将其拆分为两组，再进行排序
	MergeSort(num, begin, (begin + end) / 2);
	MergeSort(num, (begin + end) / 2 + 1, end);

	// 声明排序后数组，与插入顺序变量
	int* sortednum = (int*)malloc(sizeof(int) * (end - begin + 1));
	int seq = 0;

	// 对两组排序后的数组依次比较
	int seq_a = begin;
	int seq_b = (begin + end) / 2 + 1;
	while (seq_a <= (begin + end) / 2 || seq_b <= end) {

		if ((seq_b > end || num[seq_a] <= num[seq_b]) && seq_a <= (begin + end) / 2) {
			sortednum[seq++] = num[seq_a++];
			continue;
		}

		if ((seq_a > (begin + end) / 2 || num[seq_a] > num[seq_b]) && seq_b <= end) {
			sortednum[seq++] = num[seq_b++];
			continue;
		}
	}


	seq = 0;
	for (int i = begin; i <= end; i++) {
		num[i] = sortednum[seq++];
	}

	free(sortednum);

	return SUCCESS;


}


Status QuickSort(int* num, int begin, int end) {

	if (num == NULL || end < begin) return ERROR;

	if (end == begin) return SUCCESS;

	// 定义索引为第一个数
	int index = num[begin];
	int i = begin, j = end;

	while (i != j) {
		
		// 将j向后移动到比index大的位置并赋值到num[i]
		while (i != j && num[j] >= index) j--;

		if (i == j) break;

		num[i] = num[j];

		// 将i向前移动到比index小的位置并赋值到num[j]
		while (i != j && num[i] < index) i++;

		if (i == j) break;

		num[j] = num[i];
	}

	num[i] = index;

	// 递归，继续排序
	QuickSort(num, begin, i - 1);
	QuickSort(num, i + 1, end);

	return SUCCESS;

}


Status CountSort(int* num, int length) {


	if (num == NULL || length == 0) return ERROR;

	int max = 0, i = 0;

	// 找到最大数
	for (i = 0; i < length; i++) {
		if (num[i] > max) {
			max = num[i];
		}
	}

	// 新建木桶
	int* countnum = (int*)malloc((max + 1) * sizeof(int));
	memset(countnum, 0, (max + 1) * sizeof(int));

	// 对每一个数逐个计数
	for (i = 0; i < length; i++) {

		if (num[i] > max) {
			countnum = (int*)realloc(countnum, (num[i] + 1) * sizeof(int));
			for (int j = max + 1; j <= num[i]; j++) countnum[j] = 0;
			max = num[i];

		}

		countnum[num[i]]++;
	}

	// 将排序后结果赋值
	int j = 0;
	for (i = 0; i <= max; i++) {
		while (countnum[i] != 0) {
			countnum[i]--;
			num[j++] = i;
		}
	}

	free(countnum);

	return SUCCESS;
}


Status RadixCountSort(int* num, int length) {

	int* cache = (int*)malloc(length * sizeof(int));
	int count[10];
	memset(count, 0, 10 * sizeof(int));

	// 找到最大值
	int max = 0;
	for (int i = 0; i < length; i++) {
		if (max < num[i]) max = num[i];
	}

	// i为最小的大于最大值的数，对每一位进行排序
	for (int i = 1; i <= max; i *= 10) {
		memset(count, 0, 10 * sizeof(int));

		for (int j = 0; j < length; j++) count[(num[j] / i) % 10]++;

		for (int j = 1; j < 10; j++) count[j] += count[j - 1];

		for (int j = length - 1; j >= 0; j--) {
			cache[--count[(num[j] / i) % 10]] = num[j];
		}

		for (int j = 0; j < length; j++) num[j] = cache[j];
	}

	free(cache);

	return SUCCESS;

}


Status ColorSort(int* num, int length) {
	int p0 = 0, p1 = 1, p2 = length - 1;

	while (num[p0] == 0) p0++;
	while (num[p2] == 2) p2--;

	p1 = p0;

	while (p1 != p2) {

		// 如果p1为1，前进
		if (num[p1] == 1) {
			p1++;
			continue;
		}

		// 如果p1为0，与p0交换
		if (num[p1] == 0) {
			SwapNum(&num[p0++], &num[p1++]);
			continue;
		}

		// 如果p1为2，与p2交换
		if (num[p1] == 2) {
			SwapNum(&num[p2--], &num[p1]);
			continue;
		}
	}

	return SUCCESS;
}

Status FindtheSEQofData(int* num, int begin, int end, int seq, int* ans) {

	if (num == NULL || end < begin) return ERROR;

	if (end == begin) return SUCCESS;

	int index = num[begin];
	int i = begin, j = end;

	// 将数组分为大于index和小于index两部分
	while (i != j) {

		while (i != j && num[j] >= index) j--;

		if (i == j) break;

		num[i] = num[j];

		while (i != j && num[i] < index) i++;

		if (i == j) break;

		num[j] = num[i];
	}

	num[i] = index;

	// 如果已经找到答案，则赋值
	if (i == seq) *ans = index;

	// 如果答案在小的那一组，继续排序
	if (i > seq) {
		FindtheSEQofData(num, begin, i - 1, seq, ans);
	}

	// 如果答案在大的那一组，继续排序
	if (i < seq) {
		FindtheSEQofData(num, i + 1, end, seq, ans);
	}

	return SUCCESS;

}

Status SwapNum(int* a, int* b) {

	if (a == NULL || b == NULL) return ERROR;


	int cache = *a;
	*a = *b;
	*b = cache;

	return SUCCESS;
}