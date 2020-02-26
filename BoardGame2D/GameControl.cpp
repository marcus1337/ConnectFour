#include "GameControl.h"

#include "IOStuff.h"
#include "EnumManager.h"
#include <algorithm>
#include <iostream>
#include "Utils.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace std;



GameControl::GameControl() {
    game = gcnew ConnectFour::Controller();
    tickLastPlacement = 0;
    passedTurns = 0;
    lastTurnAnimated = -1;
}

void GameControl::tryPlace(int column) {
    bool moveOK = game->tryPlace(game->getModel()->currentPlayer, column);
    if (moveOK && lastTurnAnimated != passedTurns) {
        tickLastPlacement = miscInfo.ticks;
        lastTurnAnimated++;
    }
    if (moveOK && !game->getModel()->isGameOver()) {
        game->getModel()->nextTurn();
        passedTurns++;
    }
}

int GameControl::getAnimatedBrickYPos() {
    int brickYIndex = game->getModel()->lastBrickPos->Item2;
    int brickYPosFinal = minY - brickYIndex * btnHeight;
    int brickYPosStart = minY - 6.5f * btnHeight;

    uint64_t passedTicks = miscInfo.ticks - tickLastPlacement+1;
    uint64_t maxTicksPerSquare = maxPlaceAnimationTicks / 6;
    uint64_t maxTicksForYPosition = maxTicksPerSquare * (7 - (brickYIndex+1));
    double t = (double) passedTicks / maxTicksForYPosition;
    t = std::clamp(t, 0.0, 1.0);
    double interPolatedY = Utils::lerp<double>(brickYPosStart, brickYPosFinal, t);

    return (int)interPolatedY;
}

bool GameControl::doneAnimatingBrickDrop() {
    if (tickLastPlacement == 0)
        return true;

    int brickYIndex = game->getModel()->lastBrickPos->Item2;
    uint64_t passedTicks = miscInfo.ticks - tickLastPlacement + 1;
    uint64_t maxTicksPerSquare = maxPlaceAnimationTicks / 6;
    uint64_t maxTicksForYPosition = maxTicksPerSquare * (7 - (brickYIndex + 1));
    return passedTicks > maxTicksForYPosition;
}

Image GameControl::getButtonImageAtBoardPosition(SDL_Renderer* renderer, ShapeHandler& shapeHandler, int i, int j,
    ConnectFour::Model::COLOR color) {
    Image img;
    if (color == ConnectFour::Model::COLOR::RED)
        img.texture = shapeHandler.getImageTexture(renderer, "red_chip.png");
    if (color == ConnectFour::Model::COLOR::BLUE)
        img.texture = shapeHandler.getImageTexture(renderer, "yellow_chip.png");
    img.setWH(btnWidth, btnHeight);
    img.setXY(i*btnWidth + minX, minY - j * btnHeight);
    return img;
}

std::vector<Image> GameControl::getPlacedBricksImages(SDL_Renderer* renderer, ShapeHandler& shapeHandler) {
    std::vector<Image> placedBricks;
    auto boardColors = game->getModel()->getBoardColors();
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            if ((int)boardColors[i, j] > 0 && !isLatestBrick(i,j)) {
                Image img = getButtonImageAtBoardPosition(renderer, shapeHandler, i, j, boardColors[i, j]);
                placedBricks.push_back(img);
            }
        }
    }
    return placedBricks;
}

Image GameControl::getLastBrick(SDL_Renderer* renderer, ShapeHandler& shapeHandler) {

    Image img;
    img.texture = shapeHandler.button1;
    auto boardColors = game->getModel()->getBoardColors();

    if (game->getModel()->numBricksPlaced > 0) {
        auto lastPos = game->getModel()->lastBrickPos;
        int i = lastPos->Item1;
        int j = lastPos->Item2;
        img = getButtonImageAtBoardPosition(renderer, shapeHandler, i, j, boardColors[i, j]);
        img.setY(getAnimatedBrickYPos());
    }

    return img;
}

void GameControl::setButtonDimensions(int _minX, int _minY, int _btnWidth, int _btnHeight) {
    minX = _minX;
    minY = _minY;
    btnWidth = _btnWidth;
    btnHeight = _btnHeight;
}

void GameControl::setGameControllerDimensions(std::vector<Button>& tmpButtons) {
    sortGameButtons(tmpButtons);
    if (!tmpButtons.empty()) {
        setButtonDimensions(tmpButtons[0].getX(), tmpButtons[0].getY(),
            tmpButtons[0].getW(), tmpButtons[0].getH());
    }
}

void GameControl::sortGameButtons(std::vector<Button>& tmpButtons) {
    auto gameBrickSortFunction = [](const Button& a, const Button& b)
    {
        return (a.getX() == b.getX() ? a.getY() > b.getY() : a.getX() < b.getX());
    };
    std::sort(tmpButtons.begin(), tmpButtons.end(), gameBrickSortFunction);
}

bool GameControl::isLatestBrick(int i, int j) {
    if (tickLastPlacement == 0)
        return false;
    int brickXIndex = game->getModel()->lastBrickPos->Item1;
    int brickYIndex = game->getModel()->lastBrickPos->Item2;
    return i == brickXIndex && j == brickYIndex;
}