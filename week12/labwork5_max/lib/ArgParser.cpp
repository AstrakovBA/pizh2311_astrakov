#include "ArgParser.h"
#include <sstream>

namespace ArgumentParser {

    /**
     * @brief Конструктор парсера аргументов
     * @param programName Название программы для вывода в справке
     */
    ArgParser::ArgParser(const std::string& programName)
        : programName_(programName) {
    }

    /**
     * @brief Создает новую опцию в парсере
     * @param type Тип опции (строка, число, флаг и т.д.)
     * @param shortName Короткое имя опции (одиночный символ)
     * @param longName Длинное имя опции
     * @param description Описание опции для справки
     * @return Ссылка на созданную опцию
     */
    ArgParser::Option& ArgParser::CreateOption(ArgType type, char shortName, const std::string& longName, const std::string& description) {
        options_.push_back({});
        Option& opt = options_.back();
        opt.type = type;
        opt.longName = longName;
        opt.shortName = shortName;
        opt.description = description;
        if (type == ArgType::Flag || type == ArgType::Help) {
            opt.valueBool = false;
        }
        size_t idx = options_.size() - 1;
        if (!longName.empty()) longNameMap_[longName] = idx;
        if (shortName) shortNameMap_[shortName] = idx;
        return opt;
    }

    // Реализации методов ArgBuilder

    /**
     * @brief Конструктор построителя аргументов
     * @param parser Ссылка на парсер аргументов
     * @param index Индекс опции в списке
     */
    ArgParser::ArgBuilder::ArgBuilder(ArgParser& parser, size_t index)
        : parser_(parser), index_(index) {
    }

    /**
     * @brief Устанавливает строковое значение по умолчанию
     * @param defaultValue Значение по умолчанию
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::Default(const std::string& defaultValue) {
        auto& opt = parser_.options_[index_];
        opt.hasDefault = true;
        opt.defaultString = defaultValue;
        return *this;
    }

    /**
     * @brief Устанавливает целочисленное значение по умолчанию
     * @param defaultValue Значение по умолчанию
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::Default(int defaultValue) {
        auto& opt = parser_.options_[index_];
        opt.hasDefault = true;
        opt.defaultInt = defaultValue;
        return *this;
    }

    /**
     * @brief Устанавливает булево значение по умолчанию
     * @param defaultValue Значение по умолчанию
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::Default(bool defaultValue) {
        auto& opt = parser_.options_[index_];
        opt.hasDefault = true;
        opt.defaultBool = defaultValue;
        return *this;
    }

    /**
     * @brief Указывает переменную для сохранения строкового значения
     * @param out Ссылка на переменную для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::StoreValue(std::string& out) {
        parser_.options_[index_].storeString = &out;
        return *this;
    }

    /**
     * @brief Указывает вектор для сохранения нескольких строковых значений
     * @param out Ссылка на вектор для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::StoreValues(std::vector<std::string>& out) {
        parser_.options_[index_].storeStrings = &out;
        return *this;
    }

    /**
     * @brief Указывает переменную для сохранения целочисленного значения
     * @param out Ссылка на переменную для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::StoreValue(int& out) {
        parser_.options_[index_].storeInt = &out;
        return *this;
    }

    /**
     * @brief Указывает вектор для сохранения нескольких целочисленных значений
     * @param out Ссылка на вектор для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::StoreValues(std::vector<int>& out) {
        parser_.options_[index_].storeInts = &out;
        return *this;
    }

    /**
     * @brief Указывает переменную для сохранения булева значения
     * @param out Ссылка на переменную для сохранения
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::StoreValue(bool& out) {
        parser_.options_[index_].storeBool = &out;
        return *this;
    }

    /**
     * @brief Указывает, что опция может принимать несколько значений
     * @param minCount Минимальное количество значений
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::MultiValue(size_t minCount) {
        auto& opt = parser_.options_[index_];
        opt.multi = true;
        opt.minCount = minCount;
        return *this;
    }

    /**
     * @brief Помечает опцию как позиционную
     * @return Ссылка на себя для цепочки вызовов
     */
    ArgParser::ArgBuilder& ArgParser::ArgBuilder::Positional() {
        parser_.options_[index_].positional = true;
        return *this;
    }

    // Методы добавления аргументов

    /**
     * @brief Добавляет строковый аргумент
     * @param name Имя аргумента
     * @param description Описание аргумента
     * @return Построитель аргументов для настройки
     */
    ArgParser::ArgBuilder ArgParser::AddStringArgument(const std::string& name, const std::string& description) {
        CreateOption(ArgType::String, 0, name, description);
        return ArgBuilder(*this, options_.size() - 1);
    }

    /**
     * @brief Добавляет строковый аргумент с коротким именем
     * @param shortName Короткое имя аргумента
     * @param name Длинное имя аргумента
     * @param description Описание аргумента
     * @return Построитель аргументов для настройки
     */
    ArgParser::ArgBuilder ArgParser::AddStringArgument(char shortName, const std::string& name, const std::string& description) {
        CreateOption(ArgType::String, shortName, name, description);
        return ArgBuilder(*this, options_.size() - 1);
    }

    /**
     * @brief Добавляет целочисленный аргумент
     * @param name Имя аргумента
     * @param description Описание аргумента
     * @return Построитель аргументов для настройки
     */
    ArgParser::ArgBuilder ArgParser::AddIntArgument(const std::string& name, const std::string& description) {
        CreateOption(ArgType::Int, 0, name, description);
        return ArgBuilder(*this, options_.size() - 1);
    }

    /**
     * @brief Добавляет целочисленный аргумент с коротким именем
     * @param shortName Короткое имя аргумента
     * @param name Длинное имя аргумента
     * @param description Описание аргумента
     * @return Построитель аргументов для настройки
     */
    ArgParser::ArgBuilder ArgParser::AddIntArgument(char shortName, const std::string& name, const std::string& description) {
        CreateOption(ArgType::Int, shortName, name, description);
        return ArgBuilder(*this, options_.size() - 1);
    }

    /**
     * @brief Добавляет флаг
     * @param name Имя флага
     * @param description Описание флага
     * @return Построитель аргументов для настройки
     */
    ArgParser::ArgBuilder ArgParser::AddFlag(const std::string& name, const std::string& description) {
        CreateOption(ArgType::Flag, 0, name, description);
        return ArgBuilder(*this, options_.size() - 1);
    }

    /**
     * @brief Добавляет флаг с коротким именем
     * @param shortName Короткое имя флага
     * @param name Длинное имя флага
     * @param description Описание флага
     * @return Построитель аргументов для настройки
     */
    ArgParser::ArgBuilder ArgParser::AddFlag(char shortName, const std::string& name, const std::string& description) {
        CreateOption(ArgType::Flag, shortName, name, description);
        return ArgBuilder(*this, options_.size() - 1);
    }

    /**
     * @brief Добавляет опцию справки
     * @param shortName Короткое имя опции
     * @param name Длинное имя опции
     * @param description Описание опции
     * @return Построитель аргументов для настройки
     */
    ArgParser::ArgBuilder ArgParser::AddHelp(char shortName, const std::string& name, const std::string& description) {
        CreateOption(ArgType::Help, shortName, name, description);
        return ArgBuilder(*this, options_.size() - 1);
    }

    // Реализация парсинга

    /**
     * @brief Парсит аргументы командной строки
     * @param args Вектор строк аргументов
     * @return true, если парсинг успешен, false в случае ошибки
     */
    bool ArgParser::Parse(const std::vector<std::string>& args) {
        // Сброс состояния всех опций
        for (auto& opt : options_) {
            opt.seen = false;
            opt.valuesString.clear();
            opt.valuesInt.clear();
        }
        helpRequested_ = false;

        // Поиск позиционной опции
        Option* positionalOpt = nullptr;
        for (auto& opt : options_) if (opt.positional) { positionalOpt = &opt; break; }

        // Обработка каждого аргумента
        for (size_t i = 1; i < args.size(); ++i) {
            const auto& arg = args[i];
            if (arg.rfind("--", 0) == 0) {
                // Обработка длинных опций (--option)
                if (arg == "--help") {
                    helpRequested_ = true;
                    continue;
                }
                auto posEq = arg.find('=');
                std::string name = arg.substr(2, posEq - 2);
                if (!longNameMap_.count(name)) return false;
                Option* opt = &options_[longNameMap_[name]];
                if (opt->type == ArgType::Flag) { opt->valueBool = true; opt->seen = true; }
                else {
                    if (posEq == std::string::npos) return false;
                    std::string val = arg.substr(posEq + 1);
                    if (opt->type == ArgType::String) { if (opt->multi) opt->valuesString.push_back(val); else opt->valueString = val; }
                    else if (opt->type == ArgType::Int) { try { int v = std::stoi(val); if (opt->multi) opt->valuesInt.push_back(v); else opt->valueInt = v; } catch (...) { return false; } }
                    opt->seen = true;
                }
            }
            else if (arg.rfind("-", 0) == 0) {
                // Обработка коротких опций (-o)
                if (arg.size() == 2 && arg[1] == 'h') { helpRequested_ = true; continue; }
                if (arg.size() > 2 && arg[2] == '=') {
                    char sn = arg[1];
                    if (!shortNameMap_.count(sn)) return false;
                    Option* opt = &options_[shortNameMap_[sn]];
                    std::string val = arg.substr(3);
                    if (opt->type == ArgType::String) { if (opt->multi) opt->valuesString.push_back(val); else opt->valueString = val; }
                    else if (opt->type == ArgType::Int) { try { int v = std::stoi(val); if (opt->multi) opt->valuesInt.push_back(v); else opt->valueInt = v; } catch (...) { return false; } }
                    else return false;
                    opt->seen = true;
                }
                else {
                    for (size_t k = 1; k < arg.size(); ++k) {
                        char sn = arg[k];
                        if (!shortNameMap_.count(sn)) return false;
                        Option* opt = &options_[shortNameMap_[sn]];
                        if (opt->type == ArgType::Flag) { opt->valueBool = true; opt->seen = true; }
                        else return false;
                    }
                }
            }
            else {
                // Обработка позиционного аргумента
                if (!positionalOpt) return false;
                Option* opt = positionalOpt;
                if (opt->type == ArgType::String) { if (opt->multi) opt->valuesString.push_back(arg); else opt->valueString = arg; }
                else if (opt->type == ArgType::Int) { try { int v = std::stoi(arg); if (opt->multi) opt->valuesInt.push_back(v); else opt->valueInt = v; } catch (...) { return false; } }
                else return false;
                opt->seen = true;
            }
        }

        // Если запрошена справка, остальные проверки не нужны
        if (helpRequested_) return true;

        // Проверка обязательных аргументов и применение значений по умолчанию
        for (auto& opt : options_) {
            if (opt.type == ArgType::String) {
                if (!opt.multi) {
                    if (!opt.seen) {
                        if (opt.hasDefault) opt.valueString = opt.defaultString;
                        else return false;
                    }
                }
                else if (opt.valuesString.size() < opt.minCount) return false;
                if (opt.storeString) *opt.storeString = opt.valueString;
                if (opt.storeStrings) *opt.storeStrings = opt.valuesString;
            }
            else if (opt.type == ArgType::Int) {
                if (!opt.multi) {
                    if (!opt.seen) {
                        if (opt.hasDefault) opt.valueInt = opt.defaultInt;
                        else return false;
                    }
                }
                else if (opt.valuesInt.size() < opt.minCount) return false;
                if (opt.storeInt) *opt.storeInt = opt.valueInt;
                if (opt.storeInts) *opt.storeInts = opt.valuesInt;
            }
            else if (opt.type == ArgType::Flag) {
                if (!opt.seen && opt.hasDefault) opt.valueBool = opt.defaultBool;
                if (opt.storeBool) *opt.storeBool = opt.valueBool;
            }
        }

        return true;
    }

    /**
     * @brief Парсит аргументы командной строки (C-style)
     * @param argc Количество аргументов
     * @param argv Массив строк аргументов
     * @return true, если парсинг успешен, false в случае ошибки
     */
    bool ArgParser::Parse(int argc, char** argv) {
        std::vector<std::string> args(argv, argv + argc);
        return Parse(args);
    }

    /**
     * @brief Проверяет, был ли запрошен вывод справки
     * @return true, если запрошена справка
     */
    bool ArgParser::Help() const {
        return helpRequested_;
    }

    /**
     * @brief Генерирует строку с описанием справки
     * @return Строка с описанием использования программы
     */
    std::string ArgParser::HelpDescription() const {
        std::ostringstream oss;
        oss << programName_ << "\n";
        return oss.str();
    }

    /**
     * @brief Получает строковое значение аргумента
     * @param name Имя аргумента
     * @return Значение аргумента или пустая строка, если не найден
     */
    std::string ArgParser::GetStringValue(const std::string& name) const {
        auto it = longNameMap_.find(name);
        if (it == longNameMap_.end()) return {};
        const Option& opt = options_[it->second];
        if (!opt.multi && !opt.seen && opt.hasDefault) return opt.defaultString;
        if (opt.multi) return opt.valuesString.empty() ? std::string() : opt.valuesString[0];
        return opt.valueString;
    }

    /**
     * @brief Получает целочисленное значение аргумента
     * @param name Имя аргумента
     * @return Значение аргумента или 0, если не найден
     */
    int ArgParser::GetIntValue(const std::string& name) const {
        auto it = longNameMap_.find(name);
        if (it == longNameMap_.end()) return 0;
        const Option& opt = options_[it->second];
        if (!opt.multi && !opt.seen && opt.hasDefault) return opt.defaultInt;
        if (opt.multi) return opt.valuesInt.empty() ? 0 : opt.valuesInt[0];
        return opt.valueInt;
    }

    /**
     * @brief Получает целочисленное значение аргумента по индексу (для multi-value)
     * @param name Имя аргумента
     * @param index Индекс значения
     * @return Значение аргумента или 0, если не найден
     */
    int ArgParser::GetIntValue(const std::string& name, size_t index) const {
        auto it = longNameMap_.find(name);
        if (it == longNameMap_.end()) return 0;
        const Option& opt = options_[it->second];
        return (opt.multi && index < opt.valuesInt.size()) ? opt.valuesInt[index] : 0;
    }

    /**
     * @brief Проверяет, установлен ли флаг
     * @param name Имя флага
     * @return true, если флаг установлен или есть значение по умолчанию
     */
    bool ArgParser::GetFlag(const std::string& name) const {
        auto it = longNameMap_.find(name);
        if (it == longNameMap_.end()) return false;
        const Option& opt = options_[it->second];
        return opt.seen ? opt.valueBool : (opt.hasDefault ? opt.defaultBool : false);
    }

} // namespace ArgumentParser
