/**
 *  Main class for "noted exercise TD" in objected-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR
 * @version 11/05/2021
 */ 
public class main{
    
    public static void main(String args[]) throws PersonNoneExistant, Person_Exist {
        //Création d'un annuaire de taille 
        Annuaire a1 = new Annuaire(2);
        
        //Création d'un étudiant et d'un personnel
        Etudiant e1 = new Etudiant("Adam","Smith","adam.smith@gmail.com","Box28","Premiere annee","licence");
        Personnel p1 = new Personnel("Sarah","Lefevre","sarah.lefevre@gmail.com","A208","","Secretaire");
        
        //Ajout des personnes à l'annuaire
        try{
            a1.ajouterPersonne(e1);
            a1.ajouterPersonne(p1);
        }
        catch (Exception e){
          System.err.println(e.getMessage());
        }
        
        //Affichage de l'annuaire
        System.out.println(a1.toString());
        
        //Création d'un étudiant
        Etudiant e2 = new Etudiant("Leo","Dubois","leo.dubois@mail.com","Box55","Troisieme annee","master");
        
        //Ajout d'un étudiant à l'annuaire ce qui entraînera un agrandissement e l'annuaire
        try{
            a1.ajouterPersonne(e2);
        }
        catch (Exception e){
          System.err.println(e.getMessage());
        }
        
        //Suppression de l'étudiant numéro 2 de l'annuaire
        try{
            a1.deletePersonne("Leo","Dubois");
        }
        catch (Exception e){
            System.err.println(e.getMessage());
        }
        
        //Mise à jour de l'annuaire d'une année supplémentaire
        a1.maj_annee(1);
        
        //Affichage de l'annuaire
        System.out.println(a1.toString());
        
        
        Personne find = null;
        
        try{
            find = a1.getPersonne("Lefevre");
            if (find != null){
                System.out.println(find.toString());
            }
        }
        catch (Exception e){
          System.err.println(e.getMessage());
        }        
    }
}
