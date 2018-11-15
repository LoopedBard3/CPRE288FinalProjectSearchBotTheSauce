import java.net.*; 
import java.io.*; 

/**
 * A class that allows us to communicate with the robot over wifi
 */
public class SocketController {
    private Socket socket            = null; 
    private BufferedReader  commandInput   = null;
    private BufferedReader  botDataInput = null;
    private DataOutputStream out     = null; 
    
    /**
     * Constructor for the socket controller
     * @param address the ip address to connect to
     * @param port the port to connect to
     */
    public SocketController(String address, int port) 
    { 
        // establish a connection 
        try
        { 
            socket = new Socket(address, port); 
            System.out.println("Connected"); //Print connected once we are connected
  
            // takes input from terminal 
            commandInput  = new BufferedReader(new InputStreamReader(System.in)); //Stream of characters coming into the terminal
            
            botDataInput = new BufferedReader(new InputStreamReader(socket.getInputStream())); //The stream of characters and data coming in from the robot
  
            // sends output to the socket 
            out    = new DataOutputStream(socket.getOutputStream());  //Sends the streams to the robot
        } 
        catch(UnknownHostException u) 
        { 
            System.out.println(u); 
        } 
        catch(IOException i) 
        { 
            System.out.println(i); 
        } 
  
        // string to read message from input 
        char line = '\0'; 
  
        // keep reading until "Over" is input 
        while (line != ('Q')) //While we haven't gotten Q from the line, keep getting and sending data
        { 
            try
            { 
            	if(commandInput.ready()) {  //If we have a command reading to be read from the command input, read it and send it to the robot
            		line = (char) commandInput.read(); 
            		out.writeChar(line);
            	}
            	if(botDataInput.ready()) {  //If we have data ready to be read from the bot, send it to the terminal
            		System.out.println(botDataInput.readLine());
            	}
            } 
            catch(IOException i) 
            { 
                System.out.println(i); 
            } 
        } 
  
        // close the connection 
        try
        { 
        	botDataInput.close();
        	commandInput.close(); 
            out.close(); 
            socket.close(); 
        } 
        catch(IOException i) 
        { 
            System.out.println(i); 
        } 
    } 
  
    public static void main(String args[]) 
    { 
        SocketController client = new SocketController("192.168.1.1", 288); //Starts the controller without being setup in a different class
    } 
}
