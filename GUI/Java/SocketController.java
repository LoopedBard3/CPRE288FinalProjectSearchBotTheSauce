import java.net.*; 
import java.io.*; 

/**
 * A class that allows us to communicate with the robot over wifi
 */
public class SocketController {
    private Socket socket            = null; 
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
    } 
    // Determine if the bot has data to transmit
    public boolean hasData() throws IOException {
    	return botDataInput.ready();
    }
    
    // Get the data that the bot has to transmit
    public String getData() throws IOException {
    	if(!hasData()) {
    		return "";
    	}
    	return botDataInput.readLine();
    }
    
    // Send a character to the bot
    public void sendString(String cmd) throws IOException {
		out.writeChars(cmd);
    }
    
    // Closes connections with the bot
    public void closeConnection() throws IOException {
    	botDataInput.close(); 
        out.close(); 
        socket.close(); 
    }
    
}
