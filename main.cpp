
/**
 * main file, where are main method lives
 * 
 * @author Devin Keller & Ori Garibi
 * @version 1.0
 * @see main.cpp
 * 
 */
#include "UserPrompt.h"

int main()
{
    UserPrompt *mp = new UserPrompt;

    mp->gameMode();


    delete mp;
    return 0;
}