/**
 * @file Rectangular.h
 * Declaration of Rectangular class
 */

#ifndef ROTATION_RECTANGULAR_H
#define ROTATION_RECTANGULAR_H

#include "MatrixAction.h"
#include "Figure.h"


class Rectangular : public Figure
{
private:

public:
    Rectangular() = delete;
    Rectangular(std::vector<double>  _x, std::vector<double>  _y, std::vector<double>  _z, std::vector<double> _startPoint = std::vector<double>());

    friend bool operator==(const Rectangular& rec1, const Rectangular& rec2);

    Rectangular operator*(const matrix<double>& mat) const;
    Rectangular operator+(const std::vector<double>& vec) const;

    std::vector<double> centerOfMass() const;
    ~Rectangular() override = default;
};

namespace Transform
{
    Rectangular rotateRectangularAroundCenterZ(const Rectangular& rec, double angle);
}


#endif //ROTATION_RECTANGULAR_H
