#include"demolish/geometry/sector.h"
#include<algorithm>
#include<iostream>

using demolish::geometry::Sector;
using demolish::geometry::Vertex;

bool compRadius(std::shared_ptr<Vertex> a, std::shared_ptr<Vertex> b)
{
    return a->getRadius() < b->getRadius();
}

bool compTheta(std::shared_ptr<Vertex> a, std::shared_ptr<Vertex> b)
{
    return a->getTheta() < b->getTheta();
}

Sector::Sector()
{
    _detailLevelIndex = 0;
}

Sector::Sector(float theta1, float theta2)
{
    _theta1 = theta1; _theta2 = theta2;
    _detailLevelIndex = 0;
}

int Sector::generateNextLoD()
{
    
    if(_detailLevelIndex == _LoD.size()-1) // if we do not have the next level of detail, get it and store in cASH
    {
        if(_radiallyOrderedLoD.size() == 0)
        {
            return 0;
        }
        if(_radiallyOrderedLoD.size() == 1)
        {    
            _LoD.push_back(_finestLoD);
            _radiallyOrderedLoD.pop_back();
            _detailLevelIndex++;
            return 1;
        }
        auto currentLoD = _LoD[_detailLevelIndex];
        currentLoD.push_back(_radiallyOrderedLoD.back());
        std::sort(currentLoD.begin(),currentLoD.end(),compTheta);
        _radiallyOrderedLoD.pop_back();
        _detailLevelIndex++;
        _LoD.push_back(currentLoD);
        return 1;
    }
    else // so we do have it
    { 
            _detailLevelIndex++;
            return 1;
    }
}

void Sector::displayContents()
{
   std::cout << _theta1 << " " << _theta2 << std::endl; 
   std::cout << "the finest level of detail is:" << std::endl;
   for(auto&vert:_finestLoD)
   {
       vert->displayProperties();
   }
   std::cout << "the layers in increasing levels of detail are given by" << std::endl;
   int LoDSz = _LoD.size();
   for(int i=0;i<LoDSz;i++)
   {
       int tempSz = _LoD[i].size();
       std::cout << "Layer " << i << " vertices" << std::endl;
       for(int j=0;j<tempSz;j++)
       {
           _LoD[i][j]->displayProperties();
       }
   }
}

void Sector::prepareSector()
{
    _radiallyOrderedLoD = _finestLoD;
    _radiallyOrderedLoD.pop_back();
    _radiallyOrderedLoD.erase(_radiallyOrderedLoD.begin());
    std::sort(_radiallyOrderedLoD.begin(),_radiallyOrderedLoD.end(),compRadius); 
}

std::vector<Vertex> Sector::obtainCurrentLevelOfDetailInWorld(std::array<float,2> location)
{
    std::vector<Vertex> returnVector;
    for(auto&vecpointer:_LoD[_detailLevelIndex])
    {
        returnVector.push_back(Vertex(vecpointer->getX() + std::get<0>(location),
                                      vecpointer->getY() + std::get<1>(location)));
    }
    return returnVector;
}
