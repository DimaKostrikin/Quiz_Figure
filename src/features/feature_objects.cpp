#include "../../include/features/feature_objects.h"
#include <stdio.h>

int Object::get_elem_type() {

}

int Object::get_center() {

}

void set_center(Point p) {

}

Object::Object() {

}

Object::~Object() {

}

Handler_feature::Handler_feature(std::vector<Object_dynamic> &d_vect, std::vector<Object_activator> &a_vect, Player player) {

}

Handler_feature::~Handler_feature() {

}

Object_activated::~Object_activated() {

}

Object_activated::Object_activated() {

}

Object_activated::Object_activated(int elem_type, Point p) {

}

Object_activator::~Object_activator() {

}

Object_activator::Object_activator(int elem_type, Point p, Object_activated*) {

}

Player::Player(Point &p) {

}

Player::Player() {

}

Player::~Player() {

}

bool Object_activated::is_activated() {

}