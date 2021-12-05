/**
 * @file Scene.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/aboutScene.h"
/* external libraries */
#include <GLFW/glfw3.h>

/**
 *  Constructor.
 */
AboutScene::AboutScene() {
    heading = new Font("../External/Fonts/CaveatBrush-Regular.ttf", 100);

    float x1 = getWidth() / 2.f - 60.f, y1 = 200.f,
          x2 = x1 + 140.f, y2 = y1 + 50.f;
    Rect rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };

    NavButton* nav = new NavButton("Main menu", menu, rect, YELLOW);
    navigation.push_back(nav);
}

/** 
 *  Deconstructor.
 */
AboutScene::~AboutScene() {
    delete heading;
}

/**
 *  Draw the about scene on screen.
 */
void AboutScene::draw() {
    Scene::draw();
    // Render title
    RGB txtColor = colors.find(YELLOW)->second;
    heading->RenderText("About", getWidth() / 2.f - 80.f, getHeight() - 200.f, 1.f,
                        glm::vec3(txtColor.r, txtColor.g, txtColor.b));

    // Render about text
    text->RenderText("You have 60 seconds to draw the words that show up on the screen.",
                      getWidth() / 2.f - 360.f, getHeight() / 2.f + 50.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("For each drawing the game guesses what are, you will get a point.",
                      getWidth() / 2.f - 360.f, getHeight() / 2.f - 50.f, 1.f, glm::vec3(0, 0, 0));
}
