#include <iostream>
#include <iomanip>
#include <string>      // Supports use of "string" data type
#include <fstream>
using namespace std;

int countLines(string words[1000]) {
   int count = 0;
   for (int x = 0; x < 1000; x++) {
      if (words[x].compare("") == 0) {
         return count;
         }
         count++;
      }
      return 1000;
   }
   int countUniqueLines(string words[2000]) {
   int count = 0;
   for (int x = 0; x < 2000; x++) {
      if (words[x].compare("") == 0) {
         return count;
         }
         count++;
      }
      return 2000;
   }

string toUppercase(string word) {
   string UppercaseWord = "";
   for (int x = 0; x < int(word.length()); x++) {
      word[x] = toupper(word[x]);
      }
   return word;
   }

bool inArray(string words[1000], string word, int maxElement){
    for (int x = 0; x < maxElement; x++) {
        if (!words[x].compare(word)) {
            return true;
        }
    }
    return false;
}

void arrayToUpper(string words[1000], int maxElement) {
   for (int x = 0; x < maxElement; x++) {
      words[x] = toUppercase(words[x]);
      }
   }
   
int main(int argc, char* argv[]) {
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    ifstream inputFile;
    ofstream outputFile;
    string sources[1000];
    string destinations[1000];
    int bandwidths[1000];
    string uniqueIdentifiers[2000];
    string nonLeafIdentifiers[1000];
    int to[1000];
    int from[1000];
    int num = 0;


    inputFile.open(inputFileName);
    outputFile.open(outputFileName);

    //Records input file values in appropriate arrays
    //Keep track of number of input lines
    int lineCount = 0;
    while (lineCount < 1000){
       inputFile >> sources[lineCount];
       inputFile >> destinations[lineCount];        
       inputFile >> bandwidths[lineCount];
       if (sources[lineCount].compare("") == 0) {
       break;  
       }
       lineCount++;
    }
    
    //Make string arrays uppercase
    arrayToUpper(sources, lineCount);
    arrayToUpper(destinations, lineCount);
    
    //Record all unique identifiers
    int nextAvailable = 0;
    for (int x = 0; x < lineCount; x++) {
      string source = sources[x];
      string destination = destinations[x];
       if (!inArray(uniqueIdentifiers, source, nextAvailable)) {
          uniqueIdentifiers[nextAvailable] = source;
          nextAvailable++;
          }
       if (!inArray(uniqueIdentifiers, destination, nextAvailable)) {
          uniqueIdentifiers[nextAvailable] = destination;
          nextAvailable++;
          }
       }
       num = countUniqueLines(uniqueIdentifiers);

      //Push unique identifiers into output file
   for (int x = 0; x < num; x++) {
      outputFile << uniqueIdentifiers[x] << endl;
      }

      outputFile << endl;

      //Identify non-leaf identifiers
      nextAvailable = 0;
      string unique;
   for (int x = 0; x < num; x++) {
      unique = uniqueIdentifiers[x];
      if (inArray(sources, unique, lineCount) && inArray(destinations, unique, lineCount)) {
         nonLeafIdentifiers[nextAvailable] = unique;
         nextAvailable++;
         }
      }
      

      //Record sum of bandwidths to, from, and ratios
      num = countLines(nonLeafIdentifiers);
   for (int x = 0; x < num; x++) {
      to[x] = 0;
      from[x] = 0;
      for (int y = 0; y < lineCount; y++) {
         if(nonLeafIdentifiers[x].compare(sources[y]) == 0) {
            to[x] += bandwidths[y];
            }
            if(nonLeafIdentifiers[x].compare(destinations[y]) == 0) {
            from[x] += bandwidths[y];
            }
         }
      }
      
      //Push non-leafs, sums, and ratios into output file
      outputFile << fixed << setprecision(2);
   for (int x = 0; x < num; x++) {
      outputFile << nonLeafIdentifiers[x] << " " << to[x] << " " << from[x] << " " << double(from[x]) / double(to[x]) <<  endl;
      }
      

   
      
   
}
