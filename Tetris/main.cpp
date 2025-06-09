#include "config.h"
#include "tetris.h"

int main()
{	
	Tetris tetris;
	if (tetris.Construct(AppWidth, AppHeight, PixelWidth, PixelHeight))
	{
		tetris.Start();
	}
}