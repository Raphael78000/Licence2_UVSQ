/**
 *  A Personne class for "noted exercise TD" in objected-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR
 * @version 11/05/2021
 */ 
public class Personne{
    private String prenom;
    private String nom;
    private String adresse_email;
    protected int annee_a_universite;

    /**
     * Constructor of class Personne
     */
    public Personne(String prenom,String nom,String adresse_email){
        this.prenom = prenom;
        this.nom = nom;
        this.adresse_email = adresse_email;
        this.annee_a_universite = 1;
    }

    /**
     * Get the first name of the personne
     */
    public String getPrenom(){
        return this.prenom;
    }

    /**
     * Get the last name of the personne
     */
    public String getNom(){
        return this.nom;
    }
    
    /**
     * Get the mail adress of the personne 
     */
    public String getAdresse_email(){
        return this.adresse_email;
    }

    /**
     * Get the number of years of presence at the university of the personne
     */
    public int getAnnee_universite(){
        return this.annee_a_universite;
    }

    /**
     * Set the first name of the personne 
     */
    public void setPrenom(String prenom){
        this.prenom = prenom;
    }

    /**
     * Set the last name of the personne
     */
    public void setNom(String nom){
        this.nom = nom;
    }

    /**
     * Set the mail adress of the personne
     */
    public void setAdresse_email(String adresse_email){
        this.adresse_email = adresse_email;
    }

    /**
     * Set the number of yar of the personne 
     */
    public void setAnnee_universite(int annee_a_universite){
        this.annee_a_universite = annee_a_universite;
    }

    /**
     * Return Personne informations under a string 
     */
    @Override
    public String toString(){
            String res = "Nom: " + this.nom +
                        "\nPrenom: " + this.prenom +
                        "\nAdresse email: " + this.adresse_email +
                        "\nNombre d'annees à universite: " + this.annee_a_universite;
        return res;
    }

    /**
     * Compare if two persons has the same data informations 
     */
    public static int compareTo(Personne p1,Personne p2){
        return p1.getNom().compareTo(p2.getNom());
    }
}
