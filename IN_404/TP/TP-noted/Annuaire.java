import java.util.Arrays;
import java.lang.Exception;
/**
 * Décrivez votre classe Annuaire ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Annuaire{
    private int maxSize;
    private Personne[] tableau_personne;
    private int currentSize;

    public Annuaire(final int maxSize){
        this.maxSize = maxSize;
        this.currentSize = 0;
        this.tableau_personne = new Personne[maxSize];
    }

    public void ajouterPersonne(Personne p) throws NullPointerException,Person_Exist{
      if (p == null) throw new NullPointerException("Personne souhaitant etre ajoute existe pas");

        if (currentSize >= maxSize){
            Personne[] temp = new Personne[2 * maxSize];
            for (int i = 0;i < maxSize;i++){
              if (this.tableau_personne[i].equals(p)){
                throw new Person_Exist("Personne deja presente dans annuaire");
              }
                temp[i] = this.tableau_personne[i];
            }
            this.tableau_personne = temp;
            maxSize = 2 * maxSize;
        }
        tableau_personne[this.currentSize] = p;
        this.currentSize = this.currentSize + 1;
    }

    public void deletePersonne(String nom,String prenom) throws NullPointerException,PersonNoneExistant{
        if (this.currentSize == 0){
            throw new NullPointerException("Le tableau est vide");
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

    public Personne getPersonne(String nom) throws NullPointerException,PersonNoneExistant{
      if (this.currentSize == 0){
          throw new NullPointerException("Le tableau est vide");
      }
        for (int i = 0;i < currentSize;i++){
            if (tableau_personne[i].getNom().equals(nom)){
                return tableau_personne[i];
            }
        }
        throw new PersonNoneExistant(nom);
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

    @Override
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
