
/**
 * FileProcessor class opens the file the user inputs grabs the height and width of the 
 * 2d array and then grabs the data the user wants in the array
 * 
 * @author Devin Keller & Ori Garibi
 * @version 1.0
 * @see FileProcessor.cpp
 * 
 */

#include "Grid.h"
#include "FileProcessor.h"
#include <fstream>
#include <iostream>
using namespace std;
FileProcessor::FileProcessor()
{
    //default constructor body, it's empty
}
FileProcessor::~FileProcessor()
{
    //default destructor
}

//takes in a file from the command line and outputs a new file
string FileProcessor::processFile(string file) 
{

    // open and read the input file
    ifstream infile;
    infile.open(file);

    string fileString;
    string inputLine = "";
    int x = 0;
    //Grabs array data saves it to inputline and then closes file
    while (getline(infile, fileString))
    {
        x+=1;
        //cout<<x<<fileString<<endl;
        if(x>2){
            inputLine += fileString;
            //inputLine +='\n';
        }

    }
    cout << "Reading from the file..." << endl;
    infile >> inputLine;
    //cout<<inputLine<<endl;
    //Closes File
    infile.close();
    cout<<inputLine.length()<<endl;
    return inputLine;
}

//Opens a new file and writes data into file
void FileProcessor::outputFile(string array, string fileName){
    ofstream outFile; //open the output file
    outFile.open(fileName);

    cout << "Writing to the file:" << endl;

    //write inputted data into the file
    outFile << array << endl;

    //close the output file
    outFile.close();
}


//Gets height from file
int FileProcessor::getHeight(string file){
    ifstream infile;
    //opens file
    infile.open(file);
    int count = 0;

    string line;
    string heightString = "";
    //Grabs first line from file
    while (getline(infile, line) && x == 0)
    {
        heightString += line;
        x = 1;
        //heightString+= "\n";
    }
    //turns string to int
    int height = stoi(heightString);
    return height;
}

//Gets Width from file
int FileProcessor::getWidth(string file){
    ifstream infile;
    infile.open(file);
    int count = 0;
    int x = 0;

    string line;
    string widthString = "";
    //Skips the first lines to grab width
    while (getline(infile, line))
    {
        cout << "Start width: "<<endl;
        x+=1;
        //cout<<line<<endl;
        if(x == 2){
            widthString = line;
            //x += 1;
            break;
        }
        //heightString+= "\n";
    }
    //turns string into int
    int width = stoi(widthString);
    return width;


}