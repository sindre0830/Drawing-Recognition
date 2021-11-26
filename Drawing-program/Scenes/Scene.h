/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_SCENE_H_
#define SCENES_SCENE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

enum SceneType {
    menu,
    about,
    word
};

/**
 * Base class for all scenes.
 */
class Scene {
 private:
     int width, height;
 public:
     Scene();
     ~Scene();

     int getWidth() { return width; }
     int getHeight() { return height; }

     virtual void draw(GLFWwindow* window);
     virtual SceneType checkButtonClick(double x, double y) { return menu; }
};

#endif  // SCENES_SCENE_H_
