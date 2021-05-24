#include "Scene.h"

Scene::Scene() : plot()
{
    drones.emplace_back(20, 20);
    drones.emplace_back(-20, 20);
    drones.emplace_back(20, -20);
    drones.emplace_back(-20, -20);
    flyParam.resize(drones.size());
    opt = -1;
    active_drone = 0;
    program_run = true;
    t1 = std::thread([this] { return draw(drones, flyParam, plot, program_run); });
}

void Scene::menu()
{
    bool run = true;
    while (run)
    {
        std::cout << "1 - choose drone" << std::endl;
        std::cout << "2 - active drone" << std::endl;
        std::cout << "3 - fly active drone" << std::endl;
        std::cout << "0 - end program" << std::endl;
        std::cin >> opt;
        switch (opt)
        {
            case 0:
                run = false;
                break;
            case 1:
                for (int i = 0; i < drones.size(); ++i)
                    std::cout << "Drone " << i << " position (x, y): (" << drones.at(i).getPosition().at(0) << "," << drones.at(i).getPosition().at(1) << ")\n";
                std::cin >> active_drone;
                if (active_drone < 0 || active_drone >= drones.size())
                {
                    std::cerr << "Chose wrong drone" << std::endl;
                    std::cerr << "No active drone" << std::endl;
                    active_drone = -1;
                }
                break;
            case 2:
                if (active_drone != -1)
                    std::cout << "Drone " << active_drone << " position (x, y): (" << drones.at(active_drone).getPosition().at(0) << "," << drones.at(active_drone).getPosition().at(1) << ")\n";
                else
                    std::cout << "No active drone" << std::endl;
                break;
            case 3:
                if (drones.at(active_drone).isFlying())
                    std::cout << "Active drone is flying" << std::endl;
                else
                {
                    double a, d;
                    std::cout << "Enter angle and distance: ";
                    std::cin >> a >> d;
                    flyParam.at(active_drone) = std::make_pair(a, d);
                    drones.at(active_drone).setActive();
                }
                break;
            default:
                std::cout << "No such option" << std::endl;
                break;
        }

    }
    program_run = false;
    t1.join();
}

void Scene::run()
{
    menu();
}

void Scene::draw(std::vector<AutoDrone>& d, std::vector<std::pair<double, double>>& f, GNUPlot& p, bool& r)
{
    while(r)
    {
        for (int i = 0; i < d.size(); ++i)
        {
            d.at(i).fly(f.at(i).first, f.at(i).second);
            p.addDrone(d.at(i), "#FF0000");
        }
        p.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
