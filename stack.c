#include <stdio.h>
#include <stdbool.h>

#define STACK_SIZE 5  // スタックの固定サイズ

typedef struct {
    int data[STACK_SIZE];  // データを格納する配列
    int top;               // スタックのトップ（最後に追加された要素の位置）
} Stack;

// スタックの初期化
void initializeStack(Stack *s) {
    s->top = -1;  // 空の状態は -1
}

// スタックが空か確認
bool isEmpty(Stack *s) {
    return s->top == -1;
}

// スタックが満杯か確認
bool isFull(Stack *s) {
    return s->top == STACK_SIZE - 1;
}

// データをスタックに追加（push）
bool push(Stack *s, int value) {
    if (isFull(s)) {
        printf("スタックが満杯です。\n");
        return false;
    }
    s->top++;  // トップを1つ上げる
    s->data[s->top] = value;  // 新しい値を追加
    return true;
}

// データをスタックから取り出す（pop）
bool pop(Stack *s, int *value) {
    if (isEmpty(s)) {
        printf("スタックが空です。\n");
        return false;
    }
    *value = s->data[s->top];  // トップの値を取得
    s->top--;  // トップを1つ下げる
    return true;
}

// スタックの内容を表示（デバッグ用）
void printStack(Stack *s) {
    if (isEmpty(s)) {
        printf("スタックは空です。\n");
        return;
    }
    printf("スタックの内容（トップから順に）: ");
    for (int i = s->top; i >= 0; i--) {  // トップから表示
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

// メイン関数
int main() {
    Stack s;
    initializeStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    printStack(&s);  	// 出力: 30 20 10

    int value;
    pop(&s, &value);
    printf("取り出した値: %d\n", value);  // 出力: 30
    printStack(&s);  	// 出力: 20 10

    push(&s, 40);
    push(&s, 50);
    push(&s, 60);  		// ここで満杯になる
    push(&s, 70);		// エラー
    push(&s, 80);		// エラー
    printStack(&s);  	

    pop(&s, &value);
    printf("取り出した値: %d\n", value); 

    pop(&s, &value);
    printf("取り出した値: %d\n", value); 

    printStack(&s); 

    return 0;
}
