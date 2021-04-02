
/**
 * Décrivez votre classe Regular ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Regular extends Systeme{
    private int taille;
    
    public Regular(String nom,int taille){
        super(nom);
        this.taille = taille;
    }
    
    public int getSize(){
        return this.taille;
    }
    
    public String toString(){
        return super.toString() + "De taille: " + this.taille;
    }
}
