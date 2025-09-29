
///////////////////////////////////////////////////////////
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintStream;
///////////////////////////////////////////////////////////

class Clientchat extends Thread
{
    public void run()
    {
        try
        {
            final int iPortNumber = 122;

            // connect to the server
            Socket socketObj = new Socket("localhost",iPortNumber);
            System.out.println("Client is On with port number: "+iPortNumber);

            if(socketObj.isConnected())
            {
                System.out.println("Clinet is connected with Server...");
            }
            else
            {
                System.out.println("!!! Client is unable to connect with server !!!");
            }

            Thread sendThread = new Thread(()->
            {
                try
                {
                    // Read and write the DATA Object creation
                    BufferedReader bufferedReaderObjTypeData = new BufferedReader(new InputStreamReader(System.in)); // type the data
                    PrintStream printStreamObjSendData = new PrintStream(socketObj.getOutputStream()); // send the data to client

                    String writeMsg = null;

                    // wite the msg
                    while((writeMsg = bufferedReaderObjTypeData.readLine()) != null)
                    {
                        // send the msg
                        printStreamObjSendData.println(writeMsg);

                        if(writeMsg.equalsIgnoreCase("off"))
                        {
                            socketObj.close();
                            System.out.println("Client logout !!");
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
                    // Read and write the DATA Object creation
                     BufferedReader bufferedReaderObjRecive = new BufferedReader(new InputStreamReader(socketObj.getInputStream())); // recieve the data

                    String readMsg = null;
                    //////////////////////////////////////////
                    // read the msg
                    while((readMsg = bufferedReaderObjRecive.readLine()) != null)
                    {
                        // display the readed msg
                        if(readMsg.equalsIgnoreCase("off"))
                        {
                            socketObj.close();
                            System.out.println("Server logout");
                            System.out.println("Client is unable to recive the msg now !!");
                            break;
                        }
                        else
                        {
                            System.out.println("\t\t\t\t"+readMsg);
                        } 
                    }
                }
                catch(IOException e4)
                {
                    System.out.println("ERROR: "+e4.getMessage());
                }
            });

            sendThread.start();
            receivesThread.start();
            
            try
            {
                sendThread.join();
                receivesThread.join();
            }
            catch(InterruptedException e5)
            {
                System.out.println("ERROR: "+e5.getMessage());
            }

            // close the client
            if(socketObj.isClosed() == true)
            {
                System.out.println("Client is Disconnected with server");
            }
            
        }
        catch(UnknownHostException e1)
        {
            System.out.println("ERROR: "+e1.getMessage());
        }
        catch(IOException e2)
        {
            System.out.println("ERROR: "+e2.getMessage());
        }
        System.out.println("Thank you for using application");
    }
}

class Client
{
    public static void main(String[] arg)
    {
        Clientchat clinet1 = new Clientchat();
        Thread client1Thread = new Thread(clinet1);

        try
        {
            client1Thread.start();
            client1Thread.join();
        }
        catch(InterruptedException e6)
        {
            System.out.println("ERROR: "+e6.getMessage());
        }
    }
}