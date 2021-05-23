/**
 * @file Drone.cpp
 * Definition of Drone class
 */
#include "Drone.h"

/// 'Default' constructor place drone in space
Drone::Drone(const std::vector<double>& _centerPoint) : centerPoint(_centerPoint), body({width, 0, 0}, {0, length, 0}, {0, 0, height}), width(DRONE_SIZE), height(DRONE_SIZE / 4.), length(DRONE_SIZE * 1.2)
{
    using VectorAction::operator-;
    using VectorAction::operator+;

    body = body + (_centerPoint - body.centerOfMass());

    std::vector<double> heightOfPropeller = {0, 0, Propeller({0, 0, 0}).getSize().at(2) / 2.};
    propellers.emplace_back(body.startPoint() + body.z() + heightOfPropeller);
    propellers.emplace_back(body.startPoint() + body.x() + body.z() + heightOfPropeller);
    propellers.emplace_back(body.startPoint() + body.y() + body.z() + heightOfPropeller);
    propellers.emplace_back(body.startPoint() + body.x() + body.y() + body.z() + heightOfPropeller);
}

/// Spin drone with propellers
void Drone::spin(double angle)
{
    body = Transform::rotateRectangularAroundCenterZ(body, angle);
    for(auto& i : propellers)
        i.rotateAround(angle, centerPoint);
}
/// Move drone with propeller by the vector
void Drone::move(const std::vector<double>& vec)
{
    using VectorAction::operator+;
    body = body + vec;
    centerPoint = centerPoint + vec;
    for (auto& i : propellers)
        i.move(vec);
}

/// @return const vector of propellers
const std::vector<Propeller>& Drone::getPropellers() const
{
    return propellers;
}

/// @return vector with size in order {width, length, height}
std::vector<double> Drone::getSize() const
{
    return std::vector<double>({width, length, height});
}

/// Spin one propeller
void Drone::spinPropeller(int index, double angle)
{
    propellers.at(index).spin(angle);
}

/// @return const vector with position
const std::vector<double>& Drone::getPosition() const
{
    return centerPoint;
}

/// @return drone body
const Rectangular& Drone::getRectangular() const
{
    return body;
}

