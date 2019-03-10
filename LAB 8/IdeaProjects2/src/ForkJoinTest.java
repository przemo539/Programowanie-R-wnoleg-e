import java.util.Scanner;
import java.util.concurrent.ForkJoinPool;

public class ForkJoinTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Set array size: ");
        int totalNumbers = scanner.nextInt();
        int[] numbers = new int[totalNumbers]; // ...nadanie wartości w tablicy

        DivideTask task = new DivideTask(numbers);
        ForkJoinPool forkJoinPool = new ForkJoinPool();
        forkJoinPool.invoke(task); // invoke umożliwia oczekiwanie na wynik
//forkJoinPool.execute(task);
        System.out.println("Max el in array: " + task.join());
    }
}