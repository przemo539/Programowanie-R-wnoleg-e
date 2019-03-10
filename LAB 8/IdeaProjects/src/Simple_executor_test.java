import java.util.concurrent.*;
import java.util.List;
import java.util.ArrayList;

public class Simple_executor_test {

    private static final int NTHREADS = 10;
    public static double xp =0;
    public static double xk = Math.PI;
    public static double interv = 0.001;
        
    public static void main(String[] args) {
    	Calka_callable calka = new Calka_callable(xp, xk, interv);
		System.out.println("PIERWSZA CALKA"+calka.compute());

	Counter counter = new Counter();
	ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

	List<Future<Double>> result = new ArrayList<>();
    Callable<Double> calka2;
    Future<Double> part;
    double step = (xk-xp)/100;

	for (int i = 0; i < 100; i++) {
	   calka2 = new Calka_callable(i*step, (i+1)*step, 0.001);
	   part = executor.submit(calka2);
	   result.add(part);
	}

	double out = 0;
	for(Future<Double>p_out:result){
        try {
            out+=p_out.get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
    }
        System.out.println("Wynik po execut:"+out);
	// This will make the executor accept no new threads
	// and finish all existing threads in the queue
	executor.shutdown();

	// Wait until all threads finish
	while (!executor.isTerminated()) {}

	System.out.println("Finished all threads");
	System.out.format("\nCounter_1: %d, Counter_2 %d\n\n", 
			  counter.get_c1(), counter.get_c2());
    }
} 
