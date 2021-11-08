#ifndef  __FONT_H
#define __FONT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ft2build.h"
#include FT_FREETYPE_H

#include <string>
#include <map>

/**
 *	Struct for storing information about a character.
 */
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

/**
 *	Class for loading and rendering fonts.
 */
class Font {
private:
	std::string name;
	int size;
	std::map<GLchar, Character> Characters;
	unsigned int VAO, VBO, shader;
	glm::mat4 projection;
	FT_Library ft;
public:
	Font(FT_Library ft, std::string name, int size);
	~Font();

	void loadFont();
	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif // ! __FONT_H
