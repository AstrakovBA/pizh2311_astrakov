#pragma once
#include <cstdint>
#include <iostream>
#include <array>

/**
 * @brief Структура, представляющая 2022-битное беззнаковое целое число.
 * 
 * Хранит число в виде массива десятичных цифр (Little-Endian).
 * Максимальное значение: 2²⁰²² - 1 (≈ 10⁶¹⁰).
 */
struct uint2022_t {
    static constexpr size_t BITS = 2022;
    static constexpr size_t UINTS_NEEDED = (BITS + 31) / 32; // 64 элемента uint32_t (256 байт)
    std::array<uint32_t, UINTS_NEEDED> parts{}; // Храним число в виде 32-битных блоков

    uint2022_t() = default;
};

// Проверка размера (не более 300 байт)
static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

// Проверка переполнения (можно отключить, если написать 0 вместо 1)
#define UINT2022_OVERFLOW_CHECK 1

/**
 * @brief Создает uint2022_t из 32-битного числа.
 * @param i Исходное число (uint32_t).
 * @return Число типа uint2022_t.
 */
uint2022_t from_uint(uint32_t i);

/**
 * @brief Создает uint2022_t из строки (десятичной записи).
 * @param buff Строка, содержащая число (например, "123456").
 * @return Число типа uint2022_t.
 * @throws std::invalid_argument Если строка некорректна.
 */
uint2022_t from_string(const char* buff);

/**
 * @brief Сложение двух чисел uint2022_t.
 * @param lhs Первое слагаемое.
 * @param rhs Второе слагаемое.
 * @return Результат сложения.
 * @throws std::overflow_error Если результат превышает 2²⁰²² - 1.
 */
uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Вычитание двух чисел uint2022_t.
 * @param lhs Уменьшаемое.
 * @param rhs Вычитаемое.
 * @return Результат вычитания.
 * @throws std::underflow_error Если результат отрицательный.
 */
uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Умножение двух чисел uint2022_t.
 * @param lhs Первый множитель.
 * @param rhs Второй множитель.
 * @return Результат умножения.
 * @throws std::overflow_error Если результат превышает 2²⁰²² - 1.
 */
uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Деление двух чисел uint2022_t.
 * @param lhs Делимое.
 * @param rhs Делитель.
 * @return Результат деления.
 * @throws std::invalid_argument Если делитель равен нулю.
 */
uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Проверка на равенство двух чисел.
 * @param lhs Первое число.
 * @param rhs Второе число.
 * @return true, если числа равны, иначе false.
 */
bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Проверка на неравенство двух чисел.
 * @param lhs Первое число.
 * @param rhs Второе число.
 * @return true, если числа не равны, иначе false.
 */
bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

/**
 * @brief Вывод числа в поток.
 * @param stream Выходной поток (например, std::cout).
 * @param value Число для вывода.
 * @return Ссылка на поток.
 */
std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);

/**
 * @brief Проверяет, не превышает ли число максимально допустимое значение (2²⁰²² - 1).
 * @param num Число для проверки.
 * @throws std::overflow_error Если число слишком большое.
 */
void check_overflow(const uint2022_t& num);