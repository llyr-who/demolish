#include"vertex.h"

#include<cmath>

using demolish::geometry::Vertex;

Vertex::Vertex(float x,float y)
{
    _x = x; _y = y;
    _r = 0; _theta = 0;
}

Vertex& Vertex::operator=(const Vertex& v)
{
   _x =     v._x;
   _y =     v._y;
   _r =     v._r;
   _theta = v._theta;
   return *this;
}

// lexicographic ordering
bool Vertex::operator<(const Vertex&v) const
{
    return _x < v._x || (_x == v._x && _y < v._y);
}


/**
 * We have not found that we need to update the radial
 * and angular component of the vector as of yet. Although,
 * we do suspect that we will need to soon. 
 */

Vertex Vertex::operator+(const Vertex&v) const
{
    float X = _x + v._x, Y = _y + v._y;
    Vertex w = Vertex(X,Y);
    return w;
}

Vertex Vertex::operator-(const Vertex&v) const
{
    float X = _x - v._x, Y = _y - v._y;
    Vertex w = Vertex(X,Y);
    return w;
}

Vertex Vertex::operator*(const float&a) const
{
    float X = _x*a, Y = _y*a;
    Vertex v = Vertex(X,Y);
    return v;
}

float Vertex::operator*(const Vertex&v) const
{
    return v._x*_x + v._y*_y;
}

Vertex& Vertex::operator+=(const Vertex&v)
{
    _x += v._x;
    _y += v._y;
    return *this;
}

Vertex& Vertex::operator*=(const float&a)
{
    _x*=a;_y*=a;
    return *this;
}

void Vertex::fillPolars()
{
    //we could do without the sqrt
    _r = sqrt(_x*_x + _y*_y);
    _theta = atan2(_y,_x);
    if(_theta<0)
    {
        _theta += 2*M_PI;
    }
}

Vertex Vertex::perpendicular()
{
    Vertex returnVec(-_y,_x);
    return returnVec;
}

float Vertex::norm()
{
    return std::sqrt(_x*_x+_y*_y);
}

void Vertex::normalise()
{
    float norm = this->norm();
    _x /= norm;_y/=norm;
}

