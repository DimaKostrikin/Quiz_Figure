#ifndef PROJECT_QUIZ_FIGURE_WIMDOW_H
#define PROJECT_QUIZ_FIGURE_WIMDOW_H

#endif //PROJECT_QUIZ_FIGURE_WIMDOW_H

class Window {
private:
    unsigned int height_;
    unsigned int width;
    std::String window_name;
public:
    Events_manager my_events;

    GLFWwindow create_window();
    unsigned int get_width();
    unsigned int get_height();
    std::String get_window_name();
    void set_window();
    void clean();
    void dysplay();
    void close();
    Window();
    ~Window();
};