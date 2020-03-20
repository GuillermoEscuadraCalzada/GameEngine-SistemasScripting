#ifndef ANIMATEDTEXTURE_H
#define ANIMATEDTEXTURE_H
#include "../Texture/Texture.h"
#include "../../GameManager/Timer/Timer.h"
#include <iostream>

using std::string;
class AnimatedTexture : public Texture
{
public:
	enum WRAP_MODE{once = 0, loop = 1};
	enum ANIM_DIR{horizontal = 0, vertical = 1};

	AnimatedTexture(wstring fileName, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animDir);
	~AnimatedTexture();

	void WrapMode(WRAP_MODE mode);
	void Update();

private:
	int startX;
	int startY;

	float animationTimer;
	float animationSpeed;
	float timePerFrame;

	int frameCount;

	WRAP_MODE  wrapMode;
	ANIM_DIR animationDirection;
	Timer* timer;
	bool animationDone;



};


#endif // !ANIMATEDTEXTURE_H
