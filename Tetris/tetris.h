#ifndef TETRIS_H
#define TETRIS_H

#include "config.h"
#include "olcPixelGameEngine.h"

class Tetris : public olc::PixelGameEngine
{
public:
	Tetris(void);

	bool OnUserCreate(void) override;
	bool OnUserUpdate(float fElapsedTime) override;
private:
	void Draw(void);
	void DrawBoundaries(void);
	void DrawTopLayerString(void);
	
	float _elapsedTime = 0.0f;
};

#endif //TETRIS_H