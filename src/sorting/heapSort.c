#include <stdio.h>
#include <stdlib.h>
#include "./_common_/common.h"

void heapify(int* arr, int size, int t_idx)
{
    int largest = t_idx;
    int left = t_idx * 2 + 1; // 왼쪽 자식 노드
    int right = t_idx * 2 + 2; // 오른쪽 자식 노드

    if (left < size && arr[left] > arr[largest]) // 왼쪽 자식 노드가 더 큰 경우 largest 갱신
        largest = left;
    if (right < size && arr[right] > arr[largest])
        largest = right;
    if (largest != t_idx)
    {
        swap(&arr[largest], &arr[t_idx]);
        heapify(arr, size, largest); // target에 해당되는 것을 올바른 위치에 갈 때까지 재귀함수 처리
    }
    return;
}

void heapSort(int* arr, const int size)
{
    for (int i = size / 2 - 1; i >= 0; i--) // 가장 나중에 있는 internal node부터 루트 노드까지 차례차례 heapify한다.
        heapify(arr, size, i);

    for (int i = size - 1; i >= 0; i--) // 일반 heap의 dequeue에 해당된다.
    {
        swap(&arr[0], &arr[i]); // 루트 노드에 있는 것을 꺼내 맨 뒤로 이동시킨다. (heap의 크기는 1씩 줄어든다.)
        heapify(arr, i, 0); // 힙 재구성
    }
    return;
}

int main(void)
{
    int n;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printArray(arr, n);
    heapSort(arr, n);
    printArray(arr, n);

    free(arr);
    return 0;
}