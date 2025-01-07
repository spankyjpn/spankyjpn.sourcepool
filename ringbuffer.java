/*
 *	重要
 *　Apache Commons Collections を使うことで様々なユーティリティを使うことができる。
 *　リングバッファも提供されている。
 *　入手先のＵＲＬは下記の通り
 *　https://commons.apache.org/proper/commons-collections/
 */

import org.apache.commons.collections4.queue.CircularFifoQueue;

public class Main {
    public static void main(String[] args) {
        // リングバッファ（最大サイズ3）
        CircularFifoQueue<Integer> ringBuffer = new CircularFifoQueue<>(3);

        // データを追加
        ringBuffer.add(1);
        ringBuffer.add(2);
        ringBuffer.add(3);
        System.out.println("リングバッファの内容: " + ringBuffer); // 出力: [1, 2, 3]

        // サイズを超えると古い要素を上書き
        ringBuffer.add(4); // 1 を上書き
        System.out.println("リングバッファの内容: " + ringBuffer); // 出力: [2, 3, 4]

        ringBuffer.add(5); // 2 を上書き
        System.out.println("リングバッファの内容: " + ringBuffer); // 出力: [3, 4, 5]

        // 要素を取り出す
        System.out.println("最初の要素: " + ringBuffer.poll()); // 出力: 3
        System.out.println("リングバッファの内容: " + ringBuffer); // 出力: [4, 5]
    }
}
