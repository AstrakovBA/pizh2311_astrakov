#pragma once
#include <string>
#include <vector>
#include <map>

namespace omfl {
    class Section;

    class Value {
    public:
        // Проверка типов
        bool IsInt() const;
        bool IsFloat() const;
        bool IsBool() const;
        bool IsString() const;
        bool IsArray() const;
        bool IsSection() const;

        // Аксцессоры
        int AsInt() const;
        float AsFloat() const;
        bool AsBool() const;
        const std::string& AsString() const;
        const std::vector<Value>& AsArray() const;
        const Section& AsSection() const;

        // Констукторы для внутренного использования
        static Value CreateInt(int v);
        static Value CreateFloat(float v);
        static Value CreateBool(bool v);
        static Value CreateString(const std::string& v);
        static Value CreateArray(const std::vector<Value>& v);
        static Value CreateSection(const Section& sec);

    private:
        enum class Type { INT, FLOAT, BOOL, STRING, ARRAY, SECTION, NONE } type_{Type::NONE};
        int int_{};
        float float_{};
        bool bool_{};
        std::string string_;
        std::vector<Value> array_;
        Section* section_{}; // Указатель на собственную секцию в памяти
    };

    class Section {
    public:
        // Получить значения или подсекцию по ключу
        const Value& Get(const std::string& key) const;
        bool Has(const std::string& key) const;

        // Делаем внутренее хранилище доступным для логики парсера
        std::map<std::string, Value> values_;
    };

    class Config {
    public:
        bool valid = false;
        bool IsValid() const { return valid; }

        const Value& Get(const std::string& key) const;
        bool Has(const std::string& key) const;

        // Доступность парсера относительно корневой секции root
        Section root_;
    };

    // Парсинг omfl конфигурации из строки
    Config Parse(const std::string& str);
}