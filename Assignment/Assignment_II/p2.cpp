// 排序演算法效能比較
// 實作五種排序演算法：插入、選擇、快速、合併、堆積排序
// 作者：蔡秀吉 (H. C. Tsai)
// 電子信箱：hctsai@linux
// date: 2025/09/20

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ============================================================
// 資料結構與全域變數
// ============================================================

typedef struct {
	char name[20];
	double time;
	int count;
} Sort_Result;

// ============================================================
// 輔助函數
// ============================================================

// 交換兩個整數
void swap(int *a, int *b)
{
	int t;
	
	t = *a;
	*a = *b;
	*b = t;
}

// 檢查陣列是否已排序
int is_sorted(const int a[], const int n)
{
	int i;
	
	for (i = 0; i < n - 1; i++)
		if (a[i] > a[i + 1])
			return 0;
	return 1;
}

// 複製陣列
void copy_array(int dest[], const int src[], const int n)
{
	int i;
	
	for (i = 0; i < n; i++)
		dest[i] = src[i];
}

// 生成隨機陣列
void generate_random(int a[], const int n, const int seed)
{
	int i;
	
	srandom(seed);
	for (i = 0; i < n; i++)
		a[i] = random() % 100000;
}

// 生成已排序陣列
void generate_sorted(int a[], const int n)
{
	int i;
	
	for (i = 0; i < n; i++)
		a[i] = i;
}

// 生成反向排序陣列
void generate_reversed(int a[], const int n)
{
	int i;
	
	for (i = 0; i < n; i++)
		a[i] = n - i;
}

// 印出陣列（除錯用）
void print_array(const int a[], const int n)
{
	int i;
	
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
		if ((i + 1) % 10 == 0)
			putchar('\n');
	}
	if (n % 10 != 0)
		putchar('\n');
}

// ============================================================
// 排序演算法實作
// ============================================================

// 1. 插入排序 (Insertion Sort)
void insertion_sort(int a[], const int n)
{
	int i, j, key;
	
	for (i = 1; i < n; i++) {
		key = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

// 2. 選擇排序 (Selection Sort)
void selection_sort(int a[], const int n)
{
	int i, j, min;
	
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[min])
				min = j;
		if (min != i)
			swap(&a[i], &a[min]);
	}
}

// 3. 快速排序 (Quick Sort)
int partition(int a[], const int low, const int high)
{
	int pivot, i, j;
	
	pivot = a[high];
	i = low - 1;
	
	for (j = low; j < high; j++) {
		if (a[j] <= pivot) {
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i + 1], &a[high]);
	return i + 1;
}

void quick_sort_recursive(int a[], const int low, const int high)
{
	int pi;
	
	if (low < high) {
		pi = partition(a, low, high);
		quick_sort_recursive(a, low, pi - 1);
		quick_sort_recursive(a, pi + 1, high);
	}
}

void quick_sort(int a[], const int n)
{
	quick_sort_recursive(a, 0, n - 1);
}

// 4. 合併排序 (Merge Sort)
void merge(int a[], const int l, const int m, const int r)
{
	int i, j, k;
	int n1, n2;
	int *L, *R;
	
	n1 = m - l + 1;
	n2 = r - m;
	
	L = (int *) malloc(sizeof(int) * n1);
	R = (int *) malloc(sizeof(int) * n2);
	
	for (i = 0; i < n1; i++)
		L[i] = a[l + i];
	for (j = 0; j < n2; j++)
		R[j] = a[m + 1 + j];
	
	i = 0;
	j = 0;
	k = l;
	
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		} else {
			a[k] = R[j];
			j++;
		}
		k++;
	}
	
	while (i < n1) {
		a[k] = L[i];
		i++;
		k++;
	}
	
	while (j < n2) {
		a[k] = R[j];
		j++;
		k++;
	}
	
	free(L);
	free(R);
}

void merge_sort_recursive(int a[], const int l, const int r)
{
	int m;
	
	if (l < r) {
		m = l + (r - l) / 2;
		merge_sort_recursive(a, l, m);
		merge_sort_recursive(a, m + 1, r);
		merge(a, l, m, r);
	}
}

void merge_sort(int a[], const int n)
{
	merge_sort_recursive(a, 0, n - 1);
}

// 5. 堆積排序 (Heap Sort)
void heapify(int a[], const int n, const int i)
{
	int largest, left, right;
	
	largest = i;
	left = 2 * i + 1;
	right = 2 * i + 2;
	
	if (left < n && a[left] > a[largest])
		largest = left;
	
	if (right < n && a[right] > a[largest])
		largest = right;
	
	if (largest != i) {
		swap(&a[i], &a[largest]);
		heapify(a, n, largest);
	}
}

void heap_sort(int a[], const int n)
{
	int i;
	
	for (i = n / 2 - 1; i >= 0; i--)
		heapify(a, n, i);
	
	for (i = n - 1; i > 0; i--) {
		swap(&a[0], &a[i]);
		heapify(a, i, 0);
	}
}

// ============================================================
// 效能測試函數
// ============================================================

double test_sort(void (*sort_func)(int[], const int), 
                 int a[], const int n, const char *name)
{
	clock_t start, end;
	double cpu_time;
	
	printf("測試 %s...", name);
	fflush(stdout);
	
	start = clock();
	sort_func(a, n);
	end = clock();
	
	cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	if (is_sorted(a, n))
		printf(" 正確");
	else
		printf(" 錯誤！");
	
	printf(" (%.4f 秒)\n", cpu_time);
	
	return cpu_time;
}

// ============================================================
// 主程式
// ============================================================

int main(int ac, char *av[])
{
	int *original, *temp;
	int n, seed, debug, data_type;
	Sort_Result results[5];
	int i;
	
	// 預設參數
	n = 10000;
	seed = 12345;
	debug = 0;
	data_type = 0;  // 0: 隨機, 1: 已排序, 2: 反向
	
	// 讀取命令列參數
	if (ac > 1)
		sscanf(av[1], "%d", &n);
	if (ac > 2)
		sscanf(av[2], "%d", &seed);
	if (ac > 3)
		sscanf(av[3], "%d", &debug);
	if (ac > 4)
		sscanf(av[4], "%d", &data_type);
	
	printf("=================================================\n");
	printf("排序演算法效能比較\n");
	printf("=================================================\n");
	printf("資料量: n = %d\n", n);
	printf("隨機種子: %d\n", seed);
	printf("資料類型: ");
	
	if (data_type == 0)
		printf("隨機資料\n");
	else if (data_type == 1)
		printf("已排序資料\n");
	else
		printf("反向排序資料\n");
	
	printf("除錯模式: %s\n", debug ? "開啟" : "關閉");
	printf("=================================================\n\n");
	
	// 配置記憶體
	original = (int *) malloc(sizeof(int) * n);
	temp = (int *) malloc(sizeof(int) * n);
	
	if (original == NULL || temp == NULL) {
		printf("記憶體配置失敗！\n");
		return 1;
	}
	
	// 生成測試資料
	if (data_type == 0)
		generate_random(original, n, seed);
	else if (data_type == 1)
		generate_sorted(original, n);
	else
		generate_reversed(original, n);
	
	// 除錯模式：印出部分資料
	if (debug && n <= 100) {
		printf("原始資料：\n");
		print_array(original, n);
		putchar('\n');
	}
	
	// 測試各個排序演算法
	// 1. 插入排序
	copy_array(temp, original, n);
	results[0].time = test_sort(insertion_sort, temp, n, "插入排序");
	strcpy(results[0].name, "插入排序");
	if (debug && n <= 100) {
		printf("排序後：\n");
		print_array(temp, n);
		putchar('\n');
	}
	
	// 2. 選擇排序
	copy_array(temp, original, n);
	results[1].time = test_sort(selection_sort, temp, n, "選擇排序");
	strcpy(results[1].name, "選擇排序");
	
	// 3. 快速排序
	copy_array(temp, original, n);
	results[2].time = test_sort(quick_sort, temp, n, "快速排序");
	strcpy(results[2].name, "快速排序");
	
	// 4. 合併排序
	copy_array(temp, original, n);
	results[3].time = test_sort(merge_sort, temp, n, "合併排序");
	strcpy(results[3].name, "合併排序");
	
	// 5. 堆積排序
	copy_array(temp, original, n);
	results[4].time = test_sort(heap_sort, temp, n, "堆積排序");
	strcpy(results[4].name, "堆積排序");
	
	// 印出結果摘要
	printf("\n=================================================\n");
	printf("效能摘要 (n = %d)\n", n);
	printf("=================================================\n");
	printf("%-15s %15s\n", "演算法", "執行時間(秒)");
	printf("-------------------------------------------------\n");
	
	for (i = 0; i < 5; i++)
		printf("%-15s %15.4f\n", results[i].name, results[i].time);
	
	printf("=================================================\n");
	
	// 釋放記憶體
	free(original);
	free(temp);
	
	return 0;
}