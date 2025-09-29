package MarvellousPackerUnpacker;

import java.util.*;
import java.io.*;

public class MarvellousPacker
{
    private String PackName;
    private String DirName;

    public MarvellousPacker(String A, String B)
    {
        this.PackName = A;
        this.DirName = B;
    }

    public void PackingActivity()
    {
        try
        {
            System.out.println("--------------------------------------------------------");
            System.out.println("----------- Marvellous Packer Unpacker -----------------");
            System.out.println("--------------------------------------------------------");
            System.out.println("------------------ Packing Activity --------------------");       
            System.out.println("--------------------------------------------------------");

            int i = 0, j = 0, iRet = 0, iCountFile = 0;

            File fobj = new File(DirName);

            // Check the existance of Directory
            if((fobj.exists()) && (fobj.isDirectory()))
            {
                System.out.println(DirName + " is succesfully opened");

                File PackObj = new File(PackName);

                // Create a packed file
                boolean bRet = PackObj.createNewFile();

                if(bRet == false)
                {
                    System.out.println("Unable to create pack file");
                    return;
                }

                System.out.println("Packed file gets succesfully created with name : "+PackName);
            
                // Retive all files from directory
                File Arr[] = fobj.listFiles();

                // Packed file object
                FileOutputStream foobj = new FileOutputStream(PackObj);
                
                // Buffer for read and write activity
                byte Buffer[] = new byte[1024];

                String Header = null;

                // Directory traversal
                for(i = 0; i < Arr.length; i++)
                {
                    Header = Arr[i].getName() + " " + Arr[i].length();
                
                    // Loop to form 100 bytes header
                    for(j = Header.length(); j < 100; j++)
                    {
                        Header = Header + " ";
                    }
                    
                    // Write header into pacekd file
                    foobj.write(Header.getBytes());

                    // Open file from directoy for reading
                    FileInputStream fiobj = new FileInputStream(Arr[i]);

                    // Write contents of file into packed file
                    while((iRet = fiobj.read(Buffer)) != -1)
                    {
                        foobj.write(Buffer,0,iRet);
                        
                        System.out.println("File name Scanned : "+Arr[i].getName());
                        System.out.println("File size read is : "+iRet);
                    }

                    fiobj.close();
                    iCountFile++;
                }   

                System.out.println("Packing activity done");
                
                System.out.println("--------------------------------------------------------");
                System.out.println("------------------ Statistical Report ------------------");
                System.out.println("--------------------------------------------------------");
                
                // To be add
                System.out.println("Total files Packed : "+iCountFile);

                System.out.println("--------------------------------------------------------");
                System.out.println("--------- Thank you for using our application ----------");
                System.out.println("--------------------------------------------------------");
            }
            else
            {
                System.out.println("There is no such directory");
            }
        } // End of try
        catch(Exception eobj)
        {}
    } // End of PackingActivity function
} // End of MarvellousPacker class
