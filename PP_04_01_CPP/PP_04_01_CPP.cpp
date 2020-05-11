// PP_04_01_CPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<cmath>

//start = 4
//end = 10
int main()
{
	int i;
	int const size = 3;
	double results[size];
	double finalResult = 0;
	double result = 0;
	int countN = 3;
	#pragma omp parallel shared(results, countN, result)
	{
		#pragma omp sections nowait
		{
			#pragma omp section
			{
				double start = 4;
				double end = 6;
				result = 0;
				double h = (double)((end - start) / countN);
				for (int i = 0; i < countN; i++)
				{
					result += pow(2, start + h * (i + 0.5)) / pow(start + h * (i + 0.5), 3);
				}
				result *= h;
				results[0] = result;
			}

			#pragma omp section
			{
				 double start = 6;
				 double end = 8;
				 result = 0;
				 double h = (double)((end - start) / countN);

				for (int i = 0; i < countN; i++)
				{
					result += pow(2, start + h * (i + 0.5)) / pow(start + h * (i + 0.5), 3);
				}
				result *= h;
				results[1] = result;
			}

			#pragma omp section
			{
				double start = 8;
				double end = 10;
				result = 0;
				double h = (double)((end - start) / countN);

				for (int i = 0; i < countN; i++)
				{
					result += pow(2, start + h * (i + 0.5)) / pow(start + h * (i + 0.5), 3);
				}
				result *= h;
				results[2] = result;
			}
		}

		for (int j = 0; j < size; j++)
		{
			finalResult += results[j];
		}

		printf("Section result: %f\n", finalResult);
	}


	double resultReduction = 0;
	int chunk = 3;

	#pragma omp parallel for default(shared) schedule(static, chunk) reduction (+ :resultReduction)
	{
		for (int i = 4; i < 10; i += 2)
		{
			resultReduction += pow(2, i + 2 * (1.5)) / pow(i + 2 * (1.5), 3);
		}
	}

	printf("Reduction result: %f\n", resultReduction);

}


