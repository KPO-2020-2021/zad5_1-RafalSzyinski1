#ifndef ROTATION3D_AUTODRONE_H
#define ROTATION3D_AUTODRONE_H

#include "Drone.h"

#define MAX_ALTITUDE 30
#define SPEED 0.4

class AutoDrone : public Drone
{
private:
    double ang, dista;

    bool flying, ascent, landing, rotate, end;
    double altitude;


public:
    explicit AutoDrone(double x = 0, double y = 0);
    void moveUp();
    void moveStraight();
    void moveDown();
    void fly(double angle, double distance);
    void setActive();
};


#endif //ROTATION3D_AUTODRONE_H
