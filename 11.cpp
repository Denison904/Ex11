#include <iostream>
#include <fstream>
#include<string.h>
using namespace std;
int const dm[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
struct  date {
	int dd, mm, yy;
	date(int d = NULL, int m = NULL, int y = NULL) {
		dd = d;
		mm = m;
		yy = y;
	}

	int vis(int y);
	bool verify(int dd, int mm, int yy);
	void print(void);

};

int vis(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) return 1;
	else return 0;
}

bool verify(int dd, int mm, int yy)
{
	if (yy <= 0) return false;
	if (mm < 1 || mm>12) return false;
	if (mm != 2 && (dd<1 || dd>dm[mm])) return false;
	if (mm == 2 && (dd<1 || dd>dm[2] + vis(yy))) return false;
	return true;
}

void date::print(void)
{
	if (dd < 10)
		cout << 0;
	else
		cout << dd / 10;
	cout << dd % 10 << '.';
	if (mm < 10)
		cout << 0;
	else
		cout << mm / 10;
	cout << mm % 10 << '.';
	if (yy < 1000)
		cout << 0;
	else
		cout << yy / 1000;
	int y = yy % 1000;
	if (y < 100)
		cout << 0;
	else
		cout << y / 100;
	y = y % 100;
	if (y < 10)
		cout << 0;
	else
		cout << y / 10;
	cout << y % 10 << endl;
}

struct sotr {
	char* fam, * name, * subname;
	date dat;

	sotr* next;
	sotr(char* f, char* n, char* sn, int d, int m, int y) {
		fam = _strdup(f);
		name = _strdup(n);
		subname = _strdup(sn);
		dat.dd = d;
		dat.mm = m;
		dat.yy = y;
		next = NULL;
	}
	void print(void);
	sotr* add(sotr* first);
	bool sr(sotr* first);
};
void sotr::print(void)
{
	sotr* ptr = this;
	while (ptr)
	{
		cout.width(30);
		cout.setf(ios::left);
		cout << ptr->fam;
		cout.width(10);
		cout.setf(ios::left);
		cout << ptr->name;
		cout.width(15);
		cout.setf(ios::left);
		cout << ptr->subname;
		ptr->dat.print();
		ptr = ptr->next;
	}
}

sotr* sotr::add(sotr* first)
{
	sotr* ptr, * prev;
	ptr = first;
	prev = NULL;
	while (ptr != NULL && !ptr->sr(first))
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev == NULL)
	{
		this->next = first;
		first = this;
	}
	else
	{
		prev->next = this;
		this->next = ptr;
	}
	return first;
}
bool sotr::sr(sotr* first) {
	sotr* ptr;
	ptr = first;
	if (first->next)
		if (dat.yy >= ptr->dat.yy)
		{
			if (dat.mm >= ptr->dat.mm)
			{
				if (dat.dd > ptr->dat.dd)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}

}

int main()
{
	char f[30], n[10], sn[15];
	int d, m, y;
	fstream ff("Text.txt");
	sotr* first = NULL, * new_el;
	while (!ff.eof())
	{
		ff >> f >> n >> sn >> d >> m >> y;
		if (first == NULL)
			first = new sotr(f, n, sn, d, m, y);
		else
		{
			new_el = new sotr(f, n, sn, d, m, y);
			first = new_el->add(first);
		}

	}
	first->print();
	return 0;
}