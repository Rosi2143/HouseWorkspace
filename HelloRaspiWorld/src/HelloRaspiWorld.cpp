//============================================================================
// Name        : HelloRaspiWorld.cpp
// Author      : Michael Rossner
// Version     :
// Copyright   : LGPL2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main() {
    int i = 0;
    cout << "Hello RPi Development World !"<< endl;

    cout << "Hello RPI Development World Again !" << endl;

    while(1)
    {
        cout << "I'm in the While loop and the value of variable i is: " << i << endl;
        i++;
        usleep(1000000); //wait for 1 seconds
    }

    return 0;
}
