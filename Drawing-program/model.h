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
    void ping(const std::string cmd);

 public:
   std::string prediction;
    Model();
    ~Model();
    void initScript();
    void predict(GLFWwindow* window);
    void terminate();
};

#endif  // MODEL_H_
