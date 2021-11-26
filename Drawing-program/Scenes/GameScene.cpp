/**
 * @file GameScene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-26
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "GameScene.h"

#include <iostream>

GameScene::GameScene() {
    text = new Font("../fonts/arial.ttf", 48);

    // Add color buttons
    std::vector<Color> colorName = { red, green, blue, yellow, black };

    float x1 = 50.f, y1 = 50.f,
          x2 = x1 + 50.f, y2 = y1 + 50.f;
    Rect rect = {
        x1, y2,     // Top left
        x1, y1,     // Bottom left
        x2, y1,     // Bottom right
        x2, y2      // Top right
    };

    ColorButton* color = nullptr;

    for (int i = 0; i < colorName.size(); i++) {
        color = new ColorButton(rect, colorName[i], colorType);

        // Move the rectangle to draw the colors in different places
        x1 += 100.f;
        x2 += 100.f;

        rect = {
            x1, y2,     // Top left
            x1, y1,     // Bottom left
            x2, y1,     // Bottom right
            x2, y2      // Top right
        };

        colors.push_back(color);
    }
}

void GameScene::draw() {
    // Render all text in the scene
    text->RenderText("Your word is:", 0, getHeight() - 50, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("Timer", getWidth() / 2.f, getHeight() - 50, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("Round", getWidth() - 200, getHeight() - 50, 1.f, glm::vec3(0, 0, 0));
    text->RenderText(".. is it WORD", getWidth() - 350, 50, 1.f, glm::vec3(0, 0, 0));

    // Color buttons
    for (auto it = colors.begin(); it != colors.end(); ++it)
        (*it)->draw();

    // Paintbrush CHECK IF IT IS IN THE CORRECT PART OF THE SCENE
}
