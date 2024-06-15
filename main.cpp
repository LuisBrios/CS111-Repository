#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;
const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

//Gets the middle element within the list and makes that the pivot.
int Partition(int numbers[], int lowIndex, int highIndex){
    int midpoint = lowIndex + (highIndex - lowIndex)/2;
    int pivot = numbers[midpoint];
    bool done = false;
    //Checks if an index is lower/higher than the pivot so that it may be properly ordered.
    //If not, then the values will swap til the list is in order. 
    while(!done){
        while(numbers[lowIndex] < pivot){
            lowIndex += 1;
        }
        while (pivot < numbers[highIndex]){
            highIndex -= 1;
        }
        if(lowIndex >= highIndex){
            done = true;
        }
        else{
            swap(numbers[lowIndex], numbers[highIndex]);
            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

//Recursive function that calls a helper function to organize the list of elements.
//Parts of the list are partitioned and swapped until the correct order is met. 
void Quicksort_midpoint(int numbers[], int lowIndex, int highIndex){
    if(lowIndex >= highIndex){
        return;
    }

    int lowEndIndex = Partition(numbers, lowIndex, highIndex);
    Quicksort_midpoint(numbers, lowIndex, lowEndIndex);
    Quicksort_midpoint(numbers, lowEndIndex + 1, highIndex);
}


//Function used to calculate the Median Pivot. It returns the index of the pivot that is apparent the most often.
//If all are different, the highest value is returned.
int MOTPivot(int numbers[], int lowIndex, int highIndex){
    int left = numbers[lowIndex];
    int right = numbers[highIndex];
    int mid = numbers[lowIndex + (highIndex - lowIndex)/2];
    if((left == right) && (right == mid)){
        return left;
    }
    if(left == right || left == mid || right == mid){
        return left;
    }
    if(left < mid){
        if(mid < right){
            return mid;
        }
        else if(left < right){
            return right;
        }
        else{
            return left;
        }
    }
    else if(right < mid){
        if(left < right){
            return right;
        }
        else if(mid < left){
            return mid;
        }
        else{
            return left;
        }
    }
    else{
        if(right < left){
            return right;
        }
        else{
            return left;
        }
    }
}

//Maintains the same logic as the other partition. It calculates the pivot, then, based on that,
//swaps the lists so it may be in order (if smaller than the pivot if its a smaller index, bigger for the bigger index). 
int MOTPartition(int numbers[], int lowIndex, int highIndex){
    int pivot = MOTPivot(numbers, lowIndex, highIndex);
    bool done = false;
    while(!done){
        while(numbers[lowIndex] < pivot){
            lowIndex += 1;
        }
        while (pivot < numbers[highIndex]){
            highIndex -= 1;
        }
        if(lowIndex >= highIndex){
            done = true;
        }
        else{
            swap(numbers[lowIndex], numbers[highIndex]);
            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

//Recursive function that calls a helper function to organize the list of elements. 
//Parts of the list are partitioned and swapped until the correct order is met. 
void Quicksort_medianOfThree(int numbers[], int lowIndex, int highIndex){
    if(lowIndex >= highIndex){
        return;
    }
    int lowEndIndex = MOTPartition(numbers, lowIndex, highIndex);
    Quicksort_medianOfThree(numbers, lowIndex, lowEndIndex);
    Quicksort_medianOfThree(numbers, lowEndIndex + 1, highIndex);
}

//Traverses through the list and checks if the element behind it is of lower value.
//If so, it traverses backwards, swapping with every element it is greater than. 
void InsertionSort(int numbers[], int numbersSize){
    int i = 0;
    int j = 0;
    for(i = 1; i < numbersSize; ++i){
        j = i;
        while (j > 0 && numbers[j] < numbers[j - 1]){
            swap(numbers[j], numbers[j - 1]);
            --j; 
        }
    }
}

int main(){
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    fillArrays(arr1, arr2, arr3);
    const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;

    clock_t Start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime  << endl;

    Start = clock();
    Quicksort_medianOfThree(arr1, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime << endl;

    Start = clock();
    InsertionSort(arr1, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime << endl;

    return 0;
}