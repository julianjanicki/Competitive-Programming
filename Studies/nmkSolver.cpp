// Author: Julian Janicki 2022
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

// wypisz plansze
void print(char** board, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << board[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}


// zbadaj czy dana kolumna nie zawiera wygrywajacego podslowa
bool winColumn(char** board, int n, int m, int k, char player) {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		if (board[i][m] == player) {
			sum++;
		} 
		else {
			sum = 0;
		}

		if (sum == k) {
			return 1;
		}
	}

	return 0;
}

// zbadaj czy dany wiersz nie zawiera wygrywajacego podslowa
bool winRow(char** board, int n, int m, int k, char player) {
	int sum = 0;

	for (int j = 0; j < m; j++) {
		if (board[n][j] == player) {
			sum++;
		}
		else {
			sum = 0;
		}

		if (sum == k) {
			return 1;
		}
	}

	return 0;
}

// zbadaj czy dane przekatne nie zawieraja wygrywajacego podslowa
bool winDiag(char** board, int n, int m, int k, char player, int i, int j) {
	int x = i, y = j;
	int sum = 0;

	while (x > 0 && y > 0) {
		x--;
		y--;
	}

	while (x < n && y < m) {
		if (board[x][y] == player) {
			sum++;
		}
		else {
			sum = 0;
		}

		if (sum == k) {
			return 1;
		}

		x++;
		y++;
	}

	x = i, y = j, sum = 0;
	while (x > 0 && y < m - 1) {
		x--;
		y++;
	}
	while (x < n && y >= 0) {
		if (board[x][y] == player) {
			sum++;
		}
		else {
			sum = 0;
		}

		if (sum == k) {
			return 1;
		}

		x++;
		y--;
	}

	return 0;
}

// zbadaj czy na planszy nie ma wolnego miejsca (uzywane tylko po sprawdzeniu mozliwych wygranych wiec powodouje to kontrole remisu)
bool isDraw(char** board, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == '0') {
				return 0;
			}
		}
	}

	return 1;
}

// generuj wszystkie mozliwe ruchy
void generate(int n, int m, int k, char player) {
	int sum = 0;

	char** board = new char* [n];
	for (int i = 0; i < n; i++) {
		board[i] = new char[m];
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];

			if (board[i][j] == '0') {
				sum++;
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (winRow(board, i, m, k, (player == '1') ? '2' : '1')) {
			cout << 0 << '\n';

			return;
		}
	}

	for (int j = 0; j < m; j++) {
		if (winColumn(board, n, j, k, (player == '1') ? '2' : '1')) {
			cout << 0 << '\n';

			return;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == ((player == '1') ? '2' : '1')) {
				if (winDiag(board, n, m, k, (player == '1') ? '2' : '1', i, j)) {
					cout << 0 << '\n';

					return;
				}
			}
		}
	}

	if (isDraw(board, n, m)) {
		cout << 0 << '\n';
		
		return;
	}

	cout << sum << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == '0') {
				board[i][j] = player;
				print(board, n, m);
				board[i][j] = '0';
			}
		}
	}

	for (int i = 0; i < n; i++) {
		delete[] board[i];
	}
	delete[] board;
}

// generuj wszystkie mozliwe ruchy lub w przypadku napotkania konca gry wypisz tylko ten scenariusz
void generateToEnd(int n, int m, int k, char player) {
	int sum = 0;
	
	char** board = new char* [n];
	for (int i = 0; i < n; i++) {
		board[i] = new char[m];
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];

			if (board[i][j] == '0') {
				sum++;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (winRow(board, i, m, k, (player == '1') ? '2' : '1')) {
			cout << 0 << '\n';

			return;
		}
	}

	for (int j = 0; j < m; j++) {
		if (winColumn(board, n, j, k, (player == '1') ? '2' : '1')) {
			cout << 0 << '\n';

			return;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == ((player == '1') ? '2' : '1')) {
				if (winDiag(board, n, m, k, (player == '1') ? '2' : '1', i, j)) {
					cout << 0 << '\n';

					return;
				}
			}
		}
	}

	if (isDraw(board, n, m)) {
		cout << 0 << '\n';

		return;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == '0') {
				board[i][j] = player;

				if (winRow(board, i, m, k, player) == true) {
					cout << 1 << '\n';
					print(board, n, m);

					return;
				}
				else if (winColumn(board, n, j, k, player) == true) {
					cout << 1 << '\n';
					print(board, n, m);

					return;
				}
				else if (winDiag(board, n, m, k, player, i, j) == true) {
					cout << 1 << '\n';
					print(board, n, m);

					return;
				}

				if (isDraw(board, n, m)) {
					cout << 1 << '\n';
					print(board, n, m);

					return;
				}

				board[i][j] = '0';
			}

		}
	}

	cout << sum << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == '0') {
				board[i][j] = player;

				print(board, n, m);
				
				board[i][j] = '0';
			}
		}
	}

	for (int i = 0; i < n; i++) {
		delete[] board[i];
	}
	delete[] board;
}

// podaj wynik gry na podstawie podanej planszy
int solve(char** board, int n, int m, int k, char player, bool isMaximazing, int alpha, int beta, int depth) {
	for (int i = 0; i < n; i++) {
		if (winRow(board, i, m, k, (player == '1') ? '2' : '1')) {
			if (isMaximazing) {
				return -1;
			}
			else {
				return 1;
			}
		}
	}

	for (int j = 0; j < m; j++) {
		if (winColumn(board, n, j, k, (player == '1') ? '2' : '1')) {
			if (isMaximazing) {
				return -1;
			}
			else {
				return 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == ((player == '1') ? '2' : '1')) {
				if (winDiag(board, n, m, k, (player == '1') ? '2' : '1', i, j)) {
					if (isMaximazing) {
						return -1;
					}
					else {
						return 1;
					}
				}
			}
		}
	}

	if (isDraw(board, n, m)) {
		return 0;
	}

	if (isMaximazing) {
		// optymalizacja blokujaca tworzenie "glupich" niepotrzebnych poddrzew rekurencji
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (board[i][j] == '0') {
					board[i][j] = player;

					if (winRow(board, i, m, k, player) == true) {
						board[i][j] = '0';

						return 1;
					}
					else if (winColumn(board, n, j, k, player) == true) {
						board[i][j] = '0';

						return 1;
					}
					else if (winDiag(board, n, m, k, player, i, j) == true) {
						board[i][j] = '0';

						return 1;
					}

					board[i][j] = '0';
				}
			}
		}

		// przeszukiwanie w glab algorytmem minimax (z optymalizacja alfabeta)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (board[i][j] == '0') {
					board[i][j] = player;

					int score = solve(board, n, m, k, (player == '1') ? '2' : '1', !isMaximazing, alpha, beta, depth + 1);
					if (score > alpha) {
						alpha = score;
					}

					board[i][j] = '0';

					if (alpha >= beta) {
						return alpha;
					}
				}
			}
		}

		return alpha;
	}
	else {
		// optymalizacja blokujaca tworzenie "glupich" niepotrzebnych poddrzew rekurencji
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (board[i][j] == '0') {
					board[i][j] = player;

					if (winRow(board, i, m, k, player) == true) {
						board[i][j] = '0';

						return -1;
					}
					else if (winColumn(board, n, j, k, player) == true) {
						board[i][j] = '0';

						return -1;
					}
					else if (winDiag(board, n, m, k, player, i, j) == true) {
						board[i][j] = '0';

						return -1;
					}

					board[i][j] = '0';
				}
			}
		}

		// przeszukiwanie w glab algorytmem minimax (z optymalizacja alfabeta)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (board[i][j] == '0') {
					board[i][j] = player;

					int score = solve(board, n, m, k, (player == '1') ? '2' : '1', !isMaximazing, alpha, beta, depth + 1);
					if (score < beta) {
						beta = score;
					}
					
					board[i][j] = '0';

					if (alpha >= beta) {
						return beta;
					}
				}
			}
		}

		return beta;
	}
}

// wczytyawanie komend oraz wywolywanie powzyszych funkcji
int main() {
	string cmd;
	while (cin >> cmd) {
		int n, m, k;
		char player;
		cin >> n >> m >> k >> player;

		if (cmd == "GEN_ALL_POS_MOV") {
			generate(n, m, k, player);
		}
		else if (cmd == "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") {
			generateToEnd(n, m, k, player);
		}
		else {
			char** board;
			board = new char* [n];
			for (int i = 0; i < n; i++) {
				board[i] = new char[m];
				for (int j = 0; j < m; j++) {
					cin >> board[i][j];
				}
			}

			int score = solve(board, n, m, k, player, 1, -10, 10, 0);
			if ((score == 1 && player == '1') || (score == -1 && player == '2')) {
				cout << "FIRST_PLAYER_WINS\n";
			}
			else if ((score == -1 && player == '1') || (score == 1 && player == '2')) {
				cout << "SECOND_PLAYER_WINS\n";
			}
			else {
				cout << "BOTH_PLAYERS_TIE\n";
			}

			for (int i = 0; i < n; i++) {
				delete[] board[i];
			}
			delete[] board;
		}
	}


	return 0;
}