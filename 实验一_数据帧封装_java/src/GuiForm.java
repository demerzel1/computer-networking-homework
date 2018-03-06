import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.util.Objects;

public class GuiForm {
    private JTabbedPane tabbedPane1;
    private JPanel panel1;
    private JRadioButton DataRadioButton;
    private JRadioButton FileRadioButton;
    private JButton DoButton;
    private JButton ExitButton;
    private JTextField SourceIPtextField;
    private JTextField EndIPtextField;
    private JTextField DatatextField;
    private JTextField FileTextField;
    private JButton ViewButton;
    private JTextArea Ans_textArea;
    private JComboBox CRCcomboBox;
    private JButton CheckButton;
    private JTextArea CRCtextArea;

    private String str_ans;

    public String Data_GetIp(){
        String s;
        String srcIP=SourceIPtextField.getText();
        StringBuilder sBuilder = new StringBuilder();

        String endIP=EndIPtextField.getText();
        for(char c:endIP.toCharArray()){
            sBuilder.append(c);
        }

        for(char c:srcIP.toCharArray()){
            sBuilder.append(c);
        }
        s = sBuilder.toString();
        return s;
    }

    public String Data_GetHead(){
        StringBuilder sBuilder = new StringBuilder();
        for(int i = 0; i<7; ++i)
            sBuilder.append("aa");
        String s = sBuilder.toString();
        s+="ab";
        return s;
    }

    public String change_to_hex(int x){
        String s1=Integer.toHexString(x & 0xFF);
        if(s1.length()<2){
            s1="0"+s1;
        }
        return s1;
    }

    public String change_to_hex(char x){
        String s1=Integer.toHexString((int)(x & 0xFF));
        if(s1.length()<2){
            s1="0"+s1;
        }
        return s1;
    }

    public String change_to_hex(byte x){
        String s1=Integer.toHexString((int)(x & 0xFF));
        if(s1.length()<2){
            s1="0"+s1;
        }
        return s1;
    }


    public GuiForm() {
        DataRadioButton.setSelected(true);
        CRCtextArea.setEnabled(false);
        FileTextField.setEnabled(false);
        ViewButton.setEnabled(false);
        Ans_textArea.setLineWrap(true);
        Ans_textArea.setWrapStyleWord(true);
        Ans_textArea.setEnabled(false);

        DataRadioButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                if(FileRadioButton.isSelected())
                    FileRadioButton.setSelected(false);
                DatatextField.setEnabled(true);
                ViewButton.setEnabled(false);
            }
        });
        FileRadioButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                if(DataRadioButton.isSelected())
                    DataRadioButton.setSelected(false);
                DatatextField.setEnabled(false);
                ViewButton.setEnabled(true);

            }
        });
        ViewButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {

                //读入文件
                JFileChooser jfc = new JFileChooser();
                jfc.setFileSelectionMode(JFileChooser.FILES_ONLY);
                jfc.showDialog(new JLabel(),"选择");
                File file = jfc.getSelectedFile();
                if(file != null){
                    FileTextField.setText(file.getAbsolutePath());
                }
            }
        });
        CheckButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                String t1=EndIPtextField.getText();
                String t2=SourceIPtextField.getText();
                if(t1.length()!=12||t2.length()!=12){
                    CRCtextArea.setText("请输入正确的地址（12位16进制数）");
                    return;
                }
                String str_IP=Data_GetIp();
                String s="";

                //文件读入
                if(FileRadioButton.isSelected()){
                    if(FileTextField.getText().isEmpty()) {
                        return;
                    }
                    File file = new File(FileTextField.getText());
                    try {
                        FileInputStream FileIn = new FileInputStream(file);
                        byte[] buff=new byte[(int)file.length()];
                        FileIn.read(buff);
                        StringBuilder sBuilder = new StringBuilder(s);
                        for(byte ch:buff){
                            System.out.println(change_to_hex(ch));
                            sBuilder.append(change_to_hex(ch));
                        }
                        s = sBuilder.toString();
                        System.out.println(s);
                    } catch (java.io.IOException e1) {
                        e1.printStackTrace();
                    }
                }

                //数据输入
                else{
                    if(DatatextField.getText().isEmpty()){
                        return;
                    }
                    String s1=DatatextField.getText();
                    StringBuilder sBuilder = new StringBuilder(s);
                    for(char ch: s1.toCharArray()){
                        sBuilder.append(change_to_hex(ch));
                    }
                    s = sBuilder.toString();
                    System.out.println(s);
                }

                //计算数据长度字段
                int len=s.length()/2;
                int len_H=len/256;
                int len_L=len%256;
                String str_len="";
                str_len+=change_to_hex(len_H);
                str_len+=change_to_hex(len_L);
                System.out.println(str_len);
                System.out.println("len");
                System.out.println(len);
                //不足46字节 补0
                if(len<46){
                    StringBuilder sBuilder = new StringBuilder(s);
                    for(int i = 46-len; i>0; --i){
                        sBuilder.append("00");
                    }
                    s = sBuilder.toString();
                }
                //IP字段+数据长度字段+数据字段
                s=str_IP+str_len+s;

                //CRC-8 校验
                if(Objects.equals(CRCcomboBox.getSelectedItem().toString(), "CRC-8")){
                    s+="00";
                    char crc=0;
                    int s_len=s.length();
                    for(int i=0;i<s_len;i+=2){
//                        System.out.println("111");
                        char a=s.charAt(i),b=s.charAt(i+1);
                        char c=(char)((a<<4) | b);
                        for(char ch=(char)(0x80);ch>0;ch>>=1){
//                            System.out.println(c);
                            if((crc & (char)0x80)!=0){
                                crc<<=1;
                                if((c&ch)!=0)
                                    crc^=0x01;
                                crc^=0x07;
                            }else{
                                crc<<=1;
                                if((c&ch)!=0)
                                    crc^=0x01;
                            }
                        }
                    }
                    s=s.substring(0,s.length()-2);
                    String str_crc=change_to_hex(crc);
                    System.out.println(change_to_hex(crc));
                    s+=str_crc;
                    String he=Data_GetHead();
                    str_ans=he+s;
                    CRCtextArea.setText(str_crc);
                }else{
                    System.out.println();
                }
            }
        });

        DoButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                CheckButton.doClick();
                StringBuilder t= new StringBuilder();
                int len=str_ans.length();
                for(int i=0;i<len;i+=2){
                    String tt=String.valueOf(str_ans.charAt(i))+String.valueOf(str_ans.charAt(i+1));
                    if(i!=len-2)
                        t.append(tt).append(" ");
                    else
                        t.append(tt);
                }
                String tt=t.toString();
                Ans_textArea.setText(tt);
            }
        });
        ExitButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
    }


    public static void main(String[] args) {
        try {
            UIManager .setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
        } catch (Exception e) {
        }
        JFrame frame = new JFrame("帧封装");
        frame.setContentPane(new GuiForm().panel1);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(650,500);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        frame.setResizable(false);
    }
}
