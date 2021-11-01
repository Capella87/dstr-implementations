#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class QuickSort
{
private:
    vector<int> vt;
    int size;

    inline void swap(int idx1, int idx2)
    {
        int temp = vt[idx1];
        vt[idx1] = vt[idx2];
        vt[idx2] = temp;
    }

    int partition(int left, int right)
    {
        int pivot = vt[left];
        int low = left + 1;
        int high = right;

        while (low <= high)
        {
            while (low <= right && pivot > vt[low])
                low++;
            while (pivot < vt[high] && high > left)
                high--;
            if (low <= high) swap(low, high);
        }
        swap(left, high);
        return high;
    }

public:
    QuickSort()
    {
        string str;
        getline(cin, str);

        size_t pos = 0, cur = pos;
        int count = 0;
        while ((pos = str.find(' ', cur)) != string::npos)
        {
            vt.push_back(stoi(str.substr(cur, pos)));
            cur = pos;
            while (str[cur] == ' ') cur++;
            count++;
        }
        vt.push_back(stoi(str.substr(cur, str.length())));
        this->size = ++count;
    }

    void quSort(int left, int right)
    {
        if (left > right) return;
        int pivot_idx = partition(left, right);
        quSort(left, pivot_idx - 1);
        quSort(pivot_idx + 1, right);
    }

    void printArray()
    {
        for (int i = 0; i < this->size; i++)
            cout << vt.at(i) << ' ';
        cout << '\n';
    }

    int getSize()
    {
        return this->size;
    }
};

int main()
{
    QuickSort q = QuickSort();
    q.printArray();
    q.quSort(0, q.getSize() - 1);
    q.printArray();

    return 0;
}