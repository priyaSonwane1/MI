import java.awt.*;          // Imports AWT components like Frame, Button, TextField, and Label .
import java.awt.event.*;    //  Imports event-handling classes like ActionEvent, ActionListener, and WindowAdapter .

// Cal class extends WindowAdapter (to handle window closing events) also implements ActionListener (to handle button clicks).
class Cal extends WindowAdapter implements ActionListener
{
    public Frame mainFrame ;        // Creates the main window.
    public Button B1,B2,B3,B4 ;     // Represents (ADD, SUB, MUL, DIV) buttons.
    public TextField T1 , T2 ;      // Used for inputting numbers.
    public Label lobj ;             // Displays the result.
    Integer no1 , no2 ;             // Stores user-inputted numbers.

    // Constructor
    public Cal (int Width , int Height , String Title)
    {
        mainFrame = new Frame(Title);       // Creates a frame with a given title.
        mainFrame.setSize(Width,Height);    // Sets the size of the frame.
        mainFrame.addWindowListener(this);  // Adds a window listener so that clicking the close button terminates the program.

        // Creates four buttons for the operations.
        B1 = new Button("ADD");
        B2 = new Button("SUB");
        B3 = new Button("MUL");
        B4 = new Button("DIV");

        // Creates two text fields for user input.
        T1 = new TextField();
        T2 = new TextField();

        // Creates a label to display the result.
        lobj = new Label();

        // setBounds(x, y, width, height); sets the position and size of each component.
        B1.setBounds(10,280,80,40);
        B2.setBounds(100,280,80,40);
        B3.setBounds(190,280,80,40);
        B4.setBounds(290,280,80,40);

        T1.setBounds(70,100,100,40);
        T2.setBounds(220,100,100,40);

        lobj.setBounds(150,170,200,100);

        // Adds all buttons, text fields, and the label to the frame.
        mainFrame.add(B1);
        mainFrame.add(B2);
        mainFrame.add(B3);
        mainFrame.add(B4);

        mainFrame.add(T1);
        mainFrame.add(T2);

        mainFrame.add(lobj);

        // Registers the current class (this) as the event handler for button clicks.
        B1.addActionListener(this);
        B2.addActionListener(this);
        B3.addActionListener(this);
        B4.addActionListener(this);

        mainFrame.setLayout(null);      // Disables automatic layout management.
        mainFrame.setVisible(true);     //  Displays the window.
    }

    // Ensures that clicking the close button properly exits the application.
    public void windowClosing(WindowEvent wobj)
    {
        System.exit(0);
    }

    public void actionPerformed(ActionEvent aobj)
    {
        try
        {
            // Retrieves numbers from T1 and T2 and converts them into integers.
            no1 = Integer.parseInt(T1.getText());
            no2 = Integer.parseInt(T2.getText());

            // Checks which button is clicked and performs the corresponding operation , and  Displays the result in lobj.
            if(aobj.getSource() == B1)
            {
                lobj.setText("Addition is : "+(no1+no2));
            }
            else if(aobj.getSource() == B2)
            {
                lobj.setText("Subtraction is : "+(no1-no2));
            }
            else if(aobj.getSource() == B3)
            {
                lobj.setText("Multiplication is : "+(no1*no2));
            }
            else if(aobj.getSource() == B4)
            {
                lobj.setText("Division is : "+(no1/no2));
            }
        }
        catch(Exception eobj)
        {
            System.out.println(eobj);
        }
    }
}

class Calculator
{
    public static void main(String arg[])
    {
       Cal cobj = new Cal(400,400,"Calculator"); // It creates an instance of Cal, which automatically displays the GUI.
    }
}