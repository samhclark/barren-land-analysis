/*
 * File:    Barren.h
 * Author:  Sam Clark
 * Created: June 27, 2019 at 11:50 PM
 */

#ifndef BARREN_H
#define BARREN_H

class Barren {
public:
    // Overload assignment operator
    Barren& operator=(const Barren& other_barren);

    // Default constructor
    // Creates barren area at coords (-1,-1) to (-1,-1)
    Barren();

    // Constructor from ints
    Barren(int other_bottom_left_x, int other_bottom_left_y,
           int other_top_right_x, int other_top_right_y);

    // Copy constructor
    Barren(const Barren& other_barren);

    // Destructor
    ~Barren();

    // Getters for ints
    int get_bottom_left_x() const;
    int get_bottom_left_y() const;
    int get_top_right_x() const;
    int get_top_right_y() const;

    bool is_valid() const;

private:
    int bottom_left_x;
    int bottom_left_y;
    int top_right_x;
    int top_right_y;

    // Function to make a copy of other_barren
    void copy_barren(const Barren& other_barren);
};

Barren& Barren::operator=(const Barren& other_barren){
    if (this != &other_barren) {  //avoid self-copy
        copy_barren(other_barren);
    }
    return *this;
}

Barren::Barren() {
    bottom_left_x = -1;
    bottom_left_y = -1;
    top_right_x = -1;
    top_right_y = -1;
}

Barren::Barren(int other_bottom_left_x, int other_bottom_left_y,
        int other_top_right_x, int other_top_right_y) {
    bottom_left_x = other_bottom_left_x;
    bottom_left_y = other_bottom_left_y;
    top_right_x = other_top_right_x;
    top_right_y = other_top_right_y;
}

Barren::Barren(const Barren& other_barren) {
    copy_barren(other_barren);
}

Barren::~Barren() {};

int Barren::get_bottom_left_x() const {
    return bottom_left_x;
}

int Barren::get_bottom_left_y() const {
    return bottom_left_y;
}

int Barren::get_top_right_x() const {
    return top_right_x;
}

int Barren::get_top_right_y() const {
    return top_right_y;
}

bool Barren::is_valid() const {
    return (bottom_left_x <= top_right_x && bottom_left_x >= 0
           && bottom_left_y <= top_right_y && bottom_left_y >= 0);
}

void Barren::copy_barren(const Barren& other_barren) {
    bottom_left_x = other_barren.get_bottom_left_x();
    bottom_left_y = other_barren.get_bottom_left_y();
    top_right_x = other_barren.get_top_right_x();
    top_right_y = other_barren.get_top_right_y();

}

#endif //BARREN_H
