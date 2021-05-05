#include "application.h"

#include <sstream>
#include <stdexcept>

AbstractApplication::AbstractApplication(int screen_width, int screen_height)
    : screen_width_(screen_width), screen_height_(screen_height) {
    Init();
}

AbstractApplication::~AbstractApplication() {
    delwin(screen_);
    delwin(top_line_);
    delwin(bottom_line_);
    endwin();
}

void AbstractApplication::Run() {
    RunLoop();
}

void AbstractApplication::Init() {
    InitCurses();
    InitInput();
    InitOutput();
    InitScreen();
    InitLines();
}

void AbstractApplication::InitCurses() {
    CheckPointer(initscr(), "initscr");
    CheckError(curs_set(0), "curs_set");
    CheckError(refresh(), "refresh");
}

void AbstractApplication::InitInput() {
    CheckError(noecho(), "noecho");
    CheckError(keypad(stdscr, true), "keypad");
    CheckError(cbreak(), "cbreak");
}

void AbstractApplication::InitOutput() {
    setlocale(LC_ALL, "");
    CheckError(use_default_colors(), "use_default_colors");
}

void AbstractApplication::InitScreen() {
    if (screen_) {
        delwin(screen_);
    }

    if (LINES < 6 || COLS < 6) {
        throw std::runtime_error("terminal too small");
    }

    if (screen_width_ == 0) {
        screen_width_ = COLS - 4;
    }
    if (screen_height_ == 0) {
        screen_height_ = LINES - 4;
    }

    if (screen_height_ + 2 > LINES || screen_width_ + 2 > COLS) {
        std::stringstream error;
        error << "window too large " << screen_width_ << "x" << screen_height_
              << " while terminal is only " << COLS << 'x' << LINES;
        throw std::runtime_error(error.str());
    }

    int screen_pos_y = (LINES - screen_height_) / 2 - 1;
    int screen_pos_x = (COLS - screen_width_) / 2 - 1;
    screen_ = newwin(screen_height_ + 2, screen_width_ + 2, screen_pos_y, screen_pos_x);
    CheckPointer(screen_, "newwin");

    CheckError(box(screen_, 0, 0), "box");
    CheckError(wrefresh(screen_), "wrefresh");
}

void AbstractApplication::InitLines() {
    int top_line_pos_y = (LINES - screen_height_) / 2 - 2;
    int bottom_line_pos_y = top_line_pos_y + screen_height_ + 3;
    int lines_pos_x = (COLS - screen_width_) / 2 - 1;

    if (bottom_line_) {
        delwin(bottom_line_);
    }
    bottom_line_ = newwin(1, screen_width_ + 2, bottom_line_pos_y, lines_pos_x);
    CheckPointer(bottom_line_, "newwin");

    if (top_line_) {
        delwin(top_line_);
    }
    top_line_ = newwin(1, screen_width_ + 2, top_line_pos_y, lines_pos_x);
    CheckPointer(top_line_, "newwin");
}

void AbstractApplication::RunLoop() {
    do {
        CheckError(wrefresh(screen_), "wrefresh");

        int key = getch();
        CheckError(key, "getch");

        if (key == KEY_RESIZE) {
            HandleResize();
            continue;
        }

        UpdateState(key);
        DrawFrame();
    } while (true);
}

void AbstractApplication::ClearScreen() {
    CheckError(werase(screen_), "werase");
    CheckError(box(screen_, 0, 0), "box");
}

void AbstractApplication::ClearLine(WINDOW *line) {
    CheckError(werase(line), "werase");
}

void AbstractApplication::ClearCell(int y, int x) {
    CheckError(mvwaddch(screen_, y + 1, x + 1, ' '), "mvwaddch");
}

void AbstractApplication::SetCell(int y, int x, wchar_t character) {
    if (x >= 0 && y >= 0 && x < screen_width_ && y < screen_height_) {
        cchar_t curses_char;
        CheckError(setcchar(&curses_char, &character, {}, 0, nullptr), "setchar");
        CheckError(mvwadd_wch(screen_, y + 1, x + 1, &curses_char), "mvwadd_wch");
    }
}

void AbstractApplication::WriteMessage(WINDOW *line, const std::string &message) {
    ClearLine(line);
    CheckError(mvwaddstr(line, 0, 0, message.c_str()), "waddstr");
    CheckError(wrefresh(line), "wrefresh");
}

void AbstractApplication::CheckError(int err_code, const std::string &name) {
    if (err_code == ERR) {
        throw std::runtime_error(name + " call failed");
    }
}

void AbstractApplication::CheckPointer(void *ptr, const std::string &name) {
    if (!ptr) {
        throw std::runtime_error(name + " call failed");
    }
}

void AbstractApplication::HandleResize() {
    if (screen_height_ + 2 > LINES) {
        screen_height_ = LINES - 2;
    }
    if (screen_width_ + 2 > COLS) {
        screen_width_ = COLS - 2;
    }
    InitScreen();
    InitLines();
    CheckError(erase(), "erase");
}
