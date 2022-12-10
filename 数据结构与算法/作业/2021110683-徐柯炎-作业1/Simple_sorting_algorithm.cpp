#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define MAXSIZE 100

void PrintArr(int arr[MAXSIZE]);
void RanArr(int arr[MAXSIZE]);
void BubbleSort(int arr[MAXSIZE]);
void SelectionSort(int arr[MAXSIZE]);
void insertionSort(int arr[MAXSIZE]);
void bubbleSortd(int arr[MAXSIZE], int maxsize);
void selectionSortd(int arr[MAXSIZE], int maxsize);
void insertionSortd(int arr[MAXSIZE], int maxsize);

int main(){
    int arr[MAXSIZE];

    RanArr(arr);
    BubbleSort(arr);
    PrintArr(arr);
    printf("\n");

    RanArr(arr);
    SelectionSort(arr);
    PrintArr(arr);
    printf("\n");

    RanArr(arr);
    insertionSort(arr);
    PrintArr(arr);
    printf("\n");

    RanArr(arr);
    bubbleSortd(arr, MAXSIZE);
    PrintArr(arr);
    printf("\n");

    RanArr(arr);
    selectionSortd(arr, MAXSIZE);
    PrintArr(arr);
    printf("\n");

    RanArr(arr);
    insertionSortd(arr, MAXSIZE);
    PrintArr(arr);
    printf("\n");

    return 0;
}

void BubbleSort(int arr[MAXSIZE]){
    int temp;
    for(int i = MAXSIZE - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void PrintArr(int arr[MAXSIZE]){
    for(int i=0; i<MAXSIZE; i++){
        cout<<arr[i]<<' ';
    }
}

void RanArr(int arr[MAXSIZE]){
    for(int i=0; i<MAXSIZE; i++){
        arr[i] = rand()%500;
    }
}

void SelectionSort(int arr[MAXSIZE]){
    int temp;
    int index;
    for(int i=0; i<MAXSIZE; i++){
        temp = arr[i];
        index = i;
        for(int j=i; j<MAXSIZE; j++){
            if(arr[j] < temp){
                temp = arr[j];
                index = j;
            }
        }
        swap(arr[i],arr[index]);
    }
}

void insertionSort(int arr[MAXSIZE]){
    for(int i=0; i<MAXSIZE; i++){
        for(int j=i; j>0; j--){
            if(arr[j]<arr[j-1]){
                swap(arr[j], arr[j-1]);
            }
            else break;
        }
    }
}

void bubbleSortd(int arr[MAXSIZE], int maxsize){
    if(maxsize == 1){
        return;
    }
    for(int i=0; i<maxsize-1; i++){
        if(arr[i]>arr[i+1]){
            swap(arr[i], arr[i+1]);
        }
    }
    bubbleSortd(arr, maxsize-1);
}

void selectionSortd(int arr[MAXSIZE], int maxsize){
    int x=0;
    if(maxsize == 1){
        return;
    }
    for(int i=0; i<maxsize; i++){
        if(arr[x]<arr[i]){
            x = i;
        }
    }
    swap(arr[x], arr[maxsize-1]);
    selectionSortd(arr, maxsize-1);
}

void insertionSortd(int arr[MAXSIZE], int maxsize){
    if(maxsize == 1){
        return;
    }
    insertionSortd(arr, maxsize-1);
    for(int i=maxsize-1; i>0; i--){
        if(arr[i]<arr[i-1]){
            swap(arr[i], arr[i-1]);
        }
    }
}