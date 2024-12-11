#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include "head.h"

using namespace std;

#pragma pack(push, 1)

struct VolumeHeaderFormat
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

void FileRead(const string& filename)
{
    ifstream rar_file(filename, ios::binary);

    if (rar_file.is_open())
    {
        cout << "Файл был открыт." << endl;
    }

    rar_file.seekg(0, ios::end);
    int fileSize = rar_file.tellg();
    rar_file.seekg(0, ios::beg);

    vector<uint8_t> rar_data(fileSize, 0);

    rar_file.read(reinterpret_cast<char*>(rar_data.data()), fileSize);

    rar_file.close();

    cout << "Оглавления архива:" << endl;

    size_t offset = 7;

    int count = 1;

    while (offset < rar_data.size())
    {
        const VolumeHeaderFormat* volume_header = reinterpret_cast<const VolumeHeaderFormat*>(&rar_data[offset]);

        if (volume_header->header_type == 0x74)
        {

            if (offset + sizeof(FileHead) + sizeof(VolumeHeaderFormat) > rar_data.size())
            {
                break;
            }

            const FileHead* file_head = reinterpret_cast<const FileHead*>(&rar_data[offset + sizeof(VolumeHeaderFormat)]);

            size_t offset_n = offset + sizeof(VolumeHeaderFormat) + sizeof(FileHead);

            if (offset_n + file_head->NameSize > rar_data.size())
            {
                break;
            }

            string file_name(reinterpret_cast<const char*>(&rar_data[offset_n]), file_head->NameSize);

            cout << count << ". " << file_name << endl;

            count ++;

            offset += volume_header->header_size + file_head->PackSize;
        }

        else
        {
            offset += volume_header->header_size;
        }
    }
}
