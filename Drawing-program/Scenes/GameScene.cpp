/**
 * @file GameScene.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "GameScene.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "../build/global.h"

bool timerUp;

/**
 *  Constructor.
 */
GameScene::GameScene() {
    text = new Font("../fonts/arial.ttf", 24);

    // Add color buttons
    std::vector<Color> colorName = { red, green, blue, yellow, black };

    wordsUsed = 0;
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

    // Initialize list with words available
    words = { "banana", "strawberry", "apple", "ghost" };

    randomWord();
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

    /*/ Stop the round if the timer reaches 0
    if (timer <= 0) {
        // Clear the canvas
        paintbrush->clearPoints();
        // Choose new word
        randomWord();
        // Restart timer
    }*/

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

    text->RenderText("Your word is: " + currentWord, 30.f,
                     getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText(std::to_string(timer), getWidth() / 2.f,
                     getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("Word: " + std::to_string(wordsUsed), getWidth() - 130.f,
                     getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText(".. is it", getWidth() - 100.f, 40.f, 1.f, glm::vec3(0, 0, 0));

    // Draw the color buttons and check if one of them is clicked
    for (auto it = colors.begin(); it != colors.end(); ++it) {
        (*it)->draw();
        if ((*it)->detectClick(x, y)) {
            paintbrush->setNewColor((*it)->getColor());
        }
    }
}

/**
 *  Get a random word from the vector of words.
 */
void GameScene::randomWord() {
    // Set a random seed so it is true random
    srand(static_cast<int> (time(0)));

    if (usedWords.empty()) {
        int wordIndex = (rand() % words.size());
        currentWord = words[wordIndex];
    } else {
        // Make sure the word is not already used
        do {
            int wordIndex = (rand() % words.size());
            currentWord = words[wordIndex];
        } while (!(std::find(usedWords.begin(), usedWords.end(), currentWord) != usedWords.end()));
    }

    // Add the word to the used words list, so the player does not get the same word several times
    usedWords.push_back(currentWord);
    wordsUsed++;
}
