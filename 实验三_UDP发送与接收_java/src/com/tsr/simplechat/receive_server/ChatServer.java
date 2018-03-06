package com.tsr.simplechat.receive_server;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.HashMap;

import com.google.gson.Gson;
import com.tsr.simplechat.bean.MessageEntity;
import com.tsr.simplechat.client.ChatClient;

//���������
public class ChatServer extends Thread {
    // ����ռ�ö˿ں�
    private static final int PORT = 10000;
    // ��Ϣ�����׽��ֶ���
    private static DatagramSocket server = null;
    // �ֵ����(Key��������ID��Value�����������µĿͻ����û�����);
    private static HashMap<String, ArrayList<ChatClient>> groups = new HashMap<String, ArrayList<ChatClient>>();

    // ������
    public ChatServer() {
        try {
            // ��Ϣ�����׽��ֶ���Ĺ����ʼ��
            server = new DatagramSocket(PORT);
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }

    // ע���������µ�¼�û�
    public static void logInGroup(String groupID, ChatClient client) {
        // ͨ��������ID����ȡ�������ҵ����������û�
        ArrayList<ChatClient> clients = groups.get(groupID);
        if (clients == null) {
            clients = new ArrayList<ChatClient>();
        }
        // ���˴ν��������ҵ��û��Ǽ�
        clients.add(client);
        // ������������Ϣ
        groups.put(groupID, clients);
    }

    // ѭ��������Ϣ
    @Override
    public void run() {
        while (true) {
            receiveMessage();
        }
    }

    private void receiveMessage() {
        // UDP���ݰ�
        byte[] buf = new byte[1024];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        while (true) {
            try {
                // �������ݰ�
                server.receive(packet);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            // �������ݰ�����ȡ������Ϣ
            String content = new String(packet.getData(), 0, packet.getLength());

            // ͨ��������������json����
            Gson gson = new Gson();
            MessageEntity me = gson.fromJson(content, MessageEntity.class);

            // ������Ϣ���ݣ�ͨ��������ID����ȡ�������ҵ����������û�
            ArrayList<ChatClient> clients = groups.get(me.getGroupId());

            // �����յ�����Ϣ���ͻظ������ҵĸ����û�
            for (ChatClient client : clients) {
                client.pushBackMessage(me);
            }
        }
    }
}
