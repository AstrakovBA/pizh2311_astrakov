/**
 * @file number.cpp
 * @brief Реализация 2022-битного беззнакового целочисленного типа
 */

#include "number.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstring>

 /**
  * @brief Максимальное значение типа uint2022_t (2^2022 - 1)
  *
  * Вычисляется при первом обращении как статическая константа.
  * Последний блок битов корректируется для точного соответствия 2022 битам.
  */
const uint2022_t MAX_UINT2022 = []() {
    uint2022_t max_num;
    std::fill(max_num.parts.begin(), max_num.parts.end(), 0xFFFFFFFF);
    // Корректировка последнего блока (2022 не кратно 32)
    max_num.parts.back() >>= (32 - (2022 % 32));
    return max_num;
    }();

/**
 * @brief Проверяет, не превышает ли число максимальное значение
 * @param num Проверяемое число
 * @throw std::overflow_error Если число превышает 2^2022 - 1
 *
 * Сравнивает по блокам начиная со старших разрядов.
 * Если все блоки равны максимальным - число допустимо.
 */
static void check_overflow(const uint2022_t& num) {
    for (int i = uint2022_t::UINTS_NEEDED - 1; i >= 0; --i) {
        if (num.parts[i] > MAX_UINT2022.parts[i]) {
            throw std::overflow_error("uint2022_t overflow");
        }
        else if (num.parts[i] < MAX_UINT2022.parts[i]) {
            break; // Остальные разряды можно не проверять
        }
    }
}

/**
 * @brief Создает uint2022_t из 32-битного беззнакового числа
 * @param i Исходное 32-битное число
 * @return Число типа uint2022_t
 *
 * Записывает значение в младший 32-битный блок,
 * остальные блоки остаются нулевыми.
 */
uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    result.parts[0] = i;
    return result;
}

/**
 * @brief Создает uint2022_t из строки десятичных цифр
 * @param buff C-строка с десятичным числом
 * @return Число типа uint2022_t
 * @throw std::invalid_argument При недопустимых символах или длине строки
 *
 * Обрабатывает строку справа налево, накапливая результат
 * через умножение на степени 10 и сложение.
 */
uint2022_t from_string(const char* buff) {
    uint2022_t result;
    uint2022_t power_of_10 = from_uint(1); // Текущая степень 10

    size_t len = strlen(buff);
    if (len == 0 || len > 610) { // 610 - макс. десятичных цифр для 2022 бит
        throw std::invalid_argument("Invalid string length");
    }

    // Обработка каждой цифры, начиная с младших разрядов
    for (size_t i = 0; i < len; ++i) {
        char c = buff[len - 1 - i]; // Обрабатываем справа налево

        if (c < '0' || c > '9') {
            throw std::invalid_argument("Invalid character in string");
        }

        uint32_t digit = c - '0';
        uint2022_t term = from_uint(digit);
        term = term * power_of_10; // Умножаем цифру на текущую степень 10
        result = result + term;    // Добавляем к результату

        // Увеличиваем степень 10 для следующей цифры
        if (i < len - 1) {
            power_of_10 = power_of_10 * from_uint(10);
        }
    }

    check_overflow(result);
    return result;
}

/**
 * @brief Оператор сложения двух чисел uint2022_t
 * @param lhs Первое слагаемое
 * @param rhs Второе слагаемое
 * @return Результат сложения
 * @throw std::overflow_error При переполнении
 *
 * Реализация через поразрядное сложение с переносом.
 * Перенос обрабатывается для каждого 32-битного блока.
 */
uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint32_t carry = 0; // Перенос в старший разряд

    for (size_t i = 0; i < uint2022_t::UINTS_NEEDED; ++i) {
        uint64_t sum = (uint64_t)lhs.parts[i] + rhs.parts[i] + carry;
        result.parts[i] = static_cast<uint32_t>(sum);
        carry = static_cast<uint32_t>(sum >> 32);
    }

    if (carry != 0) {
        throw std::overflow_error("Addition overflow");
    }

    check_overflow(result);
    return result;
}

/**
 * @brief Оператор вычитания двух чисел uint2022_t
 * @param lhs Уменьшаемое
 * @param rhs Вычитаемое
 * @return Результат вычитания
 * @throw std::underflow_error Если результат отрицательный
 *
 * Реализация через поразрядное вычитание с заёмом.
 * Если заём остается после обработки старшего разряда - результат отрицательный.
 */
uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint32_t borrow = 0; // Заём из старшего разряда

    for (size_t i = 0; i < uint2022_t::UINTS_NEEDED; ++i) {
        uint64_t diff = (uint64_t)lhs.parts[i] - rhs.parts[i] - borrow;
        result.parts[i] = static_cast<uint32_t>(diff);
        borrow = (diff >> 32) ? 1 : 0; // Устанавливаем заём, если diff < 0
    }

    if (borrow != 0) {
        throw std::underflow_error("Subtraction underflow");
    }

    return result;
}

/**
 * @brief Оператор умножения двух чисел uint2022_t
 * @param lhs Первый множитель
 * @param rhs Второй множитель
 * @return Результат умножения
 * @throw std::overflow_error При переполнении
 *
 * Реализация умножения "в столбик" с накоплением результата.
 * Каждый блок умножается на все блоки второго числа с учетом переносов.
 */
uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;

    for (size_t i = 0; i < uint2022_t::UINTS_NEEDED; ++i) {
        uint32_t carry = 0;
        for (size_t j = 0; j < uint2022_t::UINTS_NEEDED - i; ++j) {
            uint64_t product = (uint64_t)lhs.parts[i] * rhs.parts[j] +
                result.parts[i + j] + carry;
            result.parts[i + j] = static_cast<uint32_t>(product);
            carry = static_cast<uint32_t>(product >> 32);
        }

        // Проверка на переполнение при наличии переноса
        if (carry != 0 && i + uint2022_t::UINTS_NEEDED < uint2022_t::UINTS_NEEDED) {
            throw std::overflow_error("Multiplication overflow");
        }
    }

    check_overflow(result);
    return result;
}

/**
 * @brief Оператор сравнения на равенство
 * @param lhs Первое число
 * @param rhs Второе число
 * @return true если числа равны, иначе false
 *
 * Поразрядное сравнение всех 32-битных блоков.
 */
bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < uint2022_t::UINTS_NEEDED; ++i) {
        if (lhs.parts[i] != rhs.parts[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Оператор сравнения на неравенство
 * @param lhs Первое число
 * @param rhs Второе число
 * @return true если числа не равны, иначе false
 */
bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Оператор "меньше" для сравнения uint2022_t
 * @param lhs Первое число
 * @param rhs Второе число
 * @return true если lhs < rhs, иначе false
 *
 * Сравнение выполняется от старших разрядов к младшим
 */
bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = uint2022_t::UINTS_NEEDED - 1; i >= 0; --i) {
        if (lhs.parts[i] < rhs.parts[i]) {
            return true;
        }
        else if (lhs.parts[i] > rhs.parts[i]) {
            return false;
        }
    }
    return false; // Все разряды равны
}

/**
 * @brief Оператор "меньше или равно" для сравнения uint2022_t
 * @param lhs Первое число
 * @param rhs Второе число
 * @return true если lhs <= rhs, иначе false
 */
bool operator<=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

/**
 * @brief Оператор целочисленного деления
 * @param lhs Делимое
 * @param rhs Делитель
 * @return Результат деления
 * @throw std::invalid_argument При делении на ноль
 *
 * Реализация через метод нормализации и последовательного вычитания.
 * Делитель нормализуется сдвигами до достижения делимого.
 */
uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (rhs == from_uint(0)) {
        throw std::invalid_argument("Division by zero");
    }

    if (lhs < rhs) {
        return from_uint(0); // Делимое меньше делителя
    }

    uint2022_t quotient;
    uint2022_t remainder = lhs;
    uint2022_t current_divisor = rhs;
    uint2022_t current_quotient = from_uint(1);

    // Нормализация делителя
    while (current_divisor <= remainder) {
        current_divisor = current_divisor + current_divisor;
        current_quotient = current_quotient + current_quotient;
    }

    // Постепенное уменьшение делителя
    while (current_quotient != from_uint(0)) {
        if (current_divisor <= remainder) {
            remainder = remainder - current_divisor;
            quotient = quotient + current_quotient;
        }

        // Уменьшаем делитель и частное в 2 раза
        current_divisor = current_divisor - (current_divisor / from_uint(2));
        current_quotient = current_quotient / from_uint(2);
    }

    return quotient;
}

/**
 * @brief Оператор вывода числа в поток
 * @param stream Выходной поток
 * @param value Выводимое число
 * @return Ссылка на поток
 *
 * Преобразует число в десятичную строку через последовательное деление на 10.
 * Цифры собираются в обратном порядке и разворачиваются перед выводом.
 */
std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    if (value == from_uint(0)) {
        stream << "0";
        return stream;
    }

    uint2022_t tmp = value;
    std::string result;

    // Последовательное деление на 10 для получения цифр
    while (tmp != from_uint(0)) {
        uint32_t remainder = 0;
        // Деление всего числа на 10
        for (size_t i = uint2022_t::UINTS_NEEDED; i-- > 0; ) {
            uint64_t value = (static_cast<uint64_t>(remainder) << 32) | tmp.parts[i];
            tmp.parts[i] = static_cast<uint32_t>(value / 10);
            remainder = static_cast<uint32_t>(value % 10);
        }
        result.push_back('0' + remainder);
    }

    // Цифры были получены в обратном порядке
    std::reverse(result.begin(), result.end());
    stream << result;
    return stream;
}
