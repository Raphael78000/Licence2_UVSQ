
/**
 * Décrivez votre classe Fichier ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public abstract class Systeme{
    protected String nom;
    
    public Systeme(String nom){
        this.nom = nom;
    }
    
    public String getName(){
        return this.nom;
    }
    
    public String toString(){
        return this.nom;
    }
    
    public boolean find(Systeme file){
        return (this == file);
    }
    
    public abstract int getSize();
}
