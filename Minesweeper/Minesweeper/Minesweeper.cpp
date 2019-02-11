// Minesweeper.cpp : Defines the entry point for the console application.
//
//	the Minesweeper size is 10.
//	Creat a 2D array which size = 10, fill the whole array with 0.
//	Randomly choice 10 different mines to change the number to -1.
//	Check all maps, find all mines and add 1 to each spot around mines.
//	Show the map.
//	1. When user left click ( +10 )
//		(1). it is a mine, game over
//		(2). it is a number 1-8, show the number 
//		(3). it is 0, we need a recusive function to check and show
//	2. when user right click ( +20 )
//		(1). if it does not have a flag, add a flag
//		(2). if it have a flag, delete the flag
//	After each time user click, we need to draw the map agian.
//
//	-1    -- mine
//  0-8   -- the number of mines around the 
//  9     -- -1 + 10 left click the mine
//  10-18 -- 0-8 + 10 left click the non-mine spot
//  19    -- -1 + 20 right click the mine
//	20-28 -- 0-8 + 20 right click the non-mine spot
//
//	result: lose - right click the mine
//			win  - all spot between 10-19

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <ctime>
#include <graphics.h>
#include <iostream>

const int Row = 10;
const int Col = 10;
const int Num = 10;
IMAGE img[14];
int over;

//	add image to our project
void LoadImage()
{
	loadimage(&img[0], L"pic/0.jpg", 50, 50);
	loadimage(&img[1], L"pic/1.jpg", 50, 50);
	loadimage(&img[2], L"pic/2.jpg", 50, 50);
	loadimage(&img[3], L"pic/3.jpg", 50, 50);
	loadimage(&img[4], L"pic/4.jpg", 50, 50);
	loadimage(&img[5], L"pic/5.jpg", 50, 50);
	loadimage(&img[6], L"pic/6.jpg", 50, 50);
	loadimage(&img[7], L"pic/7.jpg", 50, 50);
	loadimage(&img[8], L"pic/8.jpg", 50, 50);
	loadimage(&img[9], L"pic/9.jpg", 50, 50);
	loadimage(&img[10], L"pic/19.jpg", 50, 50);
	loadimage(&img[11], L"pic/flag.jpg", 50, 50);
	loadimage(&img[12], L"pic/10.jpg", 50, 50);
	loadimage(&img[13], L"pic/-1.jpg", 50, 50);	
}

//	when we click the non-mine spot, we will check the around spot and show the spot with 0
void LoadingMap(int map[][Col+2], int x, int y)
{
	map[x][y] += 10;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (map[i][j] == 0)
			{
				LoadingMap(map, i, j);
			}
			if (map[i][j] > 0 && map[i][j] <= 8)
			{
				map[i][j] += 10;
			}
		}
	}
}

//	show the map of Minesweeper
void draw(int map[][Col + 2])
{
//	if the game is not over
	for (int i = 1; over == 0 && i <= Row; i++)
	{
		for (int j = 1; over == 0 && j <= Col; j++)
		{
			if (map[i][j] < 9)
			{
				// if the spot not change yet.
				putimage((j - 1) * 50, (i - 1) * 50, &img[12]);
			}
			else if (map[i][j] > 18)
			{
				// if the spot has been add a flag.
				putimage((j - 1) * 50, (i - 1) * 50, &img[11]);
			}
			else if (map[i][j] == 9)
			{
				// the mine has been click.
				putimage((j - 1) * 50, (i - 1) * 50, &img[9]);
			}
			else if (map[i][j] == 10)
			{
				// show 0.
				putimage((j - 1) * 50, (i - 1) * 50, &img[0]);
			}
			else if (map[i][j] == 11)
			{
				// show 1.
				putimage((j - 1) * 50, (i - 1) * 50, &img[1]);
			}
			else if (map[i][j] == 12)
			{
				// show 2.
				putimage((j - 1) * 50, (i - 1) * 50, &img[2]);
			}
			else if (map[i][j] == 13)
			{
				// show 3.
				putimage((j - 1) * 50, (i - 1) * 50, &img[3]);
			}
			else if (map[i][j] == 14)
			{
				// show 4.
				putimage((j - 1) * 50, (i - 1) * 50, &img[4]);
			}
			else if (map[i][j] == 15)
			{
				// show 5.
				putimage((j - 1) * 50, (i - 1) * 50, &img[5]);
			}
			else if (map[i][j] == 16)
			{
				// show 6.
				putimage((j - 1) * 50, (i - 1) * 50, &img[6]);
			}
			else if (map[i][j] == 17)
			{
				// show 7.
				putimage((j - 1) * 50, (i - 1) * 50, &img[7]);
			}
			else if (map[i][j] == 18)
			{
				// show 8.
				putimage((j - 1) * 50, (i - 1) * 50, &img[8]);
			}
		}
	}

//	if the game is over
	for (int i = 1; over == 1 && i <= Row; i++)
	{
		for (int j = 1; over == 1 && j <= Col; j++)
		{
			//show mines
			if (map[i][j] == -1)
			{
				putimage((j - 1) * 50, (i - 1) * 50, &img[13]);
			}
			//show the mines you click
			else if (map[i][j] == 19)
			{
				putimage((j - 1) * 50, (i - 1) * 50, &img[9]);
			}
			else if (map[i][j] > 19)
			{
				putimage((j - 1) * 50, (i - 1) * 50, &img[11]);
			}
		}
	}
}

//	check whether the game end or not
bool result(int map[][Col + 2])
{
	for (int i = 1; i <= Row; i++)
	{
		for (int j = 1; j <= Col; j++)
		{
			//	the 0-9 spot did not click yet or flag the wrong one 
			if ((map[i][j] >= 0 && map[i][j] <= 8) || map[i][j] > 19)
			{
				return false;
			}
		}
	}
	return true;
}

//	creat a new map of Minesweeper
void InitMap(int map[][Col + 2])
{
//	creat 10 different miness
	srand((unsigned)time(NULL));
	int x, y;
	for (int i = 0; i < Num;)
	{
		x = rand() % Row + 1;
		y = rand() % Col + 1;
		if (map[x][y] != -1)
		{
			map[x][y] = -1;
			i++;
		}
	}
//	add 1 to the 8 spots mine adjacented 
	for (int i = 1; i <= Row; i++)
	{
		for (int j = 1; j <= Col; j++)
		{
			if (map[i][j] == -1)
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if (map[m][n] != -1)
						{
							map[m][n]++;
						}
					}
				}
			}
		}
	}
}

//	when the mouse click to a spot, what will happen
void play(int map[][Col + 2])
{
	//	need mouse to control.
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		int y = msg.x / 50 + 1;
		int x = msg.y / 50 + 1;
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			//	click the mine and game over
			if (map[x][y] == -1)
			{
				over = 1;
			}
			//	click the 0-spot and begin check the around spot
			else if (map[x][y] == 0)
			{
				LoadingMap(map, x, y);
			}
			// click the 1-8 spot, show the spot. 
			else if (map[x][y] > 0 && map[x][y] <= 8)
			{
				map[x][y] += 10;
			}
			break;

		case WM_RBUTTONDOWN:
			//	add a flag
			if (map[x][y] < 9)
			{
				map[x][y] += 20;
			}
			//	delete a flag
			else if (map[x][y] > 18)
			{
				map[x][y] -= 20;
			}
			break;
		}//	end switch
		draw(map);
		if (over == 1 || result(map))
		{
			break;
		}
	}//	end while
}//	end play

int main()
{
	int map[Row + 2][Col + 2];
	LoadImage();
	while (1)
	{
		over = 0;

		// set the whole map = 0;
				//for (int i = 0; i <= Col+1; i++)
				//{
				//	for (int j = 0; j <= Row+1; j++)
				//	{
				//		std::cout << map[i][j] << "  " ;
				//	}
				//	std::cout << '\n';
				//}
				//std::cout << '\n';
		memset(map, 0, sizeof map);
		InitMap(map);
		initgraph(Row * 50, Col * 50);
		draw(map);
		play(map);
		HWND hWnd = GetHWnd();
		if (over == 1)
		{
			if (!MessageBox(hWnd, L"GameOver.", L"Try again.", MB_OKCANCEL))
			{
				break;
			}
		}
		else
		{
			if (MessageBox(hWnd, L"Congratulation.", L"Win.", MB_OKCANCEL))
			{
				break;
			}
		}
		cleardevice();
		closegraph();
	}
	return 0;
}