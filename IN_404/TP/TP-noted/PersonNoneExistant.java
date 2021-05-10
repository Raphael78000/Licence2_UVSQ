
/**
 * Décrivez votre classe PersonNoneExistant ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class PersonNoneExistant extends Exception{
    public PersonNoneExistant(String nom,String prenom){
        super(nom + prenom);
    }
    
    public PersonNoneExistant(String nom){
        super(nom);
    }
}
