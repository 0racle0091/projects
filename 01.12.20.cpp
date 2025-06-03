#include <iostream>
#include<fstream>
int main()
{
	using namespace std;
	const int len = 81;
	ifstream fi;
	fi.open("int.txt");
	if (fi.is_open())
	{
		cout << "Vse v poryadke" << endl;
	}
	else
	{
		cout << "fail ne otkrit\n" << endl;
		return 1;
	}
	fi.seekg(0, fi.end);
	long int len = fi.tellg();
	cout << len << endl;

	char* buf = new char[len + 1];

	fi.seekg(0, fi.beg);
	fi.read(buf,len);
	buf[len] = '\0';

	long int n = 0, i = 0, j = 0;
	while (buf[i]) {
		if (buf[i] == '?') {
			for (j = n;j <= i;j++) {
				cout << buf[i];
			
			}
			n = i + 1;
		}
		if ((buf[i] == '.') || (buf[i] == '!')) {
			n = i + 1;
		}
		i++;
	}
	cout << endl;
	delete[]buf;

	fi.close();
    
	system("pause");
	return 0;
}