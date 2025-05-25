import java.util.*;

class Arithematic
{
    public int iNo1;
    public int iNo2;

    public Arithematic(int A, int B)
    {
        this.iNo1 = A;
        this.iNo2 = B;
    }

    public int Addition()
    {
        int iAns = 0;
        iAns = this.iNo1 + this.iNo2;
        return iAns;
    }
}

class program58
{
    public static void main(String A[])
    {
        int iValue1 = 0, iValue2 = 0, iRet = 0;

        Scanner sobj = new Scanner(System.in);

        System.out.println("Enter first number : ");
        iValue1 = sobj.nextInt();

        System.out.println("Enter second number : ");
        iValue2 = sobj.nextInt();

        Arithematic aobj = new Arithematic(iValue1, iValue2);

        iRet = aobj.Addition();

        System.out.println("Addition is : "+iRet);

    }
}