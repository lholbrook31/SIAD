//Logan Holbrook

import java.io.*;
import java.net.*;

public class mytcpclient{
	public static void main(String[] args) throws IOException{
		if(args.length != 2){
			System.err.println("Usage: java mytcpclient <host name><port number>");
			System.exit(1);
		}

		String hostName = args[0];
		int portNumber = Integer.parseInt(args[1]);
		
		//Create Socket
		Socket socket = new Socket(hostName, portNumber);
		System.out.println("Running on port: " + portNumber + " at host: " + hostName);

		//Output stream to send data
		PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

		//buffer reader to read from user input
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));

		new tcpclientthread(socket).start();
		String userInput;

		//enter username
		System.out.print("Please enter a username: ");
		String userName = stdin.readLine();
		System.out.println();
		System.out.println(userName + " has joined");

		//user input
		while((userInput = stdin.readLine()) != null){
			out.println(userName + ": " + userInput);
			if(userInput.equals("exit")){
				System.out.println(userName + " has exited.");
				socket.close();
				System.exit(0);
			}
		}		
	}
}

class tcpclientthread extends Thread{
	private Socket clientSocket = null;
	
	tcpclientthread(Socket clientSocket){
		super("tcpclientthread");
		this.clientSocket = clientSocket;
	}
	public void run(){
		try{
			//receive data
			BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			
			//read from user input
			while(true){
				String inputLine = in.readLine();
				while((inputLine != null) && !inputLine.isEmpty()){
					System.out.println(inputLine);
					inputLine = in.readLine();
				}
				
			}

		}catch(IOException e){
			e.printStackTrace();
		}
	}
}
