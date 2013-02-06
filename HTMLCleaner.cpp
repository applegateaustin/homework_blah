/*Programmer: Austin Applegate
  Date modified: 1/28/13 Description: read a file and take the contents of it and clean it up and fix the error's and then write it to a new file.
  Lab Number: 1
  Date Due: 2/6/13
*/
 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
 
void openFile(char*, ifstream&);
void cleanFile(ifstream&, string*, int, char*);
void getKeyWords(char*, string*&, int&);
string findKeyWords(string*, string, int);
void writeOutputFile(char*, string);
 
//(int argc, char* argv[]) is if you want to pass anything in from the command line (terminal) before you run the program. (int argc) is the number of things you want to pass in
//(argv[]) is what you are passing in like cleanHTML.html.
int main(int argc, char* argv[]) {
 
  char* sourceFile;
  char* keywordsFile;
  char* outputFile;
 
  if(argc != 3 && argc != 4) {
    cout << "Error in program input, Please try again." << endl;
    return 0;
  }
  else{
    sourceFile = argv[1];
    keywordsFile = argv[2];
    if(argc == 4) {
      outputFile = argv[3];
    }
    else {
      outputFile = "none";
    }
  }
 
  int keywordSize = 0;
  string* keywords;
  getKeyWords(keywordsFile, keywords, keywordSize);
  //the variable inputFile is of type ifstream and is pointing to a place in memory. In the the openFile fuction in the parameter the ifstream& file is pointing to the same place in memory
  //so that when we open the file in the function openFile the variable inputFile will also become "opened".
  ifstream inputFile;
  //sourceFile is just the name of the file, inputFile is the actual file(stream).
  openFile(sourceFile, inputFile);
  
  cleanFile(inputFile, keywords, keywordSize, outputFile);
 
  return 0;
}
 
void getKeyWords(char* keywordsFile, string*& keywords, int& keywordSize) {
  ifstream keyFile (keywordsFile);
 
  string temp;
 
   //keyFile is open: count how man keywords there are.
  if(keyFile.is_open()) {
    while(!keyFile.eof()) {
      //keyFile >> temp will take each word in the keyFile and send it to the temp variable that is of type String. if the temp variable was of int the keyFile would store by integers in temp.
      //if temp was of type char keyFile would save each char in temp.
      keyFile >> temp;
      keywordSize++;
    }
  }
 
   //closing keyFile and reopening it to move back to the beginning of the file.
  keyFile.close();
  //you have to give the open file and argument ('whats here in perenthases')
  keyFile.open(keywordsFile);
  //creating a string array that is of the size of the number of keywords that are in the keyword file.
  keywords = new string[keywordSize];
  //while the keyFile is open we are going take each word in the file and store that in a element in our kw[] array.
  if(keyFile.is_open()) {
    //while(!keyFile.eof()) {
      
      for(int i = 0; i < keywordSize; i++) {
        keyFile >> keywords[i];
      }
    //}
  }
  //not using the keyFile anymore since we got the keywords stored in an string array.
  keyFile.close();
}
 
//file streams require their file name type to be of char* not string...
//ifstream means input file stream.
void openFile(char* fileName, ifstream& file) {
  //'string temp;' will store the current word in the temp variable. If you do 'inFile >> temp' it will take the current word in 'inFile' and store it in temp.
  // making a while loop for the keyword file and count each word 'string' in the file once done make a string array 'string* kw = new string[count];'. Make sure
  // to delete the array so you dont have a memory leak delete kw;.
  file.open(fileName);
  //to create a vector:
  //vector<string> word
 
  //adding to vector
  //words.push_back("data");
  //to return the vector size:
  //words.size();
  
  //these 'else if' are checking to see if the file fails to open, if it does it will print to console saying "error opening file: 'file name'".
  if(!file.is_open()) {
    cout << "error opening file: " << fileName << endl;
  }
}
//everytime you pass a filestream into a function it has to be a call by reference.
// TODO: Also pass in outputFileName???***** DONE I THINK!!!!!!
void cleanFile(ifstream& inputFile, string* keyWords, int arraySize, char* outputFileName) {
  string currentKeyWord;
  string builtHTML;
  bool isOpenParagraph = false;
 
  while(!inputFile.eof()) {
    inputFile >> currentKeyWord;
    //cout << currentKeyWord;
 
    if (currentKeyWord == "<p>") {
      if (isOpenParagraph) {
        builtHTML += "</p>" + currentKeyWord;
      }
      else {
        isOpenParagraph = true;
        builtHTML += currentKeyWord;
      }
    }
    else if(currentKeyWord == "</body>") {
      if (isOpenParagraph) {
        builtHTML += "</p>" + currentKeyWord;
        isOpenParagraph = false;
      }
      else {
        builtHTML += currentKeyWord;
      }
    }
    else {
      // TODO: Don't call if it is any HTML tag???
      builtHTML += findKeyWords(keyWords, currentKeyWord, arraySize);
    }
 
    builtHTML += " ";
  }
 
  if (outputFileName == "none") {
    cout << builtHTML;
  }
  else {
    writeOutputFile(outputFileName, builtHTML);
  }
}
 
void writeOutputFile(char* fileName, string builtHTML) {
  ofstream output (fileName);
  
  output << builtHTML;
  output.close();
}
 
//this function needs to check each word in the inFile and check to see if it is also contained in the keyword file via the array we created that is storing them. If it is a keyword we will
//add <i>'word here'</i>
string findKeyWords(string* keywords, string currentword, int arraySize) {
 
  string updatedString;
  updatedString = currentword;
 
  //cout << arraySize;
  //checking to see if the current word that we a reading in is also contained in the keyword array, if it is we italicize it.
  for(int i = 0; i < arraySize; i++) {
    if(currentword == keywords[i] || currentword == keywords[i] + ',') {
      // TODO: Fix this********* THINK I FIXED IT
      updatedString = "<i>" + (string)currentword + "</i>";
      //updatedString = "<i>";
    }
  }
 
  return updatedString;
}
