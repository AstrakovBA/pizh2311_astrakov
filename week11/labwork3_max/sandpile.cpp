/**
 * @file sandpile.cpp
 * @brief Реализация модели песчаной кучи с сохранением состояний в BMP
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <unordered_map>

 // Для filesystem требуется C++17
#if __cplusplus >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

// Цвета для разных количеств песчинок
struct Color {
    uint8_t r, g, b;
};

const std::unordered_map<uint64_t, Color> COLOR_MAP = {
    {0, {255, 255, 255}}, // Белый
    {1, {0, 255, 0}},      // Зеленый
    {2, {128, 0, 128}},    // Фиолетовый
    {3, {255, 255, 0}},    // Желтый
    // Для >3 используется черный (определяется в функции get_color)
};

/**
 * @brief Получает цвет пикселя на основе количества песчинок
 * @param grains Количество песчинок в ячейке
 * @return Структура Color с компонентами RGB
 */
static Color get_color(uint64_t grains) {
    auto it = COLOR_MAP.find(grains);
    if (it != COLOR_MAP.end()) {
        return it->second;
    }
    return { 0, 0, 0 }; // Черный для >3
}

/**
 * @brief Представляет модель песчаной кучи
 */
class SandpileModel {
private:
    std::vector<std::vector<uint64_t>> grid;
    uint16_t width;
    uint16_t length;
    bool stable;

public:
    /**
     * @brief Конструктор модели
     * @param w Ширина сетки
     * @param l Длина сетки
     */
    SandpileModel(uint16_t w, uint16_t l) : width(w), length(l), stable(false) {
        grid.resize(length, std::vector<uint64_t>(width, 0));
    }

    /**
     * @brief Загружает начальное состояние из TSV файла
     * @param filename Путь к TSV файлу
     */
    void load_initial_state(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open input file: " + filename);
        }

        uint16_t x, y;
        uint64_t grains;
        while (file >> x >> y >> grains) {
            if (x < width && y < length) {
                grid[y][x] = grains;
            }
        }
    }

    /**
     * @brief Проверяет, стабильна ли модель
     * @return true, если модель стабильна, иначе false
     */
    bool is_stable() const {
        return stable;
    }

    /**
     * @brief Выполняет одну итерацию модели
     */
    void iterate() {
        stable = true;
        std::vector<std::vector<uint64_t>> new_grid = grid;

        for (uint16_t y = 0; y < length; ++y) {
            for (uint16_t x = 0; x < width; ++x) {
                if (grid[y][x] > 3) {
                    stable = false;
                    new_grid[y][x] -= 4;
                    // Распределяем песчинки соседям
                    if (x > 0) new_grid[y][x - 1] += 1;
                    if (x < width - 1) new_grid[y][x + 1] += 1;
                    if (y > 0) new_grid[y - 1][x] += 1;
                    if (y < length - 1) new_grid[y + 1][x] += 1;
                }
            }
        }

        grid = std::move(new_grid);
    }

    /**
     * @brief Сохраняет текущее состояние в BMP файл
     * @param filename Путь к выходному файлу
     */
    void save_to_bmp(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open output file: " + filename);
        }

        // Размер файла: заголовок (54 байта) + данные (3 * width * length)
        uint32_t file_size = 54 + 3 * static_cast<uint32_t>(width) * length;
        uint32_t data_offset = 54;
        uint32_t header_size = 40;
        uint16_t planes = 1;
        uint16_t bits_per_pixel = 24;
        uint32_t compression = 0;
        uint32_t image_size = 3 * static_cast<uint32_t>(width) * length;
        int32_t x_pixels_per_meter = 2835; // 72 dpi
        int32_t y_pixels_per_meter = 2835; // 72 dpi
        uint32_t colors_used = 0;
        uint32_t important_colors = 0;

        // Заголовок BMP файла
        file.write("BM", 2); // Сигнатура
        file.write(reinterpret_cast<const char*>(&file_size), 4);
        file.write("\0\0\0\0", 4); // Зарезервировано
        file.write(reinterpret_cast<const char*>(&data_offset), 4);
        file.write(reinterpret_cast<const char*>(&header_size), 4);
        file.write(reinterpret_cast<const char*>(&width), 4);
        file.write(reinterpret_cast<const char*>(&length), 4);
        file.write(reinterpret_cast<const char*>(&planes), 2);
        file.write(reinterpret_cast<const char*>(&bits_per_pixel), 2);
        file.write(reinterpret_cast<const char*>(&compression), 4);
        file.write(reinterpret_cast<const char*>(&image_size), 4);
        file.write(reinterpret_cast<const char*>(&x_pixels_per_meter), 4);
        file.write(reinterpret_cast<const char*>(&y_pixels_per_meter), 4);
        file.write(reinterpret_cast<const char*>(&colors_used), 4);
        file.write(reinterpret_cast<const char*>(&important_colors), 4);

        // Данные изображения (пиксели)
        // BMP хранит строки снизу вверх и выравнивает по 4 байта
        uint32_t row_padding = (4 - (width * 3) % 4) % 4;
        uint8_t padding[3] = { 0, 0, 0 };

        for (int y = static_cast<int>(length) - 1; y >= 0; --y) {
            for (uint16_t x = 0; x < width; ++x) {
                Color color = get_color(grid[y][x]);
                file.write(reinterpret_cast<const char*>(&color.b), 1); // BMP порядок: BGR
                file.write(reinterpret_cast<const char*>(&color.g), 1);
                file.write(reinterpret_cast<const char*>(&color.r), 1);
            }
            if (row_padding > 0) {
                file.write(reinterpret_cast<const char*>(padding), row_padding);
            }
        }
    }
};

/**
 * @brief Обрабатывает аргументы командной строки
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @param width Возвращаемая ширина сетки
 * @param length Возвращаемая длина сетки
 * @param input_file Возвращаемый путь к входному файлу
 * @param output_dir Возвращаемый путь к выходной директории
 * @param max_iter Возвращаемое максимальное число итераций
 * @param freq Возвращаемая частота сохранения
 */
static void parse_arguments(int argc, char* argv[],
    uint16_t& width, uint16_t& length,
    std::string& input_file, std::string& output_dir,
    uint32_t& max_iter, uint32_t& freq) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-l" || arg == "--length") {
            if (i + 1 < argc) length = static_cast<uint16_t>(std::stoi(argv[++i]));
        }
        else if (arg == "-w" || arg == "--width") {
            if (i + 1 < argc) width = static_cast<uint16_t>(std::stoi(argv[++i]));
        }
        else if (arg == "-i" || arg == "--input") {
            if (i + 1 < argc) input_file = argv[++i];
        }
        else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) output_dir = argv[++i];
        }
        else if (arg == "-m" || arg == "--max-iter") {
            if (i + 1 < argc) max_iter = static_cast<uint32_t>(std::stoi(argv[++i]));
        }
        else if (arg == "-f" || arg == "--freq") {
            if (i + 1 < argc) freq = static_cast<uint32_t>(std::stoi(argv[++i]));
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        // Параметры по умолчанию
        uint16_t width = 10;
        uint16_t length = 10;
        std::string input_file = "input.tsv";
        std::string output_dir = "output";
        uint32_t max_iter = 100;
        uint32_t freq = 1;

        // Разбор аргументов командной строки
        parse_arguments(argc, argv, width, length, input_file, output_dir, max_iter, freq);

        // Создаем выходную директорию, если ее нет
        if (!fs::exists(output_dir)) {
            fs::create_directory(output_dir);
        }

        // Инициализация модели
        SandpileModel model(width, length);
        model.load_initial_state(input_file);

        // Основной цикл модели
        for (uint32_t iter = 0; iter < max_iter; ++iter) {
            // Сохраняем состояние, если нужно
            if (freq > 0 && (iter % freq == 0 || iter == max_iter - 1 || model.is_stable())) {
                std::string filename = output_dir + "/state_" + std::to_string(iter) + ".bmp";
                model.save_to_bmp(filename);
            }

            // Проверяем стабильность
            if (model.is_stable()) {
                std::cout << "Model stabilized after " << iter << " iterations." << std::endl;
                break;
            }

            // Выполняем итерацию
            model.iterate();
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
