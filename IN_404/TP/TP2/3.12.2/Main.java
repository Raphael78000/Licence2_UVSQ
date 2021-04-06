import java.io.*;
import java.util.ArrayList;

public class Main{
  public static void main(String[] args) throws IOException{
    // Init a new server //
    Server server_1 = new Server("xe69uhy8");
    System.out.println(server_1.to_String());
    server_1.set_status_server("xe69uhy8", true);
    System.out.println(server_1.to_String());

    // Creat a new client //
    System.out.print("\nFirst client:");
    Client c1 = new Client();
    System.out.println(c1.to_String());
    c1.sign_in(server_1);

    // Creat a new client //
    System.out.print("\nSecond client:");
    Client c2 = new Client();
    System.out.println(c2.to_String());
    c2.sign_in(server_1);

    System.out.print("\n6 new clients");
    Client tab_client[] = new Client[6];

    for(Client c: tab_client){
        c = new Client();
        System.out.println(c.to_String());
        c.sign_in(server_1);
    }

    server_1.view_list_client();

    // Get one client connected //
    ArrayList <Client> list = server_1.get_list();
    if(list.size() > 1){
        Client tmp = list.get(0);
        tmp.send_msg("Hello everyone", server_1);
    }
  }
}
