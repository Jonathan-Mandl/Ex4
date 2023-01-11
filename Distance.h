#include <vector>
#include <iostream>
using namespace std;

class Distance
{
public:
  double euclidian(vector<double> v1, vector<double> v2);
  double manhatten(vector<double> v1, vector<double> v2);
  double chevichav(vector<double> v1, vector<double> v2);
  double canabra(vector<double> v1, vector<double> v2);
  double minkovsky(vector<double> v1, vector<double> v2);
};
