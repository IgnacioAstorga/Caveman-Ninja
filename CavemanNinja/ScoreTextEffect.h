#ifndef __SCORETEXTEFFECT_H__
#define __SCORETEXTEFFECT_H__

#include "Entity.h"

class ScoreTextEffect : public Entity
{
public:
	ScoreTextEffect(int score, std::string name, float positionX = 0.0f, float positionY = 0.0f);	// Chapuza: C++ no soporta delegados en los constructores
	~ScoreTextEffect() { OnDestroy(); };

protected:
	void OnCreate();

public:
	int score;
};
#endif	// __SCORETEXTEFFECT_H__