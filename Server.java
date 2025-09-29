///////////////////////////////////////////////////////////
import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintStream;
///////////////////////////////////////////////////////////

class Server
{
    public static void main(String[] arg)
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

            // Read and write the DATA Object creation
            BufferedReader bufferedReaderObjTypeData = new BufferedReader(new InputStreamReader(System.in)); // type the data
            BufferedReader bufferedReaderObjRecive = new BufferedReader(new InputStreamReader(socketObj.getInputStream())); // recieve the data
            PrintStream printStreamObjSendData = new PrintStream(socketObj.getOutputStream()); // send the data to client

            // read and write data
            ///////////////////////////////////////
            String readMsg = null, writeMsg = null;
            //////////////////////////////////////////

            while(true)
            {
                // read the msg
                readMsg = bufferedReaderObjRecive.readLine();
                if(readMsg.equalsIgnoreCase("off"))
                {
                    break;
                }

                // display the msg
                System.out.println("client Msg: "+readMsg);

                // type the msg
                System.out.print("\t\tServer Msg: ");
                writeMsg = bufferedReaderObjTypeData.readLine();

                // send the msg
                printStreamObjSendData.println(writeMsg);

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

        System.out.println("Server is now 'off'");
    }
}