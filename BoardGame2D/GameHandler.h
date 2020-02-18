#pragma once
#include "SDL.h"
#include <chrono>
#include "Window.h"
#include "InputManager.h"
#include "ShapeHandler.h"

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

    GameHandler() : ticks(0), shapeHandler(IOStuff::getexepath()) {
        shapeHandler.init(window.renderer);
        window.changePage(new MainMenu(shapeHandler, iostuff));
    }

    bool isUpdated() {
        using namespace std::chrono;
        bool anUpdate = false;
        auto current = steady_clock::now();
        Uint64 diff = duration_cast<microseconds>(current - previous).count();
        previous = current;
        lag += diff;
        while (lag >= MS_FRAME) {
            lag -= MS_FRAME;
            ticks++;
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

            if (isUpdated()) {
                window.page->updateContent(getMiscInfo(), inputManager);
                drawEverything();
            }
            SDL_Delay(1);
        }
    }

};