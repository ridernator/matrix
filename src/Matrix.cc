#include "Matrix.h"
#include "Drop.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
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
            for (Drop* drop : drops) {
                char* chars = drop->getChars();

                for (int index = 0; index < (int) strlen(chars); ++index) {
                    if (index == 1) {
                    }

                    if (drop->getY() - index >= 0) {
                        if (index == 0) {
                            attron(COLOR_PAIR(DROP_START_COLOUR));
                        }

                        mvaddch(drop->getY() - index, drop->getX(), chars[index]);

                        if (index == 0) {
                            attron(COLOR_PAIR(DROP_COLOUR));
                        }
                    } else {
                        break;
                    }
                }

                mvaddch(drop->getY() - (int) strlen(chars), drop->getX(), ' ');
            }

            refresh();

            if (getch() == 'q') {
                break;
            }

            drops.erase(std::remove_if(drops.begin(), drops.end(), [] (Drop* drop) {
                drop->increment();

                if (drop->getY() - (int) strlen(drop->getChars()) > getmaxy(stdscr)) {
                    delete drop;

                    return true;
                } else {
                    return false;
                }
            }), drops.end());

            if (drops.size() < getmaxx(stdscr) * 0.75) {
                drops.push_back(new Drop(((std::rand() * 0.8) / (double) RAND_MAX) + 0.2,
                                         std::rand() % 100,
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
