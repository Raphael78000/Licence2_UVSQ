/**
 * Write a description of class Cd here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class CD extends Document{
    private String artiste;
    private int Nbtitres;

    public CD(String titre,String artiste,int Nbtitres){
        super(titre);
        this.artiste = artiste;
        this.Nbtitres = Nbtitres;
    }
    
    public String getArtiste(){
        return this.artiste;
    }
    
    public int getNbTitres(){
        return this.Nbtitres;
    }

    public String getInfos(){
        return super.getInfos()+ ", " + "Artiste: " + 
        getArtiste() + ", " + "Nombre de titres: " + getNbTitres();
    }
}