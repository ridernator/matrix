#pragma once

#include <cstddef>
#include <cstdint>

namespace matrix {
    class Drop {
        public:
            Drop(const double speed,
                 const uint8_t length,
                 const uint8_t xPos);

            ~Drop();

            char* getChars();

            uint8_t getX() const;

            uint8_t getY() const;

            void increment();

            std::size_t getStartIndex() const;

            uint8_t getLength() const;

        private:
            const double speed;

            const uint8_t xPos;

            double yPos;

            char* chars;

            const uint8_t length;
    };
}
