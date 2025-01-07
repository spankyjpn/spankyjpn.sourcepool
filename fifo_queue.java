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
        int first = queue.poll(); // 先頭の要素を取得して削除
        System.out.println("取り出した値: " + first); // 出力: 10
        System.out.println("キューの内容: " + queue); // 出力: [20, 30]

        // キューの先頭を確認（削除しない）
        System.out.println("次の値: " + queue.peek()); // 出力: 20

        // キューが空か確認
        System.out.println("キューが空ですか? " + queue.isEmpty()); // 出力: false
    }
}
