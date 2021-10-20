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

//Default constructor
UserPrompt::UserPrompt(){
    cout<<"userprompt config"<<endl;
    
    config = configuration();
    cout<<config<<endl;

}
//Destructor
UserPrompt::~UserPrompt(){

}

//Asks whether you want to upload your own grid of random and gets values of height and width
string UserPrompt::configuration(){
    
    FileProcessor *sp = new FileProcessor;
    string config;
    bool x = false;
    bool isPercent = false;
    string randomConfig;
    cout<<"random prompt"<<endl;
    //Makes sure that answer is either file or random
    while(x == false){ 
        cout << "Type 'random' to have a random configuration or type 'file' to input file" << endl;
        cin >> config;
        if(config == "file"){ 

            //Run fileprocessor
            cout<<"What is your file path?"<<endl;
            cin>>filePath;
            fileInput = sp->processFile(filePath);
            cout<<fileInput<<endl;
            cout<<fileInput.length()<<endl;

            h = sp->getHeight(filePath);

            w = sp->getWidth(filePath);


            x = true;
            return config;
        }
        //Gets height and width
        else if(config == "random"){
            cout<< "What is the height of your grid?"<<endl;
            cin>> h;
            cout<< "What is the width of your grid?"<<endl;
            cin>> w;
            //Makes sure input is a percent
            while(isPercent == false){
                cout<< "What percentage of your grid do you want to be populate?" << endl;
                cin>> d;
                //float percentf = stof(percent);
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
    //cout<<"running mode"<<endl;
    Grid *sp = new Grid(h,w);
    //config = configuration();
    int mode = 4;
    bool underFour = false;
    //Makes sure the mode is under 4
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

    sp->simulation(pauseGame, mode);
    
}


int UserPrompt::pause(int mode){
    //Grid *sp = new Grid(h,w);
    int pause = 4;
    bool isTrue = false;
    //makes sure that 
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

/*
void UserPrompt::convertFileInput(){
    cout<<"What is your file path?"<<endl;
    string filePath;
    cin>>filePath;
    
}*/

