/**
 * @file Scene.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#ifndef SCENES_SCENE_H_
#define SCENES_SCENE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../Navigation/NavButton.h"
#include "../functions.h"

/**
 * Base class for all scenes.
 */
class Scene {
 private:
     int width, height;
     std::vector<NavButton*> navigation;
 public:
     Scene();
     ~Scene();

     int getWidth() { return width; }
     int getHeight() { return height; }

     void addButton(NavButton* nav) { navigation.push_back(nav); }
     virtual void draw(GLFWwindow* window);
     SceneType checkButtonClick(double x, double y);
};

#endif  // SCENES_SCENE_H_
