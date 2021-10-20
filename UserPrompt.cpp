/**
 * Grid class creates the grid for the user
 * 
 * @author Devin Keller & Ori Garibi
 * @version 1.0
 * @see FileProcessor.cpp
 * 
 */
#include "UserPrompt.h"
#include "Grid.h"
#include "FileProcessor.h"

UserPrompt::UserPrompt(){
    config = configuration();

}

UserPrompt::~UserPrompt(){

}

string UserPrompt::configuration(){
    
    FileProcessor *sp = new FileProcessor;
    string config;
    bool x = false;
    bool isPercent = false;
    string randomConfig;
    while(x == false){ //FIXME
        cout << "Type 'random' to have a random configuration or type 'file' to input file" << endl;
        cin >> config;
        if(config == "file"){ // get h and w
            //first i will run the file processor
            cout<<"What is your file path?"<<endl;
            cin>>filePath;
            fileInput = sp->processFile(filePath);

            //get i and j of the string
            h = sp->getHeight(filePath);
            w = sp->getWidth(filePath);

            x = true;
            return config;
        }
        else if(config == "random"){
            cout<< "What is the height of your grid?"<<endl;
            cin>> h;
            cout<< "What is the width of your grid?"<<endl;
            cin>> w;
            while(isPercent == false){
                cout<< "What percentage of your grid do you want to be populate?" << endl;
                cin>> d;
                if(d >= 1){
                    cout<< "Enter a decimal" << endl;
                    isPercent = false;
                }
                else{
                    isPercent = true;
                }
                
            }
            
            randomConfig+= "random";
            
            x = true;
            return randomConfig;
        }
        else{
            cout << "Invalid response" << endl;
            x = false;

        }

    }



}
    

//Creates game mode class
void UserPrompt::gameMode(){
    Grid *sp = new Grid(h,w);
    int mode = 4;
    bool underFour = false;
    while(underFour == false){
        cout<<"Enter the game mode you would like to play: \n 1. Standard \n 2. Doughnut \n 3. Mirror"<<endl;
        cin>>mode;
        if(mode > 3){
            underFour = false;

        }
        else{
            underFour = true;
        }
    }
    if(config == "file"){
        sp->buildFileArray(fileInput);
    }
    if(config=="random"){
        sp->createGrid(h,w,d, config,mode);
    }
    int pauseGame;
    pauseGame = pause(mode);

    //Calls pauses method from Grid.cpp 

    sp->pauses(pauseGame, mode);
    
}


int UserPrompt::pause(int mode){
    int pause = 4;
    bool isTrue = false;
    while(isTrue == false){
        cout<<"What pause would you like between generations: \n 1. brief pause \n 2. press enter key \n 3. output to a file"<<endl;
        cin>>pause;

    
        if(pause > 3){
            isTrue = false;

        }
        else{
            isTrue = true;
        }
        
        return pause;
    }

}


