//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_PARAMETERS_LABEL_H
#define QUIZ_FIGURE_PARAMETERS_LABEL_H

#include <iostream>
#include <map>
#include "memory"
#include "../Objects.h"

class Parameters_label{
public:
    Parameters_label(int obj_type);
    ~Parameters_label();
    void init();
    void changed();
    void close();
private:
    std::string label;
    int obj_id;
    std::map <std::string, int> parameters_num;
    std::map<std::string, bool> parameters_bool;
    std::shared_ptr<Object> obj;
};

#endif //QUIZ_FIGURE_PARAMETERS_LABEL_H
