#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>

#include "config.h"
#include "olcPixelGameEngine.h"
#include "shapes.h"
#include "utils.h"

class Tetromino
{
public:
	Tetromino(void);

	enum class Type
	{
		I = 0, O, T, S, Z, J, L, Undefined
	};

	void Draw(olc::PixelGameEngine* pge, std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board);
	void DrawPreview(olc::PixelGameEngine* pge);

	bool MoveDown(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board);
	void MoveLeft(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board);
	void MoveRight(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board);
	void Rotate(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board);

	std::array<PosI, 4> GetPositions(void) { return _property.position; }
	olc::Pixel GetColor(void) { return _property.color; }
	Type GetType(void) { return _property.type; }

private:
	enum class Rotation
	{
		Spawn,
		Rotate90,
		Rotate180,
		Rotate270
	};

	struct Property
	{
		Type type;
		Rotation rotation;
		std::array<std::array<bool, 4>, 4> shape;
		std::array<PosI, 4> position;
		PosI upperLeft;
		olc::Pixel color;
	};

	Property _property;
};

#endif // TETROMINO_H