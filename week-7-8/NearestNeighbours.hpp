#ifndef NearestNeighboursdef
#define NearestNeighboursdef

#include "armadillo.hpp"
#include <cstddef>
#include <string>
#include <vector>

template <typename T> class NearestNeigbours {
private:
  arma::mat X_train;
  arma::mat X_test;
  arma::mat Y_train; // 0 or 1

public:
  bool load_data(const std::string &x_train_file,
                 const std::string &x_test_file,
                 const std::string &y_train_file);

    void print_dimensions() const;

    void knn_metod();

};





///////////////////////////////////////////////////////////////////////



template <typename T>
bool NearestNeigbours<T>::load_data(const std::string &x_train_file,
                                    const std::string &x_test_file,
                                    const std::string &y_train_file) 
{
    if (!X_train.load(x_train_file) || !X_test.load(x_test_file) || !Y_train.load(y_train_file))
    {
        std::cerr << "Error loading one or more of the datasets" << std::endl;
        return false;
    }
    return true;
}

template<typename T>
void NearestNeigbours<T>::print_dimensions() const
{
    std::cout << "--- Dataset Dimensions ---" << std::endl;
    std::cout << "X_train : " << X_train.n_rows << "x" << X_train.n_cols << std::endl;
    std::cout << "Y_train : " << Y_train.n_elem << " elements" << std::endl;
    std::cout << "X_test  : " << X_test.n_rows << "x" << X_test.n_cols << std::endl;
}

template<typename T>
void NearestNeigbours<T>::knn_metod()
{
    /*
    we need to assign the appropriate label to each point in X_test.
    k = 5. 

    Write a new file "NN.dat" containing the assigned labels in the same
    format as "dataY.dat".
    */
    // in both X_test and X_train we have a set of features 
    // we should take the distance between these points
    unsigned int k = 5;
    arma::vec Y_pred(X_test.n_rows);

    for (size_t j = 0; j < X_test.n_rows; ++j)
    {
        arma::rowvec x_test_point = X_test.row(j);

        arma::vec distances(X_train.n_rows);

        for (size_t i = 0; i < X_train.n_rows; ++i)
        {
            distances(i) = arma::norm(X_train.row(i) - x_test_point);
        }

        arma::uvec sorted_indices = arma::sort_index(distances);

        // make the majority vote over the k closets 
        double label_sum = 0.0;
        for (int n = 0; n < k; ++n)
        {
            size_t nearest_idx = sorted_indices(n);
            label_sum += Y_train(nearest_idx);
        }

        if (label_sum > 0)
        {
            Y_pred(j) = 1;
        } 
        else 
        {
            Y_pred(j) = -1.0;
        }

        if (Y_pred.save("NN.dat", arma::raw_ascii))
        {
            std::cout << "Predictions written sucessfully" << std::endl;
        } 
        else 
        {
            std::cout << "Error: could not write to NN.dat" << std::endl;
        }

    }
}




#endif
