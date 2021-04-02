/**
 * Write a description of class Dvd here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class DVD extends Document{
    private String realisateur;
    private int annee;

    public DVD(String titre,String realisateur,int annee){
        super(titre);
        this.realisateur = realisateur;
        this.annee = annee;
    }
    
    public String getRealisateur(){
        return this.realisateur;
    }
    
    public int getAnnee(){
        return this.annee;
    }

    public String getInfos(){
        return super.getInfos()+ ", " + "Realisateur: " + 
        getRealisateur() + ", " + "Annee de sortie: " + getAnnee();
    }
}