
/**
 * Décrivez votre classe Professeur ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Professeur extends Personne{
    String bureau;
    String extension_de_bureau;
    String departement;
    
    public Professeur(String prenom,String nom,String adresse_email,String bureau,String extension_de_bureau,String departement){
        super(prenom,nom,adresse_email);
        this.bureau = bureau;
        this.extension_de_bureau = extension_de_bureau;
        this.departement = departement;
    }
    
    public void incrementerAnnee(){
        this.annee_a_universite = this.annee_a_universite + 1;
    }
    
    public String getBureau(){
        return this.bureau;
    }
    
    public String getExtension_de_Bureau(){
        return this.extension_de_bureau;
    }
    
    public String getDepartement(){
        return this.departement;
    }
    
    public void setExtension_de_Bureau(String extension_de_bureau){
        this.extension_de_bureau = extension_de_bureau;
    }
    
    public void setDepartement(String departement){
        this.departement = departement;
    }
    
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
