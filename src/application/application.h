#pragma once

#include <ncurses.h>

#include <string>

class AbstractApplication {
public:
    AbstractApplication(int screen_width = 0, int screen_height = 0);
    virtual ~AbstractApplication();

    void Run();

protected:
    virtual void Init();

    virtual void UpdateState(int key) = 0;
    virtual void DrawFrame() = 0;

    virtual void HandleResize();

protected:
    void ClearScreen();
    void ClearLine(WINDOW *line);
    void ClearCell(int y, int x);
    void SetCell(int y, int x, wchar_t character);
    void WriteMessage(WINDOW *line, const std::string &message);

    void CheckError(int err_code, const std::string &name);
    void CheckPointer(void *ptr, const std::string &name);

protected:
    WINDOW *screen_;
    WINDOW *bottom_line_;
    WINDOW *top_line_;
    int screen_width_ = 0;
    int screen_height_ = 0;

private:
    void InitCurses();
    void InitInput();
    void InitOutput();
    void InitScreen();
    void InitLines();
    void RunLoop();

private:
    std::string window_title_;
};
