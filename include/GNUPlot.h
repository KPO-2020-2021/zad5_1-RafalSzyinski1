/**
 * @file GNUPlot.h
 * Class to help drawing from gplot++.cpp
 */

#ifndef ROTATION_GNUPLOT_H
#define ROTATION_GNUPLOT_H

#include <utility>
#include <vector>
#include <stdexcept>

#include "gplot++.h"
#include "Drone.h"

class GNUPlot
{
private:
    Gnuplot plt;
    std::vector<std::string> objects;

    std::string surfaceFormula;
    std::string surfaceColor;
public:

    GNUPlot();

    void addWall(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& startPoint, const std::string& color = "#FF0000");
    void addRectangular(const Rectangular& rec, const std::string& color = "#FF0000");
    void addPropeller(const Propeller& pro, const std::string& color = "#FF0000");
    void addDrone(const Drone& drone, const std::string& color = "#FF0000");
    void draw();
};


#endif //ROTATION_GNUPLOT_H
