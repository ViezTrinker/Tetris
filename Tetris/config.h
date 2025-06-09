#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

inline constexpr int32_t AppWidth = 460;
inline constexpr int32_t AppHeight = 460;
inline constexpr int32_t PixelWidth = 1;
inline constexpr int32_t PixelHeight = 1;

inline constexpr int32_t TileSize = 20;

inline constexpr int32_t TopLayerWidth = AppWidth;
inline constexpr int32_t TopLayerHeight = TileSize;

inline constexpr int32_t NumberTilesX = 10;
inline constexpr int32_t NumberTilesY = 20;

inline constexpr int32_t GameWidth = NumberTilesX * TileSize;
inline constexpr int32_t GameHeight = NumberTilesY * TileSize;

inline constexpr int32_t InfoWidth = 10 * TileSize;
inline constexpr int32_t InfoHeight = 20 * TileSize;

inline constexpr int32_t TopLayerGameBorderHeight = TileSize;
inline constexpr int32_t LeftWallGameBorderWidth = TileSize;
inline constexpr int32_t GameInfoBorderWidth = TileSize;
inline constexpr int32_t InfoRightWallBorderWidth = TileSize;
inline constexpr int32_t GameBottomBorderHeight = TileSize;

static_assert(AppWidth == LeftWallGameBorderWidth + GameWidth + GameInfoBorderWidth + InfoWidth + InfoRightWallBorderWidth);
static_assert(AppHeight == TopLayerHeight + TopLayerGameBorderHeight + GameHeight + GameBottomBorderHeight);
static_assert(GameHeight == InfoHeight);

#endif