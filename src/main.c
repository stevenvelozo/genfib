/**
* This source file is a part of the genfib set intersection application.
* For full copyright and license information, please view the LICENSE file
* which should be distributed with this source code.
*
* @license MIT License
* @copyright Copyright (c) 2013, Steven Velozo
*/
#include <digmathcommon.h>
#include <digmathrender.h>
#include <mathoperations.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lib/gmp.h"
#include "/usr/local/include/libpng16/png.h"

int main(int argc, char *argv[])
{
	// Load command-line arguments.
	// This is all managed from ../common/libdigmathcommon.h and ../common/settings.c
	structSettingsValues tmpSettings;
	settings_set_defaults(&tmpSettings);
	settings_parse_arguments(argc, argv, &tmpSettings);

	// Show the header row if it is set to visible
	if (tmpSettings.ShowHeader)
	{
		// Each of these prints does nothing unless the first parameter is set to TRUE
		csv_print_string(tmpSettings.ShowOrdinal, "Ordinal", &tmpSettings);
		csv_print_string(tmpSettings.ShowApproximateLength, "ApproxSizeBase10", &tmpSettings);
		csv_print_string(tmpSettings.ComputeRowPrime, "ProbablyPrime", &tmpSettings);
		csv_print_string(tmpSettings.ShowRowValue, "Value", &tmpSettings);

		if (tmpSettings.ColumnValueCount > 0)
		{
			int tmpColumnOrdinalDisplayCounter;
			for (tmpColumnOrdinalDisplayCounter = 1; tmpColumnOrdinalDisplayCounter <= tmpSettings.ColumnValueCount; tmpColumnOrdinalDisplayCounter++)
			csv_print_int(true, tmpColumnOrdinalDisplayCounter, &tmpSettings);
		}
		csv_print_eol(&tmpSettings);
	}

	structIterationValue tmpColumnIterationValue;
	iteration_value_init(&tmpColumnIterationValue, tmpSettings.ColumnIterationStyle);

	if (tmpSettings.ShowColumnValue)
	{
		csv_print_string(tmpSettings.ShowOrdinal, "", &tmpSettings);
		csv_print_string(tmpSettings.ShowApproximateLength, "", &tmpSettings);
		csv_print_string(tmpSettings.ComputeRowPrime, "", &tmpSettings);
		csv_print_string(tmpSettings.ShowRowValue, "", &tmpSettings);
		int tmpColumnOrdinalDisplayCounter;
		for (tmpColumnOrdinalDisplayCounter = 1; tmpColumnOrdinalDisplayCounter <= tmpSettings.ColumnValueCount; tmpColumnOrdinalDisplayCounter++)
		{
			iteration_compute_value(&tmpColumnIterationValue);
			csv_print_mpz(true, tmpColumnIterationValue.Value, &tmpSettings);
			iteration_prepare_computation_values(&tmpColumnIterationValue);
		}
		csv_print_eol(&tmpSettings);
	}

	structIterationValue tmpRowIterationValue;
	iteration_value_init(&tmpRowIterationValue, tmpSettings.RowIterationStyle);

	mpz_t tmpModuloValue;
	mpz_init(tmpModuloValue);

	structSetStatistics tmpSetStatistics;
	statistics_init(&tmpSetStatistics);

	int tmpCounter;
	for (tmpCounter = 0; tmpCounter < tmpSettings.RowValueCount; tmpCounter++)
	{
		tmpRowIterationValue.Ordinal++;

		tmpRowIterationValue.ComputePrime = tmpSettings.ComputeRowPrime;
		iteration_compute_value(&tmpRowIterationValue);

		tmpRowIterationValue.ValueLength = mpz_sizeinbase(tmpRowIterationValue.Value, 10);

		csv_print_int(tmpSettings.ShowOrdinal, tmpRowIterationValue.Ordinal, &tmpSettings);
		csv_print_sizet(tmpSettings.ShowApproximateLength, tmpRowIterationValue.ValueLength, &tmpSettings);
		csv_print_int(tmpSettings.ComputeRowPrime, tmpRowIterationValue.IsPrime, &tmpSettings);
		csv_print_mpz(tmpSettings.ShowRowValue, tmpRowIterationValue.Value, &tmpSettings);

		if (tmpSettings.ColumnValueCount > 0)
		{
			iteration_value_init(&tmpColumnIterationValue, tmpSettings.ColumnIterationStyle);

			int tmpModuloCounter;
			for(tmpModuloCounter = 1; tmpModuloCounter <= tmpSettings.ColumnValueCount; tmpModuloCounter++)
			{
				iteration_compute_value(&tmpColumnIterationValue);

				// Figure out the value for the intersection and print it
				intersection_compute_value(tmpSettings.ComputationStyle, &tmpModuloValue, &tmpRowIterationValue, &tmpColumnIterationValue);
				csv_print_mpz(true, tmpModuloValue, &tmpSettings);
				statistics_add_value(&tmpModuloValue, &tmpSetStatistics);
				iteration_prepare_computation_values(&tmpColumnIterationValue);
			}
		}
		iteration_prepare_computation_values(&tmpRowIterationValue);
		csv_print_eol(&tmpSettings);
	}

	// TODO: Add more guards down here -- if there are 0 columns or 0 rows odd stuff might happen.
	solve_statistics_set(&tmpSetStatistics);
	renderer_color_scaled_initialize(&tmpSetStatistics);

	if (tmpSettings.PrintSetStatistics)
		debug_print_set_statistics_data(&tmpSetStatistics, "Intersection Set Statistics");

	if (tmpSettings.RenderImage)
	{
		iteration_value_init(&tmpRowIterationValue, tmpSettings.RowIterationStyle);
		structRenderableImage tmpRenderableImage;
		renderer_png_init(&tmpRenderableImage, tmpSettings.ImageFileName, tmpSettings.RowValueCount, tmpSettings.ColumnValueCount, "Intersection Image");
		for (tmpCounter = 0; tmpCounter < tmpSettings.RowValueCount; tmpCounter++)
		{
			iteration_compute_value(&tmpRowIterationValue);

			if (tmpSettings.ColumnValueCount > 0)
			{
				iteration_value_init(&tmpColumnIterationValue, tmpSettings.ColumnIterationStyle);

				int tmpModuloCounter;
				for(tmpModuloCounter = 1; tmpModuloCounter <= tmpSettings.ColumnValueCount; tmpModuloCounter++)
				{
					iteration_compute_value(&tmpColumnIterationValue);
					intersection_compute_value(tmpSettings.ComputationStyle, &tmpModuloValue, &tmpRowIterationValue, &tmpColumnIterationValue);
					iteration_prepare_computation_values(&tmpColumnIterationValue);
					renderer_png_setcolor_x(&tmpRenderableImage, tmpModuloCounter, renderer_get_red(&tmpModuloValue, &tmpSetStatistics), renderer_get_green(&tmpModuloValue, &tmpSetStatistics), renderer_get_blue(&tmpModuloValue, &tmpSetStatistics));
				}
			}
			renderer_png_write_row(&tmpRenderableImage);
			iteration_prepare_computation_values(&tmpRowIterationValue);
		}
		renderer_png_finalize(&tmpRenderableImage);
	}

	iteration_value_destroy(&tmpColumnIterationValue);
	iteration_value_destroy(&tmpRowIterationValue);
	statistics_destroy(&tmpSetStatistics);

	mpz_clear(tmpModuloValue);

	return 0;
}
