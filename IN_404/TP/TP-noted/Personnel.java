/**
 *  A Personnel class for "noted exercise TD" in objected-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR
 * @version 11/05/2021
 */ 
public class Personnel extends Personne{
    private String bureau;
    private String extension_de_bureau;
    private String status;

    /**
     * Constructor of class Personnel 
     */
    public Personnel(String prenom,String nom,String adresse_email,String bureau,String extension_de_bureau,String status){
        super(prenom,nom,adresse_email);
        this.bureau = bureau;
        this.extension_de_bureau = extension_de_bureau;
        this.status = status;
    }

    /**
     * Increment of one unit the number of year at university of the personnel
     */
    public void incrementerAnnee(){
        this.annee_a_universite = this.annee_a_universite + 1;
    }

    /**
     * Get the bureau of the personnel
     */
    public String getBureau(){
        return this.bureau;
    }

    /**
     * Get the extension de bureau of the personnel 
     */
    public String getExtension_de_bureau(){
        return this.extension_de_bureau;
    }

    /**
     * Get the status of the personnel
     */
    public String getStatus(){
        return this.status;
    }

    /**
     * Set the bureau of the personnel
     */
    public void setBureau(String bureau){
        this.bureau = bureau;
    }

    /**
     * Set the extension de bureau of the personnel 
     */
    public void setExtension_de_bureau(String extension_de_bureau){
        this.extension_de_bureau = extension_de_bureau;
    }

    /**
     * Set the status of the personnel
     */
    public void setStatus(String status){
        this.status = status;
    }

    /**
     * Return the personnel information under a string
     */
    @Override
    public String toString(){
            String res = "Personnel: " + this.getNom() + this.getPrenom() +
                         "\nAdresse email: " + this.getAdresse_email() +
                         "\nNombre d'annees a universite: " + this.annee_a_universite +
                         "\nBureau: " + this.bureau +
                         "\nStatut: " + this.status +
                         "\nExtension de bureau: " + this.extension_de_bureau;
        return res;
    }
}
