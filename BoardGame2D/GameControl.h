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
    uint64_t tickLastPlacement;
    const uint64_t maxPlaceAnimationTicks = 70;

    GameControl();

    void tryPlace(int column);

    bool doneAnimatingBrickDrop();

    Image getButtonImageAtBoardPosition(SDL_Renderer* renderer, ShapeHandler& shapeHandler, int i, int j,
        ConnectFour::Model::COLOR color);
    std::vector<Image> getPlacedBricksImages(SDL_Renderer* renderer, ShapeHandler& shapeHandler);
    Image getLastBrick(SDL_Renderer* renderer, ShapeHandler& shapeHandler);

    void setButtonDimensions(int _minX, int _minY, int _btnWidth, int _btnHeight);
    void setGameControllerDimensions(std::vector<Button>& tmpButtons);

    bool isLatestBrick(int i, int j);

    void newGame();

private:
    int btnWidth;
    int btnHeight;
    int minX;
    int minY;
    int passedTurns, lastTurnAnimated;

    void sortGameButtons(std::vector<Button>& tmpButtons);
    int getAnimatedBrickYPos();

};