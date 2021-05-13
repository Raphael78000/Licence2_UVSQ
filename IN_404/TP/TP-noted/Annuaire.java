import java.util.Arrays;
import java.lang.Exception;
/**
 *  A Annuaire class for "noted exercise TD" in objected-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR
 * @version 11/05/2021
 */ 
public class Annuaire{
    private int maxSize;
    private Personne[] tableau_personne;
    private int currentSize;

    /**
     * Constructor of class Annuaire
     */
    public Annuaire(final int maxSize){
        this.maxSize = maxSize;
        this.currentSize = 0;
        this.tableau_personne = new Personne[maxSize];
    }

    /**
     * Add a personne to the annuaire
     */
    public void ajouterPersonne(Personne p) throws NullPointerException,Person_Exist{
        if (p == null){
          throw new NullPointerException("La Personne souhaitant etre ajoutee n'existe pas");
        }
        
        for (int i = 0;i < maxSize;i++){
            if (this.tableau_personne[i].equals(p)){
                throw new Person_Exist("La Personne est deja presente dans annuaire");
            }
        }
        
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

    /**
     * Delete a personne of the annuaire
     */
    public void deletePersonne(String nom,String prenom) throws NullPointerException,PersonNoneExistant{
        if (this.currentSize == 0){
            throw new NullPointerException("L Annuaire est vide");
        }
 
        for (int i = 0;i < this.currentSize;i++){
          if (tableau_personne[i].getNom().equals(nom) && tableau_personne[i].getPrenom().equals(prenom)){
            this.currentSize = this.currentSize - 1;

            for (int j = i;j < currentSize;j++){
              tableau_personne[j] = tableau_personne[j + 1];
            }
            return;
          }
        }
        throw new PersonNoneExistant(nom,prenom);
    }

    /**
     * Get a personne if that one exist in annuaire
     */
    public Personne getPersonne(String nom) throws NullPointerException,PersonNoneExistant{
      if (this.currentSize == 0){
          throw new NullPointerException("L Annuaire est vide");
      }
        for (int i = 0;i < currentSize;i++){
            if (tableau_personne[i].getNom().equals(nom)){
                return tableau_personne[i];
            }
        }
        throw new PersonNoneExistant(nom);
    }

    /**
     * Increment of 'annee' year each personne of the annuaire
     */
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

    /**
     * Return annuaire informations under a string 
     */
    @Override
    public String toString(){
        Personne[] tab_personne = new Personne[currentSize];
        System.arraycopy(this.tableau_personne,0,tab_personne,0,currentSize);
        Arrays.sort(tab_personne,Personne::compareTo);
        String res = null;
        for (int i = 0;i < currentSize;i++){
            res = res + "\n   ---   \n" + tab_personne[i].toString();
        }
        return res;
    }
}
