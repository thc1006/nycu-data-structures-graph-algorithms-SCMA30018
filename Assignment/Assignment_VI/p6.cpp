// 線段樹區間最大值查詢
// 使用線段樹資料結構高效處理 RMQ (Range Maximum Query)
// 建構時間 O(n)，查詢時間 O(log n)，空間 O(n)

// 作者：蔡秀吉 (H. C. Tsai)
// 電子信箱：hctsai@linux
// date: 2025/11/15

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// ============================================================
// 線段樹資料結構
// ============================================================

typedef struct {
	int *tree;    // 線段樹陣列
	int *arr;     // 原始陣列
	int n;        // 陣列大小
} SegmentTree;

// ============================================================
// 線段樹操作函數
// ============================================================

// 建立線段樹
SegmentTree *create_segment_tree(const int n)
{
	SegmentTree *st;
	
	st = (SegmentTree *) malloc(sizeof(SegmentTree));
	st->n = n;
	st->arr = (int *) malloc(sizeof(int) * n);
	st->tree = (int *) malloc(sizeof(int) * (4 * n));
	
	return st;
}

// 建構線段樹（遞迴）
int build_tree(SegmentTree *st, const int node, const int start, const int end)
{
	int mid, left_max, right_max;
	
	// 葉節點
	if (start == end) {
		st->tree[node] = st->arr[start];
		return st->tree[node];
	}
	
	// 內部節點
	mid = (start + end) / 2;
	left_max = build_tree(st, 2 * node, start, mid);
	right_max = build_tree(st, 2 * node + 1, mid + 1, end);
	
	st->tree[node] = MAX(left_max, right_max);
	return st->tree[node];
}

// 查詢區間最大值（遞迴）
int query_max(const SegmentTree *st, const int node, 
              const int start, const int end,
              const int l, const int r)
{
	int mid, left_max, right_max;
	
	// 完全不相交
	if (r < start || end < l)
		return INT_MIN;
	
	// 完全包含
	if (l <= start && end <= r)
		return st->tree[node];
	
	// 部分相交
	mid = (start + end) / 2;
	left_max = query_max(st, 2 * node, start, mid, l, r);
	right_max = query_max(st, 2 * node + 1, mid + 1, end, l, r);
	
	return MAX(left_max, right_max);
}

// 初始化線段樹
void init_segment_tree(SegmentTree *st, const int arr[], const int n)
{
	int i;
	
	for (i = 0; i < n; i++)
		st->arr[i] = arr[i];
	
	build_tree(st, 1, 0, n - 1);
}

// 查詢介面
int query(const SegmentTree *st, const int l, const int r)
{
	return query_max(st, 1, 0, st->n - 1, l, r);
}

// 釋放線段樹
void free_segment_tree(SegmentTree *st)
{
	free(st->arr);
	free(st->tree);
	free(st);
}

// ============================================================
// 暴力法（用於比較和驗證）
// ============================================================

int brute_force_max(const int arr[], const int l, const int r)
{
	int i, max_val;
	
	max_val = arr[l];
	for (i = l + 1; i <= r; i++)
		if (arr[i] > max_val)
			max_val = arr[i];
	
	return max_val;
}

// ============================================================
// 輔助函數
// ============================================================

// 生成隨機陣列
void generate_random_array(int arr[], const int n, const int max_val)
{
	int i;
	
	for (i = 0; i < n; i++)
		arr[i] = rand() % max_val;
}

// 印出陣列（小規模時）
void print_array(const int arr[], const int n)
{
	int i;
	
	printf("陣列: [");
	for (i = 0; i < n; i++) {
		printf("%d", arr[i]);
		if (i < n - 1)
			printf(", ");
	}
	printf("]\n");
}

// 印出線段樹結構（除錯用）
void print_tree_helper(const SegmentTree *st, const int node, 
                       const int start, const int end, const int depth)
{
	int i, mid;
	
	if (start > end)
		return;
	
	for (i = 0; i < depth; i++)
		printf("  ");
	
	printf("[%d,%d]: %d\n", start, end, st->tree[node]);
	
	if (start == end)
		return;
	
	mid = (start + end) / 2;
	print_tree_helper(st, 2 * node, start, mid, depth + 1);
	print_tree_helper(st, 2 * node + 1, mid + 1, end, depth + 1);
}

void print_segment_tree(const SegmentTree *st)
{
	printf("\n線段樹結構:\n");
	print_tree_helper(st, 1, 0, st->n - 1, 0);
}

// ============================================================
// 測試與比較
// ============================================================

void test_correctness(const int arr[], const int n, SegmentTree *st, const int num_tests)
{
	int i, l, r, seg_result, brute_result;
	int passed, failed;
	
	printf("\n=== 正確性測試 ===\n");
	printf("進行 %d 次隨機查詢...\n", num_tests);
	
	passed = 0;
	failed = 0;
	
	for (i = 0; i < num_tests; i++) {
		l = rand() % n;
		r = l + rand() % (n - l);
		
		seg_result = query(st, l, r);
		brute_result = brute_force_max(arr, l, r);
		
		if (seg_result == brute_result) {
			passed++;
		} else {
			failed++;
			printf("錯誤 [%d,%d]: 線段樹=%d, 暴力法=%d\n", 
			       l, r, seg_result, brute_result);
		}
	}
	
	printf("測試結果: 通過 %d/%d, 失敗 %d\n", passed, num_tests, failed);
}

void performance_comparison(const int arr[], const int n, SegmentTree *st, const int num_queries)
{
	clock_t start, end;
	double seg_time, brute_time;
	int i, l, r, result;
	
	printf("\n=== 效能比較 ===\n");
	printf("陣列大小 n = %d\n", n);
	printf("查詢次數 m = %d\n\n", num_queries);
	
	// 測試線段樹
	start = clock();
	for (i = 0; i < num_queries; i++) {
		l = rand() % n;
		r = l + rand() % (n - l);
		result = query(st, l, r);
	}
	end = clock();
	seg_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	// 測試暴力法
	start = clock();
	for (i = 0; i < num_queries; i++) {
		l = rand() % n;
		r = l + rand() % (n - l);
		result = brute_force_max(arr, l, r);
	}
	end = clock();
	brute_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	// 輸出結果
	printf("線段樹方法: %.6f 秒\n", seg_time);
	printf("暴力法:     %.6f 秒\n", brute_time);
	printf("加速比:     %.2fx\n", brute_time / seg_time);
}

// ============================================================
// 互動式查詢
// ============================================================

void interactive_mode(const int arr[], const int n, SegmentTree *st)
{
	int l, r, result;
	
	printf("\n=== 互動查詢模式 ===\n");
	printf("輸入查詢區間 [l, r]（索引從 0 到 %d）\n", n - 1);
	printf("輸入 -1 -1 結束\n\n");
	
	while (1) {
		printf("查詢 [l, r]: ");
		if (scanf("%d %d", &l, &r) != 2)
			break;
		
		if (l == -1 && r == -1)
			break;
		
		if (l < 0 || r >= n || l > r) {
			printf("錯誤：無效的區間！\n");
			continue;
		}
		
		result = query(st, l, r);
		printf("區間 [%d,%d] 的最大值: %d\n\n", l, r, result);
	}
}

// ============================================================
// 主程式
// ============================================================

int main(int ac, char *av[])
{
	SegmentTree *st;
	int *arr;
	int n, i;
	int show_array, show_tree, interactive;
	
	printf("=================================================\n");
	printf("線段樹區間最大值查詢\n");
	printf("=================================================\n");
	
	// 讀取陣列大小
	if (ac > 1) {
		sscanf(av[1], "%d", &n);
	} else {
		printf("輸入陣列大小 n: ");
		scanf("%d", &n);
	}
	
	// 配置記憶體
	arr = (int *) malloc(sizeof(int) * n);
	
	// 生成隨機資料
	srand(time(NULL));
	generate_random_array(arr, n, 1000);
	
	printf("已生成 %d 個隨機數（範圍 0-999）\n", n);
	
	// 詢問是否顯示陣列
	show_array = 0;
	if (n <= 20) {
		printf("是否顯示陣列？(1=是, 0=否): ");
		scanf("%d", &show_array);
		
		if (show_array)
			print_array(arr, n);
	}
	
	// 建構線段樹
	printf("\n建構線段樹中...\n");
	st = create_segment_tree(n);
	init_segment_tree(st, arr, n);
	printf("線段樹建構完成！\n");
	
	// 詢問是否顯示樹結構
	show_tree = 0;
	if (n <= 10) {
		printf("是否顯示線段樹結構？(1=是, 0=否): ");
		scanf("%d", &show_tree);
		
		if (show_tree)
			print_segment_tree(st);
	}
	
	// 正確性測試
	test_correctness(arr, n, st, 1000);
	
	// 效能比較
	if (n >= 100) {
		int num_queries;
		
		num_queries = n * 10;
		if (num_queries > 100000)
			num_queries = 100000;
		
		performance_comparison(arr, n, st, num_queries);
	}
	
	// 互動模式
	printf("\n是否進入互動查詢模式？(1=是, 0=否): ");
	scanf("%d", &interactive);
	
	if (interactive)
		interactive_mode(arr, n, st);
	
	printf("\n=================================================\n");
	printf("程式結束\n");
	printf("=================================================\n");
	
	// 釋放記憶體
	free(arr);
	free_segment_tree(st);
	
	return 0;
}