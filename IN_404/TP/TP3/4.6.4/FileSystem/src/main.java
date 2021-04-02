public class main{
  public static void main(String []args){

    //Création d'un répertoire et de deux fichiers
    Repertoire rep = new Repertoire("File");
    Regular file1 = new Regular("essai.txt",10);
    Regular file2 = new Regular("text.txt",20);

    //Création d'un répertoire et d'un fichier
    Repertoire srep = new Repertoire("sFile");
    Regular file3 = new Regular("file.txt",4);


    //Ajout des deux fichiers dans le répertoire rep
    rep.add(file1); rep.add(file2);

    //Ajout du fichier3 dans le répertoire srep
    srep.add(file3);

    //Ajout du sous répertoire srep au répertoire Rep
    rep.add(srep);

    System.out.println(rep.getSize());
    System.out.println(rep.getName());
  }
}
