import java.util.*;

class Digits
{
    public int CountFrequency(int iNo)
    {
        int iCnt = 0, iDigit = 0;

        if(iNo < 0)
        {
            iNo = -iNo;
        }

        while(iNo != 0)
        {
            iDigit = iNo % 10;
            if(iDigit == 5)
            {
                iCnt++;
            }
            iNo = iNo / 10;
        }
        return iCnt;
    }
}

class program69
{
    public static void main(String A[])
    {
        Scanner sobj = new Scanner(System.in);

        System.out.println("Enter number : ");
        int iValue = sobj.nextInt();

        Digits dobj = new Digits();

        int iRet = dobj.CountFrequency(iValue);

        System.out.println("Number of 5 are : "+iRet);
    }
}