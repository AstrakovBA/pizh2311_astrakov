/**
 * Программирование на языке высокого уровня (C++).
 * Задание №1_max.
 *
 * Выполнил: Астраков Б. А.
 * Группа: ПИЖ-б-о-23-1
 * E-mail: bororo8918@gmail.com 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

/**
 * @class FileStats
 * @brief Класс для хранения статистики по файлу
 * 
 * Содержит информацию о количестве строк, слов, байт и символов в файле,
 * а также имя файла.
 */
class FileStats {
public:
    std::string filename;  ///< Имя файла
    size_t lines = 0;      ///< Количество строк
    size_t words = 0;      ///< Количество слов
    size_t bytes = 0;      ///< Количество байт
    size_t chars = 0;      ///< Количество символов (с учетом UTF-8)

    /**
     * @brief Конструктор с именем файла
     * @param filename Имя файла для анализа
     */
    explicit FileStats(const std::string& filename) : filename(filename) {}
};

/**
 * @class WordCounter
 * @brief Класс для подсчета статистики файла
 * 
 * Обеспечивает функциональность для подсчета строк, слов, байт и символов
 * в указанном файле.
 */
class WordCounter {
public:
    /**
     * @brief Подсчитывает статистику для указанного файла
     * @param filename Имя файла для анализа
     * @return Объект FileStats с результатами подсчета
     */
    static FileStats count(const std::string& filename) {
        FileStats stats(filename);
        std::ifstream file(filename, std::ios::binary);
        
        if (!file) {
            std::cerr << "Ошибка: Не удалось открыть файл " << filename << std::endl;
            return stats;
        }
        
        char ch;
        bool inWord = false;
        
        while (file.get(ch)) {
            stats.bytes++;
            
            // Подсчет UTF-8 символов: считаем байты продолжения частью символа)
            if ((ch & 0xC0) != 0x80) {
                stats.chars++;
            }
            
            if (ch == '\n') {
                stats.lines++;
            }
            
            if (std::isspace(static_cast<unsigned char>(ch))) {
                if (inWord) {
                    stats.words++;
                    inWord = false;
                }
            } else {
                inWord = true;
            }
        }
        
        // Учитываем последнее слово, если файл не заканчивается пробелом
        if (inWord) {
            stats.words++;
        }
        
        return stats;
    }
};

/**
 * @class ResultPrinter
 * @brief Класс для вывода результатов подсчета
 * 
 * Обеспечивает форматированный вывод статистики в соответствии
 * с выбранными опциями.
 */
class ResultPrinter {
public:
    bool showLines;  ///< Флаг показа количества строк
    bool showWords;  ///< Флаг показа количества слов
    bool showBytes;  ///< Флаг показа количества байт
    bool showChars;  ///< Флаг показа количества символов
    bool defaultMode; ///< Флаг режима по умолчанию (вывод всех основных параметров)

    /**
     * @brief Конструктор с настройками вывода
     * @param lines Показывать строки
     * @param words Показывать слова
     * @param bytes Показывать байты
     * @param chars Показывать символы
     */
    ResultPrinter(bool lines, bool words, bool bytes, bool chars)
        : showLines(lines), showWords(words), showBytes(bytes), showChars(chars),
          defaultMode(!lines && !words && !bytes && !chars) {}
    
    /**
     * @brief Выводит статистику для одного файла
     * @param stats Статистика файла для вывода
     */
    void print(const FileStats& stats) const {
        if (defaultMode) {
            std::cout << stats.lines << " " << stats.words << " " 
                      << stats.bytes << " " << stats.filename << std::endl;
            return;
        }
        
        bool first = true;
        
        if (showLines) {
            std::cout << stats.lines;
            first = false;
        }
        
        if (showWords) {
            if (!first) std::cout << " ";
            std::cout << stats.words;
            first = false;
        }
        
        if (showBytes) {
            if (!first) std::cout << " ";
            std::cout << stats.bytes;
            first = false;
        }
        
        if (showChars) {
            if (!first) std::cout << " ";
            std::cout << stats.chars;
            first = false;
        }
        
        if (!first) {
            std::cout << " " << stats.filename;
        }
        
        std::cout << std::endl;
    }
};

/**
 * @class ArgumentParser
 * @brief Класс для разбора аргументов командной строки
 * 
 * Обрабатывает аргументы командной строки, извлекает опции
 * и имена файлов для обработки.
 */
class ArgumentParser {
public:
    std::vector<std::string> filenames;  ///< Список имен файлов для обработки
    bool showLines = false;  ///< Флаг опции -l/--lines
    bool showWords = false;  ///< Флаг опции -w/--words
    bool showBytes = false;  ///< Флаг опции -c/--bytes
    bool showChars = false;  ///< Флаг опции -m/--chars

    /**
     * @brief Разбирает аргументы командной строки
     * @param argc Количество аргументов
     * @param argv Массив аргументов
     * @return true, если разбор прошел успешно, false при ошибке
     */
    bool parse(int argc, char* argv[]) {
        if (argc < 2) {
            printUsage();
            return false;
        }
        
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            
            if (arg == "-l" || arg == "--lines") {
                showLines = true;
            } else if (arg == "-w" || arg == "--words") {
                showWords = true;
            } else if (arg == "-c" || arg == "--bytes") {
                showBytes = true;
            } else if (arg == "-m" || arg == "--chars") {
                showChars = true;
            } else if (arg.size() > 1 && arg[0] == '-' && arg[1] != '-') {
                // Обработка комбинированных коротких опций (например -lwc)
                for (size_t j = 1; j < arg.size(); ++j) {
                    switch (arg[j]) {
                        case 'l': showLines = true; break;
                        case 'w': showWords = true; break;
                        case 'c': showBytes = true; break;
                        case 'm': showChars = true; break;
                        default:
                            std::cerr << "Ошибка: Неизвестная опция '" << arg[j] << "'" << std::endl;
                            return false;
                    }
                }
            } else if (arg[0] == '-') {
                std::cerr << "Ошибка: Неизвестная опция '" << arg << "'" << std::endl;
                return false;
            } else {
                filenames.push_back(arg);
            }
        }
        
        if (filenames.empty()) {
            std::cerr << "Ошибка: Не указано имя файла" << std::endl;
            return false;
        }
        
        return true;
    }

private:
    /**
     * @brief Выводит справочную информацию об использовании программы
     */
    void printUsage() const {
        std::cout << "Labwork1\n"
                  << "Использование: WordCount.exe [OPTION] filename [filename...]\n"
                  << "Опции:\n"
                  << "  -l, --lines  вывод только количества строк\n"
                  << "  -c, --bytes  вывод размера файла в байтах\n"
                  << "  -w, --words  вывод количества слов\n"
                  << "  -m, --chars  вывод количества символов\n";
    }
};

/**
 * @brief Точка входа в программу
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения программы (0 - успех, 1 - ошибка)
 */
int main(int argc, char* argv[]) {
    // Разбор аргументов командной строки
    ArgumentParser parser;
    if (!parser.parse(argc, argv)) {
        return 1;
    }
    
    // Создание принтера результатов с нужными настройками
    ResultPrinter printer(parser.showLines, parser.showWords, 
                         parser.showBytes, parser.showChars);
    
    // Обработка каждого файла
    for (const auto& filename : parser.filenames) {
        FileStats stats = WordCounter::count(filename);
        printer.print(stats);
    }
    
    return 0;
}