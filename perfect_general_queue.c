#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DATA_SIZE 100  // データサイズの上限

/*
 * ノード構造体: キュー内の各要素を表します。
 * - key: ノードの識別キー
 * - data: ノードに格納されるデータ
 * - next: 次のノードへのポインタ
 * - prev: 前のノードへのポインタ
 */
typedef struct Node
{
    int key;                    // ノードの識別キー
    char data[MAX_DATA_SIZE];   // ノードに格納されるデータ
    struct Node* next;          // 次のノードへのポインタ
    struct Node* prev;          // 前のノードへのポインタ
} Node;

/*
 * キュー構造体: キュー全体を管理します。
 * - front: キューの先頭ノード
 * - rear: キューの末尾ノード
 * - current: 現在位置を指すノード
 */
typedef struct Queue
{
    Node* front;                // キューの先頭ノード
    Node* rear;                 // キューの末尾ノード
    Node* current;              // 現在位置を指すノード
} Queue;

/*
 * キューを初期化します。
 * - 引数: queue (Queue*): 初期化するキュー構造体へのポインタ
 */
void initializeQueue(Queue* queue)
{
    queue->front = NULL;  // 初期状態では先頭はNULL
    queue->rear = NULL;   // 初期状態では末尾もNULL
    queue->current = NULL; // 現在位置もNULL
}

/*
 * 新しいノードを作成します。
 * - 引数:
 *   - key (int): ノードの識別キー
 *   - data (const char*): ノードに格納するデータ
 * - 戻り値: 作成されたノードへのポインタ
 */
Node* createNode(int key, const char* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // 新しいノードのメモリ確保
    if (newNode == NULL)
    {
        printf("メモリ確保に失敗しました。\n");
        exit(EXIT_FAILURE); // メモリ確保失敗時に終了
    }

    newNode->key = key; // ノードのキーを設定
    strncpy(newNode->data, data, MAX_DATA_SIZE - 1); // データをコピー
    newNode->data[MAX_DATA_SIZE - 1] = '\0'; // データのNull終端
    newNode->next = NULL; // 次のノードへのポインタを初期化
    newNode->prev = NULL; // 前のノードへのポインタを初期化

    return newNode;
}

/*
 * キューにノードを追加します（enqueue）。
 * - 引数:
 *   - queue (Queue*): キュー構造体へのポインタ
 *   - key (int): 追加するノードのキー
 *   - data (const char*): 追加するノードのデータ
 */
void enqueue(Queue* queue, int key, const char* data)
{
    Node* newNode = createNode(key, data); // 新しいノードを作成

    if (queue->rear == NULL) // キューが空の場合
    {
        queue->front = newNode;  // 新しいノードが先頭
        queue->rear = newNode;   // 新しいノードが末尾
        queue->current = newNode; // 現在位置も新しいノード
    }
    else
    {
        queue->rear->next = newNode; // 現在の末尾の次を新しいノードに設定
        newNode->prev = queue->rear; // 新しいノードの前を現在の末尾に設定
        queue->rear = newNode;       // 新しいノードを末尾に設定
    }

    printf("データ '%s' (キー: %d) をキューに追加しました。\n", data, key);
}

/*
 * 現在位置の前に新しいノードを挿入します。
 * - 引数:
 *   - queue (Queue*): キュー構造体へのポインタ
 *   - key (int): 挿入するノードのキー
 *   - data (const char*): 挿入するノードのデータ
 */
void insertBefore(Queue* queue, int key, const char* data)
{
    if (queue->current == NULL) // 現在位置が無効の場合
    {
        printf("現在位置が無効です。挿入できません。\n");
        return;
    }

    Node* newNode = createNode(key, data); // 新しいノードを作成

    newNode->next = queue->current;       // 新しいノードの次を現在位置に設定
    newNode->prev = queue->current->prev; // 新しいノードの前を現在位置の前に設定

    if (queue->current->prev != NULL)
    {
        queue->current->prev->next = newNode; // 現在位置の前のノードの次を新しいノードに設定
    }
    else
    {
        queue->front = newNode; // 新しいノードが先頭になる場合
    }

    queue->current->prev = newNode; // 現在位置の前を新しいノードに設定
    printf("現在位置の前にデータ '%s' を挿入しました。\n", data);
}

/*
 * キューの内容を表示します。
 * - 引数: queue (Queue*): キュー構造体へのポインタ
 */
void printQueue(Queue* queue)
{
    Node* current = queue->front; // 先頭からスタート

    printf("キューの内容: ");
    while (current != NULL)
    {
        printf("[キー: %d, データ: %s] -> ", current->key, current->data); // キーとデータを出力
        current = current->next; // 次のノードに進む
    }
    printf("NULL\n"); // 最後にNULLを表示
}

/*
 * メイン関数: キュー操作のテスト
 */
int main()
{
    Queue myQueue; // キュー構造体の宣言
    initializeQueue(&myQueue); // キューの初期化

    enqueue(&myQueue, 1, "Alice");
    enqueue(&myQueue, 2, "Bob");
    enqueue(&myQueue, 3, "Charlie");

    printQueue(&myQueue);

    myQueue.current = myQueue.front->next; // 現在位置を "Bob" に設定
    insertBefore(&myQueue, 10, "InsertedBeforeBob");

    printQueue(&myQueue);

    return 0;
}
