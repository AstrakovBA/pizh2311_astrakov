#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <locale>
#include "lib/MP3Parser.h"

int main(int argc, char* argv[]) {
    // Установка локали для корректного вывода русских символов
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    // Проверка наличия аргумента командной строки
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mp3_file>\n";
        return 1;
    }
    const char* filename = argv[1];
    
    std::cout << "Processing file: " << filename << std::endl;

    // Открытие файла в бинарном режиме
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << "\n";
        return 1;
    }
    
    // Чтение заголовка ID3 тега (10 байт)
    char header[10];
    file.read(header, 10);
    
    // Проверка наличия ID3v2 тега
    if (file.gcount() != 10 || std::strncmp(header, "ID3", 3) != 0) {
        std::cerr << "No ID3v2 tag found." << std::endl;
        return 1;
    }
    
    // Парсинг версии тега и флагов
    unsigned char verMajor = header[3];
    unsigned char verMinor = header[4];
    unsigned char flags = header[5];
    
    // Получение размера тега
    std::array<unsigned char,4> sizeBytes = {
        static_cast<unsigned char>(header[6]),
        static_cast<unsigned char>(header[7]),
        static_cast<unsigned char>(header[8]),
        static_cast<unsigned char>(header[9])
    };
    uint32_t tagSize = readSynchSafeInteger(sizeBytes);
    std::cout << "ID3v2." << int(verMajor) << "." << int(verMinor) 
              << " tag, size=" << tagSize << "\n";

    // Чтение фреймов тега
    uint32_t bytesRead = 0;
    while (bytesRead + 10 <= tagSize) {
        // Чтение идентификатора фрейма
        char frameIdChars[4];
        file.read(frameIdChars, 4);
        
        // Проверка на конец тега
        if (file.gcount() != 4 || std::all_of(frameIdChars, frameIdChars + 4, [](char c) { return c == 0; })) {
            break;
        }
        std::string frameId(frameIdChars, 4);
        
        // Чтение размера фрейма
        std::array<unsigned char,4> frameSizeBytes;
        file.read(reinterpret_cast<char*>(frameSizeBytes.data()), 4);
        uint32_t frameSize = readSynchSafeInteger(frameSizeBytes);
        
        // Чтение флагов фрейма
        uint16_t frameFlags;
        file.read(reinterpret_cast<char*>(&frameFlags), 2);

        // Проверка на конец файла или нулевой размер
        if (frameSize == 0 || file.eof()) {
            break;
        }

        // Чтение данных фрейма
        std::vector<unsigned char> frameData(frameSize);
        file.read(reinterpret_cast<char*>(frameData.data()), frameSize);
        if (file.gcount() != static_cast<std::streamsize>(frameSize)) break;

        // Обновление счетчика прочитанных байт
        bytesRead += 10 + frameSize;
        
        // Создание и вывод информации о фрейме
        auto frame = createFrame(frameId, frameSize, frameFlags, frameData);
        frame->print();
        std::cout << std::endl;
    }

    return 0;
}
