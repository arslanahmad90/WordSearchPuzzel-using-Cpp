#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
struct player
{
	int playerid;
	char playername[20];
	int score;
};
int find_length(char* ptr);
char* create_memory(int size);
void copy_1d(char* src, char* dest, int size);
void copy_2d(char** src, char** dest, int size);
char* auto_grow_1d(char* ptr, int size);
char** auto_grow_2d(char** dptr, int size);
char* shrink_1d(char* ptr, int size);
char** shrink_2d(char** dptr, int size, int no_of_rows);
void copy_int_1d(int* src, int* dest, int size);
int* shrink_int_1d(int* ptr, int size);
void write_board_infile(char filename[], char** dptr, int no_of_rows, int colsize);
char** read_data_varying_rows_cols(char filename[], char** dptr, int*& word_size, int size, int& no_of_rows);
char main_menue();
void level_selection(int& level);
void pause_game(char filename[], char**& dptr, int& no_of_rows, int colsize, int size, int& lifes);
void find_level_wining_count(char filename[], char** dictionary, int* word_size, int dic_no_of_rows, int& easy_count, int& med_count, int& hard_count);
void write_high_score(char filename4[], player info[], int size);
bool chek_word_existence(char word[], char**& dictionary, int* word_size, int& dic_no_of_rows);
bool check_word_single_row_forward(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
bool check_word_single_col_downdward(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
bool check_word_backward_singe_row(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
bool check_word_single_col_updward(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
bool check_forward_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
bool check_backward_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
bool check_forward_reverse_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
bool check_backward_reverse_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen);
void new_game(char filename1[], char filename4[], char filename3[], char**& dictionary, int* word_size, int& dic_no_of_rows, player& info, int level);
char** read_data_fixed_col(char filename[], char** dptr, int size, int& no_of_rows, int colsize);
void game_processing(char filename1[], char filename2[], char filename3[], char filename4[], char**& dictionary, int* word_size, int& dic_no_of_rows, player& info, int& level);
void display_1(char** dptr, int no_of_rows);
void display(char** dptr, int no_of_rows, int colsize);
void wining_message();
char** remove_dangaling_ptr(char** dptr, int size);
char** delete_full_memory(char** dptr, int size);
int main()
{
	int size = 1, colsize = 15, dic_no_of_rows = 0, level = 0;
	player info;
	char** dictionary = new char* [size];
	int* word_size = new int[size];
	char filename1[20] = { "board.txt" };
	char filename2[20] = { "dictionary.txt" };
	char filename3[20] = { "highscore.txt" };
	char filename4[20] = { "pausedgame.txt" };
	SetConsoleTextAttribute(console, 15);
	dictionary = read_data_varying_rows_cols(filename2, dictionary, word_size, size, dic_no_of_rows);
	game_processing(filename1, filename2, filename3, filename4, dictionary, word_size, dic_no_of_rows, info, level);
	dictionary = delete_full_memory(dictionary, dic_no_of_rows);
	return 0;
}
int find_length(char* ptr)
{
	int size = 0;
	for (size = 0; *(ptr + size) != '\0'; size++);
	return size;
}
char* create_memory(int size)
{
	char* ptr = new char[size];
	return ptr;
}
char** delete_full_memory(char** dptr, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete[] * (dptr + i);
		*(dptr + i) = NULL;
	}
	delete[]dptr;
	dptr = NULL;
	return dptr;
}
char** remove_dangaling_ptr(char** dptr, int size)
{
	for (int i = 0; i < size; i++)
		*(dptr + i) = NULL;
	delete[]dptr;
	dptr = NULL;
	return dptr;
}
void copy_1d(char* src, char* dest, int size)
{
	for (int i = 0; i < size; i++)
		*(dest + i) = *(src + i);
}
void copy_2d(char** src, char** dest, int size)
{
	for (int i = 0; i < size; i++)
		*(dest + i) = *(src + i);
}
char* auto_grow_1d(char* ptr, int size)
{
	char* temp = ptr;
	ptr = new char[size * 2];
	copy_1d(temp, ptr, size);
	delete[]temp;
	temp = NULL;
	return ptr;
}
char** auto_grow_2d(char** dptr, int size)
{
	char** temp = dptr;
	dptr = new char* [size * 2];
	copy_2d(temp, dptr, size);
	temp = remove_dangaling_ptr(temp, size);
	return dptr;
}
char* shrink_1d(char* ptr, int size)
{
	char* temp = ptr;
	size++;
	ptr = new char[size];
	copy_1d(temp, ptr, size);
	*(ptr + (size - 1)) = '\0';
	delete[]temp;
	temp = NULL;
	return ptr;
}
char** shrink_2d(char** dptr, int size, int no_of_rows)
{
	char** temp = dptr;
	dptr = new char* [no_of_rows];
	copy_2d(temp, dptr, no_of_rows);
	temp = remove_dangaling_ptr(temp, size);
	return dptr;
}
void copy_int_1d(int* src, int* dest, int size)
{
	for (int i = 0; i < size; i++)
		*(dest + i) = *(src + i);
}
int* auto_grow_int_1d(int* ptr, int size)
{
	int* temp = ptr;
	ptr = new int[size * 2];
	copy_int_1d(temp, ptr, size);
	delete[]temp;
	temp = NULL;
	return ptr;

}
int* shrink_int_1d(int* ptr, int size)
{
	int* temp = ptr;
	ptr = new int[size];
	copy_int_1d(temp, ptr, size);
	delete[]temp;
	temp = NULL;
	return ptr;
}
void write_board_infile(char filename[], char** dptr, int no_of_rows, int colsize)
{
	ofstream fout;
	fout.open(filename, ios::out);
	if (!fout.is_open())
		cout << "FILE NOT FOUND ";
	else
	{
		for (int r = 0; r < no_of_rows; r++)
		{
			for (int c = 0; c < colsize; c++)
			{
				fout << *(*(dptr + r) + c);
			}
		}
		fout.close();
	}
}
char** read_data_fixed_col(char filename[], char** dptr, int size, int& no_of_rows, int colsize)
{
	ifstream fin;
	fin.open(filename, ios::in);
	if (!fin.is_open())
		cout << "FILE NOT FOUND ";
	else
	{
		while (!fin.eof())
		{
			*(dptr + no_of_rows) = create_memory(colsize);
			for (int i = 0; i < colsize; i++)
				fin >> *(*(dptr + no_of_rows) + i);
			no_of_rows++;
			if (fin.eof())
				break;
			if (no_of_rows == size)
			{
				dptr = auto_grow_2d(dptr, size);
				size *= 2;
			}

		}
		fin.close();
		no_of_rows--;
		dptr = shrink_2d(dptr, size, no_of_rows);
	}
	return dptr;
}
char** read_data_varying_rows_cols(char filename[], char** dptr, int*& word_size, int size, int& no_of_rows)
{
	int strlen = 0;
	ifstream fin;
	fin.open(filename, ios::in);
	if (!fin.is_open())
		cout << "FILE NOT FOUND ";
	else
	{

		while (!fin.eof())
		{
			*(dptr + no_of_rows) = create_memory(100);
			fin >> *(dptr + no_of_rows);
			strlen = find_length(*(dptr + no_of_rows));
			*(word_size + no_of_rows) = strlen;
			*(dptr + no_of_rows) = shrink_1d(*(dptr + no_of_rows), strlen);
			no_of_rows++;
			if (fin.eof())
			{
				break;
			}
			if (size == no_of_rows)
			{
				dptr = auto_grow_2d(dptr, size);
				word_size = auto_grow_int_1d(word_size, size);
				size *= 2;
			}

		}
		fin.close();
		word_size = shrink_int_1d(word_size, no_of_rows);
		dptr = shrink_2d(dptr, size, no_of_rows);
	}
	return dptr;

}
void display(char** dptr, int no_of_rows, int colsize)
{
	int a = 10;
	cout << endl << endl;
	for (int r = 0; r < no_of_rows; r++)
	{
		cout << "\t\t";
		SetConsoleTextAttribute(console, a);
		if (a == 15)
			a = 10;
		a++;
		for (int c = 0; c < colsize; c++)
			cout << *(*(dptr + r) + c) << " ";
		cout << endl;
	}
	cout << endl << endl;
}
void find_level_wining_count(char filename[], char** dictionary, int* word_size, int dic_no_of_rows, int& easy_count, int& med_count, int& hard_count)
{
	int wordlen = 0, size = 1, board_no_of_rows = 0, colsize = 15;
	bool check = false;
	char** board = new char* [size];
	board = read_data_fixed_col(filename, board, size, board_no_of_rows, colsize);
	cout << "\n\n\n\n\n\t\t BE PAIENT GAME IS GOING TO LOAD" << endl;
	Sleep(2000);
	system("CLS");
	cout << "\n\n\n\n\n\t\t IT WILL TAKE FEW SECONDS TO LOAD" << endl;
	Sleep(3000);
	SetConsoleTextAttribute(console, 1);
	for (int i = 0; i < dic_no_of_rows; i++)
	{
		wordlen = find_length(*(dictionary + i));
		if (wordlen > 1)
		{
			check = check_word_single_row_forward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
			if (check == true)
				easy_count++;
			else if (check == false)
			{
				check = check_word_single_col_downdward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
				if (check == true)
					easy_count++;
			}
		}
	}
	system("CLS");
	for (int i = 0; i < dic_no_of_rows; i++)
	{
		wordlen = find_length(*(dictionary + i));
		if (wordlen > 1)
		{
			check = check_word_single_row_forward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
			if (check == true)
				med_count++;
			else if (check == false)
			{
				check = check_word_single_col_downdward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
				if (check == true)
					med_count++;
				else if (check == false)
				{
					check = check_word_backward_singe_row(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
					if (check == true)
						med_count++;
					else if (check == false)
					{
						check = check_word_single_col_updward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
						if (check == true)
							med_count++;
					}
				}

			}
		}
	}
	system("CLS");
	for (int i = 0; i < dic_no_of_rows; i++)
	{
		wordlen = find_length(*(dictionary + i));
		if (wordlen > 1)
		{
			check = check_word_single_row_forward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
			if (check == true)
				hard_count++;
			else if (check == false)
			{
				check = check_word_single_col_downdward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
				if (check == true)
					hard_count++;
				else if (check == false)
				{
					check = check_word_backward_singe_row(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
					if (check == true)
						hard_count++;
					else if (check == false)
					{
						check = check_word_single_col_updward(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);
						if (check == true)
							hard_count++;
						else if (check == false)
						{
							check = check_forward_diagonal_wise(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);;
							if (check == true)
								hard_count++;
							else if (check == false)
							{
								check = check_backward_diagonal_wise(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);;
								if (check == true)
									hard_count++;
								else if (check == false)
								{
									check = check_forward_reverse_diagonal_wise(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);;
									if (check == true)
										hard_count++;
									else if (check == false)
									{
										check = check_backward_reverse_diagonal_wise(*(dictionary + i), board, board_no_of_rows, colsize, wordlen);;
										if (check == true)
											hard_count++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	system("CLS");
	board = delete_full_memory(board, board_no_of_rows);
	SetConsoleTextAttribute(console, 15);
}
char main_menue()
{
	char ch = '\0';
	while (1)
	{

		cout << "PRESS 'n' FOR NEW GAME \n";
		cout << "PRESS 'r' FOR RESUME GAME \n";
		cout << "PRESS 'l' FOR lEVEl SELECTION \n";
		cout << "PRESS 'h' FOR HIGH SCORE \n";
		cout << "PRESS 'e' FOR EXIT \n";
		cout << "ENTER YOUR DESCION ";
		cin >> ch;
		if (ch == 'n' || ch == 'r' || ch == 'l' || ch == 'h' || ch == 'e')
		{
			system("CLS");
			break;
		}
		else
		{
			cout << "\n\n\n\tYOU ENTERED A WRONG INPUT PLEASE ENTER CORRECT FROM MENUE \n";
			Sleep(1000);
			system("CLS");
		}

	}
	return ch;
}
void level_selection(int& level)
{
	while (1)
	{
		cout << "PRESS 1 FOR EASY \n";
		cout << "PRESS 2 FOR MEDIUM\n";
		cout << "PRESS 3 FOR HARD \n";
		cout << "ENTER YOUR DESCION : ";
		cin >> level;
		if (level == 1 || level == 2 || level == 3)
		{
			break;
		}
		else
		{
			cout << "YOU ENTERED A WRONG INPUT PLEASE ENTER CORRECT FROM MENUE :\n";
		}
	}
	cout << "\n\n\t\tPRESS ENTER TO CONTINUE :";
}
void pause_game(char filename[], char**& dptr, int& no_of_rows, int colsize, int size, int& lifes)
{
	char ch = '\0';
	cout << "\n\n\t\t\t\tPAUSE\n\n";
	write_board_infile(filename, dptr, no_of_rows, colsize);
	no_of_rows = 0;
	dptr = delete_full_memory(dptr, no_of_rows);
	cout << "ENTER e FOR EXIT \n";
	cout << "ENTER r FOR RESUME\n";
	cout << "ENTER YOUR DESCION : ";
	cin >> ch;
	if (ch == 'r')
	{
		no_of_rows = 0;
		dptr = new char* [size];
		dptr = read_data_fixed_col(filename, dptr, size, no_of_rows, colsize);
		cout << "\n\n\t\tPRESS ENTER TO CONTINUE :";
		cin.ignore();
		cin.get(ch);
		if (ch != '.')
			system("CLS");
		else
			system("CLS");

	}
	else
	{
		lifes = 0;
	}
}
void write_high_score(char filename4[], player info[], int size)
{
	ofstream fout;
	fout.open(filename4, ios::out);
	if (!fout.is_open())
		cout << "FILLE NOT FOUND ";
	else
	{
		for (int i = 0; i < size; i++)
		{
			fout << info[i].playerid << " " << info[i].playername << " " << info[i].score << endl;
		}
		fout.close();
	}
}
void read_highscores(char filename4[], player info[], int& size)
{
	ifstream fin;
	fin.open(filename4, ios::out);
	if (!fin.is_open())
		cout << "FILLE NOT FOUND ";
	else
	{
		while (fin >> info[size].playerid)
		{
			fin.ignore();
			fin.getline(info[size].playername, 20, ' ');
			//fin.ignore();
			fin >> info[size].score;
			size++;
		}
		fin.close();
	}
}
void sort_player_info(player info[], int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (info[i].score > info[j].score)
				swap(info[i], info[j]);
		}
}
void display_high_scores(player info[], int size)
{
	char text[20] = " HIGH SCORES ";
	int wordlen = 0;
	wordlen = find_length(text);
	cout << "\n\n\n\n\t\t\t";
	for (int i = 0; i < wordlen; i++)
	{
		SetConsoleTextAttribute(console, 15);
		cout << text[i];
		Sleep(200);
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "\t\t\t";
		cout << info[i].playerid << " " << info[i].playername << " " << info[i].score << endl;
	}
}
bool chek_word_existence(char word[], char**& dictionary, int* word_size, int& dic_no_of_rows)
{
	int flag = 0;
	int wordlen = 0, size = 0;
	char* temp = NULL;
	char check = '\0', check1 = '\0';
	wordlen = find_length(word);
	for (int i = 0; i < dic_no_of_rows; i++)
	{
		if (wordlen == *(word_size + i))
		{
			for (int j = 0; j < wordlen; j++)
			{
				check = *(*(dictionary + i) + j);
				check -= 32;
				check1 = *(*(dictionary + i) + j);
				check1 += 32;

				if (*(word + j) != *(*(dictionary + i) + j) && *(word + j) != check && *(word + j) != check1)
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				size = dic_no_of_rows;
				swap(*(dictionary + (dic_no_of_rows - 1)), *(dictionary + i));
				dic_no_of_rows--;
				dictionary = shrink_2d(dictionary, size, dic_no_of_rows);
				return true;
			}
			flag = 0;
		}
	}
	return false;
}
bool check_word_single_row_forward(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0, count = 0;
	char check = '\0', check1 = '\0';
	int startrow = 0, startcol = 0, endcol = 0;
	for (int r = 0; r < board_no_of_rows; r++)
	{
		for (int c = 0; c < colsize; c++)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				for (int c1 = c, j = 0; j < wordlen; c1++, j++)
				{
					check = *(*(board + r) + c1);
					check = check + 32;
					check1 = *(*(board + r) + c1);
					check1 = check - 32;
					count++;
					if (*(word + j) != check && *(word + j) != *(*(board + r) + c1) && *(word + j) != check1)
					{
						flag = 1;
						break;
					}
					if (c1 == colsize - 1)
						break;
				}
				if (count == wordlen)
					if (flag == 0)
					{
						startrow = r + 1;
						startcol = c;
						endcol = c + wordlen;
						cout << "START AT (ROW " << startrow << "," << "COL" << startcol + 1 << ")" << endl;
						cout << "END AT (ROW " << startrow << "," << "COL" << endcol << ")" << endl;
						return true;
					}

				flag = 0;
				count = 0;
			}
		}

	}
	return false;
}
bool check_word_single_col_downdward(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0, r1 = 0, count = 0;
	char check = '\0', check1 = '\0';
	for (int r = 0; r < board_no_of_rows; r++)
	{
		for (int c = 0; c < colsize; c++)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				r1 = r;
				for (int j = 0; r1 < board_no_of_rows, j < wordlen; r1++, j++)
				{
					check = *(*(board + r1) + c);
					check = check + 32;
					check1 = *(*(board + r1) + c);
					check1 = check - 32;
					count++;
					if (*(word + j) != check && *(word + j) != *(*(board + r1) + c) && *(word + j) != check1)
					{
						flag = 1;
					}
					if (r1 == board_no_of_rows - 1)
						break;
				}
				if (count == wordlen)
					if (flag == 0)
					{
						cout << "START AT (ROWS" << r + 1 << ",COL" << c + 1 << ")" << endl;
						cout << "END AT (ROW " << r1 << ",COL" << c + 1 << ")" << endl;
						return true;
					}
				flag = 0;
				count = 0;
			}
		}
	}
	return false;
}
bool check_word_backward_singe_row(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0;
	char check = '\0', check1 = '\0';
	int startrow = 0, startcol = 0, endcol = 0;
	for (int r = 0; r < board_no_of_rows; r++)
	{
		for (int c = 0; c < colsize; c++)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				for (int c1 = c, j = 0; c1 >= 0, j < wordlen; c1--, j++)
				{
					check = *(*(board + r) + c1);
					check = check + 32;
					check1 = *(*(board + r) + c1);
					check1 = check - 32;
					if (*(word + j) != check && *(word + j) != *(*(board + r) + c1) && *(word + j) != check1)
					{

						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "START AT (ROW " << r + 1 << "," << "COL" << c + 1 << ")" << endl;
					cout << "END AT (ROW " << r + 1 << "," << "COL" << c - wordlen + 2 << ")" << endl;
					return true;
				}
				flag = 0;
			}
		}

	}
	return false;
}
bool check_word_single_col_updward(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0, r1 = 0, count = 0;
	char check = '\0', check1 = '\0';
	for (int r = 0; r < board_no_of_rows; r++)
	{
		for (int c = 0; c < colsize; c++)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				r1 = r;
				for (int j = 0; j < wordlen; r1--, j++)
				{
					check = *(*(board + r1) + c);
					check = check + 32;
					check1 = *(*(board + r1) + c);
					check1 = check - 32;
					count++;
					if (*(word + j) != check && *(word + j) != *(*(board + r1) + c) && *(word + j) != check1)
					{
						flag = 1;
						break;
					}
					if (r1 == 0)
						break;
				}
				if (count == wordlen)
					if (flag == 0)
					{
						cout << "START AT (ROWS" << r + 1 << ",COL" << c + 1 << ")" << endl;
						cout << "END AT (ROW " << r - wordlen + 2 << ",COL" << c + 1 << ")" << endl;
						return true;
					}
				flag = 0;
				count = 0;
			}
		}
	}
	return false;
}
bool check_forward_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0, count = 0;
	char check = '\0', check1 = '\0';
	for (int r = 0; r < board_no_of_rows; r++)
	{
		for (int c = 0; c < colsize; c++)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				for (int r1 = r, j = 0; j < wordlen; r1++, j++, c++)
				{

					check = *(*(board + r1) + c);
					check = check + 32;
					check1 = *(*(board + r1) + c);
					check1 = check - 32;
					count++;
					if (*(word + j) != check && *(word + j) != *(*(board + r1) + c) && *(word + j) != check1)
					{
						flag = 1;
						break;
					}
					if (c == colsize - 1 || r1 == board_no_of_rows - 1)
					{
						c++;
						break;
					}
				}
				if (count == wordlen)
					if (flag == 0)
					{
						cout << "START AT (ROWS" << r + 1 << ",COL" << c - wordlen + 1 << ")" << endl;
						cout << "END AT (ROW " << r + wordlen << ",COL" << c << ")" << endl;
						return true;
					}
				flag = 0;
				count = 0;
			}
		}
	}
	return false;
}
bool check_backward_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0, count = 0, r1 = 0;
	char check = '\0', check1 = '\0';
	for (int r = board_no_of_rows - 1; r >= 0; r--)
	{
		for (int c = colsize - 1; c > 0; c--)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				if (r <= wordlen)
					break;
				r1 = r;
				for (int j = 0; c >= 0, j < wordlen; r1--, j++, c--)
				{
					check = *(*(board + r1) + c);
					check = check + 32;
					check1 = *(*(board + r1) + c);
					count++;
					if (*(word + j) != check && *(word + j) != *(*(board + r1) + c) && *(word + j) != check1)
					{
						flag = 1;
					}

				}
				if (count == wordlen)
					if (flag == 0)
					{
						cout << "START AT (ROWS" << r + 1 << ",COL" << c + wordlen + 1 << ")" << endl;
						cout << "END AT (ROW " << r1 + 2 << ",COL" << c + 2 << ")" << endl;
						return true;
					}
				flag = 0;
				count = 0;
			}
		}

	}
	return false;
}
bool check_forward_reverse_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0, count = 0, r1 = 0;
	char check = '\0', check1 = '\0';
	for (int r = 0; r < board_no_of_rows; r++)
	{
		for (int c = 0; c < colsize; c++)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				r1 = r;
				for (int j = 0, c1 = c; c1 < colsize, j < wordlen; r1--, j++, c1++)
				{

					check = *(*(board + r1) + c1);
					check = check + 32;
					check1 = *(*(board + r1) + c1);
					if (*(word + j) != check && *(word + j) != *(*(board + r1) + c) && *(word + j) != check1)
					{
						flag = 1;
						break;
					}
					count++;
					if (r1 == 0)
						break;
				}
				if (count == wordlen)
					if (flag == 0)
					{
						cout << "START AT (ROWS" << r + 1 << ",COL" << c + 1 << ")" << endl;
						cout << "END AT (ROW " << r1 + 2 << ",COL" << c + wordlen << ")" << endl;
						return true;
					}
				flag = 0;
				count = 0;
			}
		}
	}
	return false;
}
bool check_backward_reverse_diagonal_wise(char word[], char** board, int board_no_of_rows, int colsize, int wordlen)
{
	int flag = 0, count = 0;
	char check = '\0', check1 = '\0';
	for (int r = 0; r < board_no_of_rows; r++)
	{
		for (int c = 0; c < colsize; c++)
		{
			check = *(*(board + r) + c);
			check = check + 32;
			check1 = *(*(board + r) + c);
			check1 = check - 32;
			if (*(word + 0) == *(*(board + r) + c) || *(word + 0) == check || *(word + 0) == check1)
			{
				for (int r1 = r, j = 0, c1 = c; j < wordlen; r1++, j++, c1--)
				{

					check = *(*(board + r1) + c1);
					check = check + 32;
					check1 = *(*(board + r1) + c1);
					check1 = check - 32;
					count++;
					if (*(word + j) != check && *(word + j) != *(*(board + r1) + c) && *(word + j) != check1)
					{
						flag = 1;
						break;
					}
					if (c1 == 0 || r1 == board_no_of_rows - 1)
					{
						break;
					}
				}
				if (count == wordlen)
					if (flag == 0)
					{
						cout << "START AT (ROWS" << r + 1 << ",COL" << c + 1 << ")" << endl;
						cout << "END AT (ROW " << r + wordlen << ",COL" << c - wordlen + 2 << ")" << endl;
						return true;
					}
				flag = 0;
				count = 0;
			}
		}
	}
	return false;
}
void new_game(char filename1[], char filename4[], char filename3[], char**& dictionary, int* word_size, int& dic_no_of_rows, player& info, int level)
{
	bool check = false;
	int lifes = 3, wordlen = 0, size = 1, easy_count = 0, med_count = 0, hard_count = 0, count = 0, a_p_size = 0;
	int board_no_of_rows = 0, colsize = 15, score = 0;
	char** board = new char* [size];
	player all_p_info[5];
	char lost_message[20] = { "GAME OVER !" };
	char word[20] = { '\0' };
	char ch;
	cout << "PLEASE ENETER YOUR ID ";
	cin >> info.playerid;
	cin.ignore();
	cout << "ENTER YOUR FIRST NAME ";
	cin.getline(info.playername, 20);
	system("CLS");
	board = read_data_fixed_col(filename1, board, size, board_no_of_rows, colsize);
	read_highscores(filename4, all_p_info, a_p_size);
	find_level_wining_count(filename1, dictionary, word_size, dic_no_of_rows, easy_count, med_count, hard_count);
	while (true)
	{
		if (lifes == 0)
		{
			system("CLS");
			wordlen = find_length(lost_message);
			cout << "\n\n\n\n\n\t\t\t";
			for (int i = 0; i < wordlen; i++)
			{
				SetConsoleTextAttribute(console, 12);
				cout << lost_message[i];
				Sleep(100);
			}
			Sleep(1000);
			system("CLS");
			break;
		}
		system("CLS");
		cout << "PLAYER SCORE(" << score << ")\t\t     LIFES (" << lifes << ")\n\t\t\t\t     lEVEL (" << level << ")";
		//cout <<easy_count<<" "<<med_count<<" "<<hard_count<<" "<<count<< "\t\t\t\t    LIFES (" << lifes << ")\n\t\t\t\t     lEVEL(" << level << ")";
		display(board, board_no_of_rows, colsize);
		SetConsoleTextAttribute(console, 15);
		cout << "ENTER WORD YOU WANT TO SEARCH :";
		cin >> word;
		wordlen = find_length(word);
		if (wordlen == 1)
		{
			if (*(word + 0) == 'p')
			{
				system("CLS");
				pause_game(filename3, board, board_no_of_rows, colsize, size, lifes);
				if (lifes == 0)
				{
					system("CLS");
					wordlen = find_length(lost_message);
					cout << "\n\n\n\n\n\t\t\t";
					for (int i = 0; i < wordlen; i++)
					{
						SetConsoleTextAttribute(console, 12);
						cout << lost_message[i];
						Sleep(100);
					}
					Sleep(1000);
					system("CLS");
					break;
					break;
				}
			}
			else
			{
				cout << "WORD CONSTISTS OF TWO OR MORE THAN TWO LETTERS TRY WITH A WORD " << endl;
				cout << "\n\n\t\tPRESS ENTER TO CONTINUE :";
				cin.ignore();
				cin.get(ch);
				if (ch != '.')
					system("CLS");
				else
					system("CLS");
			}
		}
		else if (true == chek_word_existence(word, dictionary, word_size, dic_no_of_rows))
		{
			if (level == 1)
			{
				check = check_word_single_row_forward(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
				{
					check = check_word_single_col_downdward(word, board, board_no_of_rows, colsize, wordlen);
				}
				if (check == true)
				{
					score += 10;
					count++;
				}
				else
				{
					cout << "WORD NOT FOUND IN BOARD BUT PRESENT IN DICTIONARY" << endl;
					lifes--;
				}
				if (count == easy_count)
				{
					Sleep(300);
					system("CLS");
					wining_message();
					break;
				}
			}

			else if (level == 2)
			{
				check = check_word_single_row_forward(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_word_single_col_downdward(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_word_backward_singe_row(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_word_single_col_updward(word, board, board_no_of_rows, colsize, wordlen);
				if (check == true)
				{
					score += 10;
					count++;
				}
				else
				{
					cout << "WORD NOT FOUND IN BOARD BUT PRESENT IN DICTIONARY" << endl;
					lifes--;
				}
				if (count == med_count)
				{
					Sleep(300);
					system("CLS");
					wining_message();
					break;
				}
			}
			else if (level == 3)
			{
				check = check_word_single_row_forward(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_word_single_col_downdward(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_word_backward_singe_row(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_word_single_col_updward(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_forward_diagonal_wise(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_backward_diagonal_wise(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_forward_reverse_diagonal_wise(word, board, board_no_of_rows, colsize, wordlen);
				if (check == false)
					check = check_backward_reverse_diagonal_wise(word, board, board_no_of_rows, colsize, wordlen);
				if (check == true)
				{
					score += 10;
					count++;
				}
				else
				{
					cout << "WORD NOT FOUND ON BOARD BUT PRESENT ON DICTIONARY " << endl;
					lifes--;
				}
				if (count == hard_count)
				{
					Sleep(300);
					system("CLS");
					wining_message();
					break;
				}
			}
			else
			{
				lifes--;
				cout << "WORD NOT FOUND" << endl;
			}
			cout << "\n\n\t\tPRESS ENTER TO CONTINUE :";
			cin.ignore();
			cin.get(ch);
			if (ch != '.')
				system("CLS");
			else
				system("CLS");
		}
		else
		{
			cout << "WORD NOT FOUND IN DICTIONARY" << endl;
			lifes--;
			cout << "\n\n\t\tPRESS ENTER TO CONTINUE :";
			cin.ignore();
			cin.get(ch);
			if (ch != '.')
				system("CLS");
			else
				system("CLS");
		}
	}
	info.score = score;
	sort_player_info(all_p_info, a_p_size);
	if (info.score > all_p_info[a_p_size - 1].score)
	{
		all_p_info[a_p_size - 1] = info;
	}
	sort_player_info(all_p_info, a_p_size);
	write_high_score(filename4, all_p_info, a_p_size);
	display_high_scores(all_p_info, a_p_size);
	Sleep(5000);
	board = delete_full_memory(board, board_no_of_rows);
}
void game_processing(char filename1[], char filename2[], char filename3[], char filename4[], char**& dictionary, int* word_size, int& dic_no_of_rows, player& info, int& level)
{
	player all_p_info[5];
	int a_p_size = 0;
	char descion = '\0', ch = '\0';
	int flag = 0;
	while (1)
	{
		system("CLS");
		descion = main_menue();
		if (descion == 'n')
		{
			if (flag == 0)
				level = 1;
			new_game(filename1, filename3, filename4, dictionary, word_size, dic_no_of_rows, info, level);
			break;
			system("CLS");
		}
		else
		{
			if (descion == 'r')
			{
				cout << "\n\n\n\n\n\tYOU ARE NOT ELIGIBLE TO DO SO BECAUSE YOU ARE NOT IN GAMNING MODE" << endl;
				cout << "\n\n\t\tPRESS ENTER TO CONTINUE :";
				cin.ignore();
				cin.get(ch);
				if (ch != '.')
					system("CLS");
				else
					system("CLS");
			}
			else if (descion == 'l')
			{
				level_selection(level);
				flag = 1;
			}
			else if (descion == 'h')
			{
				read_highscores(filename3, all_p_info, a_p_size);
				sort_player_info(all_p_info, a_p_size);
				display_high_scores(all_p_info, a_p_size);
				cout << "\n\n\t\tPRESS ENTER TO CONTINUE :";
				cin.ignore();
				cin.get(ch);
				if (ch != '.')
					system("CLS");
				else
					system("CLS");

			}
			else if (descion == 'e')
			{
				break;
			}
		}
	}
	cout << "\n\n\t\t\tTHANKS FOR PLAYING ";
}
void wining_message()
{
	int wordlen = 0;
	char message[50] = { "CONGRATULATION YOU WON THE GAME! " };
	wordlen = find_length(message);
	cout << "\n\n\n\n\n\t\t\t";
	for (int i = 0; i < wordlen; i++)
	{
		SetConsoleTextAttribute(console, 14);
		cout << message[i];
		Sleep(100);
	}
	Sleep(1000);
	system("CLS");

}
