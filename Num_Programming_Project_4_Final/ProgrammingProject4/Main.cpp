#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void dividedDiff(double*, double**, int);
void interPol(double*, double**, int);

int main()
{
	fstream fs;
	string textFile;

	cout << "Please enter the name of your file (including .txt): ";
	cin >> textFile;
	fs.open(textFile);

	if (fs.fail())
	{
		cout << "Failed to open file" << endl;
		return 0;
	}
	else
	{
		double number = 0;
		int numOfIndices = 0;
		while (fs >> number)
		{
			numOfIndices++;
		}
		numOfIndices /= 2;
		if (numOfIndices > 51)
		{
			cout << "Too many data points" << endl;
			return 0;
		}
		fs.clear();
		fs.seekg(0);

		double* x = new double[numOfIndices];
		double** fx = new double* [numOfIndices];
		for (int i = 0; i < numOfIndices; i++)
		{
			fx[i] = new double[numOfIndices];
		}
		for (int i = 0; i < numOfIndices; i++)
		{
			fs >> x[i];
		}
		for (int i = 0; i < numOfIndices; i++)
		{
			fs >> fx[i][0];
		}

		dividedDiff(x, fx, numOfIndices);
		cout << "x\tf[]\t";
		for (int i = 1; i < numOfIndices; i++)
		{
			cout << "f[";
			for (int j = 1; j < numOfIndices; j++)
			{
				cout << ",";
			}
			cout << "]\t";
		}
		cout << endl;
		for (int i = 0; i < numOfIndices; i++)
		{
			cout << x[i] << "\t";
			for (int j = 0; j < numOfIndices; j++)
			{
				if (abs(fx[i][j]) < 100)
					cout << setprecision(2) << fx[i][j] << "\t";
			}
			cout << endl;
		}

		interPol(x, fx, numOfIndices);

		delete[] x;
		x = nullptr;
		for (int i = 0; i < numOfIndices; i++)
		{
			delete[] fx[i];
		}
		delete[] fx;
		fx = nullptr;
	}

	cout << endl;
	system("pause");
	return 0;
}

void dividedDiff(double *x, double **fx, int numOfIndices)
{   
	for (int j = 1; j < numOfIndices; j++)
	{
		for (int i = 0; i < numOfIndices - j; i++)
		{
			fx[i][j] = (fx[i + 1][j - 1] - fx[i][j - 1]) / (x[i + j] - x[i]);
		}
	}
}

void interPol(double* x, double** fx, int numOfIndices)
{
	cout << "Interpolating Polynomial is: " << endl;
	cout << fx[0][0];
	for (int i = 1; i < numOfIndices; i++)
	{
		if (fx[0][i] < 0)
		{
			cout << "-" << abs(fx[0][i]);
		}
		else
		{
			cout << "+" << fx[0][i];
		}
		for (int j = 0; j < i; j++)
		{
			if (x[j] < 0)
			{
				cout << "(x+" << abs(x[j]) << ")";
			}
			else if (x[j] == 0)
			{
				cout << "x";
			}
			else
			{
				cout << "(x-" << x[j] << ")";
			}
		}
	}
	cout << endl;
}

