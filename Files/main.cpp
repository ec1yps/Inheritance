#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_TO_FILE

void main()
{
	setlocale(LC_ALL, "");
	cout << "HelloFiles" << endl;

#ifdef WRITE_TO_FILE
	std::ofstream fout;
	fout.open("File.txt", std::ios_base::app);	//std::ios_base::app (append) - дописывать в конец файла.
	fout << "Hello Files" << endl;
	fout << "Привет" << endl;
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE

#ifdef READ_TO_FILE
	std::ifstream fin("File.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			const int SIZE = 1024000;
			char buffer[SIZE]{};
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}

		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
#endif // READ_TO_FILE
}