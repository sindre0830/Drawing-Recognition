#ifndef MODEL_H_
#define MODEL_H_
/* external libraries */
#include <string>

void initPythonScript(std::string filename);

/**
 *	Class for controlling points.
 */
class Model {
 private:
    const char* model_path = "../../Data/model.h5";

 public:
    Model();
    ~Model();
    void initScript();
    void predict();
};

#endif  // MODEL_H_
