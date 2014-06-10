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

void intersection_compute_value(int pComputationStyle, mpz_t *pIntersectionValue, structIterationValue *pRowValue, structIterationValue *pColumnValue)
{
	switch (pComputationStyle)
	{
		case Modulo:
			mpz_mod(*pIntersectionValue, pColumnValue->Value, pRowValue->Value);
			break;
		case Divide:
			mpz_div(*pIntersectionValue, pColumnValue->Value, pRowValue->Value);
			break;
		case Multiply:
			mpz_mul(*pIntersectionValue, pColumnValue->Value, pRowValue->Value);
			break;
		case Add:
			mpz_add(*pIntersectionValue, pColumnValue->Value, pRowValue->Value);
			break;
		case Subtract:
			mpz_sub(*pIntersectionValue, pColumnValue->Value, pRowValue->Value);
			break;
	}
}
