// Input 4  4   
/*

    *   
    *   *   
    *   *   *   
    *   *   *   *
    
*/

import java.util.*;

class Pattern
{
    public void Display(int iRow, int iCol)
    {
        int i = 0, j = 0;

        if(iRow != iCol)
        {
            System.out.println("Invalid input");
            return;
        }

        for(i = 1 ; i <= iRow; i++)
        {
            for(j = 1;j <= iCol ; j++)
            {
                if((i + j) > iRow)
                {
                    System.out.print("*\t");
                }
                else
                {
                    System.out.print("o\t");
                }
            }
            System.out.println();
        }
    }
}

class program112
{
    public static void main(String A[])
    {
        Scanner sobj = new Scanner(System.in);
        int iValue1 = 0, iValue2 = 0;

        System.out.println("Enter number of rows : ");
        iValue1 = sobj.nextInt();

        System.out.println("Enter number of columns : ");
        iValue2 = sobj.nextInt();

        Pattern pobj = new Pattern();

        pobj.Display(iValue1, iValue2);
    }
}