#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//раскодируем нуклеотиды
string cod(int* a, int l) {
	string word;
	for (int i = 0; i < l; i++) {
		switch (a[i])
		{
		case 0: word += 'A'; break; 
		case 1: word += 'C'; break;
		case 2: word += 'G'; break;
		case 3: word += 'T'; break;
		default:
			break;
		}
	}
	return word;
}

int* Next_Leaf(int* a, int l, int k) {
	for (int i = l - 1; i >= 0; i--) {
		if (a[i] < k - 1) {
			a[i]++;
			return a;
		}
		a[i] = 0;
	}
	return a;
}

void All_Leaves(int l, int k) {
	int *s = new int[l];
	for (int i = 0; i < l; i++) {
		s[i] = 0;
	}
	for (;;) {
		for (int i = 0; i < l; i++) {
			cout << s[i];
		}
		cout << endl;
		s = Next_Leaf(s, l, k);
		int n;
		for (n = 0; n < l && s[n] == 0; n++) {
			;
		}
		if (n == l) return;

	}
}

int Total_Distance(string word, string* dna, int n, int l, int t) {
	int Hmg = 0; 
	int *h = new int[n-l+1];
	int *h_min = new int[t];
	for (int i = 0; i < t; i++) {
		h_min[i] = 10000000;
	}
	for (int i = 0; i < t; i++) { //считаем минимальное расстояние Хэмминга для всех строк
		string buff = dna[i];
		for (int c = 0; c < n - l + 1; c++) {
			h[c] = 0;
		}
		for (int j = 0; j < (n - l + 1); j++) {//скользящее окно
			int m; int k = j;
			for (m = 0; m < l; m++) {//считаем число различных позиций				
				if (word[m] != buff[k]) {
					h[j]++;//считаем расстояние Хэмминга для каждой стартовой позиции
				}
				k++;
			}
		}
			//найдем минимальное и перейдем на новую строку
			for (int g = 0; g < n - l + 1; g++) {
				if (h[g] < h_min[i]) {
					h_min[i] = h[g];
				}
			}		
	}
	//считаем полное расснояние Хэмминга
	for (int i = 0; i < t; i++) {
		Hmg = Hmg + h_min[i];
	}	
	return Hmg;
}

string BruteForceMedianSearch(string* dna, int t, int n, int l) {
	int* word_cod = new int[l];
	for (int i = 0; i < l; i++) {
		word_cod[i] = 0;
	}
	string word;
	word = cod(word_cod, l);
	string best_word;
	best_word = cod(word_cod, l);

	int best_distance;
	best_distance = Total_Distance(word, dna, n, l, t);

	for (;;) {
		word_cod = Next_Leaf(word_cod, l, 4);
		word = cod(word_cod, l);

		if (Total_Distance(word, dna, n, l, t) < best_distance) {
			best_distance = Total_Distance(word, dna, n, l, t);
			best_word = word;
		}


		int j;
		for (j = 0; j < l && word_cod[j] == 0; j++) {
			;
		}
		if (j == l) {
			return best_word;
		}
	}

}


int main() {
	ifstream fin("input.txt");

	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		int l;//размер шаблона

		fin >> l;

		string buff[200];

		int i = 0;
		while (!fin.eof()) {
			fin >> buff[i];
			i++;
		}

		int t;//число последовательностей
		t = i;

		string* arr_str = new string[t];

		for (int j = 0; j < t; j++) {
			arr_str[j] = buff[j];
		}

		int n = arr_str[0].length();//длина одной последовательности

		string median_string;

		median_string = BruteForceMedianSearch(arr_str, t, n, l);

		ofstream fout("output.txt");

		fout << median_string;
		
		fin.close();
	
		fout.close();
		
	}
	return 0;
}


