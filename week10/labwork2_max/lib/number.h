#pragma once
#include <cinttypes>
#include <iostream>
#include <array>

/**
 * @struct uint2022_t
 * @brief 2022-битное беззнаковое целое число
 * 
 * Реализует основные арифметические операции для чисел фиксированного размера.
 * Максимальное значение: 2^2022 - 1.
 * Размер структуры не превышает 300 байт.
 */
struct uint2022_t {
    static constexpr size_t BITS = 2022;                   ///< Количество бит
    static constexpr size_t UINTS_NEEDED = (BITS + 31) / 32; ///< Необходимое количество 32-битных слов
    std::array<uint32_t, UINTS_NEEDED> parts = {};         ///< Хранение числа (little-endian)
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

/**
 * @brief Создает uint2022_t из 32-битного числа
 * @param i Исходное 32-битное число
 * @return Число типа uint2022_t
 */
uint2022_t from_uint(uint32_t i);

/**
 * @brief Создает uint2022_t из строки
 * @param buff Строка с десятичным числом (null-terminated)
 * @return Число типа uint2022_t
 * @throw std::invalid_argument При недопустимых символах или переполнении
 */
uint2022_t from_string(const char* buff);

/**
 * @brief Оператор сложения
 * @param lhs Первое слагаемое
 * @param rhs Второе слагаемое
 * @return Результат сложения
 * @throw std::overflow_error При переполнении
 */
uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Оператор вычитания
 * @param lhs Уменьшаемое
 * @param rhs Вычитаемое
 * @return Результат вычитания
 * @throw std::underflow_error Если результат отрицательный
 */
uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Оператор умножения
 * @param lhs Первый множитель
 * @param rhs Второй множитель
 * @return Результат умножения
 * @throw std::overflow_error При переполнении
 */
uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Оператор деления
 * @param lhs Делимое
 * @param rhs Делитель
 * @return Результат деления
 * @throw std::invalid_argument При делении на ноль
 */
uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Оператор равенства
 * @param lhs Первое число
 * @param rhs Второе число
 * @return true если числа равны
 */
bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Оператор неравенства
 * @param lhs Первое число
 * @param rhs Второе число
 * @return true если числа не равны
 */
bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Оператор вывода в поток
 * @param stream Выходной поток
 * @param value Число для вывода
 * @return Ссылка на поток
 */
std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
