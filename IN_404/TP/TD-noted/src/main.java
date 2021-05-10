
/**
 * Décrivez votre classe main ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class main{
    public static void main(String args[]){
        Etudiant e1 = new Etudiant("Adam","Smith","adam.smith@gmail.com","Box28","Premiere annee","licence");
        Etudiant e2 = new Etudiant("Leo","Dubois","leo.dubois@mail.com","Box55","Troisieme annee","master");
        
        Personnel p1 = new Personnel("Sarah","Lefevre","sarah.lefevre@gmail.com","A208","","Secretaire");
        
        Professeur prof1 = new Professeur("Alice","Rolland","alice.rolland@mail.com","A111","","Mathematiques");
        Professeur prof2 = new Professeur("Guillaume","Gatti","guillaume.gatti@gmail.com","B220","","Sciences");
        
        Annuaire a1 = new Annuaire();
        a1.ajouterPersonne(e1);
        a1.ajouterPersonne(e2);
        a1.ajouterPersonne(p1);
        a1.ajouterPersonne(prof1);
        a1.ajouterPersonne(prof2);
        
        System.out.println(a1.toString());
        
        a1.maj_annee(1);
        
        Personnel p2 = new Personnel("Quentin","ercier","quentin.mercier@mail.com","B224","","Responsable commnicaion");
        Etudiant e3 = new Etudiant("Chloé","Perez","chloe.perrez@live.com","Box34","Deuxieme annee","licence");
        
        a1.ajouterPersonne(p2);
        a1.ajouterPersonne(e3);
        
        System.out.println(a1.toString());
        a1.deletePersonne(e2.getNom(),e2.getPrenom());
        System.out.println(a1.toString());
        
        System.out.println(a1.getPersonne("Lefevre"));
    }
}
