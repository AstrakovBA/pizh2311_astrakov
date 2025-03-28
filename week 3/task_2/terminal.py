"""
Программирование на языке высокого уровня (Python).
Задание №2
Выполнил: Астраков Б. А.
Группа: ПИЖ-б-о-23-1
E-Mail: bororo8918@gmail.com
"""

class Терминал:
    """Класс, представляющий терминал пиццерии."""

    def __init__(self) -> None:
        """Инициализация терминала с меню пицц."""
        self._меню: list[Пицца] = [
            ПиццаПепперони(),
            ПиццаБарбекю(),
            ПиццаДарыМоря()
        ]
        self._заказ: Заказ = Заказ()
        self._отображать_меню: bool = True

    def __str__(self) -> str:
        """Возвращает строковое представление меню.

        :return: Строковое представление меню.
        """
        return "\n".join(f"{i + 1}. {pizza}" for i, pizza in enumerate(self._меню))

    def начать(self) -> None:
        """Запускает процесс заказа пиццы."""
        print("Добро пожаловать в Пиццерию!")
        while self._отображать_меню:
            print("\nМеню:")
            print(self)
            выбор = input("Введите номер пиццы для добавления в заказ (или 0 для подтверждения): ")
            if выбор.isdigit():
                выбор = int(выбор)
                if выбор == 0:
                    self.подтвердить_заказ()
                elif 1 <= выбор <= len(self._меню):
                    self._заказ.добавить(self._меню[выбор - 1])
                    print(f"Пицца {self._меню[выбор - 1].название} добавлена в заказ.")
                else:
                    print("Неверный номер. Пожалуйста, попробуйте снова.")
            else:
                print("Пожалуйста, введите число.")

    def подтвердить_заказ(self) -> None:
        """Подтверждает заказ и отображает итоговую сумму."""
        общая_сумма: float = self._заказ.сумма()
        print(f"Общая сумма вашего заказа: {общая_сумма} руб.")
        оплата = input("Введите сумму для оплаты: ")
        if оплата.isdigit() and int(оплата) >= общая_сумма:
            print("Спасибо за ваш заказ! Приятного аппетита!")
            self._заказ.выполнить()
            self._отображать_меню = False
        else:
            print("Недостаточная сумма для оплаты. Попробуйте снова.")

    @property
    def меню(self) -> list[Пицца]:
        """Геттер для получения меню.

        :return: Список доступных пицц.
        """
        return self._меню

    @property
    def заказ(self) -> Заказ:
        """Геттер для получения текущего заказа.

        :return: Текущий заказ.
        """
        return self._заказ

    @property
    def отображать_меню(self) -> bool:
        """Геттер для получения статуса отображения меню.

        :return: Статус отображения меню.
        """
        return self._отображать_меню

    @отображать_меню.setter
    def отображать_меню(self, новое_значение: bool) -> None:
        """Сеттер для установки статуса отображения меню.

        :param новое_значение: Новое значение статуса.
        """
        self._отображать_меню = новое_значение
