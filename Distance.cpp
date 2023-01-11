#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

#include "Distance.h"

/*
The function 'chevichav' get as an input two double type of vectors v1, v2 and compute 
the distance between them in order to chevichav scheme and return it as double output.
In the function we pass by for-loop over all the indicies of v1 and v2 vectors and compute the difference in absolute value.
We define variable 'max_difference' that initialized with 0 and in every loop, we check if the current difference is bigger
then 'max_difference' and update it to the curret difference. In the end of the for-loop we return 'max_difference'.
*/

double Distance::chevichav(vector<double> v1, vector<double> v2)
{
    double max_difference = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        double difference = fabs(v1[i] - v2[i]);
        if (difference > max_difference)
        {
            max_difference = difference;
        }
    }
    return max_difference;
}

/*
The function 'euclidian' get as an input two double type of vectors v1, v2 and compute 
the distance between them in order to euclidian scheme and return it as double output.
In the function we pass by for-loop over all the indicies of v1 and v2 vectors and compute the difference between them.
We define variable 'distance' that initialized with 0 and in every loop, we add the current difference power by 2- to 'distance'
In the end of the for-loop we return 'difference' power by 0.5 (root).
*/

double Distance::euclidian(vector<double> v1, vector<double> v2)
{
    double distance = 0;
    double diff = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        diff = v1[i] - v2[i];
        distance += pow(diff, 2);
    }
    return pow(distance, 0.5);
}

/*
The function 'manhatten' get as an input two double type of vectors v1, v2 and compute 
the distance between them in order to euclidian scheme and return it as double output.
In the function we pass by for-loop over all the indicies of v1 and v2 vectors and compute the difference between them in absolute value.
We define variable 'distance' that initialized with 0 and in every loop, we add the current difference to 'distance'
In the end of the for-loop we return 'difference'.
*/

double Distance::manhatten(vector<double> v1, vector<double> v2)
{
    double distance = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        distance += fabs(v1[i] - v2[i]);
    }

    return distance;
}

/*
The function 'minkovsky' get as an input two double type of vectors v1, v2 and compute 
the distance between them in order to euclidian scheme and return it as double output.
In the function we pass by for-loop over all the indicies of v1 and v2 vectors and compute the difference between them power by 2.
We define constant variable r = 2, and variable 'sum' that initialized with 0 and in every loop, we add the current difference to 'sum'
In the end of the for-loop we return 'sum' power by 1/r.
*/

double Distance::minkovsky(vector<double> v1, vector<double> v2)
{
    double r = 2;
    double sum = 0;

    for (int i = 0; i < v1.size(); i++)
    {
        sum += pow(v1[i] - v2[i], r);
    }
    return pow(sum, 1.0 / r);
}

/*
The function 'canabra' get as an input two double type of vectors v1, v2 and compute 
the distance between them in order to euclidian scheme and return it as double output.
In the function we pass by for-loop over all the indicies of v1 and v2 vectors and compute
the difference between them in absolute value for the 'numerator',and compute the sum of the
absolute v1[i] and v2[i] separately for 'denominator'. Then we devide 'numerator' in'denominator'.
We define variable 'distance' that initialized with 0 and in every loop, we add the result of the divide in it.
In the end of the for-loop we return 'difference'.
*/

double Distance::canabra(vector<double> v1, vector<double> v2)
{
    double distance = 0;

    for (int i = 0; i < v1.size(); i++)
    {
        double numerator = fabs(v1[i] - v2[i]);
        double denominator = fabs(v1[i]) + fabs(v2[i]);
        double result;
        if (denominator==0)
        {
            result=0;
        }
        else{
        result = numerator / denominator;
        }
        distance += result;
    }

    return distance;
}
