#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int A2048[4][4], B2048[4][4], Temp1 = 0, Temp2 = 0, AScore = 0, BScore = 0;
char Move;
bool Back = false;
bool Changed = false;
bool First_Move = true;

void Initialization();
void Display();
void Motion();
void Random();
bool Game_ended();

int main()
{
	Initialization();
	cout << "Use'W','S','A','D'to move,and 'B' to return" << endl;
	cout << "The return function can only be used once in a row" << endl;
	while (true)
	{
		Display();
		Motion();
		Random();
		if (Game_ended()) break;
	}
	return 0;
}

void Initialization()
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			A2048[i][j] = 0;
		}
	}
	srand(time(NULL));
	Temp1 = rand() % 16;
	Temp2 = rand() % 16;
	A2048[Temp1 / 4][Temp1 % 4] = 2;
	while (Temp1 == Temp2)
	{
		Temp2 = rand() % 16;
	}
	A2048[Temp2 / 4][Temp2 % 4] = 2;
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			B2048[i][j] = A2048[i][j];
		}
	}
}

void Display()
{
	cout << "__________________________" << endl;
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			for (int k = 0;k < 4 - to_string(A2048[i][j]).length();k++)
			{
				cout << " ";
			}
			cout << A2048[i][j];
			if (j < 3)
			{
				cout << "|";
			}
			else
			{
				cout << "|";
				cout << endl;
				cout << "--------------------" << endl;
			}
		}
	}
	cout << "Score:" << AScore << endl;
	cout << "Move:";
}

void Motion()
{
	cin >> Move;
	if (Move == 'B' || Move == 'b')
	{
		if (First_Move) cout << "This is your inital round" << endl;
		else
		{
			if (Back)
			{
				cout << "The return function can only be used once in a row" << endl;
			}
			else
			{
				for (int i = 0;i < 4;i++)
				{
					for (int j = 0;j < 4;j++)
					{
						A2048[i][j] = B2048[i][j];
						AScore = BScore;
					}
				}
			}
			Back = true;
		}
	}
	else
	{
		Back = false;
		for (int i = 0;i < 4;i++)
		{
			for (int j = 0;j < 4;j++)
			{
				B2048[i][j] = A2048[i][j];
			}
		}
		BScore = AScore;
		if (Move == 'A' || Move == 'a')
		{
			for (int i = 0;i < 4;i++)
			{
				for (int j = 0;j < 4;j++)
				{
					if (A2048[i][j] != 0)
					{
						if (j < 3)
						{
							//Detect Merge
							Temp1 = A2048[i][j];
							for (int k = 0;k < 3 - j;k++)
							{
								if (A2048[i][j + k + 1] != 0)
								{
									if (Temp1 == A2048[i][j + k + 1])
									{
										Changed = true;
										AScore += Temp1 * 2;
										A2048[i][j] += Temp1;
										A2048[i][j + k + 1] = 0;
									}
									break;
								}
							}
						}
						if (j != 0)
						{
							//Detect Move
							for (int k = 0;k < j;k++)
							{
								if (A2048[i][j - k - 1] != 0)
								{
									if (k != 0)
									{
										Changed = true;
										A2048[i][j - k] = A2048[i][j];
										A2048[i][j] = 0;
									}
									break;
								}
								if (A2048[i][0] == 0 && k == j - 1)
								{
									Changed = true;
									A2048[i][0] = A2048[i][j];
									A2048[i][j] = 0;
								}
							}
						}
					}
				}
			}
		}
		else if (Move == 'D' || Move == 'd')
		{
			for (int i = 0;i < 4;i++)
			{
				for (int j = 0;j < 4;j++)
				{
					if (A2048[i][3 - j] != 0)
					{
						if (j < 3)
						{
							//Detect Merge
							Temp1 = A2048[i][3 - j];
							for (int k = 0;k < 3 - j;k++)
							{
								if (A2048[i][2 - j - k] != 0)
								{
									if (Temp1 == A2048[i][2 - j - k])
									{
										Changed = true;
										AScore += Temp1 * 2;
										A2048[i][3 - j] += Temp1;
										A2048[i][2 - j - k] = 0;
									}
									break;
								}
							}
						}
						if (j != 0)
						{
							//Detect Move
							for (int k = 0;k < j;k++)
							{
								if (A2048[i][4 - j + k] != 0)
								{
									if (k != 0)
									{
										Changed = true;
										A2048[i][3 - j + k] = A2048[i][3 - j];
										A2048[i][3 - j] = 0;
									}
									break;
								}
								if (A2048[i][3] == 0 && k == j - 1)
								{
									Changed = true;
									A2048[i][3] = A2048[i][3 - j];
									A2048[i][3 - j] = 0;
								}
							}
						}
					}
				}
			}
		}
		else if (Move == 'W' || Move == 'w')
		{
			for (int i = 0;i < 4;i++)
			{
				for (int j = 0;j < 4;j++)
				{
					if (A2048[j][i] != 0)
					{
						if (j < 3)
						{
							//Detect Merge
							Temp1 = A2048[j][i];
							for (int k = 0;k < 3 - j;k++)
							{
								if (A2048[j + k + 1][i] != 0)
								{
									if (Temp1 == A2048[j + k + 1][i])
									{
										Changed = true;
										AScore += Temp1 * 2;
										A2048[j][i] += Temp1;
										A2048[j + k + 1][i] = 0;
									}
									break;
								}
							}
						}
						if (j != 0)
						{
							//Detect Move
							for (int k = 0;k < j;k++)
							{
								if (A2048[j - k - 1][i] != 0)
								{
									if (k != 0)
									{
										Changed = true;
										A2048[j - k][i] = A2048[j][i];
										A2048[j][i] = 0;
									}
									break;
								}
								if (A2048[0][i] == 0 && k == j - 1)
								{
									Changed = true;
									A2048[0][i] = A2048[j][i];
									A2048[j][i] = 0;
								}
							}
						}
					}
				}
			}
		}
		else if (Move == 'S' || Move == 's')
		{
			for (int i = 0;i < 4;i++)
			{
				for (int j = 0;j < 4;j++)
				{
					if (A2048[3 - j][i] != 0)
					{
						if (j < 3)
						{
							//Detect Merge
							Temp1 = A2048[3 - j][i];
							for (int k = 0;k < 3 - j;k++)
							{
								if (A2048[2 - j - k][i] != 0)
								{
									if (Temp1 == A2048[2 - j - k][i])
									{
										Changed = true;
										AScore += Temp1 * 2;
										A2048[3 - j][i] += Temp1;
										A2048[2 - j - k][i] = 0;
									}
									break;
								}
							}
						}
						if (j != 0)
						{
							//Detect Move
							for (int k = 0;k < j;k++)
							{
								if (A2048[4 - j + k][i] != 0)
								{
									if (k != 0)
									{
										Changed = true;
										A2048[3 - j + k][i] = A2048[3 - j][i];
										A2048[3 - j][i] = 0;
									}
									break;
								}
								if (A2048[3][i] == 0 && k == j - 1)
								{
									Changed = true;
									A2048[3][i] = A2048[3 - j][i];
									A2048[3 - j][i] = 0;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			cout << "Only W,A,S,D,B(or w,a,s,d,b) are available!" << endl;
		}
	}
}

void Random()
{
	if (Changed)
	{
		if (First_Move)
		{
			First_Move = false;
		}
		if (rand() % 5 > 4)
		{
			Temp1 = 4;
		}
		else
		{
			Temp1 = 2;
		}
		Changed = false;
		Temp2 = rand() % 16;
		while (A2048[Temp2 / 4][Temp2 % 4] != 0)
		{
			Temp2 = rand() % 16;
		}
		A2048[Temp2 / 4][Temp2 % 4] = Temp1;
	}
}
	
bool Game_ended()
{
	//Detect Win
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (A2048[i][j] == 2048)
			{
				cout << "You Win!";
				return true;
			}
		}
	}
	//Detect Lose
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			if (A2048[i][j] == 0) return false;
			if (j < 3)
			{
				if (A2048[i][j] == A2048[i][j + 1]) return false;
			}
			if (i < 3)
			{
				if (A2048[i][j] == A2048[i + 1][j]) return false;
			}
		}
	}
	//Lose
	cout << "You Lose";
	return true;
}
