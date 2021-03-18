import java.util.ArrayList;
/**
 * A Document class for "the aggregation and composition" exercice(3.12.3) in 
 * object-oriented programming course.
 * 
 * @author Raphael LAZZARI-ARMOUR 
 * @version 15/03/2021
 */
public class Document{
    public String title;
    public String author;
    public int year;
    public ArrayList <Document> references;
    
    /**
     * Create a Document with his title, his author and his year.
     */
    public Document(String title,String author,int year){
        this.title = title;
        this.author = author;
        this.year = year;
        this.references = new ArrayList <Document>();
    }

    /**
     * Return the title of the Document.
     */
    public String getTitle(){
        return this.title;
    }
    
    /**
     * Return the author of the Document.
     */
    public String getAuthor(){
        return this.author;
    }
    
    /**
     * Return the year of the Document.
     */
    public int getYear(){
        return this.year;
    }
    
    /**
     * Add a Reference to the Document.
     */
    public void addReference(Document file){
        this.references.add(file);
    }
    
    /**
     * Return Informations of the Document: title, author, year and its 
     * references.
     */
    public String showDocumentInfos(){
        String show = this.getTitle()+", "+this.getAuthor()+", "+this.getYear();
        
        if (this.references.size() > 0) show = show + " References:";
        
        for(Document ref : references){
            show = show + " ->" + ref.getTitle() + "," + 
            ref.getAuthor();
        }
        return show;
    }
}