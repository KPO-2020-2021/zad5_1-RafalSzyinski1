#ifndef ROTATION3D_SCENE_H
#define ROTATION3D_SCENE_H

#include "AutoDrone.h"
#include "GNUPlot.h"

#include <thread>
#include <chrono>
#include <future>
#include <functional>


class Scene
{
private:
    GNUPlot plot;
    std::vector<AutoDrone> drones;
    std::vector<std::pair<double, double>> flyParam;
    int opt;
    int active_drone;

    std::thread t1;
    static void draw(std::vector<AutoDrone>& d, std::vector<std::pair<double, double>>& f, GNUPlot& p, bool& r);
    bool program_run;
public:
    Scene();
    void menu();
    void run();
};

#endif //ROTATION3D_SCENE_H
