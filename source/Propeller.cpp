/**
 * @file Propeller.cpp
 * Definition of class Propeller
 */
#include "Propeller.h"

#include <utility>

/// 'Default' constructor place propeller in space
Propeller::Propeller(std::vector<double> _centerPoint) : centerPoint(std::move(_centerPoint)), width(DRONE_SIZE / 2.5), length(width * std::sqrt(3)), height(width / 3)
{
    using namespace VectorAction;
    using namespace MatrixAction;
    std::vector<double> w = {width, 0, 0};
    std::vector<double> l = {0, length, 0};
    std::vector<double> h = {0, 0, height};
    recs.emplace_back(w, l, h, centerPoint - Rectangular(w, l, h).centerOfMass());
    recs.emplace_back(Transform::rotateRectangularAroundCenterZ(recs[0], 120));
    recs.emplace_back(Transform::rotateRectangularAroundCenterZ(recs[1], 120));
}

/// Constructor create propeller from the tab of Rectangular and center point
Propeller::Propeller(std::vector<Rectangular>  _recs, std::vector<double> _centerPoint) : centerPoint(std::move(_centerPoint)), width(10), length(width * std::sqrt(3)), height(width / 3)
{
    using namespace VectorAction;
    Rectangular temp = _recs.at(0);
    recs.emplace_back(temp.x(), temp.y(), temp.z(), centerPoint - temp.centerOfMass());
    recs.emplace_back(Transform::rotateRectangularAroundCenterZ(recs[0], 120));
    recs.emplace_back(Transform::rotateRectangularAroundCenterZ(recs[1], 120));
}

/// Rotate propeller around center of mass
void Propeller::spin(double angle)
{
    for (auto& i : recs)
        i = Transform::rotateRectangularAroundCenterZ(i, angle);
}

/// Rotate propeller around some point
void Propeller::rotateAround(double angle, const std::vector<double>& vec)
{
    using MatrixAction::operator*;
    using VectorAction::operator-;
    using VectorAction::operator+;
    matrix<double> m({{std::cos(M_PI/180 * angle), -std::sin(M_PI/180 * angle), 0}, {std::sin(M_PI/180 * angle), std::cos(M_PI/180 * angle), 0}, {0, 0, 1}});
    Propeller temp(recs, (m * (centerPoint - vec)) + vec);
    temp.spin(angle);
    *this = temp;
}

/// Moves propeller by the vector
void Propeller::move(const std::vector<double>& vec)
{
    using VectorAction::operator+;
    *this = Propeller(recs, centerPoint + vec);
}

/// @return const vector centerPoint
const std::vector<double>& Propeller::getCenterPoint() const
{
    return centerPoint;
}

/// @return const vector of Rectangular
const std::vector<Rectangular>& Propeller::getRectangular() const
{
    return recs;
}

/// @return vector of size in order {width, length, height}
std::vector<double> Propeller::getSize() const
{
    return std::vector<double>({width, length, height});
}
