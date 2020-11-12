#ifndef PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H
#define PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H

#endif //PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H

class Events_manager {
private:
    std::vector<int> events_;
public:
    GLFWwindow my_window_;

    void catch_events();
    Events_manager()
    ~Events_manager()
};