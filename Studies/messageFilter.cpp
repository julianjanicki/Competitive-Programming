// POP projekt 2 Janicki Julian Microsoft Visual C++ 2019 kompilator wbudowany / wewnetrzny
#include <iostream>
#include <fstream>
using namespace std;

// counting the number of words for an input - function

int count_n(string first) {
	ifstream input;
	input.open(first.c_str());
	if (!input) {
		cout << "Blad odczytu...\nKoncze program...\n";
		exit(0);
	}

	string temp;
	int ans = 0;
	while (input >> temp) {
		++ans;
	}
	input.close();

	return ans;
}

// counting the number of words for the dictionary - function

int count_m(string second) {
	ifstream dic;
	dic.open(second.c_str());
	if (!dic) {
		cout << "Blad odczytu...\nKoncze program...\n";
		exit(0);
	}

	string temp;
	int ans = 0;
	while (dic >> temp) {
		++ans;
	}
	dic.close();

	return ans;
}

// changing letters to uppercase / equal - function

void upper(string& s) {
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] >= 97 && s[i] <= 122) {
			s[i] -= 32;
		}
	}
}

// pattern search - function

bool check(string a, string b) {
	bool ok = 0;
	int n = a.length();
	int m = b.length();
	for (int i = 0; i <= n - m; ++i) {
		ok = 1;
		for (int j = 0; j < m; ++j) {
			if (a[j + i] != b[j]) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			return true;
		}
	}
	return false;
}

// filter - function

void filter(int opt, string arr[], string del[], int n, int m, ofstream& output) {
	for (int i = 0; i < n; ++i) {
		int len = arr[i].length();
		bool change = 0;
		string fst = arr[i];
		//upper(fst);
		for (int j = 0; j < m; ++j) {
			string sec = del[j];
			//upper(sec);
			if (check(fst,sec)) {
				change = 1;
				if (opt == 1) {
					for (int p = 0; p < len; ++p) {
						output << '*';
					}
				}
				else {
					output << arr[i][0];
					for (int p = 1; p < len - 1; ++p) {
						output << char(arr[i][p] - 32);
					}
					output << arr[i][len - 1];
				}
				if (i < n - 1) {
					output << ' ';
				}
				break;
			}
		}
		if (!change) {
			if (i == n - 1) {
				output << arr[i];
			}
			else {
				output << arr[i] << ' ';
			}
			
		}
	}
}

// main - function

int main() {
	// input

	cout << "Podaj nazwe pliku wejsciowego wraz z rozszerzeniem: ";
	string first;
	cin >> first;

	int n = count_n(first);

	ifstream input;
	input.open(first.c_str());
	if (!input) {
		cout << "Blad odczytu...\nKoncze program...\n";
		exit(0);
	}

	// dictionary

	cout << "Podaj nazwe pliku slownikowego wraz z rozszerzeniem: ";
	string second;
	cin >> second;

	int m = count_m(second);

	ifstream dic;
	dic.open(second.c_str());
	if (!dic) {
		cout << "Blad odczytu...\nKoncze program...\n";
		exit(0);
	}

	// output

	cout << "Podaj nazwe pliku wyjsciowego wraz z rozszerzeniem: ";
	string third;
	cin >> third;

	ofstream output;
	output.open(third.c_str());
	
	// create array

	string* arr;
	arr = new string[n];
	for (int i = 0; i < n; ++i) {
		input >> arr[i];
	}

	string* del;
	del = new string[m];
	for (int i = 0; i < m; ++i) {
		dic >> del[i];
	}

	// choice

	cout << "1 - cale\n2 - srodek\nPodaj sposob filtrowania: ";
	int opt;
	cin >> opt;
	if (opt != 1 && opt != 2) {
		cout << "Bledna opcja...\nKoncze program...\n";
		exit(0);
	}
	filter(opt, arr, del, n, m, output);

	// end

	input.close();
	output.close();
	delete[] arr;
	delete[] del;
	del = NULL;
	arr = NULL;
	return 0;
}
