

#include "armadillo.hpp"
#include <cmath>


template<typename T>
class LogisticRegression
{
    private:
      arma::mat X_train;
      arma::mat X_test;
      arma::mat Y_train; // 0 or 1

    public:
    bool load_data(const std::string &x_train_file,
                   const std::string &x_test_file,
                   const std::string &y_train_file);

    void print_dimensions() const;

    void logistic_regression();

};


template<typename T>
void LogisticRegression<T>::logistic_regression()
{

    // we should train the model 
    /*
    L(w) = 1/N \sum_{i=1}^N \log(1 + exp(-y_i w^t x_i))
    */

    unsigned int N = X_train.n_rows;
    unsigned int M = X_train.n_cols;

    arma::rowvec w(M, arma::fill::zeros);
    double epsilon = std::pow(10.0, -7.0);
    double alpha = 0.1;

    // gradient descent
    arma::rowvec gradient(M);
    double grad_norm = 1.0;
    int iter = 0;
    int max_iter = 10000;

    while (grad_norm >= epsilon && iter < max_iter)
    {
        gradient.zeros(M);
        for (size_t i = 0; i<N; i++)
        {
            arma::rowvec x_i = X_train.row(i);
            double y_i = Y_train(i);
            // w^T * x_i
            double dot_prod = arma::dot(w, x_i);
            // 1 + exp(y_i * w^T * x_i)
            double naevner = 1 + std::exp(y_i * dot_prod);
            // term
            arma::rowvec term = (y_i / naevner) * x_i;

            gradient -= term;
        }

        gradient /= N;
        w -= alpha * gradient;
        grad_norm = arma::norm(gradient);
        iter++;
    }

    unsigned int N_test = X_test.n_rows;
    arma::vec Y_pred(N_test, arma::fill::zeros);

    for (size_t i = 0; i<N_test; i++)
    {
        arma::rowvec x_test_point = X_test.row(i);

        double f_x = arma::dot(w, x_test_point);

        if (f_x > 0)
        {
            Y_pred[i] = 1;
        } 
        else 
        {
            Y_pred[i] = -1;
        }
    }

    
    if (Y_pred.save("LogReg.dat", arma::raw_ascii))
    {
        std::cout << "Predictions written sucessfully" << std::endl;
    } 
    else 
    {
        std::cerr << "Error: could not write to NN.dat" << std::endl;
    }

}












template <typename T>
bool LogisticRegression<T>::load_data(const std::string &x_train_file,
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
void LogisticRegression<T>::print_dimensions() const
{
    std::cout << "--- Dataset Dimensions ---" << std::endl;
    std::cout << "X_train : " << X_train.n_rows << "x" << X_train.n_cols << std::endl;
    std::cout << "Y_train : " << Y_train.n_elem << " elements" << std::endl;
    std::cout << "X_test   : " << X_test.n_rows << "x" << X_test.n_cols << std::endl;
}



int main()
{
    LogisticRegression<double> LR_model;
    
    if (LR_model.load_data("dataX.dat", "dataXtest.dat", "dataY.dat"))
    {
        LR_model.print_dimensions();
        LR_model.logistic_regression();
    }

    return 0;
}