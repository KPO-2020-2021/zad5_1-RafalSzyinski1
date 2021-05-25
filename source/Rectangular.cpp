/**
 * @file Rectangular.cpp
 * Definition of Rectangular class
 */
#include "Rectangular.h"
#include <sstream>
#include <utility>  


/// Single class constructor.
Rectangular::Rectangular(std::vector<double>  _x, std::vector<double>  _y, std::vector<double>  _z, std::vector<double> _startPoint)
                        : Figure(std::move(_x), std::move(_y), std::move(_z), std::move(_startPoint))
{
}

/// Function comparing two Rectangular. \n  Using operator== from VectorAction.h.
bool operator==(const Rectangular& rec1, const Rectangular& rec2)
{
    if ((rec1.x() == rec2.x()) && (rec1.y() == rec2.y()) && (rec1.z() == rec2.z()) && (rec1.startPoint() == rec2.startPoint()))
        return true;
    return false;
}

/// Multiplication by matrix. Multiply every vector of Rectangular by mat. \n Using MatrixAction.h.
Rectangular Rectangular::operator*(const matrix<double>& mat) const
{
    using MatrixAction::operator*;
    Rectangular ret(mat * x(), mat * y(), mat * z(), mat * startPoint());
    return ret;
}

/// Translation by vector. Adding vector to starting point of Rectangular. \n Using VectorAction.h
Rectangular Rectangular::operator+(const std::vector<double>& vec) const
{
    using VectorAction::operator+;
    Rectangular ret(x(), y(), z(), startPoint() + vec);
    return ret;
}

/// @return vector with center of mass
std::vector<double> Rectangular::centerOfMass() const
{
    using VectorAction::operator*;
    using VectorAction::operator+;
    return (x() + y() + z()) * (1.0/2.0);
}

/// Transform function helping to rotate Rectangular around center of mass in Z axis
Rectangular Transform::rotateRectangularAroundCenterZ(const Rectangular& rec, double angle)
{
    using namespace VectorAction;
    using namespace MatrixAction;
    matrix<double> m({{std::cos(M_PI/180.0 * angle), -std::sin(M_PI/180.0 * angle), 0}, {std::sin(M_PI/180.0 * angle), std::cos(M_PI/180.0 * angle), 0}, {0, 0, 1}});
    Rectangular temp(rec.x() - rec.centerOfMass(), rec.y() - rec.centerOfMass(), rec.z() - rec.centerOfMass(),  rec.centerOfMass());
    temp = temp * m;
    return Rectangular(temp.x() + temp.startPoint() , temp.y() + temp.startPoint(), temp.z() + temp.startPoint(), (rec.centerOfMass() - temp.startPoint()) + rec.startPoint());
}

