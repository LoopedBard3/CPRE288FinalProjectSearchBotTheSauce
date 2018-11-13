import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Window{

	static GraphicsConfiguration gc;
	static JButton btnFORWARDS;
	static JButton btnBACKWARDS;
	static JButton btnLEFT;
	static JButton btnRIGHT;

	public static void main(String[] args){
		createWindow();	
	}

	private static void createWindow(){
		JFrame frame = new JFrame();
		frame.setTitle("RombaCop");
		frame.setSize(600, 400);

		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent){
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

		return panel;
	}

	private static void createBtns(){
		btnFORWARDS= new JButton("FORWARDS");
		btnBACKWARDS= new JButton("BACKWARDS");
		btnLEFT = new JButton("LEFT");
		btnRIGHT =  new JButton("RIGHT");

		btnFORWARDS.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println("W");
			}
		}); 
	
		btnBACKWARDS.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
			
				System.out.println("S");
			}
		}); 
		
		btnLEFT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println("A");
			}
		}); 
		
		btnRIGHT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println("D");
			}
		}); 
	}
}
