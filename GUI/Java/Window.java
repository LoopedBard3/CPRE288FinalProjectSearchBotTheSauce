import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.ArrayList;

import javax.swing.*;

public class Window {

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
	static JFrame frame3;
	static Graphics2D heatGraphics;
	static SocketController client;
	static KeyboardController keyboardController;
	static JTextField txt;

	public static void main(String[] args) throws IOException {

		String clientData;
		String[] clientDataArray;
		createWindow();
		//createHeatWindow();
		createInfoWindow();

		try {
			client = new SocketController("192.168.1.1", 288); // Starts the controller without being setup in a
																// different class
		} catch (Exception e) {
			client = null;
		}

		keyboardController = new KeyboardController(client); //Might need to figure out the order to add at.
		frame.addKeyListener(keyboardController);
		frame3.addKeyListener(keyboardController);
		JLabel label1;
		label1 = new JLabel("", SwingConstants.CENTER);
		label1.setFont(new Font(label1.getName(), Font.PLAIN, 36));
		frame3.add(label1);
		ArrayList<Integer[]> intArr = new ArrayList();
		while (true && client != null) {
			if (client.hasData()) {
				clientData = client.getData();
				clientDataArray = clientData.split(" ");
				if (clientDataArray.length == 3) {
					intArr.clear();
					if(frame2 != null) frame2.dispose();
					while(clientDataArray.length == 3) {
						Integer[] temp = {Integer.parseInt(clientDataArray[0]), Integer.parseInt(clientDataArray[1])};
						intArr.add(temp);
						while(!client.hasData()) {}
						clientData = client.getData();
						clientDataArray = clientData.split(" ");
						System.out.println(clientData);
					}
					createHeatWindow(intArr);
					System.out.println("Adding to panel!");
				}
				label1.setText(clientData);
				System.out.println(clientData);
			}
		}
	}


	private static void createWindow() {
		frame = new JFrame();
		frame.setTitle("RombaCop");
		frame.setSize(600, 400);

		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent) {
				if (client != null) {
					try {
						client.closeConnection();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
				System.exit(0);
			}
		});
		frame.add(createButtonPanel());

		frame.setVisible(true);
	}

	private static void createHeatWindow(ArrayList<Integer[]> data) {
		frame2 = new JFrame();
		frame2.setTitle("RombaCopHeat");
		frame2.setSize(1000, 400);

		frame2.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent) {
				frame2.dispose();
			}
		});
		JPanel heatPanel = createHeatPanel(data);
		frame2.add(heatPanel);
		frame2.addKeyListener(keyboardController);

		frame2.setVisible(true);
	}

	private static void createInfoWindow() {
		frame3 = new JFrame();
		frame3.setTitle("RombaCopInfo");
		frame3.setSize(600, 400);

		frame3.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent) {
				if (client != null) {
					try {
						client.closeConnection();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
				System.exit(0);
			}

		});
		
		frame3.setVisible(true);
	}

	private static JPanel createButtonPanel() {
		JPanel panel = new JPanel();
		panel.setSize(500, 300);
		panel.setLayout(new GridLayout(3, 3));

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

	private static JPanel createHeatPanel(ArrayList<Integer[]> data) {
		if(data != null) {
		JPanel panel = new JPanel() {
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				heatGraphics = (Graphics2D) g;

				for (int i = 0; i < data.size(); i++) {
					heatGraphics.setColor(Color.getHSBColor(map(data.get(i)[1].floatValue(), 0f, 150f, 0f, 0.75f), 1f, 1f));
					heatGraphics.setStroke(new BasicStroke(8f));
					heatGraphics.drawLine(720 - data.get(i)[0].intValue()*4, 0, 720 - data.get(i)[0].intValue()*4, 1000);
				}
			};
		};
		return panel;
	}
		return new JPanel();
	}

	private static JPanel createInfoPanel() {
		JPanel panel = new JPanel();

		return panel;
	}

	private static float map(float x, float in_min, float in_max, float out_min, float out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	private static void createBtns() {
		btnFORWARDS = new JButton("FORWARDS");
		btnBACKWARDS = new JButton("BACKWARDS");
		btnLEFT = new JButton("LEFT");
		btnRIGHT = new JButton("RIGHT");
		btnSTOP = new JButton("STOP");
		btnQUIT = new JButton("QUIT");
		btnGO = new JButton("GO");
		btnSCAN = new JButton("SCAN");
		btnMUSIC = new JButton("MUSIC");

		btnFORWARDS.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					client.sendString("W");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnBACKWARDS.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				try {
					client.sendString("S");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnLEFT.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					client.sendString("A");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnRIGHT.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					client.sendString("D");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnSTOP.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
//					frame2.setVisible(true);
					client.sendString("X");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnQUIT.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
//					frame.setVisible(false);
					client.sendString("Q");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnGO.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					client.sendString("G");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnSCAN.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					client.sendString("L");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});

		btnMUSIC.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					client.sendString("P");
				} catch (IOException f) {
					f.printStackTrace();
				}
			}
		});
	}
}
