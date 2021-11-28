/**
 * @file WordScene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "WordScene.h"

#include <string>

WordScene::WordScene() {
    text = new Font("../fonts/arial.ttf", 48);

    std::vector<std::string> headings{ "Main menu", "Start"  };
    std::vector<SceneType> types{ menu, menu };

    float x1 = getWidth() / 2.f - 250.f, y1 = 200.f,
          x2 = x1 + 250.f, y2 = y1 + 50.f;
    Rect rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };

    // Create all navigation buttons in the scene
    NavButton* nav = new NavButton("Main menu", menu, rect, yellow, navType);
    addButton(nav);
    // Change height coordinates so the buttons are spread out
    x1 += 300.f;
    x2 += 300.f;
    rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };
    nav = new NavButton("Start", menu, rect, yellow, navType);
    addButton(nav);
}

/**
 *  Deconstructor.
 */
WordScene::~WordScene() {
}

/**
 *  Draw the about scene on screen.
 */
void WordScene::draw(GLFWwindow* window) {
    Scene::draw(window);
    text->RenderText("Your new word is:", getWidth() / 2.f - 200.f, getHeight() / 2.f + 100.f,
                      1.f, glm::vec3(0, 0, 0));
    text->RenderText("BANANA", getWidth() / 2.f - 200.f, getHeight() / 2.f, 2.f, glm::vec3(0, 0, 0));
}
