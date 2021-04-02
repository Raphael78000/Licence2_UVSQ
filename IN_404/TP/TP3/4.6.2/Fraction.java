
/**
 * Write a description of class Fraction here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public final class Fraction{
    private final int numerateur;
    private final int denominateur;
    
    public static final Fraction ZERO = new Fraction(0,1);
    public static final  Fraction UN = new Fraction(1,1);

    /**
     * Constructor for objects of class Fraction
     */
    public Fraction(int numerateur,int denominateur){
        this.numerateur = numerateur;
        this.denominateur = denominateur;
    }
    
    public Fraction(int numerateur){
        this.numerateur = numerateur;
        this.denominateur = 1;
    }
    
    public Fraction(){
        this.numerateur = 0;
        this.denominateur = 1;
    }

    public int getNumerateur(){
        return this.numerateur;
    }
       
    public int getDenominateur(){
        return this.denominateur;
    }
        
    public double getDouble(){
        return this.numerateur / this.denominateur;
    }
    
    public Fraction addtion(Fraction a,Fraction b){
       Fraction res = new Fraction((a.getNumerateur() * b.getDenominateur() + b.getNumerateur() * a.getDenominateur()),
                                    a.getDenominateur() * b.getDenominateur());
       return res;
    }
    
     public boolean equals(Fraction f){
        double num = f.getNumerateur();
        double denom = f.getDenominateur();
        double coef = (numerateur < num ? (double)num / numerateur : (double) numerateur / num);
        
        if ((numerateur * coef) == num && (denominateur * coef) == denom){
            return true;
        }
        return false;
    }
    
    public String getString(){
        String str = numerateur + " / " + denominateur;
        return str;
    }
    
    public Fraction compare(Fraction a,Fraction b){
        if (a.getDouble() < b.getDouble()) return b;
        else return a; 
    }
}
