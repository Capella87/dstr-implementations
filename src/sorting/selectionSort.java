import java.util.*;

class SelSort
{
    private int[] arr;
    private int size;
    
    public SelSort()
    {
        var input = new Scanner(System.in);
        size = input.nextInt();
        arr = new int[size];

        for (int i = 0; i < size; i++)
            arr[i] = input.nextInt();
        input.close();
    }

    public void selectionSort()
    {
        for (int i = 0; i < size - 1; i++)
        {
            int minIdx = i;
            for (int j = i + 1; j < size; j++)
                if (arr[minIdx] > arr[j])
                    minIdx = j;
            if (minIdx != i)
            {
                int temp = arr[i];
                arr[i] = arr[minIdx];
                arr[minIdx] = temp;
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

public class selectionSort
{
    public static void main(String[] args)
    {
        var s = new SelSort();
        s.printArray();
        s.selectionSort();
        s.printArray();
    }
}

/*
Input:
5
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
*/