#pragma once

#include <vector>
#include <iostream>
#include <string>
#using <ConnectFour2.dll>

using namespace System;
using namespace System::Collections::Generic;

public ref class GameControl {
public:
    ConnectFour2::Program^ program;

    GameControl() {
        program = gcnew ConnectFour2::Program();
        Console::Beep();
    }

};