#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class mSort
{
private:
    vector<int> lst;
    vector<int> temp;
    int size;

public:
    mSort()
    {
        string input;
        getline(cin, input);
        size_t pos = 0, cur = 0;
        int count = 0;

        // Split input string into integers
        while ((pos = input.find(' ', cur)) != string::npos)
        {
            lst.push_back(stoi(input.substr(cur, pos)));
            cur = pos;
            while (input[cur] == ' ') cur++; // Ignore one or more than spaces
            count++;
        }
        lst.push_back(stoi(input.substr(cur, input.length()))); // input last one
        this->size = ++count;
    }

    void mergeSort(int left, int right)
    {
        if (left >= right) return;

        // Divide
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        // Conquer
        int i = left, j = mid + 1;
        while (i <= mid && j <= right)
        {
            if (lst[i] < lst[j]) temp.push_back(lst[i++]);
            else temp.push_back(lst[j++]);
        }
        while (i <= mid) temp.push_back(lst[i++]);
        while (j <= right) temp.push_back(lst[j++]);
        for (int k = right; k >= left; k--) // To consider vector's property (only supports push and pop back)
        {
            lst[k] = temp.back();
            temp.pop_back();
        }

        return;
    }

    void printArray()
    {
        for (int i = 0; i < this->size; i++)
            cout << lst[i] << ' ';
        cout << '\n';
    }

    int getSize()
    {
        return this->size;
    }
};

int main(void)
{
    mSort n = mSort();
    n.printArray();
    n.mergeSort(0, n.getSize() - 1);
    n.printArray();
    return 0;
}

/*
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
*/