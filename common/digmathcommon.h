/**
* This include file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*/
#ifndef DIGMATHCOMMON_H_INCLUDED
#define DIGMATHCOMMON_H_INCLUDED

#include "../lib/gmp.h"
#include <stddef.h>

enum enumIterationStyle
{
	Fibonacci,
	Lucas,
	Incremental,
	Pell,
	Padovan
};

enum enumComputationStyle
{
	Modulo,
	Divide,
	Multiply,
	Add,
	Subtract
};

typedef struct
{
	int ShowApproximateLength;

	int ShowHeader;
	int ShowOrdinal;

	int ShowRowValue;
	int ShowColumnValue;

	int ComputeRowPrime;

	int RowValueCount;
	int ColumnValueCount;

	int PrintSetStatistics;

	int LineHasData;

	int RenderImage;
	char * ImageFileName;

	enum enumIterationStyle RowIterationStyle;
	enum enumIterationStyle ColumnIterationStyle;

	enum enumComputationStyle ComputationStyle;

} structSettingsValues;

typedef struct
{
	int IterationStyle;

	int Ordinal;

	int ComputePrime;
	int IsPrime;

	mpz_t Value;
	size_t ValueLength;

	mpz_t ChildValue;
	mpz_t GrandchildValue;
	mpz_t GreatGrandchildValue;
} structIterationValue;

typedef struct
{
	mpz_t ValueMin;
	mpz_t ValueMax;

	mpz_t ValueCount;
	mpz_t ValueSum;

	mpf_t ValueStep;

	mpz_t ValueMean;
	mpf_t ValueMedian;

	mpf_t GlobalRenderThreshold[256];
} structSetStatistics;

void print_help();

void csv_print_string(int pShowValue, char *pText, structSettingsValues *pSettings);
void csv_print_int(int pShowValue, int pValue, structSettingsValues *pSettings);
void csv_print_sizet(int pShowValue, size_t pValue, structSettingsValues *pSettings);
void csv_print_mpz(int pShowValue, mpz_t pValue, structSettingsValues *pSettings);
void csv_print_eol(structSettingsValues *pSettings);

void debug_print_set_statistics_data(structSetStatistics *pSetStatistics, char * pMessage);
void debug_print_iteration_data(structIterationValue *pIterationValue, char * pMessage);

void settings_set_defaults(structSettingsValues *pSettings);
void settings_parse_arguments(int argc, char *argv[], structSettingsValues *pSettings);

#endif  /* DIGMATHCOMMON_H_INCLUDED */