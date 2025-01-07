public class RingBuffer<T> {
    private final T[] buffer;
    private int head = 0; // 次に上書きする位置
    private int size = 0; // 現在の要素数
    private final int capacity;

    public RingBuffer(int capacity) {
        this.capacity = capacity;
        this.buffer = (T[]) new Object[capacity];
    }

    // 要素を追加
    public void add(T element) {
        buffer[head] = element; // 要素を追加
        head = (head + 1) % capacity; // インデックスを更新
        if (size < capacity) size++; // サイズを増やす
    }

    // 現在の要素を取得
    public T[] getElements() {
        T[] elements = (T[]) new Object[size];
        for (int i = 0; i < size; i++) {
            elements[i] = buffer[(head - size + i + capacity) % capacity];
        }
        return elements;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < size; i++) {
            if (i > 0) sb.append(", ");
            sb.append(buffer[(head - size + i + capacity) % capacity]);
        }
        sb.append("]");
        return sb.toString();
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
