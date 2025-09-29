///////////////////////////////////////////////////////////
import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintStream;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
///////////////////////////////////////////////////////////

class ServerChat extends Thread
{
    public void run()
    {
        try
        {
            //////////////////////////////
            final int iPortNumber = 122 ;
            //////////////////////////////

            // start the server.
            ServerSocket serverSocketObj = new ServerSocket(iPortNumber);

            System.out.println("Server gets Started... with port number "+iPortNumber);

            // accept the clinet connection
            Socket socketObj = serverSocketObj.accept();

            if(socketObj.isConnected())
            {
                System.out.println("Server is connected with the client: ");
            }
            else
            {
                System.out.println("!! Server is unable to connect with the client !!");
            }

            Thread sendThread = new Thread(()->
            {
                try
                {
                    // write DATA Object creation
                    BufferedReader bufferedReaderObjTypeData = new BufferedReader(new InputStreamReader(System.in)); // type the data
                    PrintStream printStreamObjSendData = new PrintStream(socketObj.getOutputStream()); // send the data to client

                    String writeMsg = null;

                    while((writeMsg = bufferedReaderObjTypeData.readLine()) != null)
                    {                        
                        // send the msg
                        printStreamObjSendData.println(writeMsg);

                        if(writeMsg.equalsIgnoreCase("off"))
                        {
                            serverSocketObj.close();
                            System.out.println("Server is off to send the msg now !!");
                            break;
                        }
                    }
                }
                catch(IOException e3)
                {
                    System.out.println("ERROR: "+e3.getMessage());
                }
            });

            Thread receivesThread = new Thread(()->
            {  
                try
                {
                    // Read DATA Object creation
                    BufferedReader bufferedReaderObjRecive = new BufferedReader(new InputStreamReader(socketObj.getInputStream())); // recieve the data

                    String readMsg = null;

                    // read the msg
                    while((readMsg = bufferedReaderObjRecive.readLine()) != null)
                    {             
                        if(readMsg.equalsIgnoreCase("off"))
                        {
                            serverSocketObj.close();
                            System.out.println("client has logout from the chat !!");
                            break;
                        }
                        else
                        {
                            // display the msg
                            System.out.println("\t\t\t\t"+readMsg);
                        }      
                    }
                }
                catch(IOException e2)
                {
                    System.out.println("ERROR: "+e2.getMessage());
                }
            });

            receivesThread.start();
            sendThread.start();
            
            try
            {
                receivesThread.join();
                sendThread.join();
            }
            catch(InterruptedException e4)
            {
                System.out.println("ERROR: "+e4.getMessage());
            }

            // close the server
            if(serverSocketObj.isClosed())
            {
                System.out.println("Server is Disconnected with client");
            }
        }
        catch(IOException e1)
        {
            System.out.println("ERROR: "+e1.getMessage());
        }
        System.out.println("Thank you for using application");
    }
}

class Server
{
    public static void main(String[] arg)
    {
        ServerChat server1 = new ServerChat();
        Thread serverThread = new Thread(server1);  

        try
        {
            serverThread.start();
            serverThread.join();
        }
        catch(InterruptedException e5)
        {
            System.out.println("ERROR: "+e5.getMessage());
        }
    }
}