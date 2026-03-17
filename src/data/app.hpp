/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "preloaded/audio.hpp"
#include "window.hpp"
#include "mouse.hpp"
#include "macroses.hpp"
#include "../cyclesNames.hpp"


// Class of whole current application
class App {
 private:
    // Flags of work
    static bool running;
    static Cycle nextCycle;
    // Shortcut for easier cycle run
    template <typename Cycle>
    static void runCycle(Window& window);

 public:
    // Commands to operate with global running
    static void stop();
    static bool isRunning();
    static void setNextCycle(Cycle nextCycle);
    static Cycle getNextCycle();
    // Start current thread
    static void run(Window& window);
};

template <typename Cycle>
void App::runCycle(Window& _window) {
   // Creating new cycle
   Cycle cycle{_window};
   // Starting it and waiting to finish
   cycle.run();
   // Destroying it
}
