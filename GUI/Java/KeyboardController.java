/**
 * @author Ben Carland, Brandon Bui, Jose Lopez, Parker Bibus
 */

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.IOException;

/**
 * Handles the keyboard input from the user
 */
public class KeyboardController implements KeyListener {

	/**
	 * Connection to client
	 */
    SocketController socket;

	/**
	 * Controller for keyboard
	 */
    KeyboardController(SocketController Sock){
        super();
        socket = Sock;
    }

	/**
	 * Overrides parent methods to do nothing
	 */
    @Override
    public void keyTyped(KeyEvent e) {
        //Do nothing
    }

	/**
	 * Overrides parent methods to do nothing
	 */
    @Override
    public void keyPressed(KeyEvent e) {
        //Do nothing
    }

	/**
	 * Move, scan, or play music depending on what key is pressed
	 */
    @Override
    public void keyReleased(KeyEvent e) {
        char keyInput = e.getKeyChar();
        switch(keyInput){
            case 'w':   //Forward
                try {
                    socket.sendString("W");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 's':   //Backward
                try {
                    socket.sendString("S");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 'a':   //Turn Left
                try {
                    socket.sendString("A");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 'd':   //Turn Right
                try {
                    socket.sendString("D");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 'q':   //Stop Button
                try {
                    socket.sendString("X");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 'x':   //Quit Button
                try {
                    socket.sendString("Q");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 'e':   //Scan Button
                try {
                    socket.sendString("L");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 'z':   //Go Button
                try {
                    socket.sendString("G");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;

            case 'c':   //Music Button
                try {
                    socket.sendString("P");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                break;
        }
    }
}
