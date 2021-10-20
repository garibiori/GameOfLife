/**
 * Grid class creates the grid for the user
 * 
 * @author Devin Keller & Ori Garibi
 * @version 1.0
 * @see FileProcessor.cpp
 * 
 */


#include "Grid.h"
#include "FileProcessor.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

//Default constructor
Grid::Grid(int h, int w){
    maxI = h;
    maxJ = w;
    grid = new char*[maxJ];
    for (int i = 0; i < maxI; ++i){
        grid[i] = new char[maxI];
    }
    shadowGrid = new char*[maxJ];
    for (int i = 0; i < maxI; ++i){
        shadowGrid[i] = new char[maxI];
    }
}

//Default Deconstructor
Grid::~Grid(){
    for (int i = 0; i < maxI; ++i){
        delete[] grid[i];
    }
    delete[] grid;
    for (int i = 0; i < maxI; ++i){
        delete[] shadowGrid[i];
    }
    delete[] shadowGrid;
}

//Creates grid for user
void Grid::createGrid(int h, int w, float d, string config, int mode){

    maxI = h;
    maxJ = w;

    //creates random grid for user given height and width
    if(config == "random") {
        int value;
        //number of cells
        int numx=0;
        //population density
        float density = 1/d;
        //rounds the percent the cells need to take  up
        int num = (maxI*maxJ)/density;

        //Loop that goes through each value of the array and determines whether
        //that cell should be alive or dead
        for (int i = 0; i < (maxI); ++i)
        {
            for (int j = 0; j < (maxJ); ++j)
            {
                //picks if there should be a cell in this spece
                value = rand() %2; 

                //if 1 adds new cell and add 1 to num cells if alive
                if(value == 1){
                    grid[i][j] = 'X';
                    numx+=1; 
                }
                //else if 0 then we set the cell to empty
                else if(value == 0){
                    grid[i][j] = '-';
                }
            }
        }

        //if there is more x's than we should delete other x's in grid
        if (numx>num){
            while(numx!=num){
                int row = rand() %(maxI-1);
                int coll = rand() %(maxJ-1);
                if(grid[row][coll]== 'X'){
                    grid[row][coll] = '-';
                    numx-=1;
                }
            }
                

        }
        //If the number of x's are less than the number of x's we need 
        //then we should be creating x's at random locations
        else if(numx<num){
            while(numx!=num){
                int row = rand() %(maxI-1);
                int coll = rand() %(maxJ-1);
                if(grid[row][coll]== '-'){
                    grid[row][coll] = 'X';
                    numx+=1;
                    
                }
            }

        }
        else{
            //the amounts of cells match the density
        }

    }
}

//Pauses takes in userChoice and mode and runs game simulation
void Grid::pauses(int userChoice, int mode){
    //Sets shadowGrid = grid
    for(int i = 0; i<maxI; ++i){
        for (int j = 0; j<maxJ; ++j){
            shadowGrid[i][j] = grid[i][j];
        }
    }

    FileProcessor *sp = new FileProcessor;
    string fileOut;
    int counter = 0;
    //if choice is = 1 then there is a brief pauses between the program running
    if (userChoice == 1){
        drawGrid(maxI,maxJ);
        //while changes made are greater than 1
        while(changes != 0){
            changes = 0;
            //Makes program pause
            cout.flush();
            sleep(1);
            //Makes every cell check its surroundings
            for(int i = 0; i<maxI; ++i){
                for (int j = 0; j<maxJ; ++j){
                    checkSurroundings(i,j, maxI, maxJ,mode);
                    
                }
            }
            
            grid = shadowGrid;
            drawShadowGrid(maxI,maxJ);
            cout<<endl;
        }
        //If there are no new changes made to the file
        if(changes == 0){
            cout<<"Your world has come to an end. Press enter to finish."<<endl;
            cin.get();
            //Press enter one more time to end program
            if(cin.get()=='\n'){
                cout<<"Goodbye"<<endl;
            }
        }
    }
    //if user choice is 2 the programs runs every time they hit enter
    if(userChoice == 2){
        drawGrid(maxI,maxJ);
        //while user hits enter program runs again
        while(cin.get() == '\n' && changes != 0){
            changes = 0;
            //runs through every cell
            for(int i = 0; i<maxI; ++i){
                for (int j = 0; j<maxJ; ++j){
                    //runs check surrondings code
                    checkSurroundings(i,j, maxI, maxJ, mode);
                }
            }
            drawShadowGrid(maxI,maxJ);
            
            grid = shadowGrid;
            if (changes == 0){
                break;
            }

        }
        if(changes == 0){
            cout<<"Your world has come to an end. Press enter to finish."<<endl;
            
            if(cin.get()=='\n'){
                cout<<"Goodbye"<<endl;
            }
        }
    }

    //if userChoice is = to 3 then keep running and keep running the program until it outputs
    // the grid to console
    if(userChoice == 3){
        
        while(changes != 0){
            //changes represents how many changes were made to the graph
            changes = 0;

            //goes through every cell
            for(int i = 0; i<maxI; ++i){
                for (int j = 0; j<maxJ; ++j){
                    //Runs checkSurroundings function
                    checkSurroundings(i,j, maxI, maxJ,mode);
                    
                }
            }

            //sets grid = to shadow grid
            grid = shadowGrid;

        }
        //If there are no changes get then program prepares to send graph
        if(changes == 0){
            string outputFile;

            cout<<"What file would you like to print this generation to?"<<endl;
            //takes in name of file
            cin>>outputFile;
            //runs through every cell and adds to new file
            for(int i = 0; i<maxI; ++i){ //this code turns the grid into a string
                for (int j = 0; j<maxJ; ++j){
                    fileOut += grid[i][j];
                    if (j == maxJ-1){
                        fileOut+= '\n';
                    }
                }
            }
            cout<<"Your world has come to an end. Press enter to finish."<<endl;
            cin.get();
            if(cin.get()=='\n'){
                //outputs file
                sp->outputFile(fileOut, outputFile);
                cout<<"Goodbye"<<endl;
            }
        }
        
    }
}

//Checks cell's surrondings
int Grid::checkSurroundings(int i, int j, int maxI, int maxJ,int mode){
    int neighbors = 0;
    //Checks top

     //CORNERS
    //TOP BOTTOM RIGHT CORNER
    if(mode==3){
        if ((i==maxI-1 && j == maxJ-1 && mode ==3)){
        if ((grid[i][j]) == 'X'){
                //cout << "Neighbors: Detected bottom RIGHT CORNER (mirror)" <<endl;
                neighbors += 3;
            }

    }
    //TOP RIGHT CORNER
    if ((i==0 && j == maxJ-1)&&mode==3){
        if ((grid[i][j]) == 'X'){
                //cout << "Neighbors: Detected top RIGHT CORNER(mirror)" <<endl;
                neighbors += 3;
            }

    }

    //TOP BOTTOM LEFt CORNER
    if ((i==maxI-1 && j == 0)&&mode==3){
        if ((grid[i][j]) == 'X'){
                //cout << "Neighbors: Detected bottom left CORNER(mirror)" <<endl;
                neighbors += 3;
            }
    }

    //TOP LEFt CORNER
    if ((i==0 && j == 0)&&mode==3){
        if ((grid[i][j]) == 'X'){
                //cout << "Neighbors: Detected top left CORNER(mirror)" <<endl;
                neighbors += 3;
            }
    }


    //TOP LEFT
    if ((i==maxI-1 && j == maxJ-1)&&mode==3){
        if ((grid[i][j-1]) == 'X'){
                //cout << "Neighbors: Detected top left (mirror)" <<endl;
                neighbors += 1;
            }

    }
    //TOP ROW MIRROR MODE
    if (i==0 && mode == 3){
        //cout << "Mirror mode" << endl;
        //TOP LEFT MIRROR
        if (j!=0){
            //cout << "J is not = 0" << endl;
            if ((grid[i][j-1]) == 'X'&&j!=0&&j!=maxJ-1){
                //cout << "Neighbors: Detected top left (mirror)" <<endl;
                neighbors += 1;
            }
        }
        //TOP MIRROR
        if ((grid[i][j] == 'X') && j!= maxJ-1 && j!=0){
            //cout << "Neighbors: Detected top (Mirror)" <<endl;
            neighbors += 1;
        }
        //TOP RIGHT MIRROR
        if (j!= maxJ-1){
            //cout << "J is not = 0" << endl;
            if ((grid[i][j+1]) == 'X'){
                //cout << "Neighbors: Detected top right (mirror)" <<endl;
                neighbors += 1;
            }
        }
        //TOP LEFT CORNER MIRROR MODE
        if (j==0){
            //cout << "J is not = 0" << endl;
            //cout << "TOP LEFT CORNER MIRROR" << endl;
            if ((grid[i][j-1]) == 'X'){
                //cout << "Neighbors: Detected top left and left (mirror)" <<endl;
                neighbors += 3;
            }
        }

    }
    //CHECKING BOTTOM ROW MIRROR
    if (i==maxI-1 && mode == 3){
        //CHECKING BOTTOM MIRROR
        if ((grid[i][j] == 'X') && j!=0 && j!= maxJ-1){
            //cout << "Neighbors: Detected bottom (Mirror)" <<endl;
            neighbors += 1;
        }
        //CHECKING BOTTOM LEFT MIRROR
        if (j!=0){
            //cout << "J is not = 0" << endl;
            if ((grid[i][j-1]) == 'X'){
                //cout << "Neighbors: Detected bottom left (mirror)" <<endl;
                neighbors += 1;
            }

        }
        //CHECKING BOTTOM RIGHT MIRROR
        if (j!=maxJ-1){
            //cout << "J is not = 0" << endl;
            if ((grid[i][j+1]) == 'X'){
                //cout << "Neighbors: Detected bottom left (mirror)" <<endl;
                neighbors += 1;
            }

        }


    }

    //MIRROR MODE LEFT
    if (j==0 && mode == 3){
        if ((grid[i][j] == 'X') && i!= maxI-1 && i!=0){
            //cout << "Neighbor Detected Left (Mirror)" <<endl;
            neighbors += 1;
        }
        if (i!= 0){
            if ((grid[i-1][j]) == 'X'){
                //cout << "Neighbor Detected left Top Left (Mirror)" <<endl;
                neighbors += 1;
            }
        }
        if (i!= maxI-1){
            if ((grid[i+1][j]) == 'X'){
                //cout << "Neighbor Detected Left bottom left(Mirror)" <<endl;
                neighbors += 1;
            }
        }
        
    }

    //MIRROR MODE RIGHT
    if (j== maxJ&& mode == 3){
        if ((grid[i][j] == 'X') && i!= maxI-1){
            //cout << "Neighbor Detected Right (Mirror)" <<endl;
            neighbors += 1;
        }
        if (i!= 0){
            if ((grid[i+1][j]) == 'X'){
                //cout << "Neighbor Detected right Top right (Mirror)" <<endl;
                neighbors += 1;
            }
        }
        if (i!= maxI-1){
            if ((grid[i-1][j]) == 'X'){
                //cout << "Neighbor Detected Right bottom right(Mirror)" <<endl;
                neighbors += 1;
            }
        }
        
    }
    }



    // Doughnut Mode
       //corners 
    if(i == 0 && j == 0 && mode == 2){ //checks position and mode
        if(grid[maxI-1][maxJ-1] == 'X'){
            neighbors+= 1; //counts neighbors
        }
        if(grid[maxI-1][0] == 'X'){
            neighbors+= 1;

        }
        if(grid[0][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[i+1][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[maxI-1][j+1] == 'X'){
            neighbors+= 1;
        }

    }

    if(i == 0 && j == maxJ-1 && mode == 2){
        if(grid[maxI-1][0] == 'X'){
            neighbors+= 1;
        }
        if(grid[maxI-1][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[maxI-1][j-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[0][0] == 'X'){
            neighbors+= 1;
        }
        if(grid[i+1][0] == 'X'){
            neighbors+= 1;
        }

    }
    if(i == maxI-1 && j == maxJ-1 && mode == 2){
        if(grid[0][0] == 'X'){
            neighbors+= 1;
        }
        if(grid[0][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[0][j-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[maxI-1][0] == 'X'){
            neighbors+= 1;
        }
        if(grid[i-1][0] == 'X'){
            neighbors+= 1;
        }
    }


    if(i == maxI-1 && j == 0 && mode == 2){
        if(grid[0][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[0][0] == 'X'){
            neighbors+= 1;
        }
        if(grid[0][j+1] == 'X'){
            neighbors+= 1;
        }
        if(grid[maxI-1][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[i-1][maxJ-1] == 'X'){
            neighbors+= 1;
        }
    }
//Program for the sides that are not corners
    if(i == 0 && j != 0 &&j!=maxJ-1 && mode == 2){
        if(grid[maxI-1][j] == 'X'){
            neighbors+= 1;
        }
        if(grid[maxI-1][j+1] == 'X'){
            neighbors+= 1;
        }
        if(grid[maxI-1][j-1] == 'X'){
            neighbors+= 1;
        }
    }

    if(i == maxI-1 && j != 0 &&j!=maxJ-1 && mode == 2){
        if(grid[0][j] == 'X'){
            neighbors+= 1;
        }
        if(grid[0][j+1] == 'X'){
            neighbors+= 1;
        }
        if(grid[0][j-1] == 'X'){
            neighbors+= 1;
        }
    }

    if(i != maxI-1 && i != 0 &&j==0 && mode == 2){
        if(grid[i][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[i-1][maxJ-1] == 'X'){
            neighbors+= 1;
        }
        if(grid[i+1][maxJ-1] == 'X'){
            neighbors+= 1;
        }
    }

    if(i != maxI-1 && i != 0 &&j==maxJ-1 && mode == 2){
        if(grid[i][0] == 'X'){
            neighbors+= 1;
        }
        if(grid[i-1][0] == 'X'){
            neighbors+= 1;
        }
        if(grid[i+1][0] == 'X'){
            neighbors+= 1;
        }
    }

    

    //Regular checking
    if (i != 0 && j!=0){
        if (((grid[i-1][j-1]) == 'X')&& i!=0 && j!=0){
            //cout << "Neighbors: Detected top left" <<endl;
            neighbors += 1;
        }
    }
    if (j != (maxJ-1) && i !=0){
        if (((grid[i-1][j+1]) == 'X')&& i!=0){
            //cout << "Neighbors: Detected top right" <<endl;
            neighbors += 1;
        }
    }
    if(j != (maxJ-1) && i != (maxI-1)){
        if ((grid[i+1][j+1]) == 'X'){
            //cout << "Neighbors: Detected bottom right" <<endl;
            neighbors += 1;
        };
    }
    if(j!=0){
        if (((grid[i][j-1]) == 'X')&& j!=0){
            //cout << "Neighbors: Detected left" <<endl;
            neighbors += 1;
        }
    }
    if (i!=0){
        if (((grid[i-1][j]) == 'X')){
            //cout << "Neighbors: Detected top" <<endl;
            neighbors += 1;
        }
    }
    if (i!=maxI-1){
        if (((grid[i+1][j]) == 'X')){
            //cout << "Neighbors: Detected bottom" <<endl;
            neighbors += 1;
        }
    }
    
    if (i != (maxI-1) && j!=0){
        if (((grid[i+1][j-1]) == 'X')&& j!=0){
            //cout << "Neighbors: Detected bottom left" <<endl;
            neighbors += 1;
        }
    }

    if (j != (maxJ-1)){
        if ((grid[i][j+1]) == 'X'){
        //cout << "Neighbors: Detected right" <<endl;
        neighbors += 1;
        }
    }
        
    //removesCell if neighbors = 0
    if (neighbors==0){
        removeCell(i,j);
    }
    //removeCells if neighbors less than or = to 1
    if (neighbors <= 1 )
    {
        if (neighbors == 1)
            {
                //cout << "I should die"<<endl;
                removeCell(i,j);
                
            }
        else
            {
                //cout << "I'm chilling" << endl;
                removeCell(i,j);
            }
    }

    //if neighbors = 3 add a cell
    else if (neighbors == 3){
        //cout << "I'm Alive: Add cell"<<endl;
        //fuction to add cell
        addCell(i, j);
    }
    //if neighbors is greater than 4 delete Cell
    else if (neighbors >= 4){    
        //cout << "Empty due to over crowding" <<endl;
        //Deletes cell
        removeCell(i,j);
    }

    //cout << "I am cell " << i << j << "and I have Neighbors: "<< neighbors <<endl;


    return neighbors;
}

//Add a cell to shadowGrid
int Grid::addCell(int i, int j){
    //cout << "Added Cell in " << i << ',' << j << endl;
    //if shadowGrid = - then its now = to x and changes adds 1
    if(shadowGrid[i][j] == '-'){
        shadowGrid[i][j] = 'X';
        changes +=1;
    }

    return 0;
}


//Creation of method to remove cell from shadow grid
int Grid::removeCell(int i, int j){
    //cout << "Remove Cell in " << i << ',' << j << endl;

    //If there is a cell in that spot remove cell from shadow grid and add +1 to changes
    if(shadowGrid[i][j] == 'X'){
        shadowGrid[i][j] = '-';
        changes +=1;
    }

    return 0;
}

//Draw grid 
int Grid::drawGrid(int maxI, int maxJ){
    for(int i = 0; i<maxI; ++i){
        for (int j = 0; j<maxJ; ++j){
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl<< endl;
    return 0;
}

//Draw shadow grid 
int Grid::drawShadowGrid(int maxI, int maxJ){
    for(int i = 0; i<maxI; ++i){
        for (int j = 0; j<maxJ; ++j){
            cout << shadowGrid[i][j];
        }
        cout << endl;
    }
    return 0;
}

//buildFileArray makes the 2d array  = to the array we got from 
// the user's file 
void Grid::buildFileArray(string file){
    int line = 0; //checks position of file string
    //go through array and sets the value cell = to what user inputted
    for(int i = 0; i<maxI;++i){
        for(int j = 0; j<maxJ;++j){
            grid[i][j] = file[line];
            line+=1;
            if(j==maxJ-1){
                line+=1;
            }

        }
    }
}

