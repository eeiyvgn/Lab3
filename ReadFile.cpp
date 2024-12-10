#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include "head.h"

using namespace std;

void FileRead(const string& filename)
{
    ifstream rar_file(filename, ios::binary);

    if (rar_file.is_open())
    {
        cout << "File has been opened" << endl;
    }

    rar_file.seekg(0, ios::end);
    int fileSize = rar_file.tellg();
    rar_file.seekg(0, ios::beg);

    vector<uint8_t> rar_data(fileSize, 0);

    rar_file.read(reinterpret_cast<char*>(rar_data.data()), fileSize);

    rar_file.close();
}
