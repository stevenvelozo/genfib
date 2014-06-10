/**
* This source file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*/
#include <digmathrender.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/gmp.h"
#include "/usr/local/include/libpng16/png.h"

void renderer_png_cleanup(structRenderableImage *pImage)
{
	if (pImage->FilePointer != NULL)
		fclose(pImage->FilePointer);
	if (pImage->png_InfoPointer != NULL)
		png_free_data(pImage->png_StructPointer, pImage->png_InfoPointer, PNG_FREE_ALL, -1);
	if (pImage->png_StructPointer != NULL)
		png_destroy_write_struct(&(pImage->png_StructPointer), (png_infopp)NULL);
	if (pImage->png_RowPointer != NULL)
		free(pImage->png_RowPointer);
}

void renderer_png_error(structRenderableImage *pImage, char *pMessage)
{
	fprintf(stderr, "%s\n", pMessage);
	renderer_png_cleanup(pImage);
}

void renderer_png_set_metadata(structRenderableImage *pImage)
{
	png_set_IHDR(pImage->png_StructPointer, pImage->png_InfoPointer, pImage->Width, pImage->Height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	if (pImage->Title != NULL)
	{
		png_text tmpTitleText;
		tmpTitleText.compression = PNG_TEXT_COMPRESSION_NONE;
		tmpTitleText.key = "Title";
		tmpTitleText.text = pImage->Title;
		png_set_text(pImage->png_StructPointer, pImage->png_InfoPointer, &tmpTitleText, 1);
	}
	png_write_info(pImage->png_StructPointer, pImage->png_InfoPointer);
}

void renderer_png_init(structRenderableImage *pImage, char *pFileName, int pWidth, int pHeight, char *pTitle)
{
	pImage->FileName = pFileName;
	pImage->Title = pTitle;

	pImage->Width = pWidth;
	pImage->Height = pHeight;

	pImage->FilePointer = fopen(pImage->FileName, "wb");

	if (pImage->FilePointer == NULL)
	{
		renderer_png_error(pImage, "Error opening png file for writing.");
		return;
	}

	pImage->png_StructPointer = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (pImage->png_StructPointer == NULL)
	{
		renderer_png_error(pImage, "Error allocating png write structure.");
		return;
	}

	pImage->png_InfoPointer = png_create_info_struct(pImage->png_StructPointer);
	if (pImage->png_InfoPointer == NULL)
	{
		renderer_png_error(pImage, "Error allocating png info structure.");
		return;
	}

	if (setjmp(png_jmpbuf(pImage->png_StructPointer)))
	{
		renderer_png_error(pImage, "Error initializing png format.");
		return;
	}

	png_init_io(pImage->png_StructPointer, pImage->FilePointer);

	pImage->png_RowPointer = (png_bytep)malloc(3 * pImage->Width * sizeof(png_byte));

	renderer_png_set_metadata(pImage);
}

void renderer_png_finalize(structRenderableImage *pImage)
{
	png_write_end(pImage->png_StructPointer, NULL);
	renderer_png_cleanup(pImage);
}

void renderer_png_write_row(structRenderableImage *pImage)
{
	png_write_row(pImage->png_StructPointer, pImage->png_RowPointer);
}

void renderer_png_setcolor_x(structRenderableImage *pImage, int pX, unsigned char pRed, unsigned char pGreen, unsigned char pBlue)
{
	pImage->png_RowPointer[pX*3] = pRed;
	pImage->png_RowPointer[pX*3+1] = pGreen;
	pImage->png_RowPointer[pX*3+2] = pBlue;
}
