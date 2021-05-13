/**
 *  A Etudiant class for "noted exercise TD" in objected-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR
 * @version 11/05/2021
 */ 
public class Etudiant extends Personne{
    private String P_O_Box;
    private String status;
    private String classe;

    /**
     * Constructor of class Etudiant
     */
    public Etudiant(String prenom,String nom,String adresse_email,String p_O_Box,String status,String classe){
        super(prenom,nom,adresse_email);
        this.P_O_Box = P_O_Box;
        this.status = status;
        this.classe = classe;
    }

    /**
     * Increment of one unit the number of year at university of the student
     */
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

    /**
     * Get postal box of the student 
     */
    public String getP_O_Box(){
        return this.P_O_Box;
    }

    /**
     * Get the status of the student 
     */
    public String getStatus(){
        return this.status;
    }

    /**
     * Get the classe of the student 
     */
    public String getClasse(){
        return this.classe;
    }

    /**
     * Set the postal box of the student 
     */
    public void setP_O_Box(String P_O_Box){
        this.P_O_Box = P_O_Box;
    }

    /**
     * Set the status of the student 
     */
    public void setStatus(String status){
        this.status = status;
    }

    /**
     * Set the casse of the student 
     */
    public void setClasse(String classe){
        this.classe = classe;
    }

    /**
     * Return the student informations under a string 
     */
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
