/**
* This include file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*/
#ifndef ITERATE_H_INCLUDED
#define ITERATE_H_INCLUDED

#include "../lib/gmp.h"
#include "digmathcommon.h"

void intersection_compute_value(int pComputationStyle, mpz_t *pIntersectionValue, structIterationValue *pRowValue, structIterationValue *pColumnValue);

void iteration_value_init(structIterationValue *pIterationValue, int pIterationStyle);
void iteration_value_destroy(structIterationValue *pIterationValue);
void iteration_compute_value(structIterationValue *pIterationValue);
void iteration_prepare_computation_values(structIterationValue *pIterationValue);

void solve_statistics_set(structSetStatistics *pSetStatistics);
void statistics_init(structSetStatistics *pSetStatistics);
void statistics_destroy(structSetStatistics *pSetStatistics);
void statistics_add_value(mpz_t *pValue, structSetStatistics *pSetStatistics);

#endif