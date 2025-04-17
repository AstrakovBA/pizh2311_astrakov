#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <string>

/**
 * @class uint2022_t
 * @brief Класс для работы с 2022-битными беззнаковыми целыми числами
 * 
 * Реализует основные арифметические операции и поддерживает создание
 * из стандартных типов и строк. Размер числа фиксирован - ровно 2022 бита.
 */
class uint2022_t {
private:
    static constexpr size_t BITS = 2022;          ///< Количество бит в числе
    static constexpr size_t UINTS_NEEDED = (BITS + 31) / 32; ///< Количество 32-битных слов
    std::array<uint32_t, UINTS_NEEDED> parts;     ///< Массив для хранения битов числа

    /**
     * @brief Проверяет переполнение числа
     * @throw std::overflow_error Если число превышает 2^2022-1
     */
    void check_overflow() const;

    /**
     * @brief Нормализует число (убирает ведущие нули)
     */
    void normalize();

public:
    // Конструкторы
    /**
     * @brief Конструктор по умолчанию (инициализирует нулем)
     */
    uint2022_t();

    /**
     * @brief Конструктор из 32-битного беззнакового числа
     * @param value Значение для инициализации
     */
    explicit uint2022_t(uint32_t value);

    /**
     * @brief Конструктор из строки
     * @param str Строка с десятичным числом
     * @throw std::invalid_argument При недопустимых символах или переполнении
     */
    explicit uint2022_t(const std::string& str);

    // Статические фабричные методы
    /**
     * @brief Создает число из uint32_t
     * @param value Исходное значение
     * @return uint2022_t
     */
    static uint2022_t from_uint(uint32_t value);

    /**
     * @brief Создает число из строки
     * @param str Строка с десятичным числом
     * @return uint2022_t
     * @throw std::invalid_argument При ошибках формата
     */
    static uint2022_t from_string(const std::string& str);

    // Арифметические операции
    /**
     * @brief Оператор сложения
     * @param other Слагаемое
     * @return Результат сложения
     * @throw std::overflow_error При переполнении
     */
    uint2022_t operator+(const uint2022_t& other) const;

    /// @brief Оператор вычитания
    uint2022_t operator-(const uint2022_t& other) const;
    
    /// @brief Оператор умножения
    uint2022_t operator*(const uint2022_t& other) const;
    
    /// @brief Оператор деления
    uint2022_t operator/(const uint2022_t& other) const;

    // Операторы сравнения
    /// @brief Оператор равенства
    bool operator==(const uint2022_t& other) const;
    
    /// @brief Оператор неравенства
    bool operator!=(const uint2022_t& other) const;
    
    /// @brief Оператор "меньше"
    bool operator<(const uint2022_t& other) const;
    
    /// @brief Оператор "меньше или равно"
    bool operator<=(const uint2022_t& other) const;

    // Ввод/вывод
    /**
     * @brief Оператор вывода в поток
     * @param out Выходной поток
     * @param value Выводимое значение
     * @return Поток для чейнинга
     */
    friend std::ostream& operator<<(std::ostream& out, const uint2022_t& value);
};

/// Проверка размера структуры
static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");
