// Gaurav Bhandari
// Point.cpp --- implemebtation of point.h
//

#include <math.h>
#include <string>
#include <sstream>
#include "point.h"

using namespace Clustering;
namespace Clustering {

    unsigned int Point::__idGen=0;

    Point::Point(int __newDim)
    {

        __dim = __newDim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
            __values[i] = 0.0;
        __id=__idGen++;
    }

    Point::Point(int __newDim, double *__newValue)
    {
        __dim = __newDim;
        __values = __newValue;
        __id=__idGen++;
    }

    Point::Point(const Point &cpy)
    {
        __dim = cpy.__dim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
            __values[i] = cpy.__values[i];
        __id = cpy.__id;
    }

    Point &Clustering::Point::operator=(const Point &rhs)
    {
        if (this == &rhs) {
            return *this;
        }
        else {
            if (__dim == rhs.__dim)

                for (int i = 0; i < __dim; i++) {
                    __values[i] = rhs.__values[i];
                }
        }
        return *this;
    }

    Point::~Point()
    {
        delete[] __values;
    }

    int Point::getId() const
    {
        return __id;
    }

    int Point::getDims() const
    {
        return __dim;
    }

    void Point::setValue(int index, double newValue)
    {
        __values[index] = newValue;
    }

    double Point::getValue(int index) const
    {
        return __values[index];
    }

    double Point::distanceTo(const Point &Kalc) const
    {
        double side;
        double storage = 0;

        for (int i = 0; i < Kalc.__dim; i++)
            storage += (pow(Kalc.__values[i] - __values[i], 2));
        side = sqrt(storage);
        return side;
    }

    Point &Point::operator*=(double rhs)
    {
        for (int i = 0; i < __dim; i++)
            __values[i] *= rhs;
        return *this;
    }

    Point &Point::operator/=(double div)
    {
        for (int i = 0; i < __dim; i++)
            __values[i] /= div;
        return *this;
    }

    const Point Point::operator*(double V) const
    {
        return Point(*this) *= V;
    }

    const Point Point::operator/(double rhs) const
    {
        return Point(*this) /= rhs;
    }

    double &Point::operator[](int index)
    {
        return __values[index];
    }

    Point &operator+=(Point &lhs, const Point &rhs)
    {
        if (&lhs == &rhs) {
            for (int i = 0; i < lhs.__dim; i++)
                lhs.__values[i] += rhs.__values[i];
        }
        else if (lhs.__dim == rhs.__dim) {
            for (int i = 0; i < lhs.__dim; i++)
                lhs.__values[i] += rhs.__values[i];
        }
        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs)
    {
        if (&lhs == &rhs) {
            for (int i = 0; i < lhs.__dim; i++) {
                lhs.__values[i] = 0;
            }
        }
        else if (lhs.__dim == rhs.__dim) {
            for (int i = 0; i < lhs.__dim; i++)
                lhs.__values[i] -= rhs.__values[i];
        }
        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);
        return p += rhs;
    }

    const Point operator-(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);
        return p -= rhs;
    }

    bool operator==(const Point &lhs, const Point &rhs)
    {
        bool equal = true;
        if(lhs.__id !=rhs.__id)
            equal=false;
        else
        {
            for(int i=0;i<lhs.__dim;i++)
                if(lhs.__values[i]!=rhs.__values[i])
                    equal=false;
        }
        return equal;
    }

    bool operator!=(const Point &lhs, const Point &rhs)
    {
        return !operator==(lhs, rhs);
    }

    bool operator<(const Point &lhs, const Point &rhs)
    {
        bool less = false;
        for (int i = 0; i < lhs.__dim; i++)
        {
            if (lhs.__values[i] < rhs.__values[i])
                return true;
            if(lhs.__values[i]>rhs.__values[i])
                return false;
        }
        return less;
    }

    bool operator>(const Point &lhs, const Point &rhs)
    {
        return operator<(rhs, lhs);
    }

    bool operator<=(const Point &lhs, const Point &rhs)
    {
        return !operator>(lhs, rhs);
    }

   bool operator>=(const Point &lhs, const Point &rhs)
    {
        return !operator<(lhs, rhs);
    }

    std::ostream &operator<<(std::ostream &os, const Point &p1)
    {
        unsigned int i=0;
        for(;i<p1.__dim-1;i++)
            os<<p1.__values[i]<<", ";
        os<<p1.__values[i];
        return os;
    }

    std::istream &operator>>(std::istream &input, Point &p2)
    {
        std::string line;
        double d;
        for(int i=0;i<p2.__dim;i++)
        {
            input>>line;
            std::stringstream inputstring(line);
            inputstring>>d;
            p2.__values[i] = d;
        }
        return input;
    }
}
