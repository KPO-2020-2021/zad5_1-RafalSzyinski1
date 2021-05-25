/**
 * @file Figure.h
 * Declaration of base class Figure
 */
#ifndef ROTATION3D_FIGURE_H
#define ROTATION3D_FIGURE_H

#include <vector>

class Figure
{
private:
    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> Z;
    std::vector<double> StartPoint;
public:
    Figure() = delete;
    Figure(std::vector<double>  _x, std::vector<double>  _y, std::vector<double>  _z, std::vector<double> _startPoint = std::vector<double>());
    const std::vector<double>& x() const;
    const std::vector<double>& y() const;
    const std::vector<double>& z() const;
    const std::vector<double>& startPoint() const;
    virtual ~Figure() = default;
};


#endif //ROTATION3D_FIGURE_H
