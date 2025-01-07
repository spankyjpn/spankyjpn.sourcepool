import java.util.ArrayDeque;
import java.util.Queue;

public class Main {
    public static void main(String[] args) {
        // QueueをArrayDequeで実装
        Queue<Integer> queue = new ArrayDeque<>();

        // データを追加（enqueue）
        queue.add(10);
        queue.add(20);
        queue.add(30);
        System.out.println("キューの内容: " + queue); // 出力: [10, 20, 30]

        // データを取り出し（dequeue）
        int first = queue.poll();
        System.out.println("取り出した値: " + first); // 出力: 10
        System.out.println("キューの内容: " + queue); // 出力: [20, 30]

        // キューが空か確認
        System.out.println("キューが空ですか? " + queue.isEmpty()); // 出力: false
    }
}

