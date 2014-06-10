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

// A simple coloring scheme with a linear set of "boxes" for values.
// Custom color for 0.
unsigned char renderer_colorer_simple(mpz_t *pValue, structSetStatistics *pSetStatistics, unsigned char pZeroColor)
{
	unsigned char tmpColor;
	unsigned int tmpColorInteger;

	mpf_t tmpMulValue;
	mpf_t tmpColorResult;

	mpf_init(tmpMulValue);
	mpf_init(tmpColorResult);

	mpf_set_z(tmpMulValue, *pValue);
	mpf_mul(tmpColorResult, tmpMulValue, pSetStatistics->ValueStep);

	tmpColorInteger = mpf_get_ui(tmpColorResult);
	tmpColor = (unsigned char)(tmpColorInteger);

	// Special coloring for the "0" value
	if (mpz_cmp_d(*pValue,0) == 0)
		tmpColor = pZeroColor;

	mpf_clear(tmpMulValue);
	mpf_clear(tmpColorResult);

	return tmpColor;
}

unsigned char renderer_get_red(mpz_t *pValue, structSetStatistics *pSetStatistics)
{
	return renderer_colorer_simple(pValue, pSetStatistics, 255);
}

unsigned char renderer_get_green(mpz_t *pValue, structSetStatistics *pSetStatistics)
{
	return renderer_colorer_simple(pValue, pSetStatistics, 0);
}

unsigned char renderer_get_blue(mpz_t *pValue, structSetStatistics *pSetStatistics)
{
	return renderer_colorer_simple(pValue, pSetStatistics, 255);
}

unsigned char renderer_color_scaled(mpz_t $pValue, structSetStatistics *pSetStatistics, unsigned char pZeroColor)
{
	unsigned char tmpColor;

	return tmpColor;
}

void renderer_color_scaled_initialize(structSetStatistics *pSetStatistics)
{
	mpf_t tmpValue;
	mpf_t tmpComputed;
	mpf_t tmpTopValue;
	mpf_t tmpDivisor;
	mpf_t tmpDivisorBase;

	mpf_init(tmpValue);
	mpf_init(tmpComputed);

	mpf_init(tmpTopValue);
	mpf_set_z(tmpTopValue, pSetStatistics->ValueMax);

	mpf_init(tmpDivisor);
	mpf_init(tmpDivisorBase);
	mpf_set_ui(tmpDivisorBase, 2);

	int tmpCounter;
	for(tmpCounter = 0; tmpCounter < 256; tmpCounter++)
	{
		mpf_init(pSetStatistics->GlobalRenderThreshold[tmpCounter]);
		mpf_set_ui(tmpComputed, tmpCounter);
		mpf_add(tmpDivisor, tmpDivisorBase, tmpComputed);

		if (tmpCounter < 255)
		{
			mpf_div(tmpValue, tmpTopValue, tmpDivisor);
			mpf_set(pSetStatistics->GlobalRenderThreshold[tmpCounter], tmpValue);
			mpf_set(tmpTopValue, tmpValue);
			//gmp_printf("   SCOMP: [%d] v:%.10Ff tv:%.10Ff d:%.10Ff c:%.10Ff\n", tmpCounter, tmpValue, tmpTopValue, tmpDivisor, tmpComputed);
		}
		else
		{
			mpf_set_ui(pSetStatistics->GlobalRenderThreshold[tmpCounter], 0);
		}
	}

	mpf_clear(tmpTopValue);
	mpf_clear(tmpValue);
	mpf_clear(tmpDivisor);
	mpf_clear(tmpDivisorBase);
	mpf_clear(tmpComputed);
}
