#include "Drop.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace matrix {
    Drop::Drop(const double speed,
               const uint8_t length,
               const uint8_t xPos) : speed(speed),
                                     xPos(xPos),
                                     yPos(0),
                                     length(length) {
        chars = new char[length];

        for (std::size_t index = 0; index < length; ++index) {
            chars[index] = (std::rand() % 93) + 33;
        }
    }

    Drop::~Drop() {
        delete [] chars;
    }

    char* Drop::getChars() {
        return chars;
    }

    uint8_t Drop::getX() const {
        return xPos;
    }

    uint8_t Drop::getY() const {
        return yPos;
    }

    void Drop::increment() {
        yPos += speed;

        if ((int) yPos != (int) (yPos - speed)) {
            chars[getStartIndex()] = (std::rand() % 93) + 33;
        }
    }

    std::size_t Drop::getStartIndex() const {
        return (std::size_t) yPos % length;
    }

    uint8_t Drop::getLength() const {
        return length;
    }
}
