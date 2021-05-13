 /**
 *  A Person doesn't exist Exception class for "noted exercise TD" in objected-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR
 * @version 11/05/2021
 */ 
public class PersonNoneExistant extends Exception{
    public PersonNoneExistant(String nom,String prenom){
        super(nom + prenom);
    }
    
    public PersonNoneExistant(String nom){
        super(nom);
    }
}
