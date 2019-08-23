#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

template <typename T>
void print(T arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << setprecision(4) << arr[i];
        if(i < n - 1)
        {
            cout << ", ";
        }
        else
        {
            cout << ";";
        }
    }
}

double* createArray(int n);
void fillArray(double arr[], int n, double range);
void mergeSort(double arr[], int left, int right);
void merge(double arr[], int left, int mid, int right);
void quickSort(double arr[], int left, int right);
void heapSort(double arr[], int n);
void heapify(double arr[], int n, int i);
void insertionSort(double arr[], int n);


int main()
{
    int n;

    cout << "Enter the array size: ";
    while(!(cin >> n))
    {
        cout << "integers only, retry: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double range;

    do{
        cout << "Enter the max number: ";
        cin >> range;
      }while(range < n);

      double* a = createArray(n);

      fillArray(a, n, range);

      //selectionSort(a, n);
      //insertionSort(a, n);
      //heapSort(a, n);
      quickSort(a, 0, n - 1);
      //mergeSort(a, 0, n - 1);

      print(a, n);

      delete[] a;



    return 0;
}

double* createArray(int n)
{
    double* newArr = new double[n];

    return newArr;
}

void fillArray(double arr[], int n, double range)
{
    srand(time(0));

    for(int i = 0; i < n; i++)
    {
        arr[i] = (rand()* range)/ RAND_MAX;

        for(int j = 0; j < i + 1; j++)
        {
            if(arr[i] == arr[j] && i != j)

            i--;
            break;
        }
    }
}

void mergeSort(double arr[], int left, int right)
{
    if(left < right)
    {
        int mid = left + (right - left)/2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(double arr[], int left, int mid, int right)
{
    int leftSide = (mid - left) + 1;
    int rightSide = right - mid;

    double* L = new double[leftSide];
    double* R = new double[rightSide];

    for(int i = 0; i < leftSide; i++)
    {
        L[i] = arr[left + i];
    }

    for(int j = 0; j < rightSide; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while(i < leftSide && j < rightSide)
    {
        if(L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while(i < leftSide)
    {
        arr[k++] = L[i++];
    }

    while(j < rightSide)
    {
        arr[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

void quickSort(double arr[], int left, int right)
{
    int i = left;
    int j = right;

    double pivot = arr[left +(right - left)/ 2];

    while(i <= j)
    {
        while(arr[i] < pivot)
        {
            i++;
        }
        while(arr[j] > pivot)
        {
            j--;
        }

        if(i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if(left < j)
    {
        quickSort(arr, left, j);
    }

    if(i < right)
    {
        quickSort(arr, i, right);
    }

}

void heapSort(double arr[], int n)
{
    for(int i = n/2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for(int i = n - 1; i >= 0; i--)
    {
        swap(arr[i], arr[0]);

        heapify(arr, i, 0);
    }
}

void heapify(double arr[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l] > arr[largest])
    {
        largest = l;
    }

    if(r < n && arr[r] > arr[largest])
    {
        largest = r;
    }

    if(largest != i)
    {
        swap(arr[largest], arr[i]);

        heapify(arr, n, largest);
    }
}

void insertionSort(double arr[], int n)
{
    int j;
    double key;

    for(int i = 1; i < n; i++)
    {
        j = i - 1;
        key = arr[i];

        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


























































































