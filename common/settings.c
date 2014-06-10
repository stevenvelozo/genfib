/**
* This source file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*/
#include "digmathcommon.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

void settings_set_defaults(structSettingsValues *pSettings)
{
	pSettings->ShowHeader = false;
	pSettings->ShowColumnValue = false;
	pSettings->ShowOrdinal = false;
	pSettings->ShowRowValue = false;
	pSettings->ShowApproximateLength = false;

	pSettings->RowValueCount = 10;
	pSettings->ColumnValueCount = 10;

	pSettings->ComputeRowPrime = false;

	pSettings->RowIterationStyle = Incremental;
	pSettings->ColumnIterationStyle = Fibonacci;
	pSettings->ComputationStyle = Modulo;

	pSettings->RenderImage = false;
	pSettings->ImageFileName = "Output.png";

	pSettings->PrintSetStatistics = false;

	pSettings->LineHasData = false;
}

void settings_parse_arguments(int argc, char *argv[], structSettingsValues *pSettings)
{
	int tmpArgParse;
	while ((tmpArgParse = getopt(argc, argv, "?adI:ehosr:c:R:C:i:pP")) != -1)
	{
		switch (tmpArgParse)
		{
			case 'o':
				pSettings->ShowOrdinal = true;
				break;
			case 's':
				pSettings->ShowApproximateLength = true;
				break;
			case 'd':
				pSettings->ShowRowValue = true;
				break;
			case 'r':
				pSettings->RowValueCount = strtoul(optarg, NULL, 0);
				break;
			case 'i':
				pSettings->RenderImage = true;
				pSettings->ImageFileName = optarg;
				break;
			case 'p':
				pSettings->PrintSetStatistics = true;
				break;
			case 'P':
				pSettings->ComputeRowPrime = true;
				break;
			case 'R':
				switch (strtoul(optarg, NULL, 0))
				{
					case 1:
						pSettings->RowIterationStyle = Fibonacci;
						break;
					case 2:
						pSettings->RowIterationStyle = Lucas;
						break;
					case 3:
						pSettings->RowIterationStyle = Incremental;
						break;
					case 4:
						pSettings->RowIterationStyle = Padovan;
						break;
					case 5:
						pSettings->RowIterationStyle = Pell;
						break;
				}
				break;

			case 'h':
				pSettings->ShowHeader = true;
				break;
			case 'a':
				pSettings->ShowColumnValue = true;
				break;
			case 'c':
				pSettings->ColumnValueCount = strtoul(optarg, NULL, 0);
				break;
			case 'C':
				switch (strtoul(optarg, NULL, 0))
				{
					case 1:
						pSettings->ColumnIterationStyle = Fibonacci;
						break;
					case 2:
						pSettings->ColumnIterationStyle = Lucas;
						break;
					case 3:
						pSettings->ColumnIterationStyle = Incremental;
						break;
					case 4:
						pSettings->ColumnIterationStyle = Padovan;
						break;
					case 5:
						pSettings->ColumnIterationStyle = Pell;
						break;
				}
				break;
			case 'I':
				switch(strtoul(optarg, NULL, 0))
				{
					case 1:
						pSettings->ComputationStyle = Modulo;
						break;
					case 2:
						pSettings->ComputationStyle = Divide;
						break;
					case 3:
						pSettings->ComputationStyle = Multiply;
						break;
					case 4:
						pSettings->ComputationStyle = Add;
						break;
					case 5:
						pSettings->ComputationStyle = Subtract;
						break;
				}
				break;

			case '?':
				print_help();
				break;
			default:
				break;
		}
	}

	if (pSettings->RowValueCount == 0)
		pSettings->RowValueCount = 10;
}