#include "AutoDrone.h"

AutoDrone::AutoDrone(double x, double y) : Drone({x, y, DRONE_SIZE / 8.})
{
    ang = 0.0;
    dista = 0.0;
    altitude = 0.0;
    state = flyingState::END;
}

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

void AutoDrone::setActive()
{
    if (state == flyingState::END)
        state = flyingState::NONE;
}

void AutoDrone::moveStraight()
{
    spinPropellers();
    using namespace VectorAction;
    dista -= SPEED;
    auto dir = getRectangular().y();
    move( (dir *  (1/abs(dir))) * SPEED);
}

void AutoDrone::moveUp()
{
    spinPropellers();
    altitude -= SPEED;
    move({0, 0, SPEED});
}

void AutoDrone::rotate()
{
    spinPropellers();
    spinPropeller(0, -PROPELLERS_SPEED);
    spinPropeller(3, PROPELLERS_SPEED);
    ang -= SPEED;
    spin(SPEED);
}

void AutoDrone::moveDown()
{
    spinPropellers();
    altitude -= SPEED;
    move({0, 0, -SPEED});
}

void AutoDrone::spinPropellers()
{
    spinPropeller(0, -PROPELLERS_SPEED);
    spinPropeller(1, PROPELLERS_SPEED);
    spinPropeller(2, -PROPELLERS_SPEED);
    spinPropeller(3, PROPELLERS_SPEED);
}

bool AutoDrone::isFlying() const
{
    if (state == flyingState::END || state == flyingState::NONE)
        return false;
    return true;
}
