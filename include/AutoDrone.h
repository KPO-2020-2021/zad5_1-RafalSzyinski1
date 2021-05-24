#ifndef ROTATION3D_AUTODRONE_H
#define ROTATION3D_AUTODRONE_H

#include "Drone.h"

#define MAX_ALTITUDE 30
#define SPEED 0.4
#define PROPELLERS_SPEED 10

class AutoDrone : public Drone
{
private:
    enum class flyingState {ASCENT, FLYING, LANDING, ROTATE, END, NONE};
    double ang, dista, altitude;

    flyingState state;

public:
    explicit AutoDrone(double x = 0, double y = 0);
    void moveUp();
    void moveStraight();
    void moveDown();
    void rotate();
    void spinPropellers();
    void fly(double angle, double distance);
    void setActive();
    bool isFlying() const;
};


#endif //ROTATION3D_AUTODRONE_H
