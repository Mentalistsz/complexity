

#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <algorithm> 
#include <string>
#include <chrono>
using namespace std;



//структура для дат + перегрузка операторов
struct date
{
	int year;
	int month;
	int day;
};
bool operator > (date &d1, date &d2)
{
	if (d1.year > d2.year)
		return true;
	if (d1.year < d2.year)
		return false;
	if (d1.month > d2.month)
		return true;
	if (d1.month < d2.month)
		return false;
	if (d1.day > d2.day)
		return true;
	return false;
}
bool operator < (date &d1, date &d2)
{
	return !(d1 > d2);
}
bool operator <= (date &d1, date &d2)
{
	if ((d1.day == d2.day) && (d1.month == d2.month) && (d1.year == d2.year))
		return true;
	return d1 < d2;
}
istream &operator >>(istream &in, date &d)
{
	cout << "Enter a date(ddmmyyyy):\n";
	cout << "day "; in >> d.day;
	cout << "month "; in >> d.month;
	cout << "year "; in >> d.year;
	return in;
}
ostream &operator <<(ostream &out, date &d)
{
	out << d.day << "." << d.month << "." << d.year << endl;
	return out;
}
ofstream &operator <<(ofstream &fout, date &d)
{
	fout << d.day << "." << d.month << "." << d.year << " ";
	return fout;
}


//функция переворачивает массив
template <typename _reverse>
void reverse(_reverse *a, size_t n)
{
	for (size_t i = 0; i < n / 2; i++)
		swap(a[i], a[n - i - 1]);
}


//набор функций  для заполнения массивов случайными данными
void randChar(char *c, int n)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < n; ++i)
		c[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
}
void randDate(date *d, int n)
{
	for (int i = 0; i < n; i++)
	{
		d[i].day = rand() % 30 + 1;
		d[i].month = rand() % 12 + 1;
		d[i].year = rand() % 120 + 1900;
	}
}
void randInt(int *a, int n)
{
	srand((unsigned)clock());
	for (int i = 0; i < n; i++)
		a[i] = rand() + rand();
}
void randNum(int *a, int n)
{
	srand((unsigned)clock());
	for (int i = 0; i < n; i++)
		a[i] = (rand() + rand())%10;
}
void randomize(int *a, int *b, char *c, date *d, int n)
{
	randInt(a, n);
	randNum(b, n);
	randChar(c, n);
	randDate(d, n);
}


//шаблоны ф-ий сортировки
template <typename _bubbleSort>
void bubbleSort(_bubbleSort *a, int begin, int end)
{
	bool sorted = true;
	do
	{
		sorted = true;
		for (int i = begin; i < end; i++)
		{
			if (a[i] > a[i + 1])
			{
				swap(a[i], a[i + 1]);
				sorted = false;
			}
		}
	} while (sorted != true);
}



template <typename _insertionSort>
void insertionSort(_insertionSort *a, int begin, int end)
{
	for (int i = begin + 1; i < end+1; i++)
		for (int j = i; j > 0 && a[j - 1] > a[j];j--)
			swap(a[j - 1], a[j]);
}



template <typename _selectionSort>
void selectionSort(_selectionSort *a, int begin, int end)
{
	for (int i = 0; i < end; i++)
	{
		int min = i;
		for (int j = i + 1; j < end+1; j++)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		if (min != i) {
			swap(a[i], a[min]);
		}
	}
}



template <typename _shellSort>
void shellSort(_shellSort *a, int begin, int end)
{
	int gap;
	_shellSort temp;
	int i, j;
	for (gap = (end+1) / 2; gap > 0; gap = gap / 2)
	{
		for (i = gap - 1; i < end+1; i++)
		{
			temp = a[i];
			for (j = i; j > gap - 1 && a[j - gap] > temp; j = j - gap)
			{
				a[j] = a[j - gap];
			}
			a[j] = temp;
		}
	}
}



template <typename _maxHeapify>
void maxHeapify(_maxHeapify *a, int index, int size)
{
	int l = (index << 1) + 1;
	int r = (index << 1) + 2;
	int largest = index;
	if (l < size && a[l] > a[index]) {
		largest = l;
	}
	if (r < size && a[r] > a[largest]) {
		largest = r;
	}
	if (largest != index) {
		swap(a[index], a[largest]);
		maxHeapify(a, largest, size);
	}
}
template <typename _buildMaxHeap>
void buildMaxHeap(_buildMaxHeap *a, int size)
{
	int count = size >> 1;
	for (int i = count - 1; i
 > -1; i--) {
		maxHeapify(a, i, size);
	}
}
template <typename _heapSort>
void heapSort(_heapSort *a, int i, int size)
{
	buildMaxHeap(a, size+1);
	i = 0;
	for (i = 0; i < size+1; i++) {
		swap(a[0], a[size - i]);
		maxHeapify(a, 0, size - i);
	}
}



template <typename _partition>
int partition(_partition a[], int beg, int end)
{
	auto p = beg;
	_partition pivot = a[beg];

	for (auto loc = beg + 1; loc <= end; loc++)
	{
		if (pivot > a[loc])
		{
			a[p] = a[loc];
			a[loc] = a[p + 1];
			a[p + 1] = pivot;

			p = p + 1;
		}
	}
	return p;
}
template <typename _quickSort>
void quickSort(_quickSort *a, int start, int end)
{
	if (start < end)
	{
		auto p = partition(a, start, end);
		quickSort(a, start, p - 1);
		quickSort(a, p + 1, end);
	}
}



template <typename _merge>
void merge(_merge *a, int low, int high, int mid)
{
	int i, j, k;
	_merge *temp = new _merge[high - low + 1];
	i = low;
	k = 0;
	j = mid + 1;

	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}

	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}

	for (i = low; i <= high; i++)
	{
		a[i] = temp[i - low];
	}
}
template <typename _mergeSort>
void mergeSort(_mergeSort *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;

		mergeSort(a, low, mid);
		mergeSort(a, mid + 1, high);

		merge(a, low, high, mid);
	}
}

ofstream fout;

template <typename _sorter>
void sorter(_sorter inp[], int n)
{
	
	void(*a[])(_sorter*, int, int) = {bubbleSort, insertionSort,heapSort,
										 selectionSort, mergeSort, shellSort, quickSort};

	string c[7];
	c[0] = "bubbleSort: ";
	c[1] = "insertionSort: ";
	c[2] = "heapSort: ";
	c[3] = "selectionSort: ";
	c[4] = "mergeSort: ";
	c[5] = "shellSort: ";
	c[6] = "quickSort: ";

	for (int i = 0; i < 7; i++)
	{
		fout << c[i];
		double t = 0;
		for(int j = 0; j < 10; j++)
		{
			auto t1 = std::chrono::high_resolution_clock::now();
			a[i](inp, 0, n - 1);
			auto t2 = std::chrono::high_resolution_clock::now();
			t += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			random_shuffle(inp, &inp[n]);
		}
		fout << t / 10;
		fout << endl;
		

	}
}


int main()
{

	fout.open("output.txt");
	int n[] = {50, 250, 1000, 2000, 4000,8000, 10000, 16000};
	
	for (int i = 0; i < 8; i++)
	{
		int *Int = new int[n[i]];
		int *Num = new int[n[i]];
		char *Char = new char[n[i]];
		date *Date = new date[n[i]];

		randomize(Int, Num, Char, Date, n[i]);	

		fout << "\n\nn = " << n[i] << endl;
		fout << "\nRandom input\n";

		fout << "\nInts\n";
		sorter(Int, n[i]);
		fout << "\nNums\n";
		sorter(Num, n[i]);
		fout << "\nChars\n";
		sorter(Char, n[i]);
		fout << "\nDates\n";
		sorter(Date, n[i]);
		cout <<"straight "<< n[i] << endl;

		reverse(Int, n[i]);
		reverse(Num, n[i]);
		reverse(Char, n[i]);
		reverse(Date, n[i]);

		fout << "\nReversed arrays\n";
		fout << "\nInts\n";
		sorter(Int, n[i]);
		fout << "\nNums\n";
		sorter(Num, n[i]);
		fout << "\nChars\n";
		sorter(Char, n[i]);
		fout << "\nDates\n";
		sorter(Date, n[i]);
		cout << "reversed " << n[i] << endl;
	}
	fout.close();
}

