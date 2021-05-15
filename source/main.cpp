#include "Drone.h"
#include "GNUPlot.h"

#include "thread"
#include "chrono"

int main()
{
    GNUPlot plot;
    Drone d({0, 0, 0});
    while (true)
    {
        plot.addDrone(d);
        plot.draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}