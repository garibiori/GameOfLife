#include <iostream>

using namespace std;

class Grid{

public:
    Grid(int x, int y);
    ~Grid();
    void createGrid(int a, int b, float c, string config, int mode);
    char** grid;
    char** shadowGrid;
    void pauses(int input, int mode);
    int checkSurroundings(int j, int k, int maxI, int maxJ, int mode);
    int addCell(int i, int j);
    int removeCell(int i, int j);
    int drawGrid(int h, int w);
    int drawShadowGrid(int h, int w);
    void buildFileArray(string file);

private:
    int maxI;
    int maxJ;
    int changes=1;

};