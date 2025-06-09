#include "tetromino.h"

#include <cstdint>
#include <cstdlib>

#include "config.h"
#include "olcPixelGameEngine.h"
#include "tetris.h"

Tetromino::Tetromino(void)
{
	_property.type = static_cast<Type>(std::rand() % static_cast<uint32_t>(Type::Undefined));
	_property.rotation = Rotation::Spawn;

	switch (_property.type)
	{
	case Type::I:
		_property.color = olc::CYAN;
		_property.shape = ShapeI[static_cast<size_t>(Rotation::Spawn)];
		break;
	case Type::J:
		_property.color = olc::BLUE;
		_property.shape = ShapeJ[static_cast<size_t>(Rotation::Spawn)];
		break;
	case Type::L:
		_property.color = olc::VERY_DARK_YELLOW;
		_property.shape = ShapeL[static_cast<size_t>(Rotation::Spawn)];
		break;
	case Type::O:
		_property.color = olc::YELLOW;
		_property.shape = ShapeO[static_cast<size_t>(Rotation::Spawn)];
		break;
	case Type::S:
		_property.color = olc::GREEN;
		_property.shape = ShapeS[static_cast<size_t>(Rotation::Spawn)];
		break;
	case Type::T:
		_property.color = olc::DARK_MAGENTA;
		_property.shape = ShapeT[static_cast<size_t>(Rotation::Spawn)];
		break;
	case Type::Z:
		_property.color = olc::RED;
		_property.shape = ShapeZ[static_cast<size_t>(Rotation::Spawn)];
		break;
	default:
		break;
	}

	_property.upperLeft = { 3, 0 };

	uint32_t indexPos = 0;
	for (uint32_t indexY = 0; indexY < 4; indexY++)
	{
		for (uint32_t indexX = 0; indexX < 4; indexX++)
		{
			if (!_property.shape[indexY][indexX])
			{
				continue;
			}
			_property.position[indexPos].x = indexX + 3;
			_property.position[indexPos].y = indexY;
			indexPos++;

		}
	}
}

void Tetromino::Rotate(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board)
{
	if (_property.rotation == Rotation::Rotate270)
	{
		_property.rotation = Rotation::Spawn;
	}
	else
	{
		_property.rotation = static_cast<Rotation>(static_cast<uint8_t>(_property.rotation) + 1);
	}
	
	switch (_property.type)
	{
	case Type::I:
		_property.shape = ShapeI[static_cast<size_t>(_property.rotation)];
		break;
	case Type::J:
		_property.shape = ShapeJ[static_cast<size_t>(_property.rotation)];
		break;
	case Type::L:
		_property.shape = ShapeL[static_cast<size_t>(_property.rotation)];
		break;
	case Type::O:
		_property.shape = ShapeO[static_cast<size_t>(_property.rotation)];
		break;
	case Type::S:
		_property.shape = ShapeS[static_cast<size_t>(_property.rotation)];
		break;
	case Type::T:
		_property.shape = ShapeT[static_cast<size_t>(_property.rotation)];
		break;
	case Type::Z:
		_property.shape = ShapeZ[static_cast<size_t>(_property.rotation)];
		break;
	default:
		break;
	}

	std::array<PosI, 4> positionBuffer;

	uint32_t indexPos = 0;
	for (uint32_t indexY = 0; indexY < 4; indexY++)
	{
		for (uint32_t indexX = 0; indexX < 4; indexX++)
		{
			if (!_property.shape[indexY][indexX])
			{
				continue;
			}
			positionBuffer[indexPos].x = indexX + _property.upperLeft.x;
			positionBuffer[indexPos].y = indexY + _property.upperLeft.y;
			indexPos++;
		}
	}

	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		if (positionBuffer[index].y > NumberTilesY - 1 || positionBuffer[index].y < 0)
		{
			return;
		}
		if (positionBuffer[index].x > NumberTilesX - 1 || positionBuffer[index].x < 0)
		{
			return;
		}
		if (board[positionBuffer[index].x][positionBuffer[index].y])
		{
			return;
		}
	}
	_property.position = positionBuffer;

}

bool Tetromino::MoveDown(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board)
{
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		if (_property.position[index].y + 1 > NumberTilesY - 1)
		{
			return true;
		}
		if (board[_property.position[index].x][_property.position[index].y + 1])
		{
			return true;
		}
	}
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		_property.position[index].y += 1;
	}
	_property.upperLeft.y += 1;
	return false;
}

void Tetromino::MoveLeft(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board)
{
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		if (_property.position[index].x - 1 < 0)
		{
			return;
		}
		if (board[_property.position[index].x - 1][_property.position[index].y])
		{
			return;
		}
	}
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		_property.position[index].x -= 1;
	}
	_property.upperLeft.x -= 1;
}

void Tetromino::MoveRight(std::array<std::array<bool, NumberTilesY>, NumberTilesX>& board)
{
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		if (_property.position[index].x + 1 > NumberTilesX - 1)
		{
			return;
		}
		if (board[_property.position[index].x + 1][_property.position[index].y])
		{
			return;
		}
	}
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		_property.position[index].x += 1;
	}
	_property.upperLeft.x += 1;
}

void Tetromino::Draw(olc::PixelGameEngine* pge)
{
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		pge->FillRect(_property.position[index].x * TileSize + LeftWallGameBorderWidth,
			_property.position[index].y * TileSize + TopLayerHeight + TopLayerGameBorderHeight,
			TileSize, TileSize,
			_property.color);
	}
}

void Tetromino::DrawPreview(olc::PixelGameEngine* pge)
{
	for (uint32_t indexX = 0; indexX < NumberBlockShape; indexX++)
	{
		for (uint32_t indexY = 0; indexY < NumberBlockShape; indexY++)
		{
			if (!_property.shape[indexY][indexX])
			{
				continue;
			}
			
			pge->FillRect(indexX * TileSize + AppWidth - InfoRightWallBorderWidth - InfoWidth + 2 * TileSize,
				indexY * TileSize + TopLayerHeight + TopLayerGameBorderHeight + 4 * TileSize,
				TileSize, TileSize,
				_property.color);
		}
	}
}