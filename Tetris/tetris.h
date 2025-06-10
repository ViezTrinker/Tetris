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
	void DrawStats(void);

	void CollisionHandler(void);
	bool CheckLineClearing(void);
	void LineClearingEvent(uint32_t row);
	void CheckLosingCondition(void);

	Tetromino _tetromino;
	Tetromino _tetrominoNext;
	
	double _elapsedTime = 0.0;

	bool _pause = true;
	bool _gameLost = false;

	std::array<std::array<bool, NumberTilesY>, NumberTilesX> _board{};
	std::array<std::array<olc::Pixel, NumberTilesY>, NumberTilesX> _boardColors{};

	uint32_t _points = 0;
	static constexpr float _elapsedTimeThresholdDefault = 0.75;
	float _elapsedTimeThreshold = _elapsedTimeThresholdDefault;

	struct Stats
	{
		uint32_t countI = 0;
		uint32_t countO = 0;
		uint32_t countT = 0;
		uint32_t countS = 0;
		uint32_t countZ = 0;
		uint32_t countJ = 0;
		uint32_t countL = 0;

		uint32_t lineClears = 0;
		uint32_t lineClears1 = 0;
		uint32_t lineClears2 = 0;
		uint32_t lineClears3 = 0;
		uint32_t lineClears4 = 0;
	};
	Stats _stats{};

	void IncrementTypeStats(Tetromino::Type type);
};

#endif //TETRIS_H