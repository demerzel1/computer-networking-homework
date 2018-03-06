package com.tsr.simplechat.client;

import java.awt.Button;
import java.awt.Event;
import java.awt.Frame;
import javax.swing.JLabel;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import com.tsr.simplechat.bean.MessageEntity;
import com.tsr.simplechat.receive_server.ChatServer;

//�ͻ��˳���
public class ChatClient extends Frame {
    private static final long serialVersionUID = 1L;
    // ������ID
    private String groupID;
    // �ͻ����û���
    private String clientName;
    // �ͻ�����Ϣ���ͷ����׽���
    private DatagramSocket msg_send;
    // ����˿�
    private final int PORT = 10000;
    // ������IP��ַ
    private InetAddress ip;

    // �ͻ��˿ؼ�
    TextField tf = new TextField(20);
    TextArea ta = new TextArea();
    Button send = new Button("send");

    // �ͻ��˹�����
    public ChatClient(String groupID, String clientName) {

        super( groupID + "/" + clientName);
        this.clientName = clientName;
        this.groupID = groupID;
        // ���ÿͻ��˽�����ʽ
        // add(new JLabel("First Name"));
        add("North",tf);
        add("Center", ta);
        add("South", send);
        setSize(300, 300);
        show();
        // ������ط�������ʼ��
        init();

        // ������
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                // �ر���Ϣ���ͷ���
                msg_send.close();
                // �رտͻ��˳���
                dispose();
                System.exit(0);
            }
        });

    }

    // ������ط�������ʼ��
    private void init() {
        // ע�ᵱǰ�û���������������Ϣע�ᵽ������
        ChatServer.logInGroup(groupID, this);
        try {
            // ��ʼ����Ϣ�����׽��ֶ���
            msg_send = new DatagramSocket();
            // ָ����Ϣ������
            try {
                ip = InetAddress.getByName("127.0.0.1");
            } catch (UnknownHostException e) {
                System.out.println("δ֪�������쳣..");
            }
        } catch (SocketException e) {
            System.out.println("�׽��������쳣..");
        }
    }

    // ��Ϣ���Ͱ�ťʱ�����
    public boolean action(Event evt, Object arg) {
        if (evt.target.equals(send)) {
            try {
                // ��ȡ��������
                String content = tf.getText();
                // ������Ϣ
                send_message(content);
                // ��������
                tf.setText(null);
            } catch (Exception ioe) {
                System.out.print(ioe.getMessage());
            }
        }
        return true;
    }

    // ��Ϣ����
    private void send_message(String content) {
        // ��Ϣ��ʽ��(json��ʽ)
        String message = messageFormat(content);
        // ����Ϣ��װ��UDP���ݰ�
        byte[] buf = message.getBytes();
        DatagramPacket packet = new DatagramPacket(buf, buf.length, ip, PORT);

        try {
            // ͨ��UDPЭ�鷢����Ϣ
            msg_send.send(packet);
        } catch (IOException e) {
            System.out.println("IO�쳣..");
        }
    }

    // ��Ϣ��ʽ��
    private String messageFormat(String content) {
        StringBuffer buffer = new StringBuffer();
        buffer.append("{\"groupId\":").append("\"").append(groupID).append(
                "\",");
        buffer.append("\"userName\":\"").append(clientName).append("\",");
        buffer.append("\"text\":\"").append(content).append("\"}");

        return buffer.toString();

    }

    // �ӷ�������ȡ��ǰ������������Ϣ(�ص�..)
    public void pushBackMessage(MessageEntity me) {
        ta.append(me.getUserName() + ":" + me.getText());
        ta.append("\n");

    }
}
