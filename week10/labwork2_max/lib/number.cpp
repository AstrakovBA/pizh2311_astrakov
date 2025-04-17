/**
 * @file number.cpp
 * @brief Реализация 2022-битного беззнакового целочисленного типа
 */

#include "number.h"
#include <algorithm>
#include <stdexcept>

/**
 * @brief Создает uint2022_t из 32-битного числа
 * @param value Исходное 32-битное число
 * @return Объект uint2022_t
 */
const uint2022_t uint2022_t::from_uint(uint32_t value) {
    return uint2022_t(value);
}

/**
 * @brief Создает uint2022_t из строки
 * @param str Строка с десятичным числом
 * @return Объект uint2022_t
 * @throw std::invalid_argument При недопустимом формате строки
 */
const uint2022_t uint2022_t::from_string(const std::string& str) {
    return uint2022_t(str);
}

/**
 * @brief Конструктор по умолчанию (инициализирует нулем)
 */
uint2022_t::uint2022_t() : parts{} {}

/**
 * @brief Конструктор из 32-битного числа
 * @param value Исходное число
 */
uint2022_t::uint2022_t(uint32_t value) : parts{} {
    parts[0] = value; // Младший разряд
}

/**
 * @brief Конструктор из строки
 * @param str Строка с десятичным числом
 * @throw std::invalid_argument При недопустимых символах или переполнении
 * 
 * Алгоритм:
 * 1. Обрабатывает строку справа налево (от младших разрядов)
 * 2. Для каждой цифры вычисляет ее вклад (digit * 10^n)
 * 3. Накопливает результат через сложение
 */
uint2022_t::uint2022_t(const std::string& str) : parts{} {
    if (str.empty()) {
        throw std::invalid_argument("Empty string");
    }

    uint2022_t power_of_10(1); // Текущая степень 10 (10^n)
    uint2022_t result;
    
    // Обработка цифр справа налево
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        if (*it < '0' || *it > '9') {
            throw std::invalid_argument("Invalid character in string");
        }
        
        uint32_t digit = *it - '0';
        uint2022_t term = from_uint(digit) * power_of_10;
        result = result + term;
        
        if (it != str.rend() - 1) {
            power_of_10 = power_of_10 * from_uint(10);
        }
    }
    
    parts = result.parts;
    check_overflow();
}

/**
 * @brief Проверка на переполнение
 * @throw std::overflow_error Если число превышает 2^2022-1
 * 
 * Сравнивает с предварительно вычисленным максимальным значением
 */
void uint2022_t::check_overflow() const {
    // Лямбда для вычисления максимального значения (2^2022-1)
    const uint2022_t max_value = []() {
        uint2022_t max;
        std::fill(max.parts.begin(), max.parts.end(), 0xFFFFFFFF);
        max.parts.back() >>= (32 - (2022 % 32)); // Коррекция последнего блока
        return max;
    }();

    // Поразрядное сравнение (от старших разрядов)
    for (int i = UINTS_NEEDED - 1; i >= 0; --i) {
        if (parts[i] > max_value.parts[i]) {
            throw std::overflow_error("uint2022_t overflow");
        } else if (parts[i] < max_value.parts[i]) {
            break; // Остальные разряды можно не проверять
        }
    }
}

/**
 * @brief Оператор сложения
 * @param other Слагаемое
 * @return Результат сложения
 * @throw std::overflow_error При переполнении
 * 
 * Алгоритм:
 * 1. Поразрядное сложение с переносом
 * 2. Перенос сохраняется между итерациями
 */
uint2022_t uint2022_t::operator+(const uint2022_t& other) const {
    uint2022_t result;
    uint32_t carry = 0; // Перенос в старший разряд
    
    for (size_t i = 0; i < UINTS_NEEDED; ++i) {
        uint64_t sum = static_cast<uint64_t>(parts[i]) + other.parts[i] + carry;
        result.parts[i] = static_cast<uint32_t>(sum & 0xFFFFFFFF);
        carry = static_cast<uint32_t>(sum >> 32);
    }
    
    if (carry) {
        throw std::overflow_error("Addition overflow");
    }
    
    result.check_overflow();
    return result;
}

/**
 * @brief Оператор вычитания
 * @param other Вычитаемое
 * @return Результат вычитания
 * @throw std::underflow_error Если результат отрицательный
 */
uint2022_t uint2022_t::operator-(const uint2022_t& other) const {
    uint2022_t result;
    uint32_t borrow = 0; // Заем из старшего разряда
    
    for (size_t i = 0; i < UINTS_NEEDED; ++i) {
        uint64_t diff = static_cast<uint64_t>(parts[i]) - other.parts[i] - borrow;
        result.parts[i] = static_cast<uint32_t>(diff & 0xFFFFFFFF);
        borrow = (diff >> 32) ? 1 : 0; // Установка заема
    }
    
    if (borrow) {
        throw std::underflow_error("Subtraction underflow");
    }
    return result;
}

/**
 * @brief Оператор умножения
 * @param other Множитель
 * @return Результат умножения
 * @throw std::overflow_error При переполнении
 * 
 * Алгоритм "в столбик":
 * 1. Умножение каждого разряда с накоплением результата
 * 2. Учет переносов между разрядами
 */
uint2022_t uint2022_t::operator*(const uint2022_t& other) const {
    uint2022_t result;
    
    for (size_t i = 0; i < UINTS_NEEDED; ++i) {
        uint32_t carry = 0;
        for (size_t j = 0; j < UINTS_NEEDED - i; ++j) {
            uint64_t product = static_cast<uint64_t>(parts[i]) * other.parts[j] 
                             + result.parts[i + j] + carry;
            result.parts[i + j] = static_cast<uint32_t>(product & 0xFFFFFFFF);
            carry = static_cast<uint32_t>(product >> 32);
        }
        
        if (carry) {
            throw std::overflow_error("Multiplication overflow");
        }
    }
    
    result.check_overflow();
    return result;
}

/**
 * @brief Оператор сравнения на равенство
 * @param other Число для сравнения
 * @return true если числа равны
 */
bool uint2022_t::operator==(const uint2022_t& other) const {
    return parts == other.parts;
}

/**
 * @brief Оператор сравнения на неравенство
 * @param other Число для сравнения
 * @return true если числа не равны
 */
bool uint2022_t::operator!=(const uint2022_t& other) const {
    return !(*this == other);
}

/**
 * @brief Оператор "меньше"
 * @param other Число для сравнения
 * @return true если текущее число меньше other
 * 
 * Сравнение выполняется от старших разрядов к младшим
 */
bool uint2022_t::operator<(const uint2022_t& other) const {
    for (int i = UINTS_NEEDED - 1; i >= 0; --i) {
        if (parts[i] < other.parts[i]) return true;
        if (parts[i] > other.parts[i]) return false;
    }
    return false; // Все разряды равны
}

/**
 * @brief Оператор "меньше или равно"
 * @param other Число для сравнения
 * @return true если текущее число <= other
 */
bool uint2022_t::operator<=(const uint2022_t& other) const {
    return (*this < other) || (*this == other);
}

/**
 * @brief Оператор вывода в поток
 * @param out Выходной поток
 * @param value Число для вывода
 * @return Ссылка на поток
 * 
 * Алгоритм:
 * 1. Последовательное деление на 10 для получения цифр
 * 2. Цифры собираются в обратном порядке
 * 3. Результат разворачивается перед выводом
 */
std::ostream& operator<<(std::ostream& out, const uint2022_t& value) {
    if (value == uint2022_t::from_uint(0)) {
        out << "0";
        return out;
    }
    
    uint2022_t tmp = value;
    std::string result;
    
    while (tmp != uint2022_t::from_uint(0)) {
        uint32_t remainder = 0;
        // Деление всего числа на 10
        for (size_t i = uint2022_t::UINTS_NEEDED; i-- > 0; ) {
            uint64_t current = (static_cast<uint64_t>(remainder) << 32) | tmp.parts[i];
            tmp.parts[i] = static_cast<uint32_t>(current / 10);
            remainder = static_cast<uint32_t>(current % 10);
        }
        result.push_back('0' + remainder);
    }
    
    std::reverse(result.begin(), result.end());
    out << result;
    return out;
}
