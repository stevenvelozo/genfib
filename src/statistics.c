/**
* This source file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*/
#include <digmathcommon.h>
#include "../lib/gmp.h"

void statistics_init(structSetStatistics *pSetStatistics)
{
	mpz_init(pSetStatistics->ValueMin);
	mpz_init(pSetStatistics->ValueMax);

	mpf_init(pSetStatistics->ValueStep);

	mpz_init(pSetStatistics->ValueCount);
	mpz_init(pSetStatistics->ValueSum);

	mpz_init(pSetStatistics->ValueMean);
	mpf_init(pSetStatistics->ValueMedian);

	mpz_set_ui(pSetStatistics->ValueMin, 0);
	mpz_set_ui(pSetStatistics->ValueMax, 0);

	mpf_set_ui(pSetStatistics->ValueStep, 0);

	mpz_set_ui(pSetStatistics->ValueCount, 0);
	mpz_set_ui(pSetStatistics->ValueSum, 0);

	mpz_set_ui(pSetStatistics->ValueMean, 0);
	mpf_set_ui(pSetStatistics->ValueMedian, 0);
}

void statistics_destroy(structSetStatistics *pSetStatistics)
{
	mpz_clear(pSetStatistics->ValueMin);
	mpz_clear(pSetStatistics->ValueMax);

	mpf_clear(pSetStatistics->ValueStep);

	mpz_clear(pSetStatistics->ValueCount);
	mpz_clear(pSetStatistics->ValueSum);

	mpz_clear(pSetStatistics->ValueMean);
	mpf_clear(pSetStatistics->ValueMedian);
}

void statistics_add_value(mpz_t *pValue, structSetStatistics *pSetStatistics)
{
	if (mpz_cmp(*pValue, pSetStatistics->ValueMin) < 0)
		mpz_set(pSetStatistics->ValueMin, *pValue);
	if (mpz_cmp(*pValue, pSetStatistics->ValueMax) > 0)
		mpz_set(pSetStatistics->ValueMax, *pValue);

	mpz_add_ui(pSetStatistics->ValueCount, pSetStatistics->ValueCount, 1);
	mpz_add(pSetStatistics->ValueSum, pSetStatistics->ValueSum, *pValue);
}

void solve_statistics_set(structSetStatistics *pSetStatistics)
{
	if (mpz_cmp_d(pSetStatistics->ValueCount,0)<=0)
		return;

	mpf_t tmpSetSize;
	mpf_t tmpSetMin;
	mpf_t tmpSetMax;
	mpf_t tmpSetValueSum;
	mpf_t tmpSetValueCount;
	mpf_t tmpColorDepth;
	mpf_init(tmpSetSize);
	mpf_init(tmpSetMin);
	mpf_init(tmpSetMax);
	mpf_init(tmpSetValueSum);
	mpf_init(tmpSetValueCount);
	mpf_init(tmpColorDepth);

	mpf_set_z(tmpSetMin, pSetStatistics->ValueMin);
	mpf_set_z(tmpSetMax, pSetStatistics->ValueMax);
	mpf_set_z(tmpSetValueSum, pSetStatistics->ValueSum);
	mpf_set_z(tmpSetValueCount, pSetStatistics->ValueCount);
	mpf_set_ui(tmpColorDepth, 256);

	mpf_sub(tmpSetSize, tmpSetMax, tmpSetMin);

	mpf_div(pSetStatistics->ValueStep, tmpColorDepth, tmpSetSize);
	mpf_div(pSetStatistics->ValueMedian, tmpSetValueSum, tmpSetValueCount);

	mpf_clear(tmpSetSize);
	mpf_clear(tmpSetMin);
	mpf_clear(tmpSetMax);
	mpf_clear(tmpSetValueSum);
	mpf_clear(tmpSetValueCount);
	mpf_clear(tmpColorDepth);
}
