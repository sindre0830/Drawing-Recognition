/**
 * @file SceneManager.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "SceneManager.h"

SceneManager::SceneManager() {
    // Create all scenes
    menuScene = new MenuScene();
    aboutScene = new AboutScene();
    gameScene = new GameScene();
    endScene = new EndScene();
    currentScene = menu;
    points = 0;
}

SceneManager::~SceneManager() {
    // Delete all scenes
    delete menuScene;
    delete aboutScene;
    delete gameScene;
    delete endScene;
}

/**
 *  Draw the current scene.
 */
void SceneManager::draw(GLFWwindow* window, std::string guessedWord) {
    // Draw the current scene and check if one of them is clicked
    switch (currentScene) {
    case menu: menuScene->draw(); break;
    case about: aboutScene->draw(); break;
    case game: gameScene->draw(window, guessedWord); break;
    case end: endScene->draw(points); break;
    }

    // Check if the scene is going to be changed
    SceneType next = none;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        switch (currentScene) {
        case menu: next = menuScene->checkButtonClick(x, y); break;
        case about: next = aboutScene->checkButtonClick(x, y); break;
        case end: next = endScene->checkButtonClick(x, y); break;
        }

        if (next != none && next != currentScene) currentScene = next;
    }

    // Check if current round is ending, by either the timer has run out or all words are used
    if ((gameScene->getTimer() <= 0) || gameScene->getAllUsed()) {
        points = gameScene->getPoints();
        gameScene->endRound();  // Reset game round
        currentScene = end;
    }
}
