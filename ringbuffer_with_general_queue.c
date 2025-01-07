#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DATA_SIZE 100  // データサイズの上限

/* 汎用キューのコードはここに含まれていると仮定します */
/* キュー構造体と関数の宣言・実装を再利用します */

/*
 * リングバッファ構造体: 固定サイズの汎用キュー
 * - queue: 汎用キュー
 * - maxSize: リングバッファの最大サイズ
 * - currentSize: 現在のサイズ
 */
typedef struct RingBuffer {
    Queue queue;        // 汎用キュー
    int maxSize;        // リングバッファの最大サイズ
    int currentSize;    // 現在のバッファサイズ
} RingBuffer;

/*
 * リングバッファを初期化します
 * - 引数:
 *   - ringBuffer (RingBuffer*): 初期化対象のリングバッファ構造体へのポインタ
 *   - maxSize (int): リングバッファの最大サイズ
 */
void initializeRingBuffer(RingBuffer* ringBuffer, int maxSize) {
    initialize(&ringBuffer->queue); // 汎用キューの初期化
    ringBuffer->maxSize = maxSize; // 最大サイズを設定
    ringBuffer->currentSize = 0;   // 現在のサイズを0に初期化
}

/*
 * リングバッファにデータを追加します
 * - 引数:
 *   - ringBuffer (RingBuffer*): 対象のリングバッファ構造体へのポインタ
 *   - key (int): データのキー
 *   - data (const char*): データ
 */
void addToRingBuffer(RingBuffer* ringBuffer, int key, const char* data) {
    // バッファが満杯の場合、最も古いデータを削除
    if (ringBuffer->currentSize >= ringBuffer->maxSize) {
        dequeueTop(&ringBuffer->queue); // 古いデータを削除
        ringBuffer->currentSize--;     // サイズを調整
    }

    // 新しいデータを追加
    enqueue(&ringBuffer->queue, key, data);
    ringBuffer->currentSize++; // サイズを更新
}

/*
 * リングバッファの内容を表示します
 * - 引数:
 *   - ringBuffer (RingBuffer*): 対象のリングバッファ構造体へのポインタ
 */
void printRingBuffer(RingBuffer* ringBuffer) {
    printf("リングバッファの内容:\n");
    printQueue(&ringBuffer->queue); // キューの内容を表示
}

/*
 * メイン関数: リングバッファの動作を確認
 */
int main() {
    RingBuffer myRingBuffer;
    initializeRingBuffer(&myRingBuffer, 3); // 最大サイズ3のリングバッファを作成

    // データを追加
    addToRingBuffer(&myRingBuffer, 1, "Alice");
    addToRingBuffer(&myRingBuffer, 2, "Bob");
    addToRingBuffer(&myRingBuffer, 3, "Charlie");

    // リングバッファの内容を表示
    printRingBuffer(&myRingBuffer);

    // リングバッファが満杯の状態で新しいデータを追加（古いデータが削除される）
    addToRingBuffer(&myRingBuffer, 4, "Dave");
    addToRingBuffer(&myRingBuffer, 5, "Eve");

    // 更新後のリングバッファの内容を表示
    printRingBuffer(&myRingBuffer);

    return 0;
}
