/**
 * @file Propeller.h
 * Declaration of Propeller class
 */

#ifndef ROTATION3D_PROPELLER_H
#define ROTATION3D_PROPELLER_H

#include "Rectangular.h"

/// Size of Drone
#define DRONE_SIZE 10

class Propeller
{
private:
    double width;
    double length;
    double height;

    std::vector<double> centerPoint;
    std::vector<Rectangular> recs;

public:
    Propeller() = delete;
    explicit Propeller(std::vector<double>  _centerPoint);
    explicit Propeller(std::vector<Rectangular> _recs, std::vector<double> _centerPoint);

    void spin(double angle);
    void rotateAround(double angle, const std::vector<double>& vec = {0, 0, 0});
    void move(const std::vector<double>& vec);
    const std::vector<double>& getCenterPoint() const;
    const std::vector<Rectangular>& getRectangular() const;
    std::vector<double> getSize() const;
};

#endif //ROTATION3D_PROPELLER_H
