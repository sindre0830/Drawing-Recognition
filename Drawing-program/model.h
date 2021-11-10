#ifndef MODEL_H_
#define MODEL_H_
/* external libraries */
#include <tensorflow/c/c_api.h>

/**
 *	Class for controlling points.
 */
class Model {
 private:
    const char* model_path = "../../Data/model/";
    const char* tags = "serve";
    int ntags;
    TF_Graph* Graph;
    TF_Status* Status;
    TF_SessionOptions* SessionOpts;
    TF_Buffer* RunOpts;
    TF_Session* Session;

 public:
    Model();
    ~Model();
    int init();
};

#endif  // MODEL_H_
