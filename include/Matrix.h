#pragma once

#include "Drop.h"

#include <chrono>
#include <cstdint>
#include <vector>

namespace matrix {
    class Matrix {
        public:
            Matrix();
            ~Matrix();

        private:
            static const int DROP_COLOUR = 1;
            static const int DROP_START_COLOUR = 2;

            static constexpr uint32_t FPS = 30;

            static constexpr std::chrono::microseconds FRAME_TIME = std::chrono::microseconds(1000000 / FPS);

            std::vector<Drop*> drops;

            void initColours();

            void mainLoop();

            void drawDrops();
    };
}
