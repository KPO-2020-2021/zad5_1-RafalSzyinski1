#include "AutoDrone.h"

AutoDrone::AutoDrone(double x, double y) : Drone({x, y, DRONE_SIZE / 8.})
{
    ang = 0.0;
    dista = 0.0;
    flying = false;
    ascent = false;
    landing = false;
    rotate = false;
    end = true;
    altitude = 0.0;
}

void AutoDrone::fly(double angle, double distance)
{
    if (end)
        return;
    if (!flying && !ascent && !landing && !rotate)
    {
        ascent = true;
        altitude = MAX_ALTITUDE;
    }
    else if (ascent && (altitude > 0))
    {
        altitude -= SPEED;
        move({0, 0, SPEED});
        if (altitude <= 0)
        {
            ascent = false;
            rotate = true;
            flying = true;
            ang = std::abs(angle);
        }
    }
    else if (flying && rotate && (ang > 0))
    {
        ang -= SPEED;
        spin(SPEED);
        if (ang <= 0)
        {
            rotate = false;
            dista = distance;
        }
    }
    else if (flying && (dista > 0))
    {
        dista -= SPEED;
        moveStraight();
        if (dista <= 0)
        {
            flying = false;
            rotate = true;
            ang = -std::abs(angle);
        }
    }
    else if (rotate && (ang < 0))
    {
        ang += SPEED;
        spin(-SPEED);
        if (ang >= 0)
        {
            rotate = false;
            landing = true;
            altitude = MAX_ALTITUDE;
        }
    }
    else if (landing && (altitude > 0))
    {
        altitude -= SPEED;
        move({0, 0, -SPEED});
        if (altitude <= 0)
        {
            landing = false;
            end = true;
        }
    }
    else
    {
        end = true;
    }
}

void AutoDrone::setActive()
{
    end = false;
}

void AutoDrone::moveStraight()
{
    using namespace VectorAction;
    auto dir = getRectangular().y();
    move( (dir *  (1/abs(dir))) * SPEED);
}
