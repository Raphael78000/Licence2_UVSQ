import java.util.ArrayList;

/**
 * A very simple library of Documents to illustrate exercise 3.12.3. 
 * This class simply stores several Documents and, at request, finds a 
 * Document by his title or finds Documents who have the same references on 
 * standard output.
 * 
 * @author Raphael LAZZARI-ARMOUR 
 * @version 15/03/2021
 */
public class Bibliotheque{
    private ArrayList <Document> listeDocuments;

    /**
     * Create a Library.
     */
    public Bibliotheque(){
        this.listeDocuments = new ArrayList <Document> ();
    }
    
    /**
     * Add a Document to the Library.
     */
    public void addDocument(Document file){
        this.listeDocuments.add(file);
    }
    
    /**
     * Search by title if the Document is in the Library.
     */
    public boolean searchDocbyTitle(String title){
        
        for (Document doc : listeDocuments){
            
            if(doc.title == title){
                return true;
            }
        }
        return false;
    }
    
    /**
     * Search Documents in Library having the reference entered.
     */
    public String searchDocbyRef(String name){
        String show = "";
        
        for (Document doc : listeDocuments){
            
            for (Document ref : doc.references){
                
                if (ref.title == name){
                  show = show + "->" + doc.getTitle() + "," + doc.getAuthor(); 
                }
            }
        }
        return show;
    }
}
