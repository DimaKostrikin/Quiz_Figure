#ifndef FEATURES_FEATURE_OBJECTS_H
#define FEATURES_FEATURE_OBJECTS_H
#include <vector>
// Общие классы
class Object_dynamic {

};

struct Point {
    int x;
    int y;
    int z;
};

class Player : public Object_dynamic {
public:
    Player();
    Player(Point& p);
    ~Player();

    void take_elem(Object_dynamic &obj);

private:
    unsigned int height;
};

class Object {
private:
    int elem_type;
    Point center;
public:
    Object();
    Object(int elem_type);
    Object(int elem_type, Point p);
    ~Object();
    int get_elem_type();
    int get_center();
    void set_center(Point p);
};


// Мои классы
class Object_activated : public Object {
private:
    bool activated;
public:
    Object_activated();
    Object_activated(int elem_type);
    Object_activated(int elem_type, Point p);
    ~Object_activated();
    bool is_activated();
    bool& get_status();
};

class Object_activator : public Object_activated {
private:
    Object_activated* linked_obj;
public:
    Object_activator();
    Object_activator(int elem_type, Object_activated* activated);
    Object_activator(int elem_type, Point p, Object_activated* activated);
    ~Object_activator();
    void activate_linked_object();
    void deactivate_linked_object();
};

class Handler_feature {
private:
    std::vector<Object_dynamic> dyn_vect;
    std::vector<Object_activator> act_vect;
    Player player;
public:
    Handler_feature(std::vector<Object_dynamic> &d_vect, std::vector<Object_activator> &a_vect, Player player);
    ~Handler_feature();
    bool is_near();
    void updater();
    void activate_activator();
    void deactivate_activator();
};

#endif //FEATURES_FEATURE_OBJECTS_H
