import java.util.*;

class Number
{
    public boolean CheckEven(int iNo)
    {
        if((iNo % 2) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

class program59
{
    public static void main(String A[])
    {
        boolean bRet = false;

        Scanner sobj = new Scanner(System.in);

        System.out.println("Enter number : ");
        int iValue = sobj.nextInt();

        Number nobj = new Number();

        bRet = nobj.CheckEven(iValue);

        if(bRet == true)
        {
            System.out.println(iValue+" is even");
        }
        else
        {
            System.out.println(iValue+" is odd");
        }
    }
}