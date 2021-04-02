import java.util.ArrayList;
/**
 * Décrivez votre classe Rep ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Repertoire extends Systeme{
    private ArrayList<Systeme> content;

    public Repertoire(String nom){
        super(nom);
        content = new ArrayList<Systeme>();
    }
    
    public boolean find(Systeme file){
        if ( this == file ) return true;
        
        for (Systeme f: content){
            if (f.find(file)){
                return true;
            }
        }
        return false;
    }
    
    public boolean add(Systeme file){
        if (this.find(file)){
            return false;
        }
        if (file.find(this)){
            return false;
        }
        content.add(file);
        return true;
    }
    
    public String getNom(){
        return super.nom;
    }
    
    public int getSize(){
        int size = 0;
        for (Systeme f: content){
            size += f.getSize();
        }
        return size;
    }
}
