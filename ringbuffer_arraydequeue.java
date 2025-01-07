import java.util.ArrayDeque;

public class RingBuffer<T> {
    private final int capacity; // 最大容量
    private final ArrayDeque<T> buffer;

    public RingBuffer(int capacity) {
        this.capacity = capacity;
        this.buffer = new ArrayDeque<>(capacity);
    }

    // 要素を追加
    public void add(T element) {
        if (buffer.size() == capacity) {
            buffer.poll(); // 最古の要素を削除
        }
        buffer.add(element); // 新しい要素を追加
    }

    // 現在の要素をすべて取得
    public T[] getElements() {
        return (T[]) buffer.toArray();
    }

    @Override
    public String toString() {
        return buffer.toString();
    }

    public static void main(String[] args) {
        RingBuffer<Integer> ringBuffer = new RingBuffer<>(3);

        ringBuffer.add(1);
        ringBuffer.add(2);
        ringBuffer.add(3);
        System.out.println("リングバッファの内容: " + ringBuffer); // 出力: [1, 2, 3]

        ringBuffer.add(4); // 1 を上書き
        System.out.println("リングバッファの内容: " + ringBuffer); // 出力: [2, 3, 4]

        ringBuffer.add(5); // 2 を上書き
        System.out.println("リングバッファの内容: " + ringBuffer); // 出力: [3, 4, 5]
    }
}
