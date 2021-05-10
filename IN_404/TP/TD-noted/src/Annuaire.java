import java.util.Arrays;
/**
 * Décrivez votre classe Annuaire ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Annuaire{
    int maxSize;
    Personne[] tableau_personne;
    int currentSize;
    
    public Annuaire(){
        maxSize = 10;
        currentSize = 0;
        tableau_personne = new Personne[maxSize];
    }
    
    public void ajouterPersonne(Personne p){
        if (currentSize >= maxSize){
            Personne[] temp = new Personne[2 * maxSize];
            for (int i = 0;i < maxSize;i++){
                temp[i] = this.tableau_personne[i];
            }
            this.tableau_personne = temp;
            maxSize = 2 * maxSize;
        }
        tableau_personne[this.currentSize] = p;
        this.currentSize = this.currentSize + 1;
    }
    
    public void deletePersonne(String nom,String prenom){
        int i = 0;
        while (i < this.currentSize){
            while (tableau_personne[i] != null && !(tableau_personne[i].getNom().equals(nom) && tableau_personne[i].getPrenom().equals(prenom))){
                i = i + 1;
            }
            
            tableau_personne[i] = tableau_personne[i + 1];
            i = i + 1;
        }
        this.currentSize = this.currentSize - 1;
    }
    
    public Personne getPersonne(String nom){
        for (int i = 0;i < currentSize;i++){
            if (tableau_personne[i].getNom().equals(nom)){
                return tableau_personne[i];
            }
        }
        return null;
    }
    
    public void maj_annee(int annee){
        for (int j = 0;j < annee;j++){
            for (int i = 0;i < currentSize;i++){
                if (tableau_personne[i] instanceof Etudiant){
                    ((Etudiant) tableau_personne[i]).incrementerAnnee();
                }
                else if (tableau_personne[i] instanceof Personnel){
                    ((Personnel) tableau_personne[i]).incrementerAnnee();
                }
                else if (tableau_personne[i] instanceof Professeur){
                    ((Professeur)tableau_personne[i]).incrementerAnnee();
                }
            }
        }
    }
    
    public String toString(){
        Personne[] tab_personne = new Personne[currentSize];
        System.arraycopy(this.tableau_personne,0,tab_personne,0,currentSize);
        Arrays.sort(tab_personne,Personne::compareTo);
        String res = null;
        for (int i = 0;i < currentSize;i++){
            res = res + "\n---------\n" + tab_personne[i].toString();
        }
        return res;
    }    
}
