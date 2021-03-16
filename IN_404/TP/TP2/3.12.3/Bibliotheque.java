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
    private Bibliotheque(){
        this.listeDocuments = new ArrayList <Document> ();
    }
    
    /**
     * Add a Document to the Library.
     */
    private void addDocument(Document file){
        this.listeDocuments.add(file);
    }
    
    /**
     * Search by title if the Document is in the Library.
     */
    private boolean searchDocbyTitle(String title){
        
        for(int i=0;i<this.listeDocuments.size();i++){
            
            if(this.listeDocuments.get(i).title == title){
                return true;
            }
        }
        return false;
    }
    
    /**
     * Search Documents in Library having the reference entered.
     */
    private String searchDocbyRef(String name){
        String show = "";
        
        for (Document doc : listeDocuments){
            
            for (Document ref : doc.references){
                
                if (ref.title.compareTo(name) == 0){
                  show = show + "->" + doc.getTitle() + "," + doc.getAuthor(); 
                }
            }
        }
        return show;
    }
}
