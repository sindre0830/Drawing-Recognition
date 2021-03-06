/**
 * @file Scene.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/menuScene.h"
/* external libraries */
#include <string>
#include <vector>
/* local libraries */
#include "./Header/navButton.h"

/**
 *  Constructor.
 */
MenuScene::MenuScene() {
    heading = new Font("../External/Fonts/CaveatBrush-Regular.ttf", 100);

    // Create navigation buttons
    std::vector<std::string> headings{ "Start game", "About", "Exit" };
    std::vector<SceneType> types{ game, about, exitGame };

    int width = 800;
    int height = 900;

    float x1 = width / 2.f - 60.f, y1 = height / 2.f + 60.f,
          x2 = x1 + 140.f, y2 = y1 + 50.f;
    Rect rect = {
        x1, y2,
        x1, y1,
        x2, y1,
        x2, y2
    };

    NavButton* nav = nullptr;
    for (int i = 0; i < headings.size(); i++) {
        nav = new NavButton(headings[i], types[i], rect, YELLOW);
        navigation.push_back(nav);

        // Change height coordinates so the buttons are spread out
        y2 -= 200.f;
        y1 -= 200.f;
        rect = {
            x1, y2,
            x1, y1,
            x2, y1,
            x2, y2
        };
    }
}

/**
 *  Deconstructor.
 */
MenuScene::~MenuScene() {
    delete heading;
}

/**
 *  Draw the menu on screen.
 */
void MenuScene::draw() {
    Scene::draw();
    // Render title
    RGB txtColor = colors.find(YELLOW)->second;
    heading->RenderText("Drawing Recognition", getWidth() / 2.f - 350.f, getHeight() - 200.f, 1.f,
                         glm::vec3(txtColor.r, txtColor.g, txtColor.b));
}

