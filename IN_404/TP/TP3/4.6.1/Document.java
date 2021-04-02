/**
 * Abstract class Document - write a description of the class here
 * 
 * @author (your name here)
 * @version (version number or date here)
 */
public abstract class Document{
    protected String titre;

    public Document(String titre){
        this.titre = titre;
    }
    
    public String getTitre(){
        return this.titre;
    }
    
    public abstract String getArtiste();
    public abstract String getRealisateur();
    public abstract int getNbTitres();
    public abstract int getAnnee();

    public String getInfos(){
        return "Titre: " + this.titre;
    }
}