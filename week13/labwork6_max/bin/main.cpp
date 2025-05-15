#include <iostream>
#include <fstream>
#include <sstream>
#include "lib/parser.h"
#include "lib/beauty.h"

using namespace omfl;

int main(int argc, char* argv[]) {
    std::string path = "../example/config.omfl";
    if (argc > 1) {
        path = argv[1];
    }

    std::ifstream file(path);
    if (!file) {
        std::cerr << "Cannot open file: " << path << std::endl;
        return 1;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();

    Config cfg = Parse(content);
    if (!cfg.IsValid()) {
        std::cerr << "Parse error." << std::endl;
        return 2;
    }

    try {
        std::cout << "Loaded successfully\n";

        // Вывод корневой секции
        beauty::PrintSection(cfg.root_, "root");

        // Получаем секцию [level1]
        if (!cfg.Has("level1")) {
            std::cerr << "No section [level1] in config file.\n";
            return 3;
        }

        const Section& level1 = cfg.Get("level1").AsSection();
        beauty::PrintSection(level1, "level1");

        // Получаем вложенную секцию [level1.level2]
        const Section& level2 = level1.Get("level2").AsSection();
        beauty::PrintSection(level2, "level1.level2");

        // Демонстрация попытки доступа напрямую к level1.level2
        try {
            const Section& shouldFail = cfg.Get("level1.level2").AsSection();
            std::cerr << "Error: Direct access to the nested section\n";
        } catch (const std::exception& e) {
            std::cout << "\n\nException caught: section [level1.level2] is only accessible through [level1]\n";
            std::cout << "Exception: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error during configuration processing: " << e.what() << std::endl;
        return 4;
    }

    return 0;
}
