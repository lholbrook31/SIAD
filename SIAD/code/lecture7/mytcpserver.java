//Logan Holbrook

import java.net.ServerSocket;
import java.net.Socket;
import java.io.*;
import java.util.Date;

public class mytcpserver{
	public static void main(String[] args) throws IOException{
		System.out.println("mytcpserver");
		int portNumber = 8000;

		//Create Server Socket
		ServerSocket serverSocket = new ServerSocket(portNumber);
		System.out.println("mytcpserver is running at port " + serverSocket.getLocalPort());
		//Socket clientSocket = serverSocket.accept();
		//System.out.println("BOOM-SHAKA-LAKA");

		while(true){
			Socket clientSocket = serverSocket.accept();
			new tcpserverthread(clientSocket).start();
			System.out.println("BOOM-SHAKA-LAKA");
		}
/*
		//Get IP Address
		System.out.println("IP Address is: " + clientSocket.getInetAddress().getHostAddress());

		//Receive Data
		BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		String inputLine = in.readLine();
		String receivedData = inputLine;
		System.out.println(receivedData);
		while(!inputLine.isEmpty()){
			inputLine = in.readLine();
			receivedData += inputLine + "\n";
		}
		System.out.println("Received from client: " + receivedData + "\n");

		//Echo Back to Client
		String response = "mytcpserver\n" + (new Date()).toString() + "\n" + receivedData;
		clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
*/
	}
}

class tcpserverthread extends Thread{
	private Socket clientSocket = null;
	
	tcpserverthread(Socket clientSocket){
		super("tcpserverthread");
		this.clientSocket = clientSocket;
	}

	public void run(){
		try{
		//handling data communication here
		System.out.println("Ip Address is: " + clientSocket.getInetAddress().getHostAddress());

		BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		String inputLine = in.readLine();
		String receivedData = inputLine;
		System.out.println(receivedData);
		while(!inputLine.isEmpty()){
			inputLine = in.readLine();
			receivedData += inputLine + "\n";
		}

		String response = "mytcpserver\n" + (new Date()).toString() + "\n" + receivedData;
		clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
		clientSocket.close();
		}catch(IOException e){}
	}
}
