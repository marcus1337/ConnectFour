#pragma once

#include <string>
#include <vector>
#include "Image.h"
#include "Button.h"
#include "ShapeHandler.h"
#include "MiscInfo.h"

#include <vcclr.h>
#using <ConnectFour.dll>

public class GameControl {
public:

    gcroot<ConnectFour::Controller^> game;
    MiscInfo miscInfo;

    GameControl();

    void tryPlace(int column);

    Image getButtonImageAtBoardPosition(SDL_Renderer* renderer, ShapeHandler& shapeHandler, int i, int j,
        ConnectFour::Model::COLOR color);
    std::vector<Image> getPlacedBricksImages(SDL_Renderer* renderer, ShapeHandler& shapeHandler);
    Image getLastBrick(SDL_Renderer* renderer, ShapeHandler& shapeHandler);

    void setButtonDimensions(int _minX, int _minY, int _btnWidth, int _btnHeight);
    void setGameControllerDimensions(std::vector<Button>& tmpButtons);

private:
    int btnWidth;
    int btnHeight;
    int minX;
    int minY;

    void sortGameButtons(std::vector<Button>& tmpButtons);

};