#include "ArgParser.h"

namespace ArgumentParser {

    /**
     * @brief Конструктор парсера аргументов
     * @param name Название программы (будет использоваться в справке)
     */
    ArgParser::ArgParser(const std::string& name) : name_(name) {}

    // Секция методов для добавления строковых аргументов

    /**
     * @brief Добавляет строковый аргумент с длинным именем
     * @param long_name Длинное имя аргумента (например, "--input")
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddStringArgument(const std::string& long_name) {
        Argument arg;
        arg.long_name = long_name;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief Добавляет строковый аргумент с коротким и длинным именем
     * @param short_name Короткое имя аргумента (например, "-i")
     * @param long_name Длинное имя аргумента
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddStringArgument(char short_name, const std::string& long_name) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief Добавляет строковый аргумент с описанием
     * @param long_name Длинное имя аргумента
     * @param description Описание аргумента для справки
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddStringArgument(const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.long_name = long_name;
        arg.description = description;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief Добавляет строковый аргумент с коротким именем и описанием
     * @param short_name Короткое имя аргумента
     * @param long_name Длинное имя аргумента
     * @param description Описание аргумента для справки
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddStringArgument(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    // Секция методов для добавления целочисленных аргументов

    /**
     * @brief Добавляет целочисленный аргумент
     * @param long_name Длинное имя аргумента
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddIntArgument(const std::string& long_name) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_int = true;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief Добавляет целочисленный аргумент с коротким именем
     * @param short_name Короткое имя аргумента
     * @param long_name Длинное имя аргумента
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddIntArgument(char short_name, const std::string& long_name) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_int = true;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief Добавляет целочисленный аргумент с описанием
     * @param long_name Длинное имя аргумента
     * @param description Описание аргумента для справки
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddIntArgument(const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_int = true;
        arg.description = description;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief Добавляет целочисленный аргумент с коротким именем и описанием
     * @param short_name Короткое имя аргумента
     * @param long_name Длинное имя аргумента
     * @param description Описание аргумента для справки
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddIntArgument(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_int = true;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    // Секция методов для добавления флагов

    /**
     * @brief Добавляет флаг (булевый аргумент)
     * @param long_name Длинное имя флага
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddFlag(const std::string& long_name) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_flag = true;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief Добавляет флаг с коротким именем
     * @param short_name Короткое имя флага
     * @param long_name Длинное имя флага
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddFlag(char short_name, const std::string& long_name) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_flag = true;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief Добавляет флаг с описанием
     * @param long_name Длинное имя флага
     * @param description Описание флага для справки
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddFlag(const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_flag = true;
        arg.description = description;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief Добавляет флаг с коротким именем и описанием
     * @param short_name Короткое имя флага
     * @param long_name Длинное имя флага
     * @param description Описание флага для справки
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddFlag(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_flag = true;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    // Секция методов для настройки аргументов

    /**
     * @brief Устанавливает описание программы для справки
     * @param description Текст описания
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::Help(const std::string& description) {
        help_description_ = description;
        return *this;
    }

    /**
     * @brief Добавляет аргумент вывода справки
     * @param short_name Короткое имя аргумента справки
     * @param long_name Длинное имя аргумента справки
     * @param description Описание справки
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::AddHelp(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_flag = true;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief Устанавливает строковое значение по умолчанию
     * @param value Значение по умолчанию
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::Default(const char* value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.default_value = value;
        }
        return *this;
    }

    /**
     * @brief Устанавливает булево значение по умолчанию
     * @param value Значение по умолчанию
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::Default(bool value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.default_bool_value = value;
        }
        return *this;
    }

    /**
     * @brief Помечает аргумент как позиционный
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::Positional() {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.is_positional = true;
            positional_args_names_.push_back(arguments_.rbegin()->second.long_name);
        }
        return *this;
    }

    /**
     * @brief Разрешает аргументу принимать несколько значений
     * @param min_args_count Минимальное количество значений (по умолчанию 0)
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::MultiValue(size_t min_args_count) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.is_multi_value = true;
            arguments_.rbegin()->second.min_args_count = min_args_count;
        }
        return *this;
    }

    // Секция методов для сохранения значений

    /**
     * @brief Сохраняет значение аргумента в строковую переменную
     * @param value Ссылка на переменную для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::StoreValue(std::string& value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.string_store = &value;
        }
        return *this;
    }

    /**
     * @brief Сохраняет значение аргумента в целочисленную переменную
     * @param value Ссылка на переменную для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::StoreValue(int& value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.int_store = &value;
        }
        return *this;
    }

    /**
     * @brief Сохраняет значение флага в булеву переменную
     * @param value Ссылка на переменную для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::StoreValue(bool& value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.bool_store = &value;
        }
        return *this;
    }

    /**
     * @brief Сохраняет несколько значений аргумента в вектор
     * @param values Ссылка на вектор для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser& ArgParser::StoreValues(std::vector<int>& values) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.int_vector_store = &values;
        }
        return *this;
    }

    // Секция методов парсинга

    /**
     * @brief Парсит аргументы командной строки
     * @param argc Количество аргументов
     * @param argv Массив аргументов
     * @return true, если парсинг успешен, false в противном случае
     */
    bool ArgParser::Parse(int argc, char** argv) {
        std::vector<std::string> args;
        for (int i = 1; i < argc; ++i) {
            args.push_back(argv[i]);
        }
        return Parse(args);
    }

    /**
     * @brief Парсит аргументы из вектора строк
     * @param args Вектор строк с аргументами
     * @return true, если парсинг успешен, false в противном случае
     */
    bool ArgParser::Parse(const std::vector<std::string>& args) {
        size_t current_arg = 0;

        // Обработка именованных аргументов и флагов
        while (current_arg < args.size()) {
            const std::string& arg = args[current_arg];

            // Проверка на запрос справки
            if (arg == "--help" || arg == "-h") {
                help_requested_ = true;
                return true;
            }

            // Пропускаем позиционные аргументы - они обрабатываются отдельно
            if (arg[0] != '-') {
                current_arg++;
                continue;
            }

            ParseArgument(arg, current_arg, args);
            current_arg++;
        }

        // Обработка позиционных аргументов
        ParsePositionalArguments(args);

        // Проверка валидности аргументов
        if (!ValidateArguments()) {
            return false;
        }

        // Сохранение значений в переданные ссылки
        StoreValuesToReferences();

        return true;
    }

    // Секция методов получения значений

    /**
     * @brief Получает строковое значение аргумента
     * @param name Имя аргумента
     * @return Значение аргумента
     */
    std::string ArgParser::GetStringValue(const std::string& name) const {
        const Argument& arg = GetArgument(name);
        if (!arg.string_values.empty()) {
            return arg.string_values[0];
        }
        if (arg.default_value.has_value()) {
            return arg.default_value.value();
        }
        return "";
    }

    /**
     * @brief Получает целочисленное значение аргумента
     * @param name Имя аргумента
     * @return Значение аргумента
     */
    int ArgParser::GetIntValue(const std::string& name) const {
        const Argument& arg = GetArgument(name);
        if (!arg.int_values.empty()) {
            return arg.int_values[0];
        }
        return 0;
    }

    /**
     * @brief Получает целочисленное значение по индексу
     * @param name Имя аргумента
     * @param index Индекс значения
     * @return Значение аргумента
     */
    int ArgParser::GetIntValue(const std::string& name, size_t index) const {
        const Argument& arg = GetArgument(name);
        if (index < arg.int_values.size()) {
            return arg.int_values[index];
        }
        return 0;
    }

    /**
     * @brief Проверяет, был ли установлен флаг
     * @param name Имя флага
     * @return true, если флаг установлен, false в противном случае
     */
    bool ArgParser::GetFlag(const std::string& name) const {
        const Argument& arg = GetArgument(name);
        return !arg.string_values.empty() || arg.default_bool_value.value_or(false);
    }

    /**
     * @brief Проверяет, был ли запрошен вывод справки
     * @return true, если запрошена справка, false в противном случае
     */
    bool ArgParser::Help() const {
        return help_requested_;
    }

    /**
     * @brief Генерирует строку с описанием справки
     * @return Форматированная строка справки
     */
    std::string ArgParser::HelpDescription() const {
        std::string result = name_ + "\n";
        if (!help_description_.empty()) {
            result += help_description_ + "\n";
        }
        result += "\n";

        // Формируем список аргументов
        for (const auto& [name, arg] : arguments_) {
            if (arg.is_positional) continue; // Позиционные аргументы обрабатываются отдельно

            // Форматируем строку с именами аргумента
            std::string names;
            if (arg.short_name.has_value()) {
                names += "-" + std::string(1, arg.short_name.value()) + ",  ";
            }
            else {
                names += "     ";
            }
            names += "--" + arg.long_name;

            // Добавляем тип значения для не-флагов
            if (!arg.is_flag) {
                names += arg.is_int ? "=<int>" : "=<string>";
            }

            // Собираем полную строку описания
            std::string line = names + ",  " + arg.description;

            // Добавляем дополнительные свойства
            if (arg.is_multi_value) {
                line += " [repeated, min args = " + std::to_string(arg.min_args_count) + "]";
            }
            if (arg.default_value.has_value()) {
                line += " [default = " + arg.default_value.value() + "]";
            }
            else if (arg.default_bool_value.has_value()) {
                line += " [default = " + std::string(arg.default_bool_value.value() ? "true" : "false") + "]";
            }

            result += line + "\n";
        }

        // Добавляем информацию о позиционных аргументах
        for (const auto& name : positional_args_names_) {
            const Argument& arg = arguments_.at(name);
            std::string line = "[" + arg.long_name + "]";
            if (arg.is_multi_value) {
                line += "...";
            }
            line += ",  " + arg.description;
            result += line + "\n";
        }

        result += "\n";
        result += "-h, --help Display this help and exit\n";

        return result;
    }

    // Внутренние методы

    /**
     * @brief Обрабатывает отдельный аргумент командной строки
     * @param arg Текущий аргумент для обработки
     * @param current_arg Индекс текущего аргумента
     * @param args Все аргументы командной строки
     */
    void ArgParser::ParseArgument(const std::string& arg, size_t& current_arg, const std::vector<std::string>& args) {
        size_t equal_pos = arg.find('=');
        std::string name_part = arg.substr(0, equal_pos);
        std::string value_part = equal_pos != std::string::npos ? arg.substr(equal_pos + 1) : "";

        // Определяем длинное имя аргумента
        std::string long_name;
        if (name_part[1] == '-') {
            // Длинное имя (--name)
            long_name = name_part.substr(2);
        }
        else {
            // Короткое имя (-n)
            char short_name = name_part[1];
            long_name = short_to_long_.at(short_name);
        }

        Argument& argument = GetArgument(long_name);

        if (argument.is_flag) {
            // Обработка флага
            argument.string_values.push_back("true");
        }
        else {
            // Обработка аргумента со значением
            if (equal_pos != std::string::npos) {
                // Значение указано через =
                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(value_part));
                }
                else {
                    argument.string_values.push_back(value_part);
                }
            }
            else if (current_arg + 1 < args.size() && args[current_arg + 1][0] != '-') {
                // Значение указано следующим аргументом
                current_arg++;
                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(args[current_arg]));
                }
                else {
                    argument.string_values.push_back(args[current_arg]);
                }
            }
            else if (argument.default_value.has_value()) {
                // Используем значение по умолчанию
                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(argument.default_value.value()));
                }
                else {
                    argument.string_values.push_back(argument.default_value.value());
                }
            }
            else if (argument.default_bool_value.has_value()) {
                // Для флагов с дефолтным значением
                argument.string_values.push_back(argument.default_bool_value.value() ? "true" : "false");
            }
        }
    }

    /**
     * @brief Обрабатывает позиционные аргументы
     * @param args Все аргументы командной строки
     */
    void ArgParser::ParsePositionalArguments(const std::vector<std::string>& args) {
        size_t positional_index = 0;

        for (const auto& arg : args) {
            if (arg[0] == '-') continue; // Пропускаем именованные аргументы

            if (positional_index < positional_args_names_.size()) {
                std::string long_name = positional_args_names_[positional_index];
                Argument& argument = arguments_[long_name];

                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(arg));
                }
                else {
                    argument.string_values.push_back(arg);
                }

                // Для не multi-value аргументов переходим к следующему позиционному
                if (!argument.is_multi_value) {
                    positional_index++;
                }
            }
        }
    }

    /**
     * @brief Сохраняет значения в связанные переменные
     */
    void ArgParser::StoreValuesToReferences() {
        for (auto& [name, arg] : arguments_) {
            if (arg.bool_store != nullptr) {
                *arg.bool_store = !arg.string_values.empty();
            }
            if (arg.string_store != nullptr && !arg.string_values.empty()) {
                *arg.string_store = arg.string_values[0];
            }
            if (arg.int_store != nullptr && !arg.int_values.empty()) {
                *arg.int_store = arg.int_values[0];
            }
            if (arg.int_vector_store != nullptr) {
                *arg.int_vector_store = arg.int_values;
            }
        }
    }

    /**
     * @brief Проверяет валидность аргументов
     * @return true, если все аргументы валидны, false в противном случае
     */
    bool ArgParser::ValidateArguments() const {
        for (const auto& [name, arg] : arguments_) {
            // Проверка обязательных аргументов
            if (!arg.default_value.has_value() && !arg.default_bool_value.has_value() &&
                arg.string_values.empty() && arg.int_values.empty() && !arg.is_flag) {
                return false;
            }

            // Проверка минимального количества значений для multi-value
            if (arg.is_multi_value && arg.int_values.size() < arg.min_args_count) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Получает аргумент по имени (неконстантная версия)
     * @param name Имя аргумента
     * @return Ссылка на аргумент
     */
    ArgParser::Argument& ArgParser::GetArgument(const std::string& name) {
        return arguments_.at(name);
    }

    /**
     * @brief Получает аргумент по имени (константная версия)
     * @param name Имя аргумента
     * @return Константная ссылка на аргумент
     */
    const ArgParser::Argument& ArgParser::GetArgument(const std::string& name) const {
        return arguments_.at(name);
    }

    /**
     * @brief Получает аргумент по короткому имени
     * @param short_name Короткое имя аргумента
     * @return Ссылка на аргумент
     */
    ArgParser::Argument& ArgParser::GetArgumentByShortName(char short_name) {
        return arguments_.at(short_to_long_.at(short_name));
    }

} // namespace ArgumentParser
