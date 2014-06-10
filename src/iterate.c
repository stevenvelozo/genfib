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

void iteration_value_init(structIterationValue *pIterationValue, int pIterationStyle)
{
	pIterationValue->Ordinal = 0;
	pIterationValue->ValueLength = 0;
	pIterationValue->IterationStyle = pIterationStyle;
	pIterationValue->IsPrime = 0;
	pIterationValue->ComputePrime  = 0;
	mpz_init(pIterationValue->Value);
	mpz_init(pIterationValue->ChildValue);
	mpz_init(pIterationValue->GrandchildValue);
	mpz_init(pIterationValue->GreatGrandchildValue);
}

void iteration_value_destroy(structIterationValue *pIterationValue)
{
	pIterationValue->Ordinal = 0;
	pIterationValue->ValueLength = 0;
	mpz_clear(pIterationValue->Value);
	mpz_clear(pIterationValue->ChildValue);
	mpz_clear(pIterationValue->GrandchildValue);
	mpz_clear(pIterationValue->GreatGrandchildValue);
}

void iteration_compute_value(structIterationValue *pIterationValue)
{
	switch(pIterationValue->IterationStyle)
	{
		case Fibonacci:
			if (mpz_cmp_d(pIterationValue->GrandchildValue,0)==0 && mpz_cmp_d(pIterationValue->ChildValue,0)==0)
				mpz_set_ui(pIterationValue->Value, 1);
			else
				mpz_add(pIterationValue->Value, pIterationValue->GrandchildValue, pIterationValue->ChildValue);
			break;
		case Lucas:
			if (mpz_cmp_d(pIterationValue->GrandchildValue,0)==0 && mpz_cmp_d(pIterationValue->ChildValue,0)==0)
				mpz_set_ui(pIterationValue->Value, 1);
			else if (mpz_cmp_d(pIterationValue->GrandchildValue,0)==0 && mpz_cmp_d(pIterationValue->ChildValue,1)==0)
				mpz_set_ui(pIterationValue->Value, 3);
			else
				mpz_add(pIterationValue->Value, pIterationValue->GrandchildValue, pIterationValue->ChildValue);
			break;
		case Padovan:
			if (mpz_cmp_d(pIterationValue->GreatGrandchildValue,0)==0)
				mpz_set_ui(pIterationValue->Value, 1);
			else
				mpz_add(pIterationValue->Value, pIterationValue->GreatGrandchildValue, pIterationValue->GrandchildValue);
			break;
		case Pell:
			if (mpz_cmp_d(pIterationValue->GrandchildValue,0)==0 && mpz_cmp_d(pIterationValue->ChildValue,0)==0)
				mpz_set_ui(pIterationValue->Value, 1);
			else
			{
				mpz_t tmpMulValue;
				mpz_init(tmpMulValue);
				mpz_mul_ui(tmpMulValue, pIterationValue->ChildValue, 2);
				mpz_add(pIterationValue->Value, tmpMulValue, pIterationValue->GrandchildValue);
				mpz_clear(tmpMulValue);
			}
			break;
		case Incremental:
		default:
			mpz_add_ui(pIterationValue->Value, pIterationValue->Value, 1);
			break;
	}

	if (pIterationValue->ComputePrime)
	{
		pIterationValue->IsPrime = mpz_probab_prime_p(pIterationValue->Value, 50);
	}

	return;
}

void iteration_prepare_computation_values(structIterationValue *pIterationValue)
{
	switch(pIterationValue->IterationStyle)
	{
		// Lucas and Fibonacci share the same post process
		case Fibonacci:
		case Lucas:
		case Pell:
			mpz_set(pIterationValue->GrandchildValue,pIterationValue->ChildValue);
			mpz_set(pIterationValue->ChildValue,pIterationValue->Value);
			break;
		case Padovan:
			mpz_set(pIterationValue->GreatGrandchildValue,pIterationValue->GrandchildValue);
			mpz_set(pIterationValue->GrandchildValue,pIterationValue->ChildValue);
			mpz_set(pIterationValue->ChildValue,pIterationValue->Value);
			break;
		case Incremental:
		default:
			break;
	}

	return;
}

