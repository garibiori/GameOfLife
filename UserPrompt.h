#include <iostream>

using namespace std;

class UserPrompt{

public:
    UserPrompt();
    ~UserPrompt();
    string configuration();
    void gameMode();
    int pause(int mode);
    



private:
    string config;
    int h;
    int w;
    float d;
    int mode;
    string filePath;
    string fileInput;

};