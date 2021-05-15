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

    void addWall(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& startPoint);
    void addRectangular(const Rectangular& rec);
    void addPropeller(const Propeller& pro);
    void addDrone(const Drone& drone);
    void draw();
};


#endif //ROTATION_GNUPLOT_H
