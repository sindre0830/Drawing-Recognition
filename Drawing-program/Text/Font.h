#ifndef TEXT_FONT_H_
#define TEXT_FONT_H_

/**
 * @file Font.h
 * @author Maren Skårestuen Grindal
 * @version 0.1
 * @date 2021-11-12
 *
 * @copyright Copyright (c) 2021 Sindre Eiklid, Rickard Loland, Maren Skårestuen Grindal
 */



#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

#endif  // TEXT_FONT_H_
