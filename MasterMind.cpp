#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int glb_code_length = 4;
const unsigned int glb_num_guess = 10;
double game_vers = 1.0;

int GetInputCmd();
void GenerateCode(int *code_arr);
int ConvertCodeToArr(int *code_arr, string input_code, char *buff);
int CheckGuess(int *code_arr, int *code_guess, char *buff);

int main() {
	bool play_game = true, sngl_player = false;
	char play_again = '2';
	string input_code;
	int *code_arr = new int[glb_code_length];
	int *code_guess = new int[glb_code_length];
	char *buff = new char[glb_code_length + 1];
	int guesses_left = glb_num_guess;

	srand(time(NULL));

	//Main game loop
	while (play_game) {
	// Introductory section
		switch (GetInputCmd())
		{
		case 1:
			sngl_player = true;
			break;
		case 2:
			sngl_player = false;
			break;
		case 3:
			cout << "The goal of this game is to guess the code input by the other" << endl;
			cout << "player or computer.  Then, Codebreaker tells you how many numbers "<< endl;
			cout << "are right and in the correct position as well as how many are the " << endl;
			cout << "right number, but wrong position." << endl;
			cout << endl;
			continue;
		case 4:
			return 0;
		default:
			cout << "Error: Command not found\n" << endl;
			continue;
		}
		
	// Code input
		if (sngl_player == true) {
			GenerateCode(code_arr);
		}
		else {
			cout << "Codemaker, please enter your code: ";
			cin >> input_code;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl;
			cout << endl;
			if (input_code.length() != glb_code_length) {
				cout << "Error: Code invalid\n" << endl;
				continue;
			}
			if (ConvertCodeToArr(code_arr,input_code, buff) == -1)
				continue;
		}

	// Take second user input
		cout << "Codebreaker, take your guesses:\n" << endl;
		while (guesses_left > 0) {
			if (guesses_left > 1)
				cout << "You have " << guesses_left << " guesses left." << endl;
			else if (guesses_left == 1)
				cout << "You have 1 guess left." << endl;
			if (int guess_val = CheckGuess(code_arr, code_guess, buff)) {
				if (guess_val == -1)
					continue;
				break;
			}
			--guesses_left;
			if (guesses_left == 0) {
				cout << "Sorry, try again next time!" << endl;
				cout << "The code was: ";
				for (int i = 0; i < glb_code_length; ++i) {
					cout << code_arr[i];
				}
				cout << endl;
				cout << endl;
			}
		}

		cout << "Do you want to play again?" << endl;
		cout << "1. Yes\n2. No" << endl;
		cout << "\n>";
		cin >> play_again;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl;
		if (play_again == '2')
			play_game = false;
		guesses_left = glb_num_guess;
	}

	cout << "\nThanks for playing!" << endl;
	delete code_arr;
	delete code_guess;
	delete buff;
	return 0;
}

// TODO: Guess error checking
int CheckGuess(int *code_arr, int *code_guess, char *buff) {
	string guess_num;
	int num_corr_pos = 0;	// Right numbers, right positions
	int num_corr = 0;		// Right numbers
	int num_wrong_pos = 0;	// Right numbers, wrong position
	int code_num_amounts[10] = {0};
	cout << "> ";
	cin >> guess_num;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (guess_num.length() != glb_code_length) {
		cout << "Error: Invalid code length.\n" << endl;
		return -1;
	}
	if (ConvertCodeToArr(code_guess, guess_num, buff) == -1)
		return -1;
	for (int i = 0; i < glb_code_length; ++i) {
		if (code_guess[i] == code_arr[i]) {
			++num_corr_pos;
		}
		++code_num_amounts[code_arr[i]];
	}
	for (int i = 0; i < glb_code_length; ++i) {
		if (code_num_amounts[code_guess[i]] > 0) {
			--code_num_amounts[code_guess[i]];
			++num_corr;
		}
	}
	cout << endl;
	if (num_corr_pos != 1)
		cout << num_corr_pos << " digits are in the correct position." << endl;
	else
		cout << "1 digit is in the correct position." << endl;
	if ((num_corr - num_corr_pos) != 1)
	else
		cout << "1 digit is correct, but in the wrong position.\n" << endl;
	if (num_corr_pos == glb_code_length) {
		cout << "Congratulations codebreaker, you have correctly guessed the code!\n" << endl;
		return 1;
	}
	return 0;
}

int ConvertCodeToArr(int *code_arr, string input_code, char *buff) {
	strncpy(buff, input_code.c_str(), glb_code_length);
	for (int i = 0; i < glb_code_length; ++i) {
		if (isdigit(buff[i]) == 0) {
			cout << "Error: Invalid code\n" << endl;
			return -1;
		}
		code_arr[i] = buff[i] - '0';
	}
	return 0;
}

// Generates the code in single player.
void GenerateCode(int *code_arr) {
	for (int i = 0; i < glb_code_length; ++i) {
		code_arr[i] = rand() % 6; // 0 - 5
	}
}

// Takes the input command and decodes it.
int GetInputCmd() {
	string input_cmd;
	char input_cmd_char;
	cout << "Hello, welcome to codebreaker version "<< game_vers << "!" << endl;
	cout << "What would you like to do?\n" << endl;
	string cmd_list[4] = {"1 Player", "2 Player", "Instructions", "Quit"};
	for (int i = 0; i < 4; ++i) {
		cout << i + 1 << ". " << cmd_list[i] << endl;
	}
	cout << "\n>";
	cin >> input_cmd;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;
	if (input_cmd.length() != 1)
		return -1;
	input_cmd_char = input_cmd.c_str()[0];
	return input_cmd_char - '0';
}
