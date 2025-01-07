#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DATA_SIZE 100  // データサイズの上限

/*
 * ノード構造体: キュー内の各要素
 * - key: ノードの識別キー
 * - data: ノードに格納されるデータ
 * - next: 次のノードへのポインタ
 * - prev: 前のノードへのポインタ
 */
typedef struct Node {
    int key;                    // ノードの識別キー
    char data[MAX_DATA_SIZE];   // ノードに格納されるデータ
    struct Node* next;          // 次のノードへのポインタ
    struct Node* prev;          // 前のノードへのポインタ
} Node;

/*
 * キュー構造体: 双方向リストを管理する
 * - front: キューの先頭ノード
 * - rear: キューの末尾ノード
 * - current: 現在位置を指すノード
 */
typedef struct Queue {
    Node* front;                // キューの先頭ノード
    Node* rear;                 // キューの末尾ノード
    Node* current;              // 現在位置を指すノード
} Queue;

/* 関数プロトタイプ */
void initialize(Queue* queue);
Node* createNode(int key, const char* data);
void enqueue(Queue* queue, int key, const char* data);
void dequeueCurrent(Queue* queue);
void dequeueTop(Queue* queue);
void dequeueLast(Queue* queue);
void insertPrev(Queue* queue, int key, const char* data);
void insertNext(Queue* queue, int key, const char* data);
void deleteCurrent(Queue* queue);
void goPrev(Queue* queue);
void goNext(Queue* queue);
void goTop(Queue* queue);
void goLast(Queue* queue);
Node* search(Queue* queue, int key);

/*
 * キューの初期化
 */
void initialize(Queue* queue) {
    queue->front = NULL;  // キューの先頭をNULLに設定
    queue->rear = NULL;   // キューの末尾をNULLに設定
    queue->current = NULL; // 現在位置をNULLに設定
}

/*
 * 新しいノードを作成
 */
Node* createNode(int key, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
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

/*
 * キューの末尾にノードを追加
 */
void enqueue(Queue* queue, int key, const char* data) {
    Node* newNode = createNode(key, data);

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
        queue->current = newNode;
    } else {
        queue->rear->next = newNode;
        newNode->prev = queue->rear;
        queue->rear = newNode;
    }
    printf("データ '%s' (キー: %d) をキューに追加しました。\n", data, key);
}

/*
 * 現在位置のノードを削除
 */
void dequeueCurrent(Queue* queue) {
    if (queue->current == NULL) {
        printf("現在位置が無効です。\n");
        return;
    }

    Node* toDelete = queue->current;

    if (toDelete->prev != NULL) {
        toDelete->prev->next = toDelete->next;
    } else {
        queue->front = toDelete->next;
    }

    if (toDelete->next != NULL) {
        toDelete->next->prev = toDelete->prev;
    } else {
        queue->rear = toDelete->prev;
    }

    queue->current = toDelete->next != NULL ? toDelete->next : toDelete->prev;

    printf("削除対象のノード：%s。\n", toDelete->data);

    free(toDelete);
    printf("現在のノードを削除しました。\n");

    if (queue->front == NULL) {
        queue->rear = NULL;
        queue->current = NULL;
    }
}

/*
 * キューの先頭ノードを削除
 */
void dequeueTop(Queue* queue) {
    if (queue->front == NULL) {
        printf("キューが空です。\n");
        return;
    }
    queue->current = queue->front;
    dequeueCurrent(queue);
}

/*
 * キューの末尾ノードを削除
 */
void dequeueLast(Queue* queue) {
    if (queue->rear == NULL) {
        printf("キューが空です。\n");
        return;
    }
    queue->current = queue->rear;
    dequeueCurrent(queue);
}

/*
 * 現在位置の前にノードを挿入
 */
void insertPrev(Queue* queue, int key, const char* data) {
    if (queue->current == NULL) {
        printf("現在位置が無効です。\n");
        return;
    }

    Node* newNode = createNode(key, data);

    newNode->next = queue->current;
    newNode->prev = queue->current->prev;

    if (queue->current->prev != NULL) {
        queue->current->prev->next = newNode;
    } else {
        queue->front = newNode;
    }

    queue->current->prev = newNode;
    printf("現在位置の前にデータ '%s' を挿入しました。\n", data);
}

/*
 * 現在位置の後にノードを挿入
 */
void insertNext(Queue* queue, int key, const char* data) {
    if (queue->current == NULL) {
        printf("現在位置が無効です。\n");
        return;
    }

    Node* newNode = createNode(key, data);

    newNode->prev = queue->current;
    newNode->next = queue->current->next;

    if (queue->current->next != NULL) {
        queue->current->next->prev = newNode;
    } else {
        queue->rear = newNode;
    }

    queue->current->next = newNode;
    printf("現在位置の後にデータ '%s' を挿入しました。\n", data);
}

/*
 * 現在位置を前に移動
 */
void goPrev(Queue* queue) {
    if (queue->current == NULL || queue->current->prev == NULL) {
        printf("前のノードが存在しません。\n");
        return;
    }
    queue->current = queue->current->prev;
    printf("現在位置を前に移動しました。\n");
}

/*
 * 現在位置を次に移動
 */
void goNext(Queue* queue) {
    if (queue->current == NULL || queue->current->next == NULL) {
        printf("次のノードが存在しません。\n");
        return;
    }
    queue->current = queue->current->next;
    printf("現在位置を次に移動しました。\n");
}

/*
 * 現在位置を先頭に移動
 */
void goTop(Queue* queue) {
    if (queue->front == NULL) {
        printf("キューが空です。\n");
        return;
    }
    queue->current = queue->front;
    printf("現在位置を先頭に移動しました。\n");
}

/*
 * 現在位置を末尾に移動
 */
void goLast(Queue* queue) {
    if (queue->rear == NULL) {
        printf("キューが空です。\n");
        return;
    }
    queue->current = queue->rear;
    printf("現在位置を末尾に移動しました。\n");
}

/*
 * 指定したキーのノードを検索
 */
Node* search(Queue* queue, int key) {
    Node* current = queue->front;

    while (current != NULL) {
        if (current->key == key) {
            printf("キー %d のノードを見つけました。\n", key);
            queue->current = current;
            return current;
        }
        current = current->next;
    }

    printf("キー %d のノードが見つかりませんでした。\n", key);
    return NULL;
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
 * メイン関数
 */
int main() {
    Queue myQueue;
    initialize(&myQueue);

    enqueue(&myQueue, 1, "Alice");
    enqueue(&myQueue, 2, "Bob");
    enqueue(&myQueue, 3, "Charlie");

    goTop(&myQueue);
    insertNext(&myQueue, 4, "Dave");
    goLast(&myQueue);
    insertPrev(&myQueue, 5, "Eve");

    dequeueTop(&myQueue);
    dequeueLast(&myQueue);

    search(&myQueue, 2);
    
    printQueue(&myQueue);

    return 0;
}
