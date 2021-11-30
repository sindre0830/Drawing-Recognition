/**
 * @file GameScene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "GameScene.h"
#include "../build/global.h"

bool timerUp;

/**
 *  Constructor.
 */
GameScene::GameScene() {
    text = new Font("../fonts/arial.ttf", 24);

    // Add color buttons
    std::vector<Color> colorName = { red, green, blue, yellow, black };

    timer = 0;
    timerUp = false;

    float x1 = 40.f, y1 = 40.f,
          x2 = x1 + 40.f, y2 = y1 + 40.f;
    Rect rect = {
        x1, y2,     // Top left
        x1, y1,     // Bottom left
        x2, y1,     // Bottom right
        x2, y2      // Top right
    };

    ColorButton* color = nullptr;

    for (int i = 0; i < colorName.size(); i++) {
        color = new ColorButton(rect, colorName[i]);

        // Move the rectangle to draw the colors in different places
        x1 += 75.f;
        x2 += 75.f;

        rect = {
            x1, y2,     // Top left
            x1, y1,     // Bottom left
            x2, y1,     // Bottom right
            x2, y2      // Top right
        };

        colors.push_back(color);
    }

    // Create the paintrbrush
    paintbrush = new Paintbrush();
}

/** 
 *  Deconstructor.
 */
GameScene::~GameScene() {
    delete text;
    delete paintbrush;
    while (!colors.empty()) {
        auto it = colors.begin();
        delete (*it);
        colors.erase(it);
    }
}

void GameScene::draw(GLFWwindow* window) {
    // Set a timer
    t = glfwGetTime();
    if (timer >= 0) {
        timer = 61 - (t + 1);
    }

    if (timer <= 0)
        timerUp = true;

    double x = 0,
           y = 0;

    // Get mouse position
    glfwGetCursorPos(window, &x, &y);

    // Check if the mouse is touching the top or bottom part of the screen (where it is text)
    if (y >= 50 && y <= 800) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            // Create point on mouse position
            paintbrush->createPoint(x, y);
        } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            paintbrush->setNewPos(true);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        paintbrush->clearPoints();
    }

    paintbrush->draw();

    text->RenderText("Your word is: ", 30.f, getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText(std::to_string(timer), getWidth() / 2.f,
                     getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("Word", getWidth() - 100.f, getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText(".. is it", getWidth() - 100.f, 40.f, 1.f, glm::vec3(0, 0, 0));

    // Draw the color buttons and check if one of them is clicked
    for (auto it = colors.begin(); it != colors.end(); ++it) {
        (*it)->draw();


        if ((*it)->detectClick(x, y)) {
            paintbrush->setNewColor((*it)->getColor());
        }
    }
}
