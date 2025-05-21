/* File: lib/MP3Parser.h */
#ifndef MP3PARSER_H
#define MP3PARSER_H

#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <string>
#include <unordered_map>

/**
 * @brief Читает synchsafe integer из массива байт
 * @param bytes Массив из 4 байт для чтения
 * @return Возвращает декодированное 32-битное число
 */
uint32_t readSynchSafeInteger(const std::array<unsigned char,4>& bytes);

/**
 * @brief Базовый класс для всех ID3 фреймов
 */
class Frame {
public:
    std::string id;         ///< Идентификатор фрейма
    uint32_t size;          ///< Размер данных фрейма
    uint16_t flags;         ///< Флаги фрейма
    std::vector<unsigned char> data; ///< Данные фрейма

    /**
     * @brief Конструктор класса Frame
     * @param id_ Идентификатор фрейма
     * @param size_ Размер данных фрейма
     * @param flags_ Флаги фрейма
     * @param data_ Данные фрейма
     */
    Frame(const std::string& id_, uint32_t size_, uint16_t flags_, const std::vector<unsigned char>& data_);
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Frame() = default;
    
    /**
     * @brief Выводит основную информацию о фрейме
     */
    virtual void print() const;
};

/**
 * @brief Возвращает описание фрейма по его ID
 * @param id Идентификатор фрейма
 * @return Строка с описанием фрейма
 */
std::string getFrameDescription(const std::string& id);

/**
 * @brief Класс для текстовых фреймов (ID начинается с 'T')
 */
class TextFrame : public Frame {
public:
    /**
     * @brief Конструктор класса TextFrame
     * @param id_ Идентификатор фрейма
     * @param size_ Размер данных фрейма
     * @param flags_ Флаги фрейма
     * @param data_ Данные фрейма
     */
    TextFrame(const std::string& id_, uint32_t size_, uint16_t flags_, const std::vector<unsigned char>& data_);
    
    /**
     * @brief Выводит информацию о текстовом фрейме
     */
    void print() const override;
};

/**
 * @brief Класс для URL фреймов (ID начинается с 'W')
 */
class UrlFrame : public Frame {
public:
    /**
     * @brief Конструктор класса UrlFrame
     * @param id_ Идентификатор фрейма
     * @param size_ Размер данных фрейма
     * @param flags_ Флаги фрейма
     * @param data_ Данные фрейма
     */
    UrlFrame(const std::string& id_, uint32_t size_, uint16_t flags_, const std::vector<unsigned char>& data_);
    
    /**
     * @brief Выводит информацию о URL фрейме
     */
    void print() const override;
};

/**
 * @brief Класс для фреймов комментариев (COMM)
 */
class CommentFrame : public Frame {
public:
    /**
     * @brief Конструктор класса CommentFrame
     * @param id_ Идентификатор фрейма
     * @param size_ Размер данных фрейма
     * @param flags_ Флаги фрейма
     * @param data_ Данные фрейма
     */
    CommentFrame(const std::string& id_, uint32_t size_, uint16_t flags_, const std::vector<unsigned char>& data_);
    
    /**
     * @brief Выводит информацию о фрейме комментария
     */
    void print() const override;
};

/**
 * @brief Класс для неизвестных типов фреймов
 */
class UnknownFrame : public Frame {
public:
    /**
     * @brief Конструктор класса UnknownFrame
     * @param id_ Идентификатор фрейма
     * @param size_ Размер данных фрейма
     * @param flags_ Флаги фрейма
     * @param data_ Данные фрейма
     */
    UnknownFrame(const std::string& id_, uint32_t size_, uint16_t flags_, const std::vector<unsigned char>& data_);
};

/**
 * @brief Фабрика для создания объектов фреймов
 * @param id Идентификатор фрейма
 * @param size Размер данных фрейма
 * @param flags Флаги фрейма
 * @param data Данные фрейма
 * @return Указатель на созданный объект фрейма
 */
std::unique_ptr<Frame> createFrame(const std::string& id,
                                   uint32_t size,
                                   uint16_t flags,
                                   const std::vector<unsigned char>& data);

#endif // MP3PARSER_H
