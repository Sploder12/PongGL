#include <glm/glm.hpp>
#include <map>

std::map<char, glm::vec2> spriteSizes = {('p',(8,32)), ('E',(32,32))};


class spriteObj {
private:
	glm::vec2 wh = glm::vec2(0.0f,0.0f);
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
public:
	glm::vec4 pos = glm::vec4(-5.0f,-5.0f,-5.0f,0.0f);
	char sprite = NULL;

	spriteObj(glm::vec4 pos, char spr) {
		this->pos = pos;
		this->sprite = spr;
		try {
			this->wh = spriteSizes[spr];
		}
		catch (int e) {
			this->sprite = 'E';
			this->wh = spriteSizes['E'];
		}
	}

	void scale(glm::vec3 scl) {
		this->scale = scl;
		wh.x *= scl.x;
		wh.y *= scl.y;
	}
};
