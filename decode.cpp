//
//  decode.cpp
//  project1decode
//
//  Created by Lexi Diep on 9/25/19.
//  Copyright © 2019 Lexi Diep. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


//get last character of every sorted cyclic shift and make into a string
string lastCol(string &str) {
    string lastChar;
    int tab, noTab;
    
    //retrieve characters from encoded string
    for (int i = 0; i < str.length(); i += 4) {
        //handles the case if there is a tab character
        tab = (str[i + 1] -'0') + 10*(str[i]-'0');  //calculate # of indexes tab consists of
        noTab = str[i]-'0';
        
        //if there is no tab, continue through array as normal
        if (str[i + 1] == ' ') {
            for (int j = 0; j < noTab; j++) {
                lastChar = lastChar + str[i + 2];
            }
        }
        //if there is a tab, skip over extra indices
        else {
            for (int j = 0; j < tab; j++) {
                lastChar = lastChar + str[i + 2];
            }
            i++;
        }
    }   //end for
    
    return lastChar;
}   //end of lastCol


//uses insertion sort to sort the letters in the 'last' string
void insertionSort(string &str) {
    char key;
    
    for (int i = 0; i < (str.length()); i++) {
        key = str[i];
        int j = i - 1;
        while (j >= 0 && str[j] > key) {
            str[j+1] = str[j];
            j = j - 1;
        }
        str[j+1] = key;
    }   //end for
    
}   //end of insertionSort


//used to merge subarrays in mergeSort
void merge(string &str, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;
    char* tempArr = new char[right - left + 1];
    
    while (i <= mid && j <= right) {
        if (str[i] <= str[j]) {
            tempArr[k++] = str[i++];
        }
        else {
            tempArr[k++] = str[j++];
        }
    }
    
    while (i <= mid) {
        tempArr[k++] = str[i++];
    }
    
    while (j <= right) {
        tempArr[k++] = str[j++];
    }
    
    k = 0;
    
    for (i = left; i <= right; i++) {
        str[i] = tempArr[k];
        k++;
    }
    
}   //end of merge


//uses merge sort to sort the letters in the 'last' string
void mergeSort(string &str, int left, int right) {
    int mid;
    
    if (left < right) {
        mid = left + (right - left) / 2;
        
        mergeSort(str, left, mid);
        mergeSort(str, mid + 1, right);
        merge(str, left, mid, right);
    }
    
}   //end of mergeSort


//computes the 'next' indices and stores in an array
int* nextCol(string str1, string str2) {
    int nextIndex;
    int* nextArr = new int[str1.length()];
    
    for (int i = 0; i < str1.length(); i++) {
        nextIndex = 0;
        
        //if character is the same, move to next shift
        if (str1[i] == str1[i-1]) {
            nextIndex = nextArr[i-1] + 1;
        }
        
        //increment index until same character found
        while (str1[i] != str2[nextIndex]) {
            nextIndex++;
        }
        
        nextArr[i] = nextIndex;
    }
    return nextArr;
}


//finds the next characters and puts into string to return original string
string findOriginal(int originalIndex, string &str1, string &str2) {
    int j;
    int* next = nextCol(str1, str2);
    string original = "";
    
    j = next[originalIndex];
    for (int i = 0; i < str2.length(); i++) {
        original += str2[j];
        j = next[j];
    }
    
    return original;
}   //end of findOriginal
 
 
int main(int argc, const char * argv[]) {
    string sortType = argv[1];  //sortType =  argument at position 1 from user input
    string inputText, lastStr, sortedLast, original;
    int indexOfOrig;
    
    while (getline(cin, inputText)) {
        
        indexOfOrig = atoi(inputText.c_str());  //retrieves the index of the original string from the encoded file
        
        getline(cin, inputText);    //retrieves the encoded string
        lastStr = lastCol(inputText);
        sortedLast = lastCol(inputText);
        
        //performs insertion sort or merge sort based on user input
        if (sortType == "insertion") {
            insertionSort(sortedLast);
        }
        else if (sortType == "merge") {
            mergeSort(sortedLast, 0 , sortedLast.length() - 1);
        }
        
        original = findOriginal(indexOfOrig, sortedLast, lastStr);
        
        //print original string
        cout << original << endl;
        
    }   //end while
     
    
    return 0;
}   //end of main
