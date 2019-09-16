#include "mcalc.h"

using namespace std;
#define MAX_NUMBER	24
#define BUFFER_SIZE MAX_NUMBER + 4
#define ROUND		true

double matrix[BUFFER_SIZE][BUFFER_SIZE];
double kvalue[BUFFER_SIZE];

void calc(int number)
{
	double val = 0.0;
	double tmp = 0.0; 
	int n = number + 3;

	memset(matrix, 0, sizeof(matrix));
	memset(kvalue, 0, sizeof(kvalue));

	for (int j = 0; j < n - 1; j++)
	{
		for (int i = 0; i < n - 1; i++)
			matrix[j][i] = pow((double)(j + 1), (double)(n - 2 - i));
		val += pow((double)(j + 1), (double)number);
		matrix[j][n] = val;
	}

	for (int i = 0; i < n; i++)
	{
		tmp = matrix[i][i];
		for (int j = n; j >= i; j--)
			matrix[i][j] /= tmp;
		for (int j = i + 1; j < n; j++)
		{
			tmp = matrix[j][i];
			for (int k = n; k >= i; k--)
				matrix[j][k] -= tmp * matrix[i][k];
		}
	}
	kvalue[n - 2] = matrix[n - 2][n - 1]; 
	for (int i = n - 2; i >= 0; i--)
	{
		kvalue[i] = matrix[i][n];
		for (int j = i + 1; j < n; j++)
			kvalue[i] -= matrix[i][j] * kvalue[j];
	}
}

int main()
{
	int number = 0;
	double sum = 0.0;
	double koeff = 0.0;
	cout << "Input number of power (from 1 to " << MAX_NUMBER << ") or 0 for exit." << endl;
	while (1)
	{
		cout << "Number:" << endl;
		cin >> number;
		if (number <= 0) {
			return 0;
		}
		else if (number > MAX_NUMBER) {
			cout << "Max number is: " << MAX_NUMBER;
			number = MAX_NUMBER;
		}
		
		calc(number);
		cout << "Formula:" << endl;
		
		double zero = powl(0.1, number);
		for (int k = 0; k < number + 2; k++)
		{
			koeff = ((abs(kvalue[k]) < zero) && ROUND) ? 0 : kvalue[k];
			if (k)
				if (koeff < 0.0)
					cout << " - ";
				else if (koeff > 0.0)
					cout << " + ";
			if (koeff != 0.0)
				if (number == k)
					cout << abs(koeff) << "x";
				else if (number + 1 == k)
					cout << abs(koeff);
				else
					cout << abs(koeff) << "x" << number + 1 - k;

			sum += koeff;
		}
		cout << " = " << endl; // << "Control sum:" << sum << endl; // must be 1 always!
	}
	return 0;
}
