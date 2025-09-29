import java.io.*;
import java.util.*;

class FPU {
    static final int HEADER_SIZE = 100;

    public static void main(String[] args) {
        Scanner sobj = new Scanner(System.in);
        System.out.println("---------------------------------------------------------------------");
        System.out.println("--------------  Packer Unpacker CUI Module ----------------");
        System.out.println("---------------------------------------------------------------------");

        System.out.println("Choose operation:");
        System.out.println("1. Pack files");
        System.out.println("2. Unpack files");
        System.out.print("Enter choice (1/2): ");
        int choice = sobj.nextInt();
        sobj.nextLine(); // consume newline

        switch (choice) {
            case 1:
                packFiles(sobj);
                break;
            case 2:
                unpackFiles(sobj);
                break;
            default:
                System.out.println("Invalid choice. Exiting.");
        }

        System.out.println("---------------------------------------------------------------------");
        System.out.println("--------- Thank you for using Packer-Unpacker ------------");
        System.out.println("---------------------------------------------------------------------");
    }

    public static void packFiles(Scanner sobj) {
        try {
            System.out.println("Enter the name of directory to pack:");
            String dirName = sobj.nextLine();

            System.out.println("Enter the name of packed file to create:");
            String packName = sobj.nextLine();

            File dir = new File(dirName);
            if (!dir.exists() || !dir.isDirectory()) {
                System.out.println("Invalid directory.");
                return;
            }

            File[] files = dir.listFiles((d, name) -> name.endsWith(".txt"));
            if (files == null || files.length == 0) {
                System.out.println("No .txt files found in the directory.");
                return;
            }

            FileOutputStream fout = new FileOutputStream(packName);
            byte[] buffer = new byte[1024];
            int totalPacked = 0;

            for (File file : files) {
                String header = file.getName() + " " + file.length();
                header = String.format("%-100s", header); // pad to 100 chars

                fout.write(header.getBytes());

                try (FileInputStream fin = new FileInputStream(file)) {
                    int len;
                    while ((len = fin.read(buffer)) != -1) {
                        fout.write(buffer, 0, len);
                    }
                }

                totalPacked++;
            }

            fout.close();
            System.out.println("Total files packed: " + totalPacked);

        } catch (Exception e) {
            System.out.println("Packing error: " + e.getMessage());
        }
    }

    public static void unpackFiles(Scanner sobj) {
        try {
            System.out.println("Enter the packed file to unpack:");
            String packName = sobj.nextLine();

            File packedFile = new File(packName);
            if (!packedFile.exists()) {
                System.out.println("Packed file does not exist.");
                return;
            }

            FileInputStream fin = new FileInputStream(packedFile);
            byte[] headerBytes = new byte[HEADER_SIZE];
            byte[] buffer = new byte[1024];
            int totalUnpacked = 0;

            while (fin.read(headerBytes) != -1) {
                String header = new String(headerBytes).trim();
                String[] parts = header.split(" ");
                String fileName = parts[0];
                int fileSize = Integer.parseInt(parts[1]);

                FileOutputStream fout = new FileOutputStream("unpacked_" + fileName);
                int bytesRead = 0;

                while (fileSize > 0) {
                    int len = fin.read(buffer, 0, Math.min(buffer.length, fileSize));
                    if (len == -1) break;
                    fout.write(buffer, 0, len);
                    fileSize -= len;
                }

                fout.close();
                totalUnpacked++;
            }

            fin.close();
            System.out.println("Total files unpacked: " + totalUnpacked);

        } catch (Exception e) {
            System.out.println("Unpacking error: " + e.getMessage());
        }
    }
}
