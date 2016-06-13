#pragma once
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;
class CSaveBoard
{
public:
	CSaveBoard(void);
	~CSaveBoard(void);
public:
	static bool SaveBoard();
	static ofstream output_file;
};

