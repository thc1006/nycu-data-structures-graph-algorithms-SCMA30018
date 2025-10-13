// 稀疏矩陣資料結構與運算
// 使用 linked list 表示每一行，支援加法、乘法運算
// 作者：蔡秀吉 (H. C. Tsai)
// 電子信箱：hctsai@linux
// date: 2025/10/12

#include <stdio.h>
#include <stdlib.h>

// ============================================================
// 資料結構定義
// ============================================================

// 節點：儲存單一非零元素
typedef struct Node {
	int col;           // 欄位編號（1 到 n）
	int val;           // 元素值
	struct Node *next; // 下一個元素
} Node;

// 稀疏矩陣
typedef struct {
	int m, n;          // 矩陣大小 m × n
	Node **rows;       // m 個 linked list（每行一個）
} SparseMatrix;

// ============================================================
// 基本操作函數
// ============================================================

// 建立空的稀疏矩陣
SparseMatrix *create_sparse_matrix(const int m, const int n)
{
	SparseMatrix *mat;
	int i;
	
	mat = (SparseMatrix *) malloc(sizeof(SparseMatrix));
	mat->m = m;
	mat->n = n;
	mat->rows = (Node **) malloc(sizeof(Node *) * (m + 1));
	
	for (i = 0; i <= m; i++)
		mat->rows[i] = NULL;
	
	return mat;
}

// 在指定位置插入元素（按欄位排序）
void insert_element(SparseMatrix *mat, const int row, const int col, const int val)
{
	Node *node, *curr, *prev;
	
	if (val == 0)
		return;
	
	// 建立新節點
	node = (Node *) malloc(sizeof(Node));
	node->col = col;
	node->val = val;
	node->next = NULL;
	
	// 插入到適當位置（保持欄位遞增順序）
	if (mat->rows[row] == NULL || mat->rows[row]->col > col) {
		node->next = mat->rows[row];
		mat->rows[row] = node;
	} else {
		prev = NULL;
		curr = mat->rows[row];
		
		while (curr != NULL && curr->col < col) {
			prev = curr;
			curr = curr->next;
		}
		
		// 如果該位置已有元素，更新值
		if (curr != NULL && curr->col == col) {
			curr->val = val;
			free(node);
		} else {
			node->next = curr;
			prev->next = node;
		}
	}
}

// 釋放稀疏矩陣記憶體
void free_sparse_matrix(SparseMatrix *mat)
{
	Node *curr, *temp;
	int i;
	
	for (i = 1; i <= mat->m; i++) {
		curr = mat->rows[i];
		while (curr != NULL) {
			temp = curr;
			curr = curr->next;
			free(temp);
		}
	}
	
	free(mat->rows);
	free(mat);
}

// ============================================================
// 輸入輸出函數
// ============================================================

// 讀取稀疏矩陣
SparseMatrix *read_sparse_matrix()
{
	SparseMatrix *mat;
	int m, n, i, col, val;
	
	scanf("%d %d", &m, &n);
	mat = create_sparse_matrix(m, n);
	
	for (i = 1; i <= m; i++) {
		while (1) {
			scanf("%d", &col);
			if (col == 0)
				break;
			scanf("%d", &val);
			insert_element(mat, i, col, val);
		}
	}
	
	return mat;
}

// 印出矩陣（完整格式）
void print_matrix_regular(const SparseMatrix *mat)
{
	Node *curr;
	int i, j;
	
	printf("\n完整矩陣 (%d × %d):\n", mat->m, mat->n);
	
	for (i = 1; i <= mat->m; i++) {
		curr = mat->rows[i];
		for (j = 1; j <= mat->n; j++) {
			if (curr != NULL && curr->col == j) {
				printf("%4d ", curr->val);
				curr = curr->next;
			} else {
				printf("%4d ", 0);
			}
		}
		putchar('\n');
	}
}

// 計算記憶體使用量
int calculate_memory(const SparseMatrix *mat)
{
	Node *curr;
	int i, count;
	
	count = 0;
	
	// 計算非零元素數量
	for (i = 1; i <= mat->m; i++) {
		curr = mat->rows[i];
		while (curr != NULL) {
			count++;
			curr = curr->next;
		}
	}
	
	// 記憶體 = 2 (m,n) + m (行指標) + 3*count (每個節點)
	return 2 + mat->m + 3 * count;
}

// 印出矩陣（列表格式 + 記憶體）
void print_matrix_list(const SparseMatrix *mat)
{
	Node *curr;
	int i;
	
	printf("\n列表格式 (%d × %d):\n", mat->m, mat->n);
	
	for (i = 1; i <= mat->m; i++) {
		printf("Row %d: ", i);
		curr = mat->rows[i];
		while (curr != NULL) {
			printf("(%d,%d) ", curr->col, curr->val);
			curr = curr->next;
		}
		putchar('\n');
	}
	
	printf("記憶體使用量: %d 單位\n", calculate_memory(mat));
}

// ============================================================
// 矩陣運算
// ============================================================

// 矩陣加法
SparseMatrix *add_matrices(const SparseMatrix *A, const SparseMatrix *B)
{
	SparseMatrix *C;
	Node *a, *b;
	int i, sum;
	
	// 檢查維度
	if (A->m != B->m || A->n != B->n) {
		printf("錯誤：矩陣維度不符，無法相加！\n");
		return NULL;
	}
	
	C = create_sparse_matrix(A->m, A->n);
	
	// 逐行相加
	for (i = 1; i <= A->m; i++) {
		a = A->rows[i];
		b = B->rows[i];
		
		while (a != NULL || b != NULL) {
			if (a == NULL) {
				insert_element(C, i, b->col, b->val);
				b = b->next;
			} else if (b == NULL) {
				insert_element(C, i, a->col, a->val);
				a = a->next;
			} else if (a->col < b->col) {
				insert_element(C, i, a->col, a->val);
				a = a->next;
			} else if (a->col > b->col) {
				insert_element(C, i, b->col, b->val);
				b = b->next;
			} else {
				sum = a->val + b->val;
				if (sum != 0)
					insert_element(C, i, a->col, sum);
				a = a->next;
				b = b->next;
			}
		}
	}
	
	return C;
}

// 矩陣轉置
SparseMatrix *transpose_matrix(const SparseMatrix *mat)
{
	SparseMatrix *trans;
	Node *curr;
	int i;
	
	trans = create_sparse_matrix(mat->n, mat->m);
	
	for (i = 1; i <= mat->m; i++) {
		curr = mat->rows[i];
		while (curr != NULL) {
			insert_element(trans, curr->col, i, curr->val);
			curr = curr->next;
		}
	}
	
	return trans;
}

// 計算兩個稀疏向量的內積
int dot_product(const Node *a, const Node *b)
{
	int sum;
	
	sum = 0;
	
	while (a != NULL && b != NULL) {
		if (a->col < b->col) {
			a = a->next;
		} else if (a->col > b->col) {
			b = b->next;
		} else {
			sum += a->val * b->val;
			a = a->next;
			b = b->next;
		}
	}
	
	return sum;
}

// 矩陣乘法
SparseMatrix *multiply_matrices(const SparseMatrix *A, const SparseMatrix *B)
{
	SparseMatrix *C, *B_trans;
	int i, j, product;
	
	// 檢查維度
	if (A->n != B->m) {
		printf("錯誤：矩陣維度不符，無法相乘！\n");
		printf("A 是 %d×%d，B 是 %d×%d\n", A->m, A->n, B->m, B->n);
		return NULL;
	}
	
	C = create_sparse_matrix(A->m, B->n);
	
	// 轉置 B 以方便計算
	B_trans = transpose_matrix(B);
	
	// 計算 C[i][j] = A[i] · B^T[j]
	for (i = 1; i <= A->m; i++) {
		if (A->rows[i] == NULL)
			continue;
		
		for (j = 1; j <= B->n; j++) {
			if (B_trans->rows[j] == NULL)
				continue;
			
			product = dot_product(A->rows[i], B_trans->rows[j]);
			if (product != 0)
				insert_element(C, i, j, product);
		}
	}
	
	free_sparse_matrix(B_trans);
	
	return C;
}

// ============================================================
// 主程式
// ============================================================

int main()
{
	SparseMatrix *A, *B, *C;
	
	printf("=================================================\n");
	printf("稀疏矩陣運算程式\n");
	printf("=================================================\n");
	
	// 讀取第一個矩陣
	printf("\n請輸入矩陣 A（格式：m n，然後每行的非零元素）:\n");
	A = read_sparse_matrix();
	
	printf("\n矩陣 A:");
	print_matrix_regular(A);
	print_matrix_list(A);
	
	// 讀取第二個矩陣
	printf("\n請輸入矩陣 B:\n");
	B = read_sparse_matrix();
	
	printf("\n矩陣 B:");
	print_matrix_regular(B);
	print_matrix_list(B);
	
	// 矩陣加法
	printf("\n=================================================\n");
	printf("計算 A + B:\n");
	printf("=================================================\n");
	
	C = add_matrices(A, B);
	if (C != NULL) {
		printf("\n結果 A + B:");
		print_matrix_regular(C);
		print_matrix_list(C);
		free_sparse_matrix(C);
	}
	
	// 矩陣乘法
	printf("\n=================================================\n");
	printf("計算 A × B:\n");
	printf("=================================================\n");
	
	C = multiply_matrices(A, B);
	if (C != NULL) {
		printf("\n結果 A × B:");
		print_matrix_regular(C);
		print_matrix_list(C);
		free_sparse_matrix(C);
	}
	
	// 測試轉置
	printf("\n=================================================\n");
	printf("計算 A 的轉置:\n");
	printf("=================================================\n");
	
	C = transpose_matrix(A);
	printf("\n結果 A^T:");
	print_matrix_regular(C);
	print_matrix_list(C);
	free_sparse_matrix(C);
	
	// 釋放記憶體
	free_sparse_matrix(A);
	free_sparse_matrix(B);
	
	printf("\n=================================================\n");
	
	return 0;
}
