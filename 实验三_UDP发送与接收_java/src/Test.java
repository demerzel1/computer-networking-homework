import com.tsr.simplechat.client.ChatClient;
import com.tsr.simplechat.receive_server.ChatServer;

public class Test {
    public static void main(String[] args) {
        ChatServer r = new ChatServer();
        r.start();

        ChatClient c1 = new ChatClient("001", "ÌğÌğ");
        ChatClient c2 = new ChatClient("001", "ÃÈÃÈ");
        ChatClient c3 = new ChatClient("002", "´óÌğÌğ");
        ChatClient c4 = new ChatClient("002", "´óÃÈÃÈ");
    }
}
