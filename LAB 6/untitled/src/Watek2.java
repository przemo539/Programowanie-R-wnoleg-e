public class Watek2 extends Thread implements Runnable
{
    private char znak;
    Obraz obraz;
    int moj_id;
    int liczbaZnakow;
    public Watek2(int id, char znaczek, Obraz obrazek, int lZnakow){
        znak = znaczek;
        obraz = obrazek;
        moj_id = id;
        liczbaZnakow= lZnakow;
    }
    public void run() {

        for (int i = 0; i < liczbaZnakow; i++){
            String wynik = "";
             int liczbaWystapien = obraz.licz_wystapienia(znak);
             for (int j = 0; j < liczbaWystapien; j++)
                wynik += "=";
            System.out.println("Watek " + moj_id + ": " + znak + " " + wynik + " ");
            znak++;
         }

    }
}
