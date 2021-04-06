import java.util.ArrayList;

public class Server{
  private String name;
  private boolean is_open;
  private String pass_word;

  private int nbr_client;
  private ArrayList <Client> list_client;

  public Server(String init_pass_word){

    My_random rand = new My_random();
    this.name = rand.get_rand_string();
    this.is_open = false;
    this.pass_word = init_pass_word;

    this.nbr_client = 0;
    this.list_client = new ArrayList<Client>();
  }

  public String get_serv_name(){
    return name;
  }

  public boolean get_opening(){
    return is_open;
  }

  public ArrayList <Client> get_list(){
    return list_client;
  }

  public void add_client(Client c){
    nbr_client++;
    list_client.add(c);
  }

  public boolean set_status_server(String s_pass_word, boolean new_status){
    if (this.pass_word.compareTo(s_pass_word) == 0){
      System.out.println("The status server is change.");
      is_open = new_status;
    }
    else{
      System.out.println("Status serveur failed: Autorisation denied.");
    }
    return is_open;
  }

  public boolean sign(Client c){
    if (c.get_errors() == 0){
      return true;
    }
    else{
      return false;
    }
  }

  public void broadcast(String msg, Client sender){

    for (Client c: list_client){
      if (!sender.is_equal(c)){
        c.receive_msg(msg);
      }
    }
  }

  public void view_list_client(){
    System.out.println("\nListe of client connected:");
    if (nbr_client == 0){
      System.out.println("Nobody.");
    }
    else{
      for (Client c: list_client){
        System.out.println("Client name: " + c.get_user_name());
      }
    }
  }

  public String to_String(){
    return "\nServeur name: " + name + ". It's open: " + is_open + ".";
  }
}
