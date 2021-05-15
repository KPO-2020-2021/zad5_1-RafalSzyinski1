/**
 * @file GNUPlot.cpp
 * Definition of GNUPlot class
 */

#include "GNUPlot.h"

#include "VectorAction.h"

/**
 * Default constructor
 */
GNUPlot::GNUPlot() : plt(), objects(), surfaceColor("#FFFFFF00"), surfaceFormula("0")
{
}

/**
 * Make and save object wall made from 2 vectors and starting point. \n
 * Using VectorAction.h.
 * @param a first side of the wall
 * @param b second side of the wall
 * @param startPoint point where vectors start
 */
void GNUPlot::addWall(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& startPoint)
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
    ss << " fillstyle transparent solid fillcolor rgb \"#FF0000\"";
    objects.push_back(ss.str());
}

/**
 * Adding rectangular to space. \n
 * Using addWall method and VectorAction.h
 */
void GNUPlot::addRectangular(const Rectangular& rec)
{
    using namespace VectorAction;
    addWall(rec.x(), rec.y(), rec.startPoint());
    addWall(rec.x(), rec.z(), rec.startPoint());
    addWall(rec.y(), rec.z(), rec.startPoint());
    std::vector<double> newPoint = rec.startPoint() + rec.x() + rec.y() + rec.z();
    addWall(-rec.x(), -rec.y(), newPoint);
    addWall(-rec.x(), -rec.z(), newPoint);
    addWall(-rec.y(), -rec.z(), newPoint);
}

/**
 * Setup the space and drawing all object. \n
 * At end delete all object.
 */
void GNUPlot::draw()
{
    plt.sendcommand("set ticslevel 0");
    plt.sendcommand("set xyplane at 0");
    plt.sendcommand("set xrange [-30:30]");
    plt.sendcommand("set yrange [-30:30]");
    plt.sendcommand("set zrange [-30:30]");

    for (auto& i : objects)
        plt.sendcommand(i);
    plt.sendcommand("splot " + surfaceFormula +  " linecolor \"" + surfaceColor + "\" ");
    objects.clear();
}

/// Adding propeller to space
void GNUPlot::addPropeller(const Propeller& pro)
{
    for (auto& i : pro.getRectangular())
        addRectangular(i);
}

/// Adding drone to space
void GNUPlot::addDrone(const Drone& drone)
{
    addRectangular(drone.body);
    for (auto& i : drone.propellers)
        addPropeller(i);
}

