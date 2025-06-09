#include "tetris.h"

#include <ctime>

Tetris::Tetris(void)
{
	sAppName = "Tetris";
	
	// Initialize random number generator
	std::srand(static_cast<unsigned int>(std::time(0)));

	Tetromino tetromino;
	Tetromino tetrominoNext;
	_tetromino = tetromino;
	_tetrominoNext = tetrominoNext;

	for (uint32_t indexX = 0; indexX < NumberTilesX; indexX++)
	{
		for (uint32_t indexY = 0; indexY < NumberTilesY; indexY++)
		{
			_board[indexX][indexY] = false;
			_boardColors[indexX][indexY] = olc::WHITE;
		}
	}
}

bool Tetris::OnUserCreate(void)
{
	return true;
}

bool Tetris::OnUserUpdate(float fElapsedTime)
{
	_elapsedTime += fElapsedTime;
	Input();
	if (!_pause && _elapsedTime > 0.75)
	{
		Logic();
		_elapsedTime = 0;
	}
	Draw();

	return true;
}

void Tetris::Input()
{
	if (!_pause && GetKey(olc::Key::LEFT).bPressed)
	{
		_tetromino.MoveLeft(_board);
		return;
	}
	if (!_pause && GetKey(olc::Key::RIGHT).bPressed)
	{
		_tetromino.MoveRight(_board);
		return;
	}
	if (!_pause && GetKey(olc::Key::UP).bPressed)
	{
		_tetromino.Rotate(_board);
		return;
	}
	if (!_pause && GetKey(olc::Key::DOWN).bPressed)
	{
		if (_tetromino.MoveDown(_board))
		{
			CollisionHandler();
		}
		return;
	}
	if (GetKey(olc::Key::SPACE).bPressed)
	{
		_pause = !_pause;
		return;
	}
}

void Tetris::Logic(void)
{	
	if (_tetromino.MoveDown(_board))
	{
		// Collision Detected!
		CollisionHandler();
	}
	bool isLineClearing = true;
	int8_t linesCleared = 0;
	while (isLineClearing)
	{
		isLineClearing = CheckLineClearing();
		if (isLineClearing)
		{
			linesCleared++;
		}
	}
	static constexpr std::array<uint32_t, 4> bonusPoints = {40, 100, 300, 1200};
	if (linesCleared > 0)
	{
		_points += bonusPoints[linesCleared - 1];
	}
}

bool Tetris::CheckLineClearing(void)
{
	uint8_t countExist = 0;
	for (uint32_t indexY = 0; indexY < NumberTilesY; indexY++)
	{
		countExist = 0;
		for (uint32_t indexX = 0; indexX < NumberTilesX; indexX++)
		{
			if (_board[indexX][indexY])
			{
				countExist++;
			}
		}
		if (countExist == NumberTilesX)
		{
			LineClearingEvent(indexY);
			return true;
		}
	}
	return false;
}

void Tetris::LineClearingEvent(uint32_t row)
{
	for (uint32_t indexX = 0; indexX < NumberTilesX; indexX++)
	{
		_board[indexX][row] = false;
	}
	for (uint32_t indexY = row; indexY > 0; indexY--)
	{
		for (uint32_t indexX = 0; indexX < NumberTilesX; indexX++)
		{
			_board[indexX][indexY] = _board[indexX][indexY - 1];
			_boardColors[indexX][indexY] = _boardColors[indexX][indexY - 1];
		}
	}
	for (uint32_t indexX = 0; indexX < NumberTilesX; indexX++)
	{
		_board[indexX][0] = false;
	}

}

void Tetris::CollisionHandler(void)
{
	for (uint32_t index = 0; index < NumberBlockShape; index++)
	{
		_board[_tetromino.GetPositions()[index].x][_tetromino.GetPositions()[index].y] = true;
		_boardColors[_tetromino.GetPositions()[index].x][_tetromino.GetPositions()[index].y] = _tetromino.GetColor();
	}
	Tetromino tetromino;
	_tetromino = _tetrominoNext;
	_tetrominoNext = tetromino;
}

void Tetris::Draw(void)
{
	// Erase previous frame
	Clear(olc::BLACK);
	
	DrawBoard();
	DrawBoundaries();
	DrawTopLayerString();
	DrawPointString();

	_tetromino.Draw(this);
	DrawNextTetromino();
}

void Tetris::DrawPointString(void)
{
	std::string pointString = "Points: ";
	pointString.append(std::to_string(_points));
	DrawString(AppWidth - InfoRightWallBorderWidth - InfoWidth + TileSize,
				TopLayerHeight + TopLayerGameBorderHeight + TileSize,
				pointString, olc::WHITE, 2);
}

void Tetris::DrawNextTetromino(void)
{
	_tetrominoNext.DrawPreview(this);
}

void Tetris::DrawTopLayerString(void)
{
	const std::string topLayerString = "TETRIS";
	const olc::vi2d textSize = GetTextSize(topLayerString);
	DrawString((AppWidth - textSize.x) / 2, (TopLayerHeight - textSize.y) / 2, topLayerString, olc::WHITE);
}

void Tetris::DrawBoundaries(void)
{
	DrawLine(0, TopLayerHeight, AppWidth, TopLayerHeight, olc::WHITE);

	DrawLine(LeftWallGameBorderWidth, TopLayerHeight + TopLayerGameBorderHeight,
			LeftWallGameBorderWidth + GameWidth, TopLayerHeight + TopLayerGameBorderHeight,
			olc::WHITE);
	DrawLine(LeftWallGameBorderWidth + GameWidth + GameInfoBorderWidth, TopLayerHeight + TopLayerGameBorderHeight,
			LeftWallGameBorderWidth + GameWidth + GameInfoBorderWidth + InfoWidth, TopLayerHeight + TopLayerGameBorderHeight,
			olc::WHITE);
	DrawLine(LeftWallGameBorderWidth, AppHeight - GameBottomBorderHeight,
			LeftWallGameBorderWidth + GameWidth, AppHeight - GameBottomBorderHeight,
			olc::WHITE);
	DrawLine(LeftWallGameBorderWidth + GameWidth + GameInfoBorderWidth, AppHeight - GameBottomBorderHeight,
			LeftWallGameBorderWidth + GameWidth + GameInfoBorderWidth + InfoWidth, AppHeight - GameBottomBorderHeight,
			olc::WHITE);

	DrawLine(LeftWallGameBorderWidth, TopLayerHeight + TopLayerGameBorderHeight,
			LeftWallGameBorderWidth, TopLayerHeight + TopLayerGameBorderHeight + GameHeight,
			olc::WHITE);
	DrawLine(LeftWallGameBorderWidth + GameWidth, TopLayerHeight + TopLayerGameBorderHeight,
			LeftWallGameBorderWidth + GameWidth, TopLayerHeight + TopLayerGameBorderHeight + GameHeight,
			olc::WHITE);
	DrawLine(LeftWallGameBorderWidth + GameWidth + GameInfoBorderWidth, TopLayerHeight + TopLayerGameBorderHeight,
			LeftWallGameBorderWidth + GameWidth + GameInfoBorderWidth, TopLayerHeight + TopLayerGameBorderHeight + GameHeight,
			olc::WHITE);

	DrawLine(AppWidth - InfoRightWallBorderWidth, TopLayerHeight + TopLayerGameBorderHeight,
			AppWidth - InfoRightWallBorderWidth, TopLayerHeight + TopLayerGameBorderHeight + GameHeight,
			olc::WHITE);

	DrawRect(AppWidth - InfoRightWallBorderWidth - InfoWidth + TileSize,
		     TopLayerHeight + TopLayerGameBorderHeight + 3 * TileSize,
		     5 * TileSize, 5 * TileSize, olc::WHITE);

	for (int32_t index = 1; index < NumberTilesY; index++)
	{
		DrawLine(LeftWallGameBorderWidth, TopLayerHeight + TopLayerGameBorderHeight + TileSize * index,
				LeftWallGameBorderWidth + GameWidth, TopLayerHeight + TopLayerGameBorderHeight + TileSize * index,
				olc::WHITE);
	}
	for (int32_t index = 1; index < NumberTilesX; index++)
	{
		DrawLine(LeftWallGameBorderWidth + index * TileSize, TopLayerHeight + TopLayerGameBorderHeight,
				LeftWallGameBorderWidth + index * TileSize, TopLayerHeight + TopLayerGameBorderHeight + GameHeight,
				olc::WHITE);
	}
}

void Tetris::DrawBoard(void)
{
	for (uint32_t indexX = 0; indexX < NumberTilesX; indexX++)
	{
		for (uint32_t indexY = 0; indexY < NumberTilesY; indexY++)
		{
			if (_board[indexX][indexY])
			{
				FillRect(indexX * TileSize + LeftWallGameBorderWidth, indexY * TileSize + TopLayerGameBorderHeight + TopLayerHeight,
						TileSize, TileSize, _boardColors[indexX][indexY]);
			}
		}
	}
}