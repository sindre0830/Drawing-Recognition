#ifndef MODEL_H_
#define MODEL_H_
/* external libraries */
#include <GLFW/glfw3.h>
#include <string>

void initPythonScript(std::string filename);

/**
 *	Class for controlling points.
 */
class Model {
 private:
    const char* model_path = "../../Data/model.h5";
    void ping(const std::string cmd);

 public:
    Model();
    ~Model();
    void initScript();
    void predict(GLFWwindow* window);
    void terminate();
};

#endif  // MODEL_H_
