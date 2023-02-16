#include <stdio.h>

void selection_sort(int a[], int n);
void bubble_sort(int a[], int n);
void insertion_sort(int a[], int n);

int main()
{
    int a[] = {1, 2, 3, 1, 2, 2, 7, 4, 9, 3, 5};
    int n = sizeof(a) / sizeof(a[0]);
    insertion_sort(a, n);
    for (int i = 0; i < 11; i++)
        printf("%d ", a[i]);
}

void insertion_sort(int a[], int n)
{
    int key, j;
    for (int i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        while (key < a[j] && j >= 0)
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

void selection_sort(int a[], int n)
{
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        if (i != min)
        {
            int t = a[i];
            a[i] = a[min];
            a[min] = t;
        }
    }
}

void bubble_sort(int a[], int n)
{
    for (int i = n; i > 0; i--)
    {
        for (int j = 0; j < i - 1; j++)
        {
            if (a[j] < a[j + 1])
            {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}