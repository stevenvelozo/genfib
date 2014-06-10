/**
* This include file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*/
#ifndef DIGMATHRENDER_H_INCLUDED
#define DIGMATHRENDER_H_INCLUDED
#include "../lib/gmp.h"
#include "/usr/local/include/libpng16/png.h"
#include "../common/digmathcommon.h"
#include <stdio.h>

typedef struct
{
	int Width;
	int Height;

	char *FileName;
	FILE *FilePointer;

	char *Title;

	png_structp png_StructPointer;
	png_infop png_InfoPointer;
	png_bytep png_RowPointer;
} structRenderableImage;

unsigned char renderer_get_red(mpz_t *pValue, structSetStatistics *pSetStatistics);
unsigned char renderer_get_green(mpz_t *pValue, structSetStatistics *pSetStatistics);
unsigned char renderer_get_blue(mpz_t *pValue, structSetStatistics *pSetStatistics);

void renderer_png_init(structRenderableImage *pImage, char *pFileName, int pWidth, int pHeight, char *pTitle);
void renderer_png_finalize(structRenderableImage *pImage);
void renderer_png_write_row(structRenderableImage *pImage);
void renderer_png_setcolor_x(structRenderableImage *pImage, int pX, unsigned char pRed, unsigned char pGreen, unsigned char pBlue);

void renderer_color_scaled_initialize(structSetStatistics *pSetStatistics);

#endif /* DIGMATHRENDER_H_INCLUDED */