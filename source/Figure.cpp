/**
* @file Figure.cpp
* Definition of Figure class
*/

#include "Figure.h"
#include <stdexcept>

/// Constructor of class
Figure::Figure(std::vector<double> _x, std::vector<double> _y, std::vector<double> _z, std::vector<double> _startPoint)
              : X(std::move(_x)), Y(std::move(_y)), Z(std::move(_z)), StartPoint(std::move(_startPoint))
{
    if (StartPoint.empty())
        StartPoint = std::vector<double>(X.size());
    if (X.size() != Y.size() || X.size() != Z.size() || X.size() != StartPoint.size())
        throw std::invalid_argument("ERROR Rectangular: x.size() != y.size() || x.size() != z.size() || x.size() != startPoint.size()");
}


/// @return const vector x.
const std::vector<double>& Figure::x() const
{
    return X;
}

/// @return const vector y.
const std::vector<double>& Figure::y() const
{
    return Y;
}

/// @return const vector z.
const std::vector<double>& Figure::z() const
{
    return Z;
}

/// @return const vector startPoint.
const std::vector<double>& Figure::startPoint() const
{
    return StartPoint;
}