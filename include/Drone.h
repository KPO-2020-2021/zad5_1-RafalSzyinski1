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
    Rectangular body;
public:

    Drone() = delete;
    explicit Drone(const std::vector<double>& _centerPoint);

    void spin(double angle);
    void move(const std::vector<double>& vec);

    void spinPropeller(int index, double angle);

    const std::vector<Propeller>& getPropellers() const;
    const std::vector<double>& getPosition() const;
    const Rectangular& getRectangular() const;
    std::vector<double> getSize() const;
};


#endif //ROTATION3D_DRONE_H
