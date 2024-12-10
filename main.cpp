#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include "head.h"

using namespace std;

#pragma pack(push, 1)

struct VolumeHeaderFromat
{
    uint16_t header_crc;
    uint8_t header_type;
    uint16_t header_flags;
    uint16_t header_size;

};

struct FileHead
{
    uint32_t PackSize;
    uint32_t UnpSize;
    uint8_t HostOS;
    uint32_t FileCRC;
    uint32_t FileTime;
    uint8_t UnpVer;
    uint8_t Method;
    uint16_t NameSize;
    uint32_t FileAttr;
};

#pragma pack(pop)


int main()
{
    setlocale(LC_ALL, "Russian");

    string name = "Example.rar";

    FileRead(name);

    return 0;
}
