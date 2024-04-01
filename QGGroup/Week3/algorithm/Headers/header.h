/*
* 实现插入(InsertSort)				√
* 归并(MergeSort)
* 快排(QuickSort)(递归版)
* 计数(CountSort)
* 基数计数排序(RadixCountSort)
*/

typedef enum Status {
	SUCCESS,
	ERROR
} Status;

char ch_menu[8][50] = {
	"Here are functions you can use:",
	"A. Generate the time of use in 3 level",
	"B. Generate the time of use in lots of small data",
	"C. Generate data and save to file",
	"D. Read data and save to file",
	"E. Read data and color sort",
	"F. Read data and find the num after A numbers",
	"Please enter the letter:"
};

void menu();

Status GenerateAndSort(clock_t* usedoftime, int* data, int length);

Status GenerateRandomData(int* data, int length, int max);

Status InsertSort(int* num, int length);

Status MergeSort(int* num, int begin, int end);

Status QuickSort(int* num, int begin, int end);

Status CountSort(int* num, int length);

Status RadixCountSort(int* num, int length);

Status ColorSort(int* num, int length);

Status FindtheSEQofData(int* num, int begin, int end, int seq, int* ans);

Status SwapNum(int* a, int* b);