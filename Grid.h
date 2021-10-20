#include <iostream>

using namespace std;

class Grid{

public:
    Grid(int x, int y);
    ~Grid();
    void createGrid(int a, int b, float c, string config, int mode);
    //string pauses(char** input);
    char** grid;
    char** shadowGrid;
    void simulation(int input, int mode);
    int checkSurroundings(int j, int k, int maxI, int maxJ, int mode);
    int addCell(int i, int j);
    int removeCell(int i, int j);
    int drawGrid(int h, int w);
    int drawShadowGrid(int h, int w);
    void buildFileArray(string file);

private:
    //char grid[][];
    //char** grid;
    int maxI;
    int maxJ;
    //char grid[maxI][maxJ];
    int changes=1;

};