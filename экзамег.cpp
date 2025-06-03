#include <fstream>
#include <iostream>

int main()
{
	using namespace std;
	ifstream fi;
	fi.open("input.txt");

	if (fi.is_open())
	{
		cout << "Vse v poryadke" << endl;
	}
	else
	{
		cout << "fail ne otkrit\n" << endl;
		return 1;
	}

	int m;
	fi >> m;

	int* D = new int[m];

	for (int i = 0;i < m;i++) {
		fi >> D[i];
	}

	int max, imax, min, imin;
	max = min = D[0];
	imax = imin = 0;
	for (int i = 1;i < m;i++) {
		
		if (D[i] > max) {
			max = D[i];
			imax = i;
		}
		
		if (D[i] < min) {
			min = D[i];
			imin = i;
		}

	}

	ofstream fo;
	fo.open("output.txt");

	if (fo.is_open())
	{
		cout << "Vse v poryadke" << endl;
	}
	else
	{
		cout << "fail ne otkrit\n" << endl;
		return 1;
	}
	int k;

	if (imax < imin) {
		k = imin - imax + 1;
	}

	if (imax == imin) {
		k = m;
	}

	if (imax > imin) {
		k = imin + m - imax + 1;
	}

	int* A = new int[k];
	
	if (imax < imin) {
		int j = 0;
		for (int i = imax;i <= imin;i++) {
			A[j] = D[i];
			j++;
		}
	}

	if (imax == imin) {
		for (int i = 0;i < m;i++) {
			A[i] = D[i] ;
		}
	}

	if (imax > imin) {
		int j = 0;
		for (int i = 0;i <= imin;i++) {
			A[j] = D[i];
			j++;
		}

		for (int i = imax;i < m;i++) {
			A[j] = D[i];
			j++;
		}

	}

	/*for (int i = 0;i < k;i++) {
		cout << A[i]<<" ";
	}*/
	
	for (int i = 0;i < k;i++) {
		fo << A[i]<<" ";
	}

	fi.close();
	fo.close();
	
	system("pause");
	return 0;
}
