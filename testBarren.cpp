#include <iostream>
#include "Barren.h"

void check_barren(Barren b, int x1, int y1, int x2, int y2) {
    if (b.is_valid()) {
        std::cout << "Valid" << std::endl;
    }
    else {
        std::cout << "Invalid" << std::endl;
    }

    std::cout << "Expected: " << x1 << "\tRead: " << b.get_bottom_left_x() << std::endl;
    std::cout << "Expected: " << y1 << "\tRead: " << b.get_bottom_left_y() << std::endl;
    std::cout << "Expected: " << x2 << "\tRead: " << b.get_top_right_x() << std::endl;
    std::cout << "Expected: " << y2 << "\tRead: " << b.get_top_right_y() << std::endl << std::endl;
}

int main() {
    Barren b0(0, 292, 399, 307);
    std::cout << "Plain, four integer assignment" << std::endl;
    check_barren(b0, 0, 292, 399, 307);

    Barren b1(399, 307, 0, 292);
    std::cout << "Four integer assignment, invalid shape" << std::endl;
    check_barren(b1, 399, 307, 0, 292);

    b1 = b0;
    std::cout << "operator= check" << std::endl;
    check_barren(b0, 0, 292, 399, 307);

    std::pair<int, int> p0(48, 192);
    std::pair<int, int> p1(351, 207);
    Barren b2(p0, p1);
    std::cout << "Created with 2 pairs" << std::endl;
    check_barren(b2, 48, 192, 351, 207);

    Barren* b3 = new Barren();
    std::cout << "Using default constructor" << std::endl;
    check_barren(*b3, -1, -1, -1, -1);

    Barren* b4 = new Barren(b2);
    std::cout << "Calling copy constructor" << std::endl;
    check_barren(b2, 48, 192, 351, 207);

    Barren b5(-10, -10, 10, 10);
    std::cout << "Initializing with negative bounds" << std::endl;
    check_barren(b5, -10, -10, 10, 10);

    /**
     * Add tests that give it weird numbers, weird inputs
     */


    return 0;
}
