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
	static JFrame frame;
	static JFrame frame2;
	static SocketController client;

	public static void main(String[] args) throws IOException {
		client = new SocketController("192.168.1.1", 288); //Starts the controller without being setup in a different class
		createWindow();	
		createWindow2();
//		while(true) {
//			if(client.hasData()) {
//				System.out.println(client.getData());
//			}
//		}
	}

	private static void createWindow(){
		frame = new JFrame();
		frame.setTitle("RombaCop");
		frame.setSize(600, 400);

		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent){
				try {
					client.closeConnection();
				} catch (IOException e) {
					e.printStackTrace();
				}
				System.exit(0);
			}
		});
		frame.add(createButtonPanel());

		frame.setVisible(true);
	}
	
	private static void createWindow2(){
		frame2 = new JFrame();
		frame2.setTitle("RombaCopHeat");
		frame2.setSize(600, 400);

		frame2.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent){
				try {
					client.closeConnection();
				} catch (IOException e) {
					e.printStackTrace();
				}
				System.exit(0);
			}
		});
		frame2.add(createHeatPanel());

		frame2.setVisible(true);
	}

	private static JPanel createButtonPanel(){
		JPanel panel = new JPanel();
		panel.setSize(500, 300);
		panel.setLayout(new GridLayout (3,3));
		
		createBtns();

		panel.add(btnSTOP);
		panel.add(btnFORWARDS);
		panel.add(btnSCAN);
		panel.add(btnLEFT);
		panel.add(btnBACKWARDS);
		panel.add(btnRIGHT);
		panel.add(btnGO);
		panel.add(btnQUIT);
		panel.add(btnMUSIC);

		return panel;
	}
	
	private static JPanel createHeatPanel() {
		JPanel panel = new JPanel() {
				protected void paintComponent (Graphics g) {
					super.paintComponent(g);
					for (int i =0; i<= 500; i += 2) {
						switch(i%3) {
						case 0:
							g.setColor(Color.RED);
							break;
						case 1:
							g.setColor(Color.WHITE);
							break;
						case 2:
							g.setColor(Color.GREEN);
							break;
						}
						g.drawLine(i,  0, i, 300);
					}
				};
		};
		
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
					f.printStackTrace();
				}
			}
		}); 
	
		btnBACKWARDS.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
			
				try {
					client.sendString("S");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		}); 
		
		btnLEFT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("A");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		}); 
		
		btnRIGHT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("D");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});
		
		btnSTOP.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					frame.setVisible(false);
					frame2.setVisible(true);
					client.sendString("X");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});
		
		btnQUIT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("Q");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});
		
		btnGO.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("G");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});
		
		btnSCAN.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("L");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});
		
		btnMUSIC.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					client.sendString("P");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});
	}
}
