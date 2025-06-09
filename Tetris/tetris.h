#ifndef TETRIS_H
#define TETRIS_H

#include <array>

#include "config.h"
#include "olcPixelGameEngine.h"
#include "tetromino.h"

class Tetris : public olc::PixelGameEngine
{
public:
	Tetris(void);

	bool OnUserCreate(void) override;
	bool OnUserUpdate(float fElapsedTime) override;
private:	
	void Input(void);
	
	void Logic(void);
	
	void Draw(void);
	void DrawBoundaries(void);
	void DrawTopLayerString(void);
	void DrawPointString(void);
	void DrawBoard(void);
	void DrawNextTetromino(void);

	void CollisionHandler(void);
	bool CheckLineClearing(void);
	void LineClearingEvent(uint32_t row);

	Tetromino _tetromino;
	Tetromino _tetrominoNext;
	
	double _elapsedTime = 0.0;

	bool _pause = true;

	std::array<std::array<bool, NumberTilesY>, NumberTilesX> _board{};
	std::array<std::array<olc::Pixel, NumberTilesY>, NumberTilesX> _boardColors{};

	uint32_t _points = 0;
	static constexpr float _elapsedTimeThresholdDefault = 0.75;
	float _elapsedTimeThreshold = _elapsedTimeThresholdDefault;
};

#endif //TETRIS_H