#pragma once
#include "SDL.h"
#include <chrono>
#include "Window.h"
#include "InputManager.h"
#include "ShapeHandler.h"

#include <iostream>

class GameHandler {
public:

    const Uint64 MS_FRAME = 15000;
    Uint64 lag;
    uint64_t ticks;
    std::chrono::steady_clock::time_point previous;
    Window window;
    InputManager inputManager;
    ShapeHandler shapeHandler;
    IOStuff iostuff;

    PageState pageState;

    GameHandler() : ticks(0), shapeHandler(IOStuff::getexepath()), pageState(PageState::MAINMENU) {
        shapeHandler.init(window.renderer);
        window.changePage(new MainMenu(shapeHandler, iostuff), getMiscInfo());
    }

    void addLagTime() {
        using namespace std::chrono;
        auto current = steady_clock::now();
        Uint64 diff = duration_cast<microseconds>(current - previous).count();
        previous = current;
        lag += diff;
        if (lag > MS_FRAME * 300)
            lag = 0;
    }

    void handlePageChange(PageState _newPageState) {
        if (_newPageState) {
            if (_newPageState == PageState::MAINMENU)
                window.changePage(new MainMenu(shapeHandler, iostuff), getMiscInfo());
        }
    }

    void gameTick() {
        auto _newPageState = window.page->process(getMiscInfo(), inputManager);
        handlePageChange(_newPageState);
        inputManager.resetStates();
        lag -= MS_FRAME;
        ticks++;
    }

    bool updateGameIfTime() {
        bool anUpdate = false;
        addLagTime();
        while (lag >= MS_FRAME) {
            gameTick();
            anUpdate = true;
        }
        return anUpdate;
    }

    void drawEverything() {
        window.page->draw(window.renderer);
        SDL_RenderPresent(window.renderer);
    }

    MiscInfo getMiscInfo() {
        MiscInfo miscinfo;
        miscinfo.ticks = ticks;
        SDL_GetWindowSize(window.window, &miscinfo.windowWidth, &miscinfo.windowHeight);
        return miscinfo;
    }

    void loopUntilQuit() {
        while (!inputManager.shutdownGame) {
            inputManager.processInput();

            if (updateGameIfTime()) {
                window.page->updateContent(getMiscInfo(), inputManager, window.renderer);
                drawEverything();
            }
            SDL_Delay(1);
        }
    }

};