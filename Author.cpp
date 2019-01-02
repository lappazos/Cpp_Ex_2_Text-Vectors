// Author.cpp

#include <cmath>
#include "Author.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Author.
// --------------------------------------------------------------------------------------

/**
* return the distance between vectors
* @param other other author to calculate distance from
* @return distance as double
*/
double Author::distFrom(const Author other) const
{

    double dotProduct = 0;
    double tempA = 0;
    double tempB = 0;
    for (int i = 0; i < _frequentWordNum.size(); i ++)
    {
        dotProduct += _frequentWordNum[i] * other._frequentWordNum[i];
        tempA += pow(_frequentWordNum[i], 2);
        tempB += pow(other._frequentWordNum[i], 2);
    }
    return (dotProduct / (sqrt(tempA) * sqrt(tempB)));
}