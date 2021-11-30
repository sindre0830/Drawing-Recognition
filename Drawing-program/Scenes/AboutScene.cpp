/**
 * @file Scene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "AboutScene.h"

#include <GLFW/glfw3.h>

AboutScene::AboutScene() {
    heading = new Font("../fonts/CaveatBrush-Regular.ttf", 100);
    text = new Font("../fonts/arial.ttf", 24);

    float x1 = getWidth() / 2.f - 60.f, y1 = 200.f,
          x2 = x1 + 140.f, y2 = y1 + 50.f;
    Rect rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };

    NavButton* nav = new NavButton("Main menu", menu, rect, yellow);
    addButton(nav);
}

/** 
 *  Deconstructor.
 */
AboutScene::~AboutScene() {
    delete heading;
    delete text;
}

/**
 *  Draw the about scene on screen.
 */
void AboutScene::draw(GLFWwindow* window) {
    Scene::draw(window);
    // Render title
    heading->RenderText("About", getWidth() / 2.f - 80.f, getHeight() - 200.f, 1.f,
                        glm::vec3(findColor(yellow).r, findColor(yellow).g, findColor(yellow).b));

    // Render about text
    text->RenderText("You have 30 seconds to draw the word that shows up on the screen.",
                      getWidth() / 2.f - 360.f, getHeight() / 2.f + 50.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("For each drawing the game guesses what are, you will get a point.",
                      getWidth() / 2.f - 360.f, getHeight() / 2.f - 50.f, 1.f, glm::vec3(0, 0, 0));
}
