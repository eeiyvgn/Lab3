#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include "head.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    string name = "Example.rar";

    FileRead(name);

    return 0;
}
