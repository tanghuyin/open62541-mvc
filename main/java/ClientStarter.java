import java.util.Scanner;

public class ClientStarter {
    public static void main(String[] args) {
        ClientRunner clientRunner = new ClientRunner();
        Thread client = new Thread(clientRunner);
        client.start();
    }
}
