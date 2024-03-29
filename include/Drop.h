#pragma once

#include <cstdint>

namespace matrix {
    class Drop {
        public:
            Drop(const double speed,
                 const uint8_t length,
                 const uint8_t xPos);

            ~Drop();

            char* getChars();

            uint8_t getX();

            uint8_t getY();

            void increment();

        private:
            const double speed;

            const uint8_t xPos;

            double yPos;

            char* chars;
    };
}
