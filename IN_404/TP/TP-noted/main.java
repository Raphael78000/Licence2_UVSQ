
/**
 * Décrivez votre classe main ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class main{
    public static void main(String args[]) throws PersonNoneExistant, Person_Exist {
        Annuaire a1 = new Annuaire(10);
        
        Etudiant e1 = new Etudiant("Adam","Smith","adam.smith@gmail.com","Box28","Premiere annee","licence");
        Etudiant e2 = new Etudiant("Leo","Dubois","leo.dubois@mail.com","Box55","Troisieme annee","master");

        Personnel p1 = new Personnel("Sarah","Lefevre","sarah.lefevre@gmail.com","A208","","Secretaire");

        Professeur prof1 = new Professeur("Alice","Rolland","alice.rolland@mail.com","A111","","Mathematiques");
        Professeur prof2 = new Professeur("Guillaume","Gatti","guillaume.gatti@gmail.com","B220","","Sciences");

        try{
            a1.ajouterPersonne(e1);
            a1.ajouterPersonne(e2);
            a1.ajouterPersonne(p1);
            a1.ajouterPersonne(prof1);
            a1.ajouterPersonne(prof2);
        }
        catch (NullPointerException e){
          System.err.println(e.getMessage());
        }

        System.out.println(a1.toString());

        a1.maj_annee(1);

        Personnel p2 = new Personnel("Quentin","ercier","quentin.mercier@mail.com","B224","","Responsable commnicaion");
        Etudiant e3 = new Etudiant("Chloé","Perez","chloe.perrez@live.com","Box34","Deuxieme annee","licence");

        try{
          a1.ajouterPersonne(p2);
          a1.ajouterPersonne(e3);
        }
        catch (NullPointerException e){
          System.err.println(e.getMessage());
        }

        System.out.println(a1.toString());

        try{
            a1.deletePersonne(e2.getNom(),e2.getPrenom());
        }

        catch (NullPointerException e){
            System.err.println(e.getMessage());
        }
        System.out.println(a1.toString());

        Personne find = null;
        
        try{
            find = a1.getPersonne("Lefevre");
        }

        catch (NullPointerException e){
          System.err.println(e.getMessage());
        }
        
        if (find != null){
            System.out.println(find.toString());
        }
    }
}
