/**
* This source file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*
* This code provides common messaging and printing functions
*/
#include <digmathcommon.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "../lib/gmp.h"

void print_help()
{
	printf(" genfib version 0.1\n");
	printf(" Licensed under the MIT License\n");
	printf(" Copyright Steven Velozo (steven@velozo.com) 2013\n");
	printf("\n");
	printf("   Command Line Arguments:\n");
	printf(" --------------------------------\n");
	printf(" -h                         Show the CSV Header\n");
	printf(" -a                         Show Column Value\n");
	printf(" -d                         Show Row Value\n");
	printf(" -s                         Show the Approximate Number of Characters\n");
	printf(" -o                         Show the Ordinal\n");
	printf(" -r [number]                Show [number] Rows (default 10)\n");
	printf(" -R [iteration_number]      Use [iteration_number] Algorithm for Row Values\n");
	printf(" -c [number]                Show [number] Columns (default 10)\n");
	printf(" -C [iteration_number]      Use [iteration_number] Algorithm for Column Values\n");
	printf(" -I [computation_style]     Use [computation_style] for Intersections\n");
	printf(" -?                         Show help\n");
	printf("\n");
	printf("   Iteration Styles:\n");
	printf(" -------------------------------\n");
	printf(" 1 . . . . . . . . . . Fibonacci\n");
	printf(" 2 . . . . . . . . . . . . Lucas\n");
	printf(" 3 . . . . . . . . . Incremental\n");
	printf(" 4 . . . . . . . . . . . Padovan\n");
	printf(" 5 . . . . . . . . . . . .  Pell\n");
	printf("\n");
	printf("   Computation Styles:\n");
	printf(" -------------------------------\n");
	printf(" 1 . . . . . . . . . . .  Modulo\n");
	printf(" 2 . . . . . . . . . . .  Divide\n");
	printf(" 3 . . . . . . . . . .  Multiply\n");
	printf(" 4 . . . . . . . . . . . . . Add\n");
	printf(" 5 . .. . . . . . . . . Subtract\n");
	printf("\n");
	return;
}

void csv_print_string(int pShowValue, char *pText, structSettingsValues *pSettings)
{
	if (!pShowValue)
		return;
	if (pSettings->LineHasData)
		gmp_printf(",");
	gmp_printf(pText);
	pSettings->LineHasData = true;
}

void csv_print_int(int pShowValue, int pValue, structSettingsValues *pSettings)
{
	if (!pShowValue)
		return;
	if (pSettings->LineHasData)
		gmp_printf(",");
	gmp_printf("%i", pValue);
	pSettings->LineHasData = true;
}

void csv_print_sizet(int pShowValue, size_t pValue, structSettingsValues *pSettings)
{
	if (!pShowValue)
		return;
	if (pSettings->LineHasData)
		gmp_printf(",");
	gmp_printf("%zd", pValue);
	pSettings->LineHasData = true;
}

void csv_print_mpz(int pShowValue, mpz_t pValue, structSettingsValues *pSettings)
{
	if (!pShowValue)
		return;
	if (pSettings->LineHasData)
		gmp_printf(",");
	gmp_printf("%Zd", pValue);
	pSettings->LineHasData = true;
}

void csv_print_eol(structSettingsValues *pSettings)
{
	if (pSettings->LineHasData)
		printf("\n");
	pSettings->LineHasData = false;
}

void debug_print_set_statistics_data(structSetStatistics *pSetStatistics, char * pMessage)
{
	gmp_printf("\n=== %s ===\n", pMessage);
	gmp_printf("     Min: %Zd\n", pSetStatistics->ValueMin);
	gmp_printf("     Max: %Zd\n", pSetStatistics->ValueMax);
	gmp_printf("   Count: %Zd\n", pSetStatistics->ValueCount);
	gmp_printf("     Sum: %Zd\n", pSetStatistics->ValueSum);
	gmp_printf("    Step: %.*Ff\n", 10, pSetStatistics->ValueStep);
	gmp_printf("    Mean: %.*Ff\n", 10, pSetStatistics->ValueMedian);
//	int tmpCounter;
//	for(tmpCounter = 0; tmpCounter < 256; tmpCounter++)
//		gmp_printf("   Scale: [%d] %.90F\n", tmpCounter, pSetStatistics->GlobalRenderThreshold[tmpCounter]);
}

void debug_print_iteration_data(structIterationValue *pIterationValue, char * pMessage)
{
	gmp_printf("\n=== %s ===\n", pMessage);
	gmp_printf("  Value: %Zd\n", pIterationValue->Value);
	gmp_printf(" CValue: %Zd\n", pIterationValue->ChildValue);
	gmp_printf("GCValue: %Zd\n", pIterationValue->GrandchildValue);
	gmp_printf("GGValue: %Zd\n", pIterationValue->GreatGrandchildValue);
}
