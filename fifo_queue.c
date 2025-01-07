#include <stdio.h>
#include <stdbool.h>

#define QUEUE_SIZE 5  		// キューの固定サイズ

typedef struct {
    int data[QUEUE_SIZE];  	// データを格納する配列
    int front;             	// キューの先頭
    int rear;              	// キューの末尾
    int count;             	// 現在の要素数
} Queue;

// キューの初期化
void initializeQueue(Queue *q) 
{
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// キューが空か確認
bool isEmpty(Queue *q) 
{
    return q->count == 0;
}

// キューが満杯か確認
bool isFull(Queue *q) 
{
    return q->count == QUEUE_SIZE;
}

// データをキューに追加（enqueue）
bool enqueue(Queue *q, int value) 
{
    if (isFull(q)) {
        printf("キューが満杯です。\n");
        return false;
    }
    q->rear = (q->rear + 1) % QUEUE_SIZE;  // 循環インデックス
    q->data[q->rear] = value;
    q->count++;
    return true;
}

// データをキューから取り出す（dequeue）
bool dequeue(Queue *q, int *value) 
{
    if (isEmpty(q)) {
        printf("キューが空です。\n");
        return false;
    }
    *value = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;  // 循環インデックス
    q->count--;
    return true;
}

// キューの内容を表示（デバッグ用）
void printQueue(Queue *q) 
{
    if (isEmpty(q)) 
	{
        printf("キューは空です。\n");
        return;
    }
    printf("キューの内容: ");
    int index = q->front;
    for (int i = 0; i < q->count; i++) 
	{
        printf("%d ", q->data[index]);
        index = (index + 1) % QUEUE_SIZE;
    }
    printf("\n");
}

// メイン関数
int main() {
    Queue q;
    initializeQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printQueue(&q);

    int value;
    dequeue(&q, &value);
    printf("取り出した値: %d\n", value);
    printQueue(&q);

    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);  	// ここで満杯になる
    enqueue(&q, 70);	// エラー
    enqueue(&q, 80);	// エラー
    printQueue(&q);

    dequeue(&q, &value);
    printf("取り出した値: %d\n", value);

    dequeue(&q, &value);
    printf("取り出した値: %d\n", value);

    printQueue(&q);

    return 0;
}
