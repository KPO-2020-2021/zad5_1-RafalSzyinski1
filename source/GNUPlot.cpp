/**
 * @file GNUPlot.cpp
 * Definition of GNUPlot class
 */

#include "GNUPlot.h"
#include "VectorAction.h"

/**
 * Default constructor
 */
GNUPlot::GNUPlot() : plt(), objects(), surfaceColor("#000000"), surfaceFormula("0")
{
}

/**
 * Make and save object wall made from 2 vectors and starting point. \n
 * Using VectorAction.h.
 * @param a first side of the wall
 * @param b second side of the wall
 * @param startPoint point where vectors start
 */
void GNUPlot::addWall(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& startPoint, const std::string& color)
{
    using namespace VectorAction;
    std::vector<double> fig;
    std::stringstream ss;
    ss << " set object " << objects.size() + 1 << " polygon from ";
    fig = startPoint;
    ss << fig << " to ";
    fig = fig + a;
    ss << fig << " to ";
    fig = fig + b;
    ss << fig << " to ";
    fig = fig - a;
    ss << fig << " to ";
    fig = fig - b;
    ss << startPoint;
    ss << R"( fs border lc "#000000" transparent solid fc rgb ")" + color + "\"";
    objects.push_back(ss.str());
}

/**
 * Adding rectangular to space. \n
 * Using addWall method and VectorAction.h
 */
void GNUPlot::addRectangular(const Rectangular& rec, const std::string& color)
{
    using namespace VectorAction;
    addWall(rec.x(), rec.y(), rec.startPoint(), color);
    addWall(rec.x(), rec.z(), rec.startPoint(), color);
    addWall(rec.y(), rec.z(), rec.startPoint(), color);
    std::vector<double> newPoint = rec.startPoint() + rec.x() + rec.y() + rec.z();
    addWall(-rec.x(), -rec.y(), newPoint, color);
    addWall(-rec.x(), -rec.z(), newPoint, color);
    addWall(-rec.y(), -rec.z(), newPoint, color);
}

/**
 * Setup the space and drawing all object. \n
 * At end delete all object.
 */
void GNUPlot::draw()
{
    plt.sendcommand("set ticslevel 0");
    plt.sendcommand("set xyplane at 0");
    plt.sendcommand("set xrange [-60:60]");
    plt.sendcommand("set yrange [-60:60]");
    plt.sendcommand("set zrange [-60:60]");
    plt.sendcommand("unset border");
    plt.sendcommand("unset tics");
    for (auto& i : objects)
        plt.sendcommand(i);
    plt.sendcommand("splot " + surfaceFormula +  " linecolor \"" + surfaceColor + "\" notitle");
    objects.clear();
}

/// Adding propeller to space
void GNUPlot::addPropeller(const Propeller& pro, const std::string& color)
{
    for (auto& i : pro.getRectangular())
        addRectangular(i, color);
}

/// Adding drone to space
void GNUPlot::addDrone(const Drone& drone, const std::string& color)
{
    addRectangular(drone.getRectangular(), color);
    for (auto& i : drone.getPropellers())
        addPropeller(i, color);
}

/// Adding path of drone to space
void GNUPlot::addDronePath(const std::vector<double>& pos, const std::vector<double>& dir, double angle, double dista)
{
    using namespace VectorAction;
    using namespace MatrixAction;
    std::vector<double> fig;
    matrix<double> m({{std::cos(M_PI/180 * angle), -std::sin(M_PI/180 * angle), 0}, {std::sin(M_PI/180 * angle), std::cos(M_PI/180 * angle), 0}, {0, 0, 1}});
    std::stringstream ss;
    ss << " set arrow " << objects.size() + 1 << " from ";
    fig = pos;
    ss << fig << " to ";
    fig = fig + std::vector<double>({0, 0, MAX_ALTITUDE});
    ss << fig;
    objects.push_back(ss.str());
    ss = std::stringstream();
    ss << " set arrow " << objects.size() + 1 << " from " << fig << " to ";
    fig = fig + ((m * dir) * (1/abs(dir)) * dista);
    ss << fig;
    objects.push_back(ss.str());
    ss = std::stringstream();
    ss << " set arrow " << objects.size() + 1 << " from " << fig << " to ";
    fig = fig - std::vector<double>({0, 0, MAX_ALTITUDE});
    ss << fig;
    objects.push_back(ss.str());
}

