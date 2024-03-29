#include "Drop.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace matrix {
    Drop::Drop(const double speed,
               const uint8_t length,
               const uint8_t xPos) : speed(speed),
                                     xPos(xPos),
                                     yPos(0) {
        chars = new char[length + 1];

        for (std::size_t index = 0; index < length; ++index) {
            chars[index] = (rand() % 93) + 33;
        }

        chars[length] = 0;
    }

    Drop::~Drop() {
        delete [] chars;
    }

    char* Drop::getChars() {
        return chars;
    }

    uint8_t Drop::getX() {
        return xPos;
    }

    uint8_t Drop::getY() {
        return yPos;
    }

    void Drop::increment() {
        yPos += speed;
    }
}
