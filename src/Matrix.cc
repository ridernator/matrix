#include "Matrix.h"
#include "Drop.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ncurses.h>
#include <chrono>
#include <thread>

namespace matrix {
    Matrix::Matrix() {
        std::srand(std::time(nullptr));

        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        nodelay(stdscr, true);
        curs_set(0);

        initColours();

        mainLoop();
    }

    Matrix::~Matrix() {
        endwin();

        for (Drop* drop : drops) {
            delete drop;
        }
    }

    void Matrix::initColours() {
        if (has_colors()) {
            start_color();

            init_pair(DROP_COLOUR,       COLOR_GREEN, COLOR_BLACK);
            init_pair(DROP_START_COLOUR, COLOR_WHITE, COLOR_BLACK);
        }
    }

    void Matrix::mainLoop() {
        auto wakeTime = std::chrono::steady_clock::now() + FRAME_TIME;

        while (true) {
            erase();

            for (Drop* drop : drops) {
                for (uint8_t index = 0; index < drop->getLength(); ++index) {
                    if (drop->getY() >= index) {
                        if (index == 0) {
                            attron(COLOR_PAIR(DROP_START_COLOUR));
                        }

                        mvaddch(drop->getY() - index,
                                drop->getX(),
                                drop->getChars()[drop->getStartIndex() >= index ? drop->getStartIndex() - index :
                                                                                  drop->getLength() - (index - drop->getStartIndex())]);

                        if (index == 0) {
                            attron(COLOR_PAIR(DROP_COLOUR));
                        }
                    } else {
                        break;
                    }
                }

                drop->increment();
            }

            refresh();

            if (getch() == 'q') {
                break;
            }

            drops.erase(std::remove_if(drops.begin(), drops.end(), [] (Drop* drop) {
                if (drop->getY() - drop->getLength() > getmaxy(stdscr)) {
                    delete drop;

                    return true;
                } else {
                    return false;
                }
            }), drops.end());

            while (drops.size() < getmaxx(stdscr) * 0.9) {
                drops.push_back(new Drop(std::rand() / (double) (RAND_MAX / 4),
                                         (std::rand() % getmaxy(stdscr)) + 1,
                                         std::rand() % getmaxx(stdscr)));
            }

            std::this_thread::sleep_until(wakeTime);

            wakeTime += FRAME_TIME;
        }
    }
}

int main() {
    matrix::Matrix matrix;
}
