/**
 * @file Drone.h
 * Declaration of Drone class
 */
#ifndef ROTATION3D_DRONE_H
#define ROTATION3D_DRONE_H

#include "Propeller.h"

class Drone
{
private:
    double width;
    double height;
    double length;

    std::vector<double> centerPoint;
    std::vector<Propeller> propellers;
public:
    Rectangular body;

    Drone() = delete;
    explicit Drone(const std::vector<double>& _centerPoint);

    void spin(double angle);
    void move(const std::vector<double>& vec);

    const std::vector<Propeller>& getPropellers() const;
    std::vector<double> getSize() const;
};


#endif //ROTATION3D_DRONE_H
