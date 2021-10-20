/**
 * FileProcessor header file
 * @author Devin Keller & Ori Garibi
 * @version 1.0
 * @see FileProcessor.cpp
 * 
 */


#include <iostream> 

using namespace std;

class FileProcessor
{

public:
    FileProcessor(); //default constructor
    ~FileProcessor(); //destructor
    string processFile(string input);
    void outputFile(string theArray, string theFile);
    int getHeight(string file);
    int getWidth(string file);

private:
    int x = 0;

};