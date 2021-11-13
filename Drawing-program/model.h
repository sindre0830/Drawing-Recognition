#ifndef MODEL_H_
#define MODEL_H_
/* external libraries */
#include <mlpack/core.hpp>
#include <armadillo>
#include <vector>

/**
 *	Class for controlling points.
 */
class Model {
 private:
    const char* model_path = "../../Data/model.h5";

 public:
    Model();
    ~Model();
    int init();
    void predict(int* data[4 * 128 * 128]);
};

#endif  // MODEL_H_
