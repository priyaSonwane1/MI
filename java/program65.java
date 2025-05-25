import java.util.*;

class Digits
{
    public int CountDigits(int iNo)
    {
        int iCnt = 0, iDigit = 0;

        while(iNo != 0)
        {
            iDigit = iNo % 10;
            iCnt++;
            iNo = iNo / 10;
        }
        return iCnt;
    }
}

class program65
{
    public static void main(String A[])
    {
        Scanner sobj = new Scanner(System.in);

        System.out.println("Enter number : ");
        int iValue = sobj.nextInt();

        Digits dobj = new Digits();

        int iRet = dobj.CountDigits(iValue);

        System.out.println("Number of digits are : "+iRet);
    }
}