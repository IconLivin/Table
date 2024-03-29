// TTable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "TScanTable.h"
#include "TSortTable.h"
#include "THashTable.h"
#include <cstdlib>

int main()
{
	TScanTable<int, int> ts(100);
	TSortTable<int, int> ts1(100);
	THashTable<int, int> th(100);
	for (int i = 0; i < 50; i++) {
		TRecord<int, int> tmp;
		tmp.key = rand();
		tmp.val = rand();
		ts.Insert(tmp);
		ts1.Insert(tmp);
		th.Insert(tmp);
	}
	ts.Print();
	ts1.Print();
	th.Print();
	cout << "ScanTable eff:" << ts.GetEff() << " SortTable eff:" << ts1.GetEff() << " HashTable eff:" << th.GetEff() << endl;
	int key = 0;
	while (key != -1) {
		cout << "1.Delete 2.Add 3.Find: " << endl;
		cin >> key;
		switch (key) {
		case 1: {
			int dkey;
			cout << "Insert key:";
			cin >> dkey;
			ts.NullEff();
			ts1.NullEff();
			th.NullEff();
			if(ts.DeleteKey(dkey))ts.Print();
			if (ts1.DeleteKey(dkey))ts1.Print();
			if (th.DeleteKey(dkey))th.Print();
			break;
		}
		case 2:
		{
			TRecord<int,int> dkey;
			cout << "Insert Record:";
			cin >> dkey.key >> dkey.val;
			ts.NullEff();
			ts1.NullEff();
			th.NullEff();
			if (ts.Insert(dkey))ts.Print();
			if(ts1.Insert(dkey))ts1.Print();
			if(th.Insert(dkey))th.Print();		
			break;
		}
		case 3:
		{
			int dkey;
			cout << "Insert Record:";
			cin >> dkey;
			ts.NullEff();
			ts1.NullEff();
			th.NullEff();
			if (ts.Find(dkey))cout << "Element found!" << endl;
			else cout << "Element not found!" << endl;
			ts1.Find(dkey);
			th.Find(dkey);
		}
		}
		cout << "ScanTable eff:" << ts.GetEff() << " SortTable eff:" << ts1.GetEff() << " HashTable eff:" << th.GetEff() << endl;
	}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
