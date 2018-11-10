import java.net.*; 
import java.io.*; 

public class SocketController {
    private Socket socket            = null; 
    private BufferedReader  commandInput   = null;
    private BufferedReader  botDataInput = null;
    private DataOutputStream out     = null; 
    
    public SocketController(String address, int port) 
    { 
        // establish a connection 
        try
        { 
            socket = new Socket(address, port); 
            System.out.println("Connected"); 
  
            // takes input from terminal 
            commandInput  = new BufferedReader(new InputStreamReader(System.in)); 
            
            botDataInput = new BufferedReader(new InputStreamReader(socket.getInputStream()));
  
            // sends output to the socket 
            out    = new DataOutputStream(socket.getOutputStream()); 
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
        while (line != ('Q')) 
        { 
            try
            { 
            	if(commandInput.ready()) {
            		line = (char) commandInput.read(); 
            		out.writeChar(line);
            	}
            	if(botDataInput.ready()) {
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
        SocketController client = new SocketController("192.168.1.1", 288); 
    } 
}
