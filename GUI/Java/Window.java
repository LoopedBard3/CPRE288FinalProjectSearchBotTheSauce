/**
 * @author Ben Carland, Brandon Bui, Jose Lopez, Parker Bibus
 */
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import javax.swing.*;

/**
 * This class  is the user interface to control The Sauce
 */
public class Window{

	/**
	 * For graphics
	 */
	static GraphicsConfiguration gc;
	/**
	 * Move forwards
	 */
	static JButton btnFORWARDS;
	/**
	 * Move backwards
	 */
	static JButton btnBACKWARDS;
	/**
	 * Move to the left
	 */
	static JButton btnLEFT;
	/**
	 * Move to the right
	 */
	static JButton btnRIGHT;
	/**
	 * Stop moving
	 */
	static JButton btnSTOP;
	/**
	 * Stop accepting commands like scan, music, and direction
	 */
	static JButton btnQUIT;
	/**
	 * Start accepting commands
	 */
	static JButton btnGO;
	/**
	 * Scan surroundings
	 */
	static JButton btnSCAN;
	/**
	 * Play music
	 */
	static JButton btnMUSIC;
	/**
	 * Connect to The Sauce
	 */
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

	/**
	 * Creates a JFrame that has buttons for the user to control
	 */
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

	/**
	 * Creates a JPanel for the first JFrame with buttons to move, scan, and play music
	 */
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

	/**
	 * Creates buttons ot move The Sauce, scan whats in front, and play music
	 */
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
