#include "parser.h"
#include <sstream>
#include <cctype>
#include <stdexcept>

namespace omfl {

/**
 * @brief Проверяет соответствие типа значения
 * @throws std::runtime_error если тип не соответствует ожидаемому
 */
#define VALUE_CHECK(type) if (type_ != Type::type) throw std::runtime_error("Bad type");

bool Value::IsInt()    const { return type_ == Type::INT; }
bool Value::IsFloat()  const { return type_ == Type::FLOAT; }
bool Value::IsBool()   const { return type_ == Type::BOOL; }
bool Value::IsString() const { return type_ == Type::STRING; }
bool Value::IsArray()  const { return type_ == Type::ARRAY; }
bool Value::IsSection()const { return type_ == Type::SECTION; }

/**
 * @brief Возвращает значение как целое число
 * @throws std::runtime_error если тип не INT
 */
int Value::AsInt() const    { VALUE_CHECK(INT);    return int_; }

/**
 * @brief Возвращает значение как число с плавающей точкой
 * @throws std::runtime_error если тип не FLOAT
 */
float Value::AsFloat() const{ VALUE_CHECK(FLOAT);  return float_; }

/**
 * @brief Возвращает значение как булево
 * @throws std::runtime_error если тип не BOOL
 */
bool Value::AsBool() const  { VALUE_CHECK(BOOL);   return bool_; }

/**
 * @brief Возвращает значение как строку
 * @throws std::runtime_error если тип не STRING
 */
const std::string& Value::AsString() const { VALUE_CHECK(STRING); return string_; }

/**
 * @brief Возвращает значение как массив
 * @throws std::runtime_error если тип не ARRAY
 */
const std::vector<Value>& Value::AsArray() const { VALUE_CHECK(ARRAY);  return array_; }

/**
 * @brief Возвращает значение как секцию
 * @throws std::runtime_error если тип не SECTION
 */
const Section& Value::AsSection() const { VALUE_CHECK(SECTION); return *section_; }

/**
 * @brief Создает значение типа INT
 */
Value Value::CreateInt(int v)         { Value val; val.type_ = Type::INT;    val.int_ = v;    return val; }

/**
 * @brief Создает значение типа FLOAT
 */
Value Value::CreateFloat(float v)     { Value val; val.type_ = Type::FLOAT;  val.float_ = v;  return val; }

/**
 * @brief Создает значение типа BOOL
 */
Value Value::CreateBool(bool v)       { Value val; val.type_ = Type::BOOL;   val.bool_ = v;   return val; }

/**
 * @brief Создает значение типа STRING
 */
Value Value::CreateString(const std::string& v) { Value val; val.type_ = Type::STRING; val.string_ = v; return val; }

/**
 * @brief Создает значение типа ARRAY
 */
Value Value::CreateArray(const std::vector<Value>& v) { Value val; val.type_ = Type::ARRAY; val.array_ = v; return val; }

/**
 * @brief Создает значение типа SECTION
 */
Value Value::CreateSection(const Section& sec) { Value val; val.type_ = Type::SECTION; val.section_ = new Section(sec); return val; }

/**
 * @brief Получает значение по ключу
 * @param key Ключ для поиска
 * @return Константная ссылка на значение
 * @throws std::runtime_error если ключ не найден
 */
const Value& Section::Get(const std::string& key) const {
    auto it = values_.find(key);
    if (it == values_.end()) throw std::runtime_error("Key not found");
    return it->second;
}

/**
 * @brief Проверяет наличие ключа в секции
 * @param key Ключ для проверки
 * @return true если ключ существует, false в противном случае
 */
bool Section::Has(const std::string& key) const {
    return values_.find(key) != values_.end();
}

/**
 * @brief Получает значение из корневой секции по ключу
 */
const Value& Config::Get(const std::string& key) const { return root_.Get(key); }

/**
 * @brief Проверяет наличие ключа в корневой секции
 */
bool Config::Has(const std::string& key) const { return root_.Has(key); }

/**
 * @brief Удаляет пробельные символы с начала и конца строки
 */
static inline void trim(std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    s = (a == std::string::npos ? "" : s.substr(a, b - a + 1));
}

/**
 * @brief Парсит строковое значение в объект Value
 */
Value parseValue(const std::string& s);

/**
 * @brief Основная функция парсинга конфигурации
 * @param str Строка с конфигурацией в формате OMFL
 * @return Объект Config с распарсенными данными
 */
Config Parse(const std::string& str) {
    Config cfg;
    Section* current = &cfg.root_;
    std::istringstream in(str);
    std::string line;
    try {
        while (std::getline(in, line)) {
            bool inStr = false;
            std::string clean;
            for (char c : line) {
                if (c == '"') inStr = !inStr;
                if (!inStr && c == '#') break;
                clean += c;
            }
            trim(clean);
            if (clean.empty()) continue;
            if (clean.front() == '[' && clean.back() == ']') {
                std::string name = clean.substr(1, clean.size() - 2);
                trim(name);
                Section* sec = &cfg.root_;
                size_t start = 0;
                while (start < name.size()) {
                    size_t dot = name.find('.', start);
                    std::string part = name.substr(start, dot == std::string::npos ? std::string::npos : dot - start);
                    if (!sec->Has(part)) {
                        Section newSec;
                        sec->values_[part] = Value::CreateSection(newSec);
                    }
                    sec = &const_cast<Section&>(sec->values_[part].AsSection());
                    if (dot == std::string::npos) break;
                    start = dot + 1;
                }
                current = sec;
                continue;
            }
            size_t eq = clean.find('=');
            if (eq == std::string::npos) throw std::runtime_error("Invalid line");
            std::string key = clean.substr(0, eq);
            std::string val = clean.substr(eq + 1);
            trim(key); trim(val);
            if (key.empty() || val.empty()) throw std::runtime_error("Empty key or value");
            Value v = parseValue(val);
            if (current->Has(key)) throw std::runtime_error("Duplicate key");
            current->values_[key] = std::move(v);
        }
        cfg.valid = true;
    } catch (...) {
        cfg.valid = false;
    }
    return cfg;
}

/**
 * @brief Парсит строку в соответствующее значение Value
 * @param s Строка для парсинга
 * @return Объект Value с распарсенным значением
 * @throws std::runtime_error при ошибке парсинга
 */
Value parseValue(const std::string& s) {
    if (s.front() == '"' && s.back() == '"') {
        return Value::CreateString(s.substr(1, s.size() - 2));
    }
    if (s == "true" || s == "false") {
        return Value::CreateBool(s == "true");
    }
    if (s.front() == '[' && s.back() == ']') {
        std::vector<Value> arr;
        std::string inner = s.substr(1, s.size() - 2);
        int depth = 0;
        size_t start = 0;
        for (size_t i = 0; i <= inner.size(); ++i) {
            if (i < inner.size()) {
                if (inner[i] == '[') depth++;
                if (inner[i] == ']') depth--;
                if (inner[i] == ',' && depth == 0) {
                    std::string item = inner.substr(start, i - start);
                    trim(item);
                    arr.push_back(parseValue(item));
                    start = i + 1;
                }
                continue;
            }
            std::string item = inner.substr(start);
            trim(item);
            if (!item.empty()) arr.push_back(parseValue(item));
        }
        return Value::CreateArray(arr);
    }
    bool hasDot = s.find('.') != std::string::npos;
    if (!hasDot) {
        int v = std::stoi(s);
        return Value::CreateInt(v);
    } else {
        float v = std::stof(s);
        return Value::CreateFloat(v);
    }
}

}
