#ifndef PROJECT_QUIZ_FIGURE_MODELS_PATH_H
#define PROJECT_QUIZ_FIGURE_MODELS_PATH_H

#endif //PROJECT_QUIZ_FIGURE_MODELS_PATH_H

class Models_path{
private:
    std::vector<std::String> paths_;
public:
    std::vector<std::String> get_paths();
    void set_paths();
    void add_path(std::String);
    void erase_path(std::String);
    Model_path();
    ~Model_path();
};