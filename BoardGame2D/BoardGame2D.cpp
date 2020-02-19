#include <stdlib.h>
#include "EnumManager.h"
#include "IOstuff.h"

#include "SDL.h"
#include <iostream>
#include "GameHandler.h"

//#using <ConnectFour2.dll>
using namespace std;

int main(int argc, char *argv[])
{

    GameHandler gameHandler;
    gameHandler.loopUntilQuit();

    std::cout << "Hello World!\n";

    return 0;
}

