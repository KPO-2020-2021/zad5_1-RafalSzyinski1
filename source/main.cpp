#include "AutoDrone.h"
#include "GNUPlot.h"

#include "thread"
#include "chrono"

int main()
{
    GNUPlot plot;
    AutoDrone d;
    d.setActive();
    while (true)
    {
        plot.addDrone(d, "#FF00FF");
        d.fly(100, 5);
        plot.draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}