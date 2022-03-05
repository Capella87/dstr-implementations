import java.util.Scanner;

class BSort
{
    private int size;
    private int[] arr;

    public BSort()
    {
        var input = new Scanner(System.in);
        size = input.nextInt();
        arr = new int[size];
        for (int i = 0; i < size; i++)
            arr[i] = input.nextInt();
        input.close();
    }

    public void bubbleSort()
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    public void printArray()
    {
        for (int e : arr)
            System.out.printf("%d ", e);
        System.out.println();
    }
}

public class bubbleSort
{
    public static void main(String[] args)
    {
        var b = new BSort();
        b.printArray();
        b.bubbleSort();
        b.printArray();
    }
}