import java.awt.*;
import java.awt.event.*;
import java.io.IOException;

import javax.swing.*;

public class Window{

	static GraphicsConfiguration gc;
	static JButton btnFORWARDS;
	static JButton btnBACKWARDS;
	static JButton btnLEFT;
	static JButton btnRIGHT;
	static JButton btnSTOP;
	static JButton btnQUIT;
	static JButton btnGO;
	static JButton btnSCAN;
	static JButton btnMUSIC;
	static SocketController client;

	public static void main(String[] args) throws IOException {
		client = new SocketController("192.168.1.1", 288); //Starts the controller without being setup in a different class
		createWindow();	
		while(true) {
			if(client.hasData()) {
				System.out.println(client.getData());
			}
		}
	}

	private static void createWindow(){
		JFrame frame = new JFrame();
		frame.setTitle("RombaCop");
		frame.setSize(600, 400);

		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent){
				try {
					client.closeConnection();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.exit(0);
			}
		});
		frame.add(createPanel());

		frame.setVisible(true);
	}

	private static JPanel createPanel(){
		JPanel panel = new JPanel();
		panel.setBackground(Color.darkGray);
		panel.setSize(500, 300);
		panel.setLayout(new FlowLayout());

		createBtns();

		panel.add(btnFORWARDS);
		panel.add(btnBACKWARDS);
		panel.add(btnLEFT);
		panel.add(btnRIGHT);
		panel.add(btnSTOP);
		panel.add(btnQUIT);
		panel.add(btnGO);
		panel.add(btnSCAN);
		panel.add(btnMUSIC);

		return panel;
	}

	private static void createBtns(){
		btnFORWARDS= new JButton("FORWARDS");
		btnBACKWARDS= new JButton("BACKWARDS");
		btnLEFT = new JButton("LEFT");
		btnRIGHT =  new JButton("RIGHT");
		btnSTOP =  new JButton("STOP");
		btnQUIT = new JButton("QUIT");
		btnGO= new JButton("GO");
		btnSCAN = new JButton("SCAN");
		btnMUSIC = new JButton("MUSIC");
		
		btnFORWARDS.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("W");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		}); 
	
		btnBACKWARDS.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
			
				try {
					client.sendString("S");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		}); 
		
		btnLEFT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("A");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		}); 
		
		btnRIGHT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("D");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		});
		
		btnSTOP.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("X");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		});
		
		btnQUIT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("Q");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		});
		
		btnGO.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("G");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		});
		
		btnSCAN.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("L");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		});
		
		btnMUSIC.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("P");
				} catch (IOException f) {
					// TODO Auto-generated catch block
					f.printStackTrace();
				}
			}
		});
	}
}
