#include "tetris.h"

Tetris::Tetris(void)
{
	sAppName = "Tetris";
}

bool Tetris::OnUserCreate(void)
{
	return true;
}

bool Tetris::OnUserUpdate(float fElapsedTime)
{
	_elapsedTime = fElapsedTime;

	Draw();

	return true;
}

void Tetris::Draw(void)
{
	// Erase previous frame
	Clear(olc::BLACK);
	
	DrawBoundaries();
	DrawTopLayerString();
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