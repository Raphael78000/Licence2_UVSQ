
/**
 * Décrivez votre classe Personnel ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Personnel extends Personne{
    private String bureau;
    private String extension_de_bureau;
    private String status;

    public Personnel(String prenom,String nom,String adresse_email,String bureau,String extension_de_bureau,String status){
        super(prenom,nom,adresse_email);
        this.bureau = bureau;
        this.extension_de_bureau = extension_de_bureau;
        this.status = status;
    }

    public void incrementerAnnee(){
        this.annee_a_universite = this.annee_a_universite + 1;
    }

    public String getBureau(){
        return this.bureau;
    }

    public String getExtension_de_bureau(){
        return this.extension_de_bureau;
    }

    public String getStatus(){
        return this.status;
    }

    public void setBureau(String bureau){
        this.bureau = bureau;
    }

    public void setExtension_de_bureau(String extension_de_bureau){
        this.extension_de_bureau = extension_de_bureau;
    }

    public void setStatus(String status){
        this.status = status;
    }

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
