/**
 * @file AutoDrone.cpp
 * Definition of AutoDrone class
 */

#include "AutoDrone.h"


/// Single class constructor
AutoDrone::AutoDrone(double x, double y) : Drone({x, y, DRONE_SIZE / 8.})
{
    ang = 0.0;
    dista = 0.0;
    altitude = 0.0;
    state = flyingState::END;
}

/// Fly method (made to be use in another thread)
void AutoDrone::fly(double angle, double distance)
{
    switch (state)
    {
        case flyingState::NONE:
            state = flyingState::ASCENT;
            altitude = MAX_ALTITUDE;
        case flyingState::ASCENT:
            moveUp();
            if (altitude <= 0)
            {
                state = flyingState::ROTATE;
                ang = std::abs(angle);
                ang = ang - (360 * int(ang / 360));
            }
            break;
        case flyingState::ROTATE:
            rotate();
            if (ang <= 0)
            {
                state = flyingState::FLYING;
                dista = distance;
            }
            break;
        case flyingState::FLYING:
            moveStraight();
            if (dista <= 0)
            {
                state = flyingState::LANDING;
                altitude = MAX_ALTITUDE;
            }
            break;
        case flyingState::LANDING:
            moveDown();
            if (altitude <= 0)
            {
                state = flyingState::END;
            }
            break;
        case flyingState::END:
            return;
            break;
    }
}

/// Set active drone
void AutoDrone::setActive()
{
    if (state == flyingState::END)
        state = flyingState::NONE;
}

/// Move straight drone
void AutoDrone::moveStraight()
{
    spinPropellers();
    using namespace VectorAction;
    dista -= SPEED;
    auto dir = getRectangular().y();
    move( (dir *  (1/abs(dir))) * SPEED);
}

/// Move up drone to some altitude
void AutoDrone::moveUp()
{
    spinPropellers();
    altitude -= SPEED;
    move({0, 0, SPEED});
}

/// Rotate drone
void AutoDrone::rotate()
{
    spinPropellers();
    spinPropeller(0, -PROPELLERS_SPEED);
    spinPropeller(3, PROPELLERS_SPEED);
    ang -= SPEED;
    spin(SPEED);
}

/// Landing
void AutoDrone::moveDown()
{
    spinPropellers();
    altitude -= SPEED;
    move({0, 0, -SPEED});
}

/// Spin propellers
void AutoDrone::spinPropellers()
{
    spinPropeller(0, -PROPELLERS_SPEED);
    spinPropeller(1, PROPELLERS_SPEED);
    spinPropeller(2, -PROPELLERS_SPEED);
    spinPropeller(3, PROPELLERS_SPEED);
}

/// @return true if drone is not flying
bool AutoDrone::isFlying() const
{
    if (state == flyingState::END || state == flyingState::NONE)
        return false;
    return true;
}
