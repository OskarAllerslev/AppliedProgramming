
#include "NearestNeighbours.hpp"
#include "armadillo.hpp"


int main()
{
    
    NearestNeigbours<double> knn_model;

    knn_model.load_data("dataX.dat", "dataXtest.dat", "dataY.dat");

    knn_model.print_dimensions();

    






    
    return 0;
}