import java.util.concurrent.RecursiveTask;


class DivideTask extends RecursiveTask<int[]> {
 
  int[] arrayToDivide;
 
  public DivideTask(int[] arrayToDivide) {
    this.arrayToDivide = arrayToDivide;
  }
 
  protected int[] compute() {
      int []array_1=new int[arrayToDivide.length/2];
      int []array_2;
      if(arrayToDivide.length%2 == 0) {
          for (int i = 0; i < arrayToDivide.length / 2; i++) {
              array_1[i] = arrayToDivide[i];
          }
          array_2 = new int[arrayToDivide.length/2];
          for (int i = arrayToDivide.length / 2; i < arrayToDivide.length; i++) {
              array_2[i-arrayToDivide.length / 2] = arrayToDivide[i];
          }
      }else {
          array_2 = new int[arrayToDivide.length/2+1];
          for (int i = 0; i < arrayToDivide.length / 2; i++) {
              array_1[i] = arrayToDivide[i];
          }
           for (int i = arrayToDivide.length / 2; i < arrayToDivide.length+1; i++) {
              array_2[i-arrayToDivide.length / 2] = arrayToDivide[i];
          }
      }
 
      DivideTask task1 = new DivideTask(array_1);
      DivideTask task2 = new DivideTask(array_2);

      task1.fork();
      task2.fork();
      int[] scal_tab =new int[arrayToDivide.length];
      //Wait for results from both tasks
      int[] tab1 = task1.join();
      int[] tab2 = task2.join();

      scal_tab(tab1, tab2, scal_tab);
      return scal_tab;
  }

  private void scal_tab(
          int[] tab1,
          int[] tab2,
          int[] scal_tab) {
     
    int i = 0, j = 0, k = 0;
     
    while ((i < tab1.length) && (j < tab2.length)) {
     
      if (tab1[i] < tab2[j]) {
        scal_tab[k] = tab1[i++];
      } else {
        scal_tab[k] = tab2[j++];
      }
       
      k++;
    }
     
    if (i == tab1.length) {
       
      for (int a = j; a < tab2.length; a++) {
        scal_tab[k++] = tab2[a];
      }
       
    } else {
       
      for (int a = i; a < tab1.length; a++) {
        scal_tab[k++] = tab1[a];
      }
       
    }
  }

}
