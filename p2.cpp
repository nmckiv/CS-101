#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>
using namespace std;



bool BinarySearch(int numbers[], int numbersSize, int key) {
   int mid;
   int low;
   int high;
   
   low = 0;
   high = numbersSize - 1;
   
   while (high >= low) {
      mid = (high + low) / 2;
      if (numbers[mid] < key) {
         low = mid + 1;
      }
      else if (numbers[mid] > key) {
         high = mid - 1;
      }
      else {
         return true;
      }
   }
   
   return false; // not found
}

bool BinarySearch(string numbers[], int numbersSize, string key) {
   int mid;
   int low;
   int high;
   
   low = 0;
   high = numbersSize - 1;
   
   while (high >= low) {
      mid = (high + low) / 2;
      if (numbers[mid] < key) {
         low = mid + 1;
      }
      else if (numbers[mid] > key) {
         high = mid - 1;
      }
      else {
         return true;
      }
   }
   
   return false; // not found
}

void inBoth(int nums1[], int nums2[], int inBoth[], int lineCount1, int lineCount2, int &inBothCount) {
    if (lineCount1 < lineCount2) {
        for (int x = 0; x < lineCount1; x++) {
        if (BinarySearch(nums2, lineCount2, nums1[x]) && !BinarySearch(inBoth, inBothCount, nums1[x])) {
            inBoth[inBothCount] = nums1[x];
            inBothCount++;
        }
    }
    }
    else {
        for (int x = 0; x < lineCount2; x++) {
        if (BinarySearch(nums1, lineCount1, nums2[x]) && !BinarySearch(inBoth, inBothCount, nums2[x])) {
            inBoth[inBothCount] = nums2[x];
            inBothCount++;
        }
    }
    }    
}

void inBoth(string nums1[], string nums2[], string inBoth[], int lineCount1, int lineCount2, int &inBothCount) {
    int nextAvailable = 0;
    if (lineCount1 < lineCount2) {
        for (int x = 0; x < lineCount1; x++) {
        if (BinarySearch(nums2, lineCount2, nums1[x]) && !BinarySearch(inBoth, nextAvailable, nums1[x])) {
            inBoth[nextAvailable] = nums1[x];
            nextAvailable++;
            inBothCount++;
        }
    }
    }
    else {
        for (int x = 0; x < lineCount2; x++) {
        if (BinarySearch(nums1, lineCount1, nums2[x]) && !BinarySearch(inBoth, nextAvailable, nums2[x])) {
            inBoth[nextAvailable] = nums2[x];
            nextAvailable++;
            inBothCount++;
        }
    }
    }    
}

int Partition(string numbers[], int i, int k) {
   int l;
   int h;
   int midpoint;
   string pivot;
   string temp;
   bool done;
   
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];
   
   done = false;
   l = i;
   h = k;
   
   while (!done) {
      
      while (numbers[l] < pivot) {
         ++l;
      }
      
      while (pivot < numbers[h]) {
         --h;
      }
      
      if (l >= h) {
         done = true;
      }
      else {
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}
void Quicksort(string numbers[], int i, int k) {
   int j;
   
   if (i >= k) {
      return;
   }
   
   j = Partition(numbers, i, k);
   

   Quicksort(numbers, i, j);
   Quicksort(numbers, j + 1, k);
}

void Merge(int numbers[], int i, int j, int k) {
    int mergedSize = k - i + 1;
    int mergePos = 0;
    int leftPos = i;
    int rightPos = j + 1;
    int* mergedNumbers = nullptr;
    mergedNumbers = new int[mergedSize];

    while (leftPos <= j && rightPos <= k) {
      if (numbers[leftPos] < numbers[rightPos]) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;
      
      MergeSort(numbers, i, j);
      MergeSort(numbers, j + 1, k);
      
      Merge(numbers, i, j, k);
   }
}

int main(int argc, char* argv[]) {
    string type = argv[1]; // Indicates integer or string
    string inputFileName1 = argv[2]; //First and second input files
    string inputFileName2 = argv[3];
    ifstream inputFile1;
    ifstream inputFile2;
    int lineCount1 = 0;
    int lineCount2 = 0;
    int inBothCount = 0;
    inputFile1.open(inputFileName1);
    inputFile2.open(inputFileName2);


    //Process integer files
    if (type == "i") {
        int nums1[20000];
        int nums2[20000];

        //Push file input lines into arrays
        while (inputFile1 >> nums1[lineCount1]) {
            lineCount1++;
        }
        while (inputFile2 >> nums2[lineCount2]) {
            lineCount2++;
        }

        //Sort both arrays
        MergeSort(nums1, 0, lineCount1 - 1);
        MergeSort(nums2, 0, lineCount2 - 1);

        //Find unique values in both arrays and print
        int numsInBoth[20000];
        inBoth(nums1, nums2, numsInBoth, lineCount1, lineCount2, inBothCount);
        for (int x = 0; x < inBothCount; x++) {
            cout << numsInBoth[x] << endl;
        }
    }  

    //Process string files
    else if (type == "s") {
        string words1[20000];
        string words2[20000];

        //Push file input lines into arrays
        while (inputFile1 >> words1[lineCount1]) {
            lineCount1++;
        }
        while (inputFile2 >> words2[lineCount2]) {
            lineCount2++;
        }

        //Sort both arrays
        Quicksort(words1, 0, lineCount1 - 1);
        Quicksort(words2, 0, lineCount2 - 1);

        //Find unique values in both arrays and print
        string wordsInBoth[20000];
        inBoth(words1, words2, wordsInBoth, lineCount1, lineCount2, inBothCount);
        for (int x = 0; x < inBothCount; x++) {
            cout << wordsInBoth[x] << endl;
        }
    }
}