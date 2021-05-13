/**
 *  A Professeur class for "noted exercise TD" in objected-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR
 * @version 11/05/2021
 */ 
public class Professeur extends Personne{
    private String bureau;
    private String extension_de_bureau;
    private String departement;

    /**
     * Constructor of class Professeur 
     */
    public Professeur(String prenom,String nom,String adresse_email,String bureau,String extension_de_bureau,String departement){
        super(prenom,nom,adresse_email);
        this.bureau = bureau;
        this.extension_de_bureau = extension_de_bureau;
        this.departement = departement;
    }

    /**
     * Increment of one unit the number of year at university of the professor 
     */
    public void incrementerAnnee(){
        this.annee_a_universite = this.annee_a_universite + 1;
    }

    /**
     * Get the bureau of the professor 
     */
    public String getBureau(){
        return this.bureau;
    }

    /**
     * Get extension de bureau of the professor 
     */
    public String getExtension_de_Bureau(){
        return this.extension_de_bureau;
    }

    /**
     * Get the departement of the professor
     */
    public String getDepartement(){
        return this.departement;
    }
    
    /**
     * Set bureau of professor
     */
    public void setBureau(String bureau){
        this.bureau = bureau;
    }

    /**
     * Set the extension de bureau of the professor
     */
    public void setExtension_de_Bureau(String extension_de_bureau){
        this.extension_de_bureau = extension_de_bureau;
    }

    /**
     * Set the departement of the professor
     */
    public void setDepartement(String departement){
        this.departement = departement;
    }

    /**
     * Return Professor informations under a string 
     */
    @Override
    public String toString(){
            String res = "Professeur: " + this.getNom() + this.getPrenom() +
                         "\nAdresse email: " + this.getAdresse_email() +
                         "\nNombre annees a universite: " + this.annee_a_universite +
                         "\nBureau: " + this.bureau +
                         "\nDepartement: " + this.departement +
                         "\nExtension de bureau: " + this.extension_de_bureau;

        return res;
    }
}
