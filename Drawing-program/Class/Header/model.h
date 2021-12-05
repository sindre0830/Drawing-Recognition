/**
 * @file model.h
 * @author Sindre Eiklid
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_MODEL_H_
#define CLASS_HEADER_MODEL_H_

/* external libraries */
#include <GLFW/glfw3.h>
#include <string>

/**
 *	Class for controlling points.
 */
class Model {
 private:
    std::string filename;
    void ping(const std::string cmd);

 public:
    std::string prediction;
    Model();
    ~Model();
    void initScript();
    void predict(GLFWwindow* window);
    void terminate();
};

#endif  // CLASS_HEADER_MODEL_H_
