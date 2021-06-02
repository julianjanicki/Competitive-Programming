// POP 2020-12-10 projekt 1 Janicki Julian Microsoft Visual C++ 2019 kompilator wbudowany / wewnetrzny
#include <iostream>
#include <iomanip>
using namespace std;


const int CARS = 5; // ilosc samochodow
const int MIN_KG = 50; // minimalna waga paczki
const int MAX_KG = 150; // maksymalna waga paczki
const int MAX_SKIP = 2; // maksymalna waga paczki
const int MAX = 100; // pojemnosc jednego auta


struct info {
	int id; // numer auta
	int kg; // zaladowanie auta
	int skip; // liczba pominiec
};


struct item {
	int id; // numer auta na liscie
	int kg; // zaladowanie auta na liscie
};


struct list {
	item* array; // tablica uzywana jako dynamiczna
	int capacity; // pojemnosc listy
	int current_size; // ilosc akutalnych elementow
};


void push(int id, int kg, list &ans) { // dodawawnie elementu na koniec listy
	if (ans.capacity == ans.current_size) {
		item* temp = ans.array;
		ans.array = new item[ans.capacity *= 2];
		for (int i = 0; i < ans.current_size; ++i) { // przepisywanie starej
			ans.array[i] = temp[i];
		}
		delete[] temp;
		temp = NULL;
	}
	ans.array[ans.current_size].id = id; // element na koniec
	ans.array[ans.current_size].kg = kg;
	++ans.current_size;
}


void set_default(info car[]) { // zerowanie 
	for (int i = 0; i < CARS; ++i) {
		car[i].id = i + 1;
		car[i].kg = 0;
		car[i].skip = 0;
	}
}


void leave_queue(info car[], list &ans) {
	cout << "-------------------------------\n";
	cout << "Odjezdza auto o numerze " << car[0].id << '\n';
	cout << "-------------------------------\n\n";
	push(car[0].id, car[0].kg, ans); // dajemy element na koniec listy (wynikowej)
	car[0].kg = 0; // wyjezdzamy
	car[0].skip = 0;
	info temp = car[0];
	for (int i = 1; i < CARS; ++i) { // przesuwamy auta w kolejce
		car[i - 1] = car[i];
	}
	car[CARS - 1] = temp;
}


void give(info car[], int weight) { // odkladanie paczki
	bool in_car = false; // czy paczka w aucie
	for (int i = 0; i < CARS; ++i) {
		if (car[i].kg + weight > MAX) { 
			++car[i].skip; // liczenie pomietych "tur"
		}
		else { // ladowanie do auta 
			cout << "Paczka o wadze " << weight << " kg zapakowana do auta nr " << car[i].id << "\n\n";
			car[i].kg += weight;
			in_car = true;
			break;
		}
	}
	if (!in_car) { // paczka nie miesci sie nigdzie
		cout << "Paczka do wyrzucenia - brak miejsca!\n\n";
	}
}


void clear_queue(info car[], list &ans) { // sprawdzmy czy moze juz cos nie odjechalo
	int counter = 0;
	for (int i = 0; i < CARS; ++i) {
		if (car[i].skip == MAX_SKIP || car[i].kg == MAX) { // warunek o odjechaniu
			++counter;
		}
	}
	for (int i = 0; i < counter; ++i) { // dla i+1'tego samochodu odjezdzamy nim
		leave_queue(car, ans);
	}
}


void output(list &ans) { // wypisywanie listy wynikowej
	cout << '\n' << "Numer Auta" << setw(4) << "|" << setw(13) << "Ladunek\n";
	cout << "-------------+---------------\n";
	for (int i = 0; i < ans.current_size; ++i) {
		cout << ans.array[i].id << setw(13) <<"|" << setw(6) << " " << ans.array[i].kg << '\n';
	}
	cout << "\n\n";
}


int main() {
	list ans = { new item[1], 1, 0 }; // lista wynikowa
	info* car = new info[CARS]; // dynamicznie zaalokowana pamiec dla tablicy car no i sama jej delkaracja
	set_default(car);
	int weight = 0; // do lososawnia wagi paczki
	char input, last = 'o'; // tu wiadomo input jako opcja menu no i last jako ostatni element wybrany sposrod o i p zeby kontrolowac gdyby ktos chcial za duzo paczek dac kurierowi itd
	while (true) {
		cout << "p - przekaz paczke kurierowi\no - kurier odklada paczke do auta\nw - wypisz liste odjazdow samochodow\nq - zakoncz dzialanie programu\n\n";
		cout << "Podaj opcje menu p lub o lub w lub q: ";
		cin >> input;
		switch (input) {
		case 'p':
			if (last != 'o') {
				cout << "Aby przekazac kurierowi nastepna paczke najpierw musi on odlozyc poprzednia\n\n";
				break;
			}
			srand((unsigned int)time(NULL));
			weight = MIN_KG + rand() % (MAX_KG - MIN_KG + 1); // losowanie od 1 do 10
			cout << "\n\nWylosoana waga: " << weight << "\n\n";
			cout << "Przekazano paczke kurierowi\n\n";
			break;
		case 'o':
			if (last != 'p') {
				cout << "Aby wlozyc paczke do auta najpierw musisz ja przekazac kurierowi kilkajac\n\n";
				break;
			}
			give(car, weight); // do auta
			clear_queue(car, ans); // czystka bo moze cos wyjechało
			break;
		case 'w':
			if (ans.current_size == 0) {
				cout << "Zaden samochod jeszcze nie odjechal\n\n";
				break;
			}
			output(ans); // wypisz
			break;
		case 'q':
			cout << "KONCZE PROGRAM...\n";
			exit(0); // exit - zamknij 
		default:
			cout << "Niepoprawna opcja menu wybierz o lub p!\n\n";
			break;
		}
		if (input == 'o' || input == 'p') {
			last = input; // tutaj ta kontrola wejscia czy mozna odlozyc paczke lub dac kolejna itp
		}
	}

	delete[] car; // no i usuwamy 
	car = NULL;

	return 0;
}
