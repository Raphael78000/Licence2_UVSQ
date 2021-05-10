
/**
 * Décrivez votre classe etudiant ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Etudiant extends Personne{
    private String P_O_Box;
    private String status;
    private String classe;

    public Etudiant(String prenom,String nom,String adresse_email,String p_O_Box,String status,String classe){
        super(prenom,nom,adresse_email);
        this.P_O_Box = P_O_Box;
        this.status = status;
        this.classe = classe;
    }

    public void incrementerAnnee(){
        this.annee_a_universite = this.annee_a_universite + 1;
        if (this.status.equals("Premiere annee")){
            this.status = "Deuxieme annee";
        }

        else if (this.status.equals("Deuxieme annee")){
            this.status = "Troisieme annee";
        }

        else if (this.status.equals("Troisieme annee")){
            this.status = "Diplome";
        }
    }

    public String getP_O_Box(){
        return this.P_O_Box;
    }

    public String getStatus(){
        return this.status;
    }

    public String getClasse(){
        return this.classe;
    }

    public void setP_O_Box(String P_O_Box){
        this.P_O_Box = P_O_Box;
    }

    public void setStatus(String status){
        this.status = status;
    }

    public void setClasse(String classe){
        this.classe = classe;
    }

    @Override
    public String toString(){
            String res = "Etudiant " + this.getNom() + " " + this.getPrenom() +
                         "\nAdresse mail: " + this.getAdresse_email() +
                         "\nNombre d'années à l'université: " + this.annee_a_universite +
                         "\nBoite aux lettres: " + this.P_O_Box +
                         "\nStatut: " + this.status +
                         "\nClasse: " + this.classe;
            return res;
    }
}
