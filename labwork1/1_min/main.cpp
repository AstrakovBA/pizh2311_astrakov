/**
 * Программирование на языке высокого уровня (C++).
 * Задание №1, вариант 3
 *
 * Выполнил: Астраков Б. А.
 * Группа: ПИЖ-б-о-23-1
 * E-mail: bororo8918@gmail.com 
 */

#include <iostream>
#include <string>
#include <vector>

/**
 * @class Personality
 * @brief Класс, представляющий личность в энциклопедии.
 * 
 * Содержит информацию об имени, роде деятельности и описании личности.
 */
class Personality {
private:
    std::string name;           ///< Имя личности
    std::string occupation;     ///< Род деятельности
    std::string description;    ///< Описание личности

public:
    /**
     * @brief Конструктор класса Personality.
     * @param name Имя личности.
     * @param occupation Род деятельности.
     * @param description Описание личности.
     */
    Personality(const std::string& name, const std::string& occupation, const std::string& description)
        : name(name), occupation(occupation), description(description) {}

    // Геттеры
    std::string getName() const { return name; }
    std::string getOccupation() const { return occupation; }
    std::string getDescription() const { return description; }

    /**
     * @brief Выводит информацию о личности в консоль.
     */
    void display() const {
        std::cout << "Имя: " << name << "\n";
        std::cout << "Род деятельности: " << occupation << "\n";
        std::cout << "Описание: " << description << "\n\n";
    }
};

/**
 * @class Encyclopedia
 * @brief Класс, представляющий энциклопедию "История в лицах".
 * 
 * Содержит информацию о названии, годе издания и список личностей.
 */
class Encyclopedia {
private:
    std::string title;                  ///< Название энциклопедии
    int publicationYear;                ///< Год издания
    std::vector<Personality> personalities; ///< Список личностей

public:
    /**
     * @brief Конструктор класса Encyclopedia.
     * @param title Название энциклопедии.
     * @param year Год издания.
     */
    Encyclopedia(const std::string& title, int year)
        : title(title), publicationYear(year) {}

    // Геттеры
    std::string getTitle() const { return title; }
    int getPublicationYear() const { return publicationYear; }

    /**
     * @brief Добавляет личность в энциклопедию.
     * @param personality Объект личности для добавления.
     */
    void addPersonality(const Personality& personality) {
        personalities.push_back(personality);
    }

    /**
     * @brief Выводит информацию об энциклопедии и всех личностях в консоль.
     */
    void display() const {
        std::cout << "Энциклопедия: " << title << "\n";
        std::cout << "Год издания: " << publicationYear << "\n\n";
        std::cout << "Содержит следующие личности:\n";
        std::cout << "---------------------------\n";

        for (const auto& personality : personalities) {
            personality.display();
        }
    }
};

/**
 * @brief Основная функция программы.
 * 
 * Создает экземпляр энциклопедии, добавляет личности и выводит информацию.
 */
int main() {
    // Создаем энциклопедию
    Encyclopedia historyEncyclopedia("История в лицах", 2025);

    // Добавляем личности в энциклопедию
    Personality einstein("Альберт Эйнштейн", "Физик",
        "Физик-теоретик, один из основателей современной теоретической физики, "
        "лауреат Нобелевской премии по физике 1921 года.");

    Personality napoleon("Наполеон Бонапарт", "Государственный деятель",
        "Французский государственный деятель и полководец, император французов "
        "в 1804-1814 и 1815 годах.");

    Personality cleopatra("Дэвид Боуи", "Музыкант",
        "Британский рок-музыкант, певец и автор песен, а также продюсер, звукорежиссёр, художник и актёр.");

    historyEncyclopedia.addPersonality(einstein);
    historyEncyclopedia.addPersonality(napoleon);
    historyEncyclopedia.addPersonality(cleopatra);

    // Выводим информацию об энциклопедии и личностях
    historyEncyclopedia.display();

    return 0;
}
