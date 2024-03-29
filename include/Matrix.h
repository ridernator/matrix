#pragma once

#include "Drop.h"

#include <vector>

namespace matrix {
    class Matrix {
        public:
            Matrix();
            ~Matrix();

        private:
            static const int DROP_COLOUR = 1;
            static const int DROP_START_COLOUR = 2;

            std::vector<Drop*> drops;

            void initColours();

            void mainLoop();

            void drawDrops();
    };
}
