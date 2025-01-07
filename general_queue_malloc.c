/*****************************************************************************
 *	汎用キュー（動的メモリ確保版）
 *	様々なキューを構築できる汎用的なサポート関数を持ったキュー
 *	Ｃ言語版 malloc()にてメモリを動的に確保する
 *****************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DATA_SIZE 100

/* ノード構造体: キュー内の各要素 */
typedef struct Node
{
    int key;                   // ノードの識別キー
    char data[MAX_DATA_SIZE];  // ノードに格納されるデータ
    struct Node* next;         // 次のノードへのポインタ
    struct Node* prev;         // 前のノードへのポインタ
} Node;

/* キュー構造体: 双方向リスト */
typedef struct Queue
{
    Node* front;               // キューの先頭ノード
    Node* rear;                // キューの末尾ノード
    Node* current;             // 現在位置を指すノード
} Queue;

/* キューの初期化 */
void initializeQueue(Queue* queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->current = NULL;
}

/* 新しいノードを作成 */
Node* createNode(int key, const char* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("メモリ確保に失敗しました。\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = key;
    strncpy(newNode->data, data, MAX_DATA_SIZE - 1);
    newNode->data[MAX_DATA_SIZE - 1] = '\0';
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

/* キューにノードを追加（enqueue） */
void enqueue(Queue* queue, int key, const char* data)
{
    Node* newNode = createNode(key, data);

    if (queue->rear == NULL)
    {
        queue->front = newNode;
        queue->rear = newNode;
        queue->current = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        newNode->prev = queue->rear;
        queue->rear = newNode;
    }

    printf("データ '%s' (キー: %d) をキューに追加しました。\n", data, key);
}

/* キューの先頭に戻る */
void moveToFront(Queue* queue)
{
    if (queue->front == NULL)
    {
        printf("キューが空です。\n");
        return;
    }
    queue->current = queue->front;
    printf("現在位置を先頭に移動しました: [キー: %d, データ: %s]\n", queue->current->key, queue->current->data);
}

/* キューの末尾に移動 */
void moveToRear(Queue* queue)
{
    if (queue->rear == NULL)
    {
        printf("キューが空です。\n");
        return;
    }
    queue->current = queue->rear;
    printf("現在位置を末尾に移動しました: [キー: %d, データ: %s]\n", queue->current->key, queue->current->data);
}

/* 現在位置を1つ進める */
void moveNext(Queue* queue)
{
    if (queue->current == NULL || queue->current->next == NULL)
    {
        printf("次のノードが存在しません。\n");
        return;
    }
    queue->current = queue->current->next;
    printf("現在位置を1つ進めました: [キー: %d, データ: %s]\n", queue->current->key, queue->current->data);
}

/* 現在位置を1つ戻す */
void movePrev(Queue* queue)
{
    if (queue->current == NULL || queue->current->prev == NULL)
    {
        printf("前のノードが存在しません。\n");
        return;
    }
    queue->current = queue->current->prev;
    printf("現在位置を1つ戻しました: [キー: %d, データ: %s]\n", queue->current->key, queue->current->data);
}

/* 現在のノードを削除 */
void deleteCurrent(Queue* queue)
{
    if (queue->current == NULL)
    {
        printf("現在位置が無効です。\n");
        return;
    }

    Node* toDelete = queue->current;

    if (toDelete->prev != NULL)
    {
        toDelete->prev->next = toDelete->next;
    }
    else
    {
        queue->front = toDelete->next;
    }

    if (toDelete->next != NULL)
    {
        toDelete->next->prev = toDelete->prev;
    }
    else
    {
        queue->rear = toDelete->prev;
    }

    queue->current = toDelete->next != NULL ? toDelete->next : toDelete->prev;

    printf("現在のノードを削除しました: [キー: %d, データ: %s]\n", toDelete->key, toDelete->data);
    free(toDelete);
}

/* キューの内容を表示 */
void printQueue(Queue* queue)
{
    Node* current = queue->front;

    printf("キューの内容: ");
    while (current != NULL)
    {
        printf("[キー: %d, データ: %s] -> ", current->key, current->data);
        current = current->next;
    }
    printf("NULL\n");
}

/* メイン関数 */
int main()
{
    Queue myQueue;
    initializeQueue(&myQueue);

    enqueue(&myQueue, 1, "Alice");
    enqueue(&myQueue, 2, "Bob");
    enqueue(&myQueue, 3, "Charlie");

    printQueue(&myQueue);

    moveToFront(&myQueue);
    moveNext(&myQueue);
    movePrev(&myQueue);
    moveToRear(&myQueue);
    deleteCurrent(&myQueue);

    printQueue(&myQueue);

    return 0;
}
