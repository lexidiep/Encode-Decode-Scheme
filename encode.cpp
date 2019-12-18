//
//  main.cpp
//  project1
//
//  Created by Lexi Diep on 9/9/19.
//  Copyright © 2019 Lexi Diep. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


//performs cyclic shifts (unsorted)
void cyclicShift(string str, char** shifts, int n) {
    //allocating array
    for (int i = 0; i < n; i++) {
        shifts[i] = new char[n+1];
    }

    strcpy(shifts[0], str.c_str()); //first pointer points to original string
    
    //shifting every element to the left and storing in a new row
    for (int i = 1; i < n; i++) {
        char temp = shifts[i-1][0];
        for (int j = 0; j < n; j++) {
            shifts[i][j] = shifts[i-1][j+1];
        }
        shifts[i][n-1] = temp;
        shifts[i][n] = '\0';    //null terminates each string
    }
    
}   //end of cyclicShifts


//uses the insertion sort to sort each line of input file
//the array used in parameter should be array of pointers that point to each cyclic shift
void insertionSort(char** cyclicArray, int n) {
    int  i, j;
    char* key;  //key = temporary string that holds current string
    
    for (i = 1; i < n; i++) {
        key = cyclicArray[i];
        //insert array[j] into sorted subsequence array[1..j-1]
        j = i - 1;
        while ((j >=0) && (string(cyclicArray[j]).compare(string(key)) > 0)) {
            cyclicArray[j+1] = cyclicArray[j];
            j = j - 1;
        }
        cyclicArray[j + 1] = key;
    }
}   //end of insertionSort


//used to merge subarrays in mergeSort
void merge(char** cyclicArray, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;

    char** tempArr = new char*[right - left + 1];
    
    while (i <= mid && j <= right) {
        if (string(cyclicArray[i]).compare(string(cyclicArray[j])) <= 0) {
            tempArr[k++] = cyclicArray[i++];
        }
        else {
            tempArr[k++] = cyclicArray[j++];
        }
    }   //end while
    
    while (i <= mid) {
        tempArr[k++] = cyclicArray[i++];
    }
    
    while (j <= right) {
        tempArr[k++] = cyclicArray[j++];
    }
    
    k = 0;
    
    for (i = left; i <= right; i++) {
        cyclicArray[i] = tempArr[k];
        k++;
    }
        
}


//uses the merge sort to sort each line of input file
void mergeSort(char** cyclicArray, int left, int right) {
    int mid;
    if (left < right) {
        mid = left + (right - left) / 2;
        
        mergeSort(cyclicArray, left, mid);
        mergeSort(cyclicArray, mid + 1, right);
        merge(cyclicArray, left, mid, right);
    }
    
}   //end of mergeSort


//searches for orignal string in the sorted cyclic shifts and returns the index of the original string
int binarySearch(char** array, string str, int n) {
    int l = 0;  //left (first element) = 0
    int r = n - 1; // right (last element)  = length - 1
    int mid;    //middle element
    
    while (l <= r) {
        mid = l + (r - l) / 2;
    
        //if the string at mid == original string, return mid
        if (str.compare(array[mid]) == 0) {
            return mid;
        }
        //if str > array[mid], search right
        else if (str.compare(array[mid]) > 0) {
            l = mid + 1;
        }
        //if str < array[mid], search left
        else {
            r = mid - 1;
        }
    }   //end of while loop
    
    return 0;
}   //end of binarySearch


int main(int argc, const char* argv[]) {
    string inputText;   //inputText = file user chooses to read
    string sortType = argv[1];  //sortType =  argument at position 1 from user input

    //if user types any other argument, error message is displayed
    if (sortType != "insertion" && sortType != "merge") {
        cout << "Please specify which sort type ('merge' or 'insertion') you would like to execute." << endl;
    }
    else {
        while (getline(cin, inputText)) {
            char** cyclicArr = new char*[inputText.length()]; //creates 2d array to store each unsorted cyclic shift of string
            string last = "";  //creates string to store the last element of each cyclic shift
            int originalIndex, clusterSize = 1;  //originalIndex stores the index of the original string in the sorted 2d array; clusterSize = number of same consecuticve characters
            
            
            //if the line is an empty line
            if (inputText.length() == 0) {
                clusterSize = 0;
                last = "\n";
            }
            else {
                cyclicShift(inputText, cyclicArr, inputText.length());    //performing and storing each unsorted cyclic shift
            }
            
            //performs insertion sort or merge sort based on user input
            if (sortType == "insertion") {
                insertionSort(cyclicArr, inputText.length());
            }
            else if (sortType == "merge") {
                mergeSort(cyclicArr, 0, inputText.length()-1);
            }
            
             //extracts last element of each shift and stores in 'last'
             for (int i = 0; i < inputText.length(); i++) {
                 last = last + cyclicArr[i][inputText.length()-1];
             }
            
            //searches for index original string in sorted shifts and prints index
            originalIndex = binarySearch(cyclicArr, inputText, inputText.length());
            cout << originalIndex << endl;

            for (int i = 0; i < inputText.length(); i++) {
                while (last[i] == last[i+1]) {
                    clusterSize++;
                    i++;
                }
                cout << clusterSize << " " << last[i] << " ";
                clusterSize = 1;
            }
            cout << endl;
        }   //end of while loop
    }

    return 0;
}   //end of main

