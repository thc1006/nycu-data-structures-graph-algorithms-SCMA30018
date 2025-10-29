// 算術表達式求值器
// 使用 Shunting Yard 演算法將中綴表達式轉換為後綴表達式並求值
// 支援四則運算、括號、變數賦值
// 作者：蔡秀吉 (H. C. Tsai)
// 電子信箱：hctsai@linux
// date: 2025/11/01

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LEN 1000
#define MAX_TOKENS 500

// ============================================================
// 資料結構定義
// ============================================================

// Token 類型
typedef enum {
	TOKEN_NUMBER,
	TOKEN_VARIABLE,
	TOKEN_OPERATOR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_ASSIGN,
	TOKEN_END
} TokenType;

// Token 結構
typedef struct {
	TokenType type;
	double value;      // 數字的值
	char op;           // 運算符或變數名稱
} Token;

// Stack 節點（用於運算符）
typedef struct OpNode {
	char op;
	struct OpNode *next;
} OpNode;

// Stack 節點（用於數值）
typedef struct ValNode {
	double val;
	struct ValNode *next;
} ValNode;

// 運算符 Stack
typedef struct {
	OpNode *top;
} OpStack;

// 數值 Stack
typedef struct {
	ValNode *top;
} ValStack;

// 符號表（變數值）
typedef struct {
	double vars[26];   // a-z 對應 0-25
	int defined[26];   // 是否已定義
} SymbolTable;

// ============================================================
// Stack 操作函數
// ============================================================

OpStack *create_op_stack()
{
	OpStack *s;
	
	s = (OpStack *) malloc(sizeof(OpStack));
	s->top = NULL;
	return s;
}

ValStack *create_val_stack()
{
	ValStack *s;
	
	s = (ValStack *) malloc(sizeof(ValStack));
	s->top = NULL;
	return s;
}

int is_op_empty(const OpStack *s)
{
	return s->top == NULL;
}

int is_val_empty(const ValStack *s)
{
	return s->top == NULL;
}

void push_op(OpStack *s, const char op)
{
	OpNode *node;
	
	node = (OpNode *) malloc(sizeof(OpNode));
	node->op = op;
	node->next = s->top;
	s->top = node;
}

void push_val(ValStack *s, const double val)
{
	ValNode *node;
	
	node = (ValNode *) malloc(sizeof(ValNode));
	node->val = val;
	node->next = s->top;
	s->top = node;
}

char pop_op(OpStack *s)
{
	OpNode *node;
	char op;
	
	node = s->top;
	op = node->op;
	s->top = node->next;
	free(node);
	return op;
}

double pop_val(ValStack *s)
{
	ValNode *node;
	double val;
	
	node = s->top;
	val = node->val;
	s->top = node->next;
	free(node);
	return val;
}

char peek_op(const OpStack *s)
{
	return s->top->op;
}

void free_op_stack(OpStack *s)
{
	OpNode *curr, *temp;
	
	curr = s->top;
	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(s);
}

void free_val_stack(ValStack *s)
{
	ValNode *curr, *temp;
	
	curr = s->top;
	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(s);
}

// ============================================================
// 符號表操作
// ============================================================

SymbolTable *create_symbol_table()
{
	SymbolTable *table;
	int i;
	
	table = (SymbolTable *) malloc(sizeof(SymbolTable));
	
	for (i = 0; i < 26; i++) {
		table->vars[i] = 0.0;
		table->defined[i] = 0;
	}
	
	return table;
}

void set_variable(SymbolTable *table, const char var, const double val)
{
	int idx;
	
	idx = var - 'a';
	table->vars[idx] = val;
	table->defined[idx] = 1;
}

double get_variable(const SymbolTable *table, const char var, int *defined)
{
	int idx;
	
	idx = var - 'a';
	*defined = table->defined[idx];
	return table->vars[idx];
}

void free_symbol_table(SymbolTable *table)
{
	free(table);
}

// ============================================================
// Tokenizer（詞法分析）
// ============================================================

int is_operator(const char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int tokenize(const char *expr, Token tokens[])
{
	int i, pos, len;
	char ch;
	
	i = 0;
	pos = 0;
	len = strlen(expr);
	
	while (i < len) {
		ch = expr[i];
		
		// 跳過空白
		if (isspace(ch)) {
			i++;
			continue;
		}
		
		// 數字
		if (isdigit(ch) || ch == '.') {
			tokens[pos].type = TOKEN_NUMBER;
			tokens[pos].value = 0.0;
			sscanf(&expr[i], "%lf", &tokens[pos].value);
			
			while (i < len && (isdigit(expr[i]) || expr[i] == '.'))
				i++;
			pos++;
		}
		// 變數（小寫字母）
		else if (islower(ch)) {
			tokens[pos].type = TOKEN_VARIABLE;
			tokens[pos].op = ch;
			i++;
			pos++;
		}
		// 運算符
		else if (is_operator(ch)) {
			tokens[pos].type = TOKEN_OPERATOR;
			tokens[pos].op = ch;
			i++;
			pos++;
		}
		// 左括號
		else if (ch == '(') {
			tokens[pos].type = TOKEN_LPAREN;
			tokens[pos].op = ch;
			i++;
			pos++;
		}
		// 右括號
		else if (ch == ')') {
			tokens[pos].type = TOKEN_RPAREN;
			tokens[pos].op = ch;
			i++;
			pos++;
		}
		// 賦值符號
		else if (ch == '=') {
			tokens[pos].type = TOKEN_ASSIGN;
			tokens[pos].op = ch;
			i++;
			pos++;
		}
		else {
			i++;
		}
	}
	
	tokens[pos].type = TOKEN_END;
	return pos;
}

// ============================================================
// 運算符優先級
// ============================================================

int get_precedence(const char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

int is_left_associative(const char op)
{
	return 1;  // 所有運算符都是左結合
}

// ============================================================
// Shunting Yard 演算法（中綴轉後綴）
// ============================================================

int infix_to_postfix(const Token infix[], Token postfix[])
{
	OpStack *op_stack;
	int in_pos, out_pos;
	Token token;
	
	op_stack = create_op_stack();
	in_pos = 0;
	out_pos = 0;
	
	while (infix[in_pos].type != TOKEN_END) {
		token = infix[in_pos];
		
		// 數字或變數：直接輸出
		if (token.type == TOKEN_NUMBER || token.type == TOKEN_VARIABLE) {
			postfix[out_pos++] = token;
		}
		// 運算符
		else if (token.type == TOKEN_OPERATOR) {
			while (!is_op_empty(op_stack)) {
				char top_op;
				
				top_op = peek_op(op_stack);
				if (top_op == '(')
					break;
				
				if (get_precedence(top_op) > get_precedence(token.op) ||
				    (get_precedence(top_op) == get_precedence(token.op) &&
				     is_left_associative(token.op))) {
					postfix[out_pos].type = TOKEN_OPERATOR;
					postfix[out_pos].op = pop_op(op_stack);
					out_pos++;
				} else {
					break;
				}
			}
			push_op(op_stack, token.op);
		}
		// 左括號
		else if (token.type == TOKEN_LPAREN) {
			push_op(op_stack, token.op);
		}
		// 右括號
		else if (token.type == TOKEN_RPAREN) {
			while (!is_op_empty(op_stack) && peek_op(op_stack) != '(') {
				postfix[out_pos].type = TOKEN_OPERATOR;
				postfix[out_pos].op = pop_op(op_stack);
				out_pos++;
			}
			if (!is_op_empty(op_stack))
				pop_op(op_stack);  // 彈出左括號
		}
		
		in_pos++;
	}
	
	// 彈出剩餘的運算符
	while (!is_op_empty(op_stack)) {
		postfix[out_pos].type = TOKEN_OPERATOR;
		postfix[out_pos].op = pop_op(op_stack);
		out_pos++;
	}
	
	postfix[out_pos].type = TOKEN_END;
	
	free_op_stack(op_stack);
	return out_pos;
}

// ============================================================
// 後綴表達式求值
// ============================================================

double evaluate_postfix(const Token postfix[], const SymbolTable *table, int *error)
{
	ValStack *val_stack;
	int i;
	Token token;
	double result, operand1, operand2;
	
	val_stack = create_val_stack();
	i = 0;
	*error = 0;
	
	while (postfix[i].type != TOKEN_END) {
		token = postfix[i];
		
		if (token.type == TOKEN_NUMBER) {
			push_val(val_stack, token.value);
		}
		else if (token.type == TOKEN_VARIABLE) {
			int defined;
			double val;
			
			val = get_variable(table, token.op, &defined);
			if (!defined) {
				printf("錯誤：變數 '%c' 未定義！\n", token.op);
				*error = 1;
				free_val_stack(val_stack);
				return 0.0;
			}
			push_val(val_stack, val);
		}
		else if (token.type == TOKEN_OPERATOR) {
			operand2 = pop_val(val_stack);
			operand1 = pop_val(val_stack);
			
			if (token.op == '+')
				push_val(val_stack, operand1 + operand2);
			else if (token.op == '-')
				push_val(val_stack, operand1 - operand2);
			else if (token.op == '*')
				push_val(val_stack, operand1 * operand2);
			else if (token.op == '/')
				push_val(val_stack, operand1 / operand2);
		}
		
		i++;
	}
	
	result = pop_val(val_stack);
	free_val_stack(val_stack);
	
	return result;
}

// ============================================================
// 主處理函數
// ============================================================

void process_line(const char *line, SymbolTable *table)
{
	Token tokens[MAX_TOKENS], postfix[MAX_TOKENS];
	int token_count, is_assignment, error;
	char var_name;
	double result;
	
	// Tokenize
	token_count = tokenize(line, tokens);
	
	if (token_count == 0)
		return;
	
	// 檢查是否為賦值語句
	is_assignment = 0;
	if (token_count >= 3 && 
	    tokens[0].type == TOKEN_VARIABLE &&
	    tokens[1].type == TOKEN_ASSIGN) {
		is_assignment = 1;
		var_name = tokens[0].op;
	}
	
	// 轉換為後綴表達式
	if (is_assignment) {
		// 跳過變數名和等號
		infix_to_postfix(&tokens[2], postfix);
	} else {
		infix_to_postfix(tokens, postfix);
	}
	
	// 求值
	result = evaluate_postfix(postfix, table, &error);
	
	if (error)
		return;
	
	// 輸出結果
	if (is_assignment) {
		set_variable(table, var_name, result);
		printf("%c = %g\n", var_name, result);
	} else {
		printf("%g\n", result);
	}
}

// ============================================================
// 主程式
// ============================================================

int main()
{
	SymbolTable *table;
	char line[MAX_EXPR_LEN];
	
	printf("=================================================\n");
	printf("算術表達式求值器\n");
	printf("=================================================\n");
	printf("支援：+, -, *, /, 括號, 變數 (a-z)\n");
	printf("範例：\n");
	printf("  1 + 2 * 3\n");
	printf("  (1 + 2) * 3\n");
	printf("  a = 10\n");
	printf("  b = a * 2 + 5\n");
	printf("輸入 exit 或按 Ctrl+D 結束\n");
	printf("=================================================\n\n");
	
	table = create_symbol_table();
	
	while (1) {
		printf("> ");
		
		if (fgets(line, MAX_EXPR_LEN, stdin) == NULL)
			break;
		
		// 移除換行符
		line[strcspn(line, "\n")] = 0;
		
		// 檢查結束
		if (strcmp(line, "exit") == 0)
			break;
		
		// 跳過空行
		if (strlen(line) == 0)
			continue;
		
		// 處理這一行
		process_line(line, table);
	}
	
	printf("\n程式結束\n");
	
	free_symbol_table(table);
	
	return 0;
}