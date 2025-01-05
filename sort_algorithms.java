import java.util.*;

public class Main {

    public static void main(String[] args) {
        // テストデータ
        int[] array = {20, 6, 55, 74, 3, 45, 13, 87, 46, 30};

        System.out.println("Original Array:");
        printArray(array);

        // バブルソート
        int[] bubbleSortedArray = array.clone();
        BubbleSort.sort(bubbleSortedArray);
        System.out.println("Bubble Sort:");
        printArray(bubbleSortedArray);

        // 選択ソート
        int[] selectionSortedArray = array.clone();
        SelectionSort.sort(selectionSortedArray);
        System.out.println("Selection Sort:");
        printArray(selectionSortedArray);

        // 挿入ソート
        int[] insertionSortedArray = array.clone();
        InsertionSort.sort(insertionSortedArray);
        System.out.println("Insertion Sort:");
        printArray(insertionSortedArray);

        // シェルソート
        int[] shellSortedArray = array.clone();
        ShellSort.sort(shellSortedArray);
        System.out.println("Shell Sort:");
        printArray(shellSortedArray);
    }

    // 配列を表示する関数
    public static void printArray(int[] array) {
        for (int value : array) {
            System.out.print(value + " ");
        }
        System.out.println();
    }
}

// シェルソート
class ShellSort {
    public static void sort(int[] a) {
        int n = a.length;

        // Knuthの間隔を計算
        ArrayList<Integer> intervals = getKnuthIntervals(n);

        // シェルソート
        for (int h : intervals) {
            for (int i = h; i < n; i++) {
                int j = i;
                while (j >= h && a[j - h] > a[j]) {
                    // スワップ処理
                    int temp = a[j];
                    a[j] = a[j - h];
                    a[j - h] = temp;
                    j -= h;
                }
            }
        }
    }

    // Knuthの間隔を計算する関数
    private static ArrayList<Integer> getKnuthIntervals(int n) {
        ArrayList<Integer> intervals = new ArrayList<>();
        int h = 1;

        // Knuthの間隔を生成
        while (h < n) {
            intervals.add(h);
            h = 3 * h + 1; // 次の間隔を計算
        }

        // 大きい順にする
        Collections.reverse(intervals);

        return intervals;
    }
}

// バブルソート
class BubbleSort {
    public static void sort(int[] a) {
        int n = a.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    // スワップ処理
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }
    }
}

// 選択ソート
class SelectionSort {
    public static void sort(int[] a) {
        int n = a.length;
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[minIndex]) {
                    minIndex = j;
                }
            }
            // スワップ処理
            int temp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = temp;
        }
    }
}

// 挿入ソート
class InsertionSort {
    public static void sort(int[] a) {
        int n = a.length;
        for (int i = 1; i < n; i++) {
            int key = a[i];
            int j = i - 1;

            // keyより大きい値を1つ右にずらす
            while (j >= 0 && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
    }
}
