#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct infodump
{
	vector<int> values;
	vector<float> points;
	float time;
	int k;
} dp;

int main()
{
	srand(time(NULL));

	//1 - generate data
	int n1 = rand() % 50 + 100;
	dp.values.resize(n1);
	for (int i = 0; i < n1; i++)
	{
		dp.values[i] = rand() % 25;
	}
	int n2 = rand() % 50 + 100;
	dp.points.resize(n2);
	for (int i = 0; i < n2; i++)
	{
		dp.points[i] = (float)(rand() % 100) + (float)(rand() % 100) / 100;
	}
	dp.time = time(NULL);
	dp.k = rand() % 35;

	printf("Data generated\n");

	//2 - write data
	ofstream writer("data.bin", ios::out | ios::binary);
	writer.write((char*)&n1, sizeof(int));
	int * valdat = dp.values.data();
	writer.write((char*)valdat, n1 * sizeof(int));
	writer.write((char*)&n2, sizeof(int));
	float * poidat = dp.points.data();
	writer.write((char*)poidat, n2 * sizeof(float));
	writer.write((char*)&dp.time, sizeof(float));
	writer.write((char*)&dp.k, sizeof(int));
	writer.close();

	printf("Data written\n");

	//3 - read data
	infodump nd;
	ifstream reader("data.bin", ios::in | ios::binary);
	int nn1;
	reader.read((char*)&nn1, sizeof(int));
	nd.values.resize(nn1);
	for (int i=0;i<nn1;i++)
	reader.read((char*)&nd.values[i], sizeof(int));

	int nn2;
	reader.read((char*)&nn2, sizeof(int));
	nd.points.resize(nn2);
	for (int i = 0; i < nn2; i++)
	reader.read((char*)&nd.points[i], sizeof(float));
	reader.read((char*)&nd.time, sizeof(float));
	reader.read((char*)&nd.k, sizeof(int));
	reader.close();

	//4 - show data
	for (int i = 0; i < dp.values.size(); i++)
	{
		printf("%d) %d ///// %d\n", i, dp.values[i], nd.values[i]);
	}
	for (int i = 0; i < dp.points.size(); i++)
	{
		printf("%d) %f ///// %f\n", i, dp.points[i], nd.points[i]);
	}
}