/**
 * @file GameScene.cpp
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#include "./Header/gameScene.h"
/* external libraries */
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

/**
 *  Constructor.
 */
GameScene::GameScene() {
    points = 0;

    // Create the paintrbrush
    paintbrush = new Paintbrush();

    // Initialize list with words available
    words = {
        "green apple",
        "banana",
        "strawberry",
        "campfire",
        "watermelon",
        "umbrella",
        "blueberry",
        "cheese",
        "star",
        "cucumber"
    };
    allUsed = false;    // If all words are used or not
    randomWord();

    // Add color buttons
    std::vector<Color> colorName = {RED, GREEN, BLUE, YELLOW, BROWN, GRAY, BLACK, WHITE};
    float x1 = 40.f, y1 = 40.f,
          x2 = x1 + 30.f, y2 = y1 + 30.f;
    Rect rect = {
        x1, y2,     // Top left
        x1, y1,     // Bottom left
        x2, y1,     // Bottom right
        x2, y2      // Top right
    };

    for (int i = 0; i < colorName.size(); i++) {
        colors.push_back(new ColorButton(rect, colorName[i]));

        // White needs a border around it to not blend in with the background
        if (colorName[i] == WHITE) {
            colors.push_back(new ColorButton(rect, BLACK));
            x1 += 3.f; x2 -= 3.f;
            y1 += 3.f; y2 -= 3.f;
            rect = {
                x1, y2,     // Top left
                x1, y1,     // Bottom left
                x2, y1,     // Bottom right
                x2, y2      // Top right
            };
            colors.push_back(new ColorButton(rect, WHITE));
        }
        // Move the rectangle to draw the colors in different places
        x1 += 50.f;
        x2 += 50.f;
        rect = {
            x1, y2,     // Top left
            x1, y1,     // Bottom left
            x2, y1,     // Bottom right
            x2, y2      // Top right
        };
    }
}

/** 
 *  Deconstructor.
 */
GameScene::~GameScene() {
    delete paintbrush;
    while (!colors.empty()) {
        auto it = colors.begin();
        delete (*it);
        colors.erase(it);
    }
}

/**
 *  Draw the game scene on screen.
 * 
 *  @param window - The game window
 *  @param guessedWord - The word that is currently guessed
 */
void GameScene::draw(GLFWwindow* window, std::string guessedWord, int timer) {
    // Get mouse position
    double x = 0,
           y = 0;
    glfwGetCursorPos(window, &x, &y);

    // It is only possible to draw with the paintbrush if the timer is running
    if (timer > 0) {
        // Check if the mouse is touching the top or bottom part of the screen (where it is text)
        if (y >= 50 && y <= 800) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                // Create point on mouse position
                paintbrush->createPoint(x, y);
            } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                paintbrush->setNewPos(true);
            }
        }
        paintbrush->draw();
    }

    // Make sure the guessed word is in lowercase
    std::for_each(guessedWord.begin(), guessedWord.end(), [](char& c) {
        c = ::tolower(c);
    });
    // Check if the words is guessed correctly
    if (currentWord == guessedWord) {
        points++;
        paintbrush->clearPoints();
        randomWord();
    }

    // Clear canvas if C is pressed
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) paintbrush->clearPoints();

    // Text rendering
    text->RenderText("Your word is: " + currentWord, 30.f,
                     getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText(std::to_string(static_cast<int>(timer)), getWidth() / 2.f,
                     getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("Points: " + std::to_string(points), getWidth() - 130.f,
                     getHeight() - 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText(".. is it " + guessedWord, getWidth() - 200.f, 40.f, 1.f, glm::vec3(0, 0, 0));
    text->RenderText("Press 'C' to clear the canvas.", 40.f, 15.f, 0.75f, glm::vec3(0, 0, 0));

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

    // Return if all available words are used
    if (usedWords.size() == words.size()) {
        allUsed = true;     // Set flag
        return;
    }
    if (usedWords.empty()) {
        int wordIndex = (rand() % words.size());  // NOLINT(runtime/threadsafe_fn)
        currentWord = words[wordIndex];
    } else {
        // Make sure the word is not already used
        do {
            int wordIndex = (rand() % words.size());  // NOLINT(runtime/threadsafe_fn)
            currentWord = words[wordIndex];
        } while (std::find(usedWords.begin(), usedWords.end(), currentWord) != usedWords.end());
    }
    // Add the word to the used words list, so the player does not get the same word several times
    usedWords.push_back(currentWord);
}

/**
 *  Reset game round variables.
 */
void GameScene::endRound() {
    usedWords.clear();
    points = 0;
    paintbrush->clearPoints();
    randomWord();
    allUsed = false;
}
