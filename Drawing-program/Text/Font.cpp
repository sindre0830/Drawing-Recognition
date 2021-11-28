/**
 * @file Font.cpp
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-12
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */

#include "Font.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <utility>
#include "../functions.h"
#include "../const.h"
#include "../shaders/textShader.h"

 /**
  * Constructor.
  *
  * @param path - Path to the font file
  * @param size - Wanted size of the font
  */
Font::Font(std::string path, int size) {
    this->path = path;
    this->size = size;
    loadFont();

    // Get the monitor's dimensions to set orthographic matrix
    int width = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    int height = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    // compile and setup the shader
    // ----------------------------
    shader = CompileShader(textVertexShaderSrc, textFragmentShaderSrc, "");
    projection = glm::ortho(
        0.0f,
        static_cast<float>(width),
        0.0f,
        static_cast<float>(height));

    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
 *  Load font with character glyphs.
 */
void Font::loadFont() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    } else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, size);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++) {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face(face);
    }

    // destroy FreeType once we're finished
    FT_Done_FreeType(ft);
}

/**
 *  Render text on screen.
 *
 *  @param text - The text to be rendered
 *  @param x - The x-coordinate of the text
 *  @param y - The y-coordinate of the text
 *  @param scale - Scale of the text
 *  @param color - Color of the text
 */
void Font::RenderText(std::string text, float x, float y, float scale, glm::vec3 color) {
    // activate corresponding render state
    glUseProgram(shader);
    glUniform3f(glGetUniformLocation(shader, "textColor"), color.x, color.y, color.z);
    glUniformMatrix4fv(glGetUniformLocation(
        shader,
        "projection"),
        1,
        GL_FALSE,
        glm::value_ptr(projection));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            sizeof(vertices),
            vertices);  // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // bitshift by 6 to get value in pixels
        // (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
