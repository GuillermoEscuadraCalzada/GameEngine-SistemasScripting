#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(string fileName, int x, int y,int w, int h, int frameCount, float animationSpeed, ANIM_DIR animDir) : Texture(fileName, x, y, w, h)
{
	timer = Timer::getPTR();

	startX = x;
	startY = y;
	
	this->frameCount = frameCount;
	this->animationSpeed = animationSpeed;
	timePerFrame = this->animationSpeed / this->frameCount;
	animationTimer = 0.0f;

	animationDirection = animDir;
	animationDone = false;

	wrapMode = loop;
}

AnimatedTexture::~AnimatedTexture()
{
}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	wrapMode = mode;
}

void AnimatedTexture::Update()
{
	if(!animationDone)
	{
		animationTimer += timer->DeltaTime();
		if(animationTimer >= animationSpeed)
		{
			if(wrapMode == loop)
			{
				animationTimer -= animationSpeed;
			} else
			{
				animationDone = true;
				animationTimer = animationSpeed - timePerFrame;
			}
		}
		if(animationDirection == horizontal)
		{
			clippedRect.x = startX + (int)(animationTimer/timePerFrame) * width;
		} else
		{
			clippedRect.y = startY + (int)(animationTimer / timePerFrame) * height;
		}
	}
}
