// Input 4  4   
/*

    *   *   *   *
    *   o   o   *
    *   o   o   *
    *   *   *   *
    
*/

import java.util.*;

class Pattern
{
    public void Display(int iRow, int iCol)
    {
        int i = 0, j = 0;

        for(i = 1 ; i <= iRow; i++)
        {
            for(j = 1; j <= iCol; j++)
            {
                if((j == 1) || (j == iCol) || (i == 1) || (i == iRow))
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

class program105
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