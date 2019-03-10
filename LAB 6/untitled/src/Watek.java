public class Watek extends Thread
{
    private char znak;
    Obraz obraz;
    int moj_id;
    public Watek(int id, char znaczek, Obraz obrazek){
        znak = znaczek;
        obraz = obrazek;
        moj_id = id;
    }
    public void run(){
        String wynik="";
        int liczbaWystapien = obraz.licz_wystapienia(znak);
        for(int i=0; i<liczbaWystapien;i++)
            wynik+="=";
        System.out.println("Watek "+moj_id+": "+znak+" "+wynik+" ");

    }
}
