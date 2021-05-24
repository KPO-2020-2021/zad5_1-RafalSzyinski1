#include "AutoDrone.h"
#include "GNUPlot.h"

#include <thread>
#include <chrono>
#include <future>

AutoDrone d;
AutoDrone d2;
void fun()
{
    d.fly(10, 20);
}

void fun2()
{
    d2.fly(100, 30);
}

int main()
{
    GNUPlot plot;
    d.setActive();
    while (true)
    {
        auto t1 = std::async(fun);
        auto t2 = std::async(fun2);


        t1.get();
        t2.get();
        plot.addDrone(d, "#FF00FF");
        plot.addDrone(d2, "#FFFF00");
        plot.draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}