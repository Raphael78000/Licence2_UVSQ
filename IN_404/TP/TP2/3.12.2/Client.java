import java.io.*;

public class Client{
  private String name;
  private int errors;

  public Client(){
    My_random rand = new My_random();

    this.name = rand.get_rand_string();
    this.errors = rand.get_rand_int();
  }

  public String get_user_name(){
    return name;
  }

  public int get_errors(){
    return errors;
  }

  public void set_user_name(String u_name){
    System.out.println("User name is change.");
    name = u_name;
  }

  public boolean sign_in(Server s){

    if (s.get_opening()){

      if (s.sign(this)){
        System.out.println(this.name + ": Connected.");
        s.add_client(this);

        return true;
      }
      else {
        return false;
      }
    }
    return false;
  }

  public boolean is_equal(Client other){
    if ((this.name.compareTo(other.get_user_name()) == 0) && (this.errors == other.errors))
      return true;
    return false;
  }

  public void send_msg(String msg, Server s){
    System.out.println("\nClient '" + name + "' send a new message for everyone.");
    s.broadcast(msg, this);
  }

  public void receive_msg(String msg){
    System.out.println("\nClient: '" + name + "' receive a new message :\n" + msg + ".");
  }

  public String to_String(){
    return "\nName user is: " + name + ". Number(s) of error(s) is: " + errors + ".";
  }
}
