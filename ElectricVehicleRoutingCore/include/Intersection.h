#pragma once

class Intersection {
public:
    Intersection(unsigned int id, int x, int y);

    Intersection() = default;

    unsigned int getId() const;

    int getX() const;

    int getY() const;

    bool operator==(const Intersection &rhs) const;

    bool operator!=(const Intersection &rhs) const;

private:
    unsigned int id;
    int x;
    int y;
};
