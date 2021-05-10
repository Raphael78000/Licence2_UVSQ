
/**
 * Décrivez votre classe personne ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Personne{
    private String prenom;
    private String nom;
    private String adresse_email;
    protected int annee_a_universite;
    
    public Personne(String prenom,String nom,String adresse_email){
        this.prenom = prenom;
        this.nom = nom;
        this.adresse_email = adresse_email;
        this.annee_a_universite = 1;
    }
    
    public String getPrenom(){
        return this.prenom;
    }
    
    public String getNom(){
        return this.nom;
    }
    
    public String getAdresse_email(){
        return this.adresse_email;
    }
    
    public int getAnnee_universite(){
        return this.annee_a_universite;
    }
    
    public void setPrenom(String prenom){
        this.prenom = prenom;
    }
    
    public void setNom(String nom){
        this.nom = nom;
    }
    
    public void setAdresse_email(String adresse_email){
        this.adresse_email = adresse_email;
    }
    
    public void setAnnee_universite(int annee_a_universite){
        this.annee_a_universite = annee_a_universite;
    }
    
    public String toString(){
            String res = "Nom: " + this.nom + 
                        "\nPrenom: " + this.prenom + 
                        "\nAdresse email: " + this.adresse_email + 
                        "\nNombre d'annees à universite: " + this.annee_a_universite;
        return res;
    }
    
    public static int compareTo(Personne p1,Personne p2){
        return p1.getNom().compareTo(p2.getNom());
    }
}
