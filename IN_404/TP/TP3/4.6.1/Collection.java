import java.util.ArrayList;
import java.util.List;
/**
 * Write a description of class Collection here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Collection{
    public ArrayList<Document> collection;

    public Collection(){
        this.collection = new ArrayList<Document>();
    }
    
    public void ajouterDoc(Document doc){
        this.collection.add(doc);
    }

    public String listCollection(){
        String list = "";
        
        for (Document doc: collection){
            list += doc.getTitre() + ", ";
        }
        return list;
    }
    
    public String DocFound(String name){
        String list = "";
        
        for (Document doc: collection){
            if (doc.getTitre().compareTo(name) == 0){
                list += doc.getTitre() + ", ";
            }
            else if (doc.getArtiste().compareTo(name) == 0){
                list += doc.getTitre() + ", ";
            }
            else if (doc.getRealisateur().compareTo(name) == 0){
                list += doc.getTitre() + ", ";
            }
        }
        return list;
    }
}