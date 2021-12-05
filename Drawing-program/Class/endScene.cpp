/**
 * @file EndScene.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/endScene.h"
/* external libraries */
#include <GLFW/glfw3.h>
#include <string>

/**
 *  Constructor.
 */
EndScene::EndScene() {
    heading = new Font("../External/Fonts/CaveatBrush-Regular.ttf", 100);

    float x1 = getWidth() / 2.f - 150.f, y1 = 200.f,
          x2 = x1 + 140.f, y2 = y1 + 50.f;
    Rect rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };
    navigation.push_back(new NavButton("Play again", game, rect, YELLOW));
    x2 += 175.f;
    x1 += 175.f;
    rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };
    navigation.push_back(new NavButton("Main menu", menu, rect, YELLOW));
}

/** 
 *  Deconstructor.
 */
EndScene::~EndScene() {
    delete heading;
}

/**
 *  Draw the about scene on screen.
 */
void EndScene::draw(int points) {
    Scene::draw();
    // Render title
    RGB txtColor = colors.find(YELLOW)->second;
    heading->RenderText("Game over", getWidth() / 2.f - 175.f, getHeight() - 200.f, 1.f,
                        glm::vec3(txtColor.r, txtColor.g, txtColor.b));

    // Render text based on how many points the player got
    if (points > 0) {
        text->RenderText("Congrats!", getWidth() / 2.f - 40.f,
                         getHeight() / 2.f + 50.f, 1.f, glm::vec3(0, 0, 0));
    } else {
        text->RenderText("Too bad!", getWidth() / 2.f - 40.f,
                         getHeight() / 2.f + 50.f, 1.f, glm::vec3(0, 0, 0));
    }

    // Write "point" if there is only one point
    std::string pointsText = (points == 1) ? " point" : " points";
    text->RenderText("You got " + std::to_string(points) + pointsText,
                      getWidth() / 2.f - 70.f, getHeight() / 2.f - 50.f, 1.f, glm::vec3(0, 0, 0));
}
