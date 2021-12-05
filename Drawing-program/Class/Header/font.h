/**
 * @file font.h
 * @author Joey de Vries
 * @author Maren Sk�restuen Grindal
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copytight (c) Joey de Vries https://learnopengl.com/In-Practice/Text-Rendering
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Sk�restuen Grindal
 */

#ifndef CLASS_HEADER_FONT_H_
#define CLASS_HEADER_FONT_H_

/* external libraries */
#include <glad/glad.h>
#include <ft2build.h>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include FT_FREETYPE_H

/**
 *  Struct for storing information about a character.
 */
struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Horizontal offset to advance to next glyph
};

/**
 *  Class for loading and rendering fonts.
 */
class Font {
 private:
    std::string path;
    int size;
    std::map<GLchar, Character> Characters;
    unsigned int VAO, VBO, shader;
    glm::mat4 projection;
 public:
    Font(std::string path, int size);
    ~Font();

    void loadFont();
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif  // CLASS_HEADER_FONT_H_
