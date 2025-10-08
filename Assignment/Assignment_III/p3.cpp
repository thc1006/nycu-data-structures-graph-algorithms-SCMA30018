// 迷宮最短路徑尋找
// 使用 BFS 演算法找出從起點 s 到終點 t 的最短路徑
// author: [Your Name]
// date: 2025/10/05

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================
// 資料結構定義
// ============================================================

// 座標結構
typedef struct {
	int row;
	int col;
} Position;

// 佇列節點
typedef struct QNode {
	Position pos;
	struct QNode *next;
} QNode;

// 佇列結構
typedef struct {
	QNode *front;
	QNode *rear;
} Queue;

// 迷宮格子類型
#define EMPTY '0'
#define OBSTACLE 'x'
#define START 's'
#define TARGET 't'

// ============================================================
// 佇列操作函數（自己實作）
// ============================================================

Queue *create_queue()
{
	Queue *q;
	
	q = (Queue *) malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	return q;
}

int is_empty(const Queue *q)
{
	return q->front == NULL;
}

void enqueue(Queue *q, const Position p)
{
	QNode *node;
	
	node = (QNode *) malloc(sizeof(QNode));
	node->pos = p;
	node->next = NULL;
	
	if (q->rear == NULL) {
		q->front = node;
		q->rear = node;
	} else {
		q->rear->next = node;
		q->rear = node;
	}
}

Position dequeue(Queue *q)
{
	QNode *temp;
	Position p;
	
	temp = q->front;
	p = temp->pos;
	q->front = temp->next;
	
	if (q->front == NULL)
		q->rear = NULL;
	
	free(temp);
	return p;
}

void free_queue(Queue *q)
{
	QNode *temp;
	
	while (q->front != NULL) {
		temp = q->front;
		q->front = temp->next;
		free(temp);
	}
	free(q);
}

// ============================================================
// 迷宮操作函數
// ============================================================

// 讀取迷宮
char **read_maze(int *m, int *n, Position *start, Position *target)
{
	char **maze;
	int i, j, col;
	char type;
	
	// 讀取迷宮大小
	scanf("%d %d", m, n);
	
	// 配置記憶體
	maze = (char **) malloc(sizeof(char *) * (*m + 1));
	for (i = 0; i <= *m; i++) {
		maze[i] = (char *) malloc(sizeof(char) * (*n + 1));
		for (j = 0; j <= *n; j++)
			maze[i][j] = EMPTY;
	}
	
	// 讀取每一列的非空格子
	for (i = 1; i <= *m; i++) {
		while (1) {
			scanf("%d", &col);
			if (col == 0)
				break;
			
			scanf(" %c", &type);
			maze[i][col] = type;
			
			if (type == START) {
				start->row = i;
				start->col = col;
			}
			if (type == TARGET) {
				target->row = i;
				target->col = col;
			}
		}
	}
	
	return maze;
}

// 印出迷宮（除錯用）
void print_maze(char **maze, const int m, const int n)
{
	int i, j;
	
	printf("\n迷宮內容:\n");
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (maze[i][j] == EMPTY)
				printf("  . ");
			else
				printf("  %c ", maze[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

// 釋放迷宮記憶體
void free_maze(char **maze, const int m)
{
	int i;
	
	for (i = 0; i <= m; i++)
		free(maze[i]);
	free(maze);
}

// ============================================================
// BFS 最短路徑演算法
// ============================================================

int bfs(char **maze, const int m, const int n, 
        const Position start, const Position target,
        Position **parent)
{
	Queue *q;
	int **visited;
	Position current, next;
	int i, j;
	int dx[4] = {-1, 1, 0, 0};  // 上下左右四個方向
	int dy[4] = {0, 0, -1, 1};
	int found;
	
	// 配置 visited 和 parent 陣列
	visited = (int **) malloc(sizeof(int *) * (m + 1));
	*parent = (Position *) malloc(sizeof(Position) * (m + 1) * (n + 1));
	
	for (i = 0; i <= m; i++) {
		visited[i] = (int *) malloc(sizeof(int) * (n + 1));
		for (j = 0; j <= n; j++) {
			visited[i][j] = 0;
			(*parent)[i * (n + 1) + j].row = -1;
			(*parent)[i * (n + 1) + j].col = -1;
		}
	}
	
	// 建立佇列並開始 BFS
	q = create_queue();
	enqueue(q, start);
	visited[start.row][start.col] = 1;
	
	found = 0;
	
	while (!is_empty(q)) {
		current = dequeue(q);
		
		// 找到目標
		if (current.row == target.row && current.col == target.col) {
			found = 1;
			break;
		}
		
		// 探索四個方向
		for (i = 0; i < 4; i++) {
			next.row = current.row + dx[i];
			next.col = current.col + dy[i];
			
			// 檢查是否在範圍內
			if (next.row < 1 || next.row > m || 
			    next.col < 1 || next.col > n)
				continue;
			
			// 檢查是否可通行且未訪問
			if (maze[next.row][next.col] != OBSTACLE && 
			    !visited[next.row][next.col]) {
				visited[next.row][next.col] = 1;
				(*parent)[next.row * (n + 1) + next.col] = current;
				enqueue(q, next);
			}
		}
	}
	
	// 釋放記憶體
	free_queue(q);
	for (i = 0; i <= m; i++)
		free(visited[i]);
	free(visited);
	
	return found;
}

// ============================================================
// 路徑重建與輸出
// ============================================================

int reconstruct_path(const Position *parent, const int n,
                      const Position start, const Position target,
                      Position **path)
{
	Position current;
	int count, i;
	Position *temp;
	
	// 計算路徑長度
	count = 0;
	current = target;
	while (current.row != start.row || current.col != start.col) {
		count++;
		current = parent[current.row * (n + 1) + current.col];
	}
	count++;  // 加上起點
	
	// 配置路徑陣列
	*path = (Position *) malloc(sizeof(Position) * count);
	
	// 從終點回溯到起點
	i = count - 1;
	current = target;
	while (i >= 0) {
		(*path)[i] = current;
		if (current.row == start.row && current.col == start.col)
			break;
		current = parent[current.row * (n + 1) + current.col];
		i--;
	}
	
	return count;
}

void print_path(const Position *path, const int count)
{
	int i;
	
	printf("最短路徑:\n");
	for (i = 0; i < count; i++) {
		printf("(%d,%d)", path[i].row, path[i].col);
		if (i < count - 1)
			printf(" -> ");
		if ((i + 1) % 5 == 0)
			putchar('\n');
	}
	putchar('\n');
}

void print_maze_with_path(char **maze, const int m, const int n,
                          const Position *path, const int count)
{
	int **dist;
	int i, j, k;
	
	// 配置距離陣列
	dist = (int **) malloc(sizeof(int *) * (m + 1));
	for (i = 0; i <= m; i++) {
		dist[i] = (int *) malloc(sizeof(int) * (n + 1));
		for (j = 0; j <= n; j++)
			dist[i][j] = -1;
	}
	
	// 標記路徑上的距離
	for (k = 0; k < count; k++)
		dist[path[k].row][path[k].col] = k;
	
	// 印出視覺化迷宮
	printf("\n視覺化路徑（數字表示步數）:\n");
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (maze[i][j] == START)
				printf("  s ");
			else if (maze[i][j] == TARGET)
				printf("  t ");
			else if (maze[i][j] == OBSTACLE)
				printf("  x ");
			else if (dist[i][j] >= 0)
				printf("%3d ", dist[i][j]);
			else
				printf("  . ");
		}
		putchar('\n');
	}
	putchar('\n');
	
	// 釋放記憶體
	for (i = 0; i <= m; i++)
		free(dist[i]);
	free(dist);
}

// ============================================================
// 主程式
// ============================================================

int main(int ac, char *av[])
{
	char **maze;
	int m, n;
	Position start, target;
	Position *parent, *path;
	int found, path_length;
	
	printf("=================================================\n");
	printf("迷宮最短路徑尋找程式\n");
	printf("=================================================\n");
	printf("請輸入迷宮資料（格式：m n，然後每行的非空格子）\n\n");
	
	// 讀取迷宮
	maze = read_maze(&m, &n, &start, &target);
	
	printf("迷宮大小: %d x %d\n", m, n);
	printf("起點: (%d,%d)\n", start.row, start.col);
	printf("終點: (%d,%d)\n", target.row, target.col);
	
	// 除錯：印出迷宮
	if (ac > 1)
		print_maze(maze, m, n);
	
	// 執行 BFS 尋找最短路徑
	printf("\n開始搜尋最短路徑...\n");
	found = bfs(maze, m, n, start, target, &parent);
	
	if (!found) {
		printf("\n無法找到從起點到終點的路徑！\n");
		free(parent);
		free_maze(maze, m);
		return 1;
	}
	
	// 重建路徑
	path_length = reconstruct_path(parent, n, start, target, &path);
	
	printf("找到路徑！長度: %d 步\n\n", path_length - 1);
	
	// 印出路徑
	print_path(path, path_length);
	
	// 視覺化顯示
	print_maze_with_path(maze, m, n, path, path_length);
	
	printf("=================================================\n");
	
	// 釋放記憶體
	free(path);
	free(parent);
	free_maze(maze, m);
	
	return 0;
}
