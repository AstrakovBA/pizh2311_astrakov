class Заказ:
    """Класс, представляющий заказ пиццы."""

    def __init__(self) -> None:
        """Инициализация нового заказа."""
        self._заказанные_пиццы: list['Пицца'] = []  # Список заказанных пицц
        self._счётчик_заказов: int = 0  # Счётчик заказов

    def __str__(self) -> str:
        """Возвращает строковое представление заказа.

        :return: Строковое представление заказа.
        """
        return f"Заказ #{self._счётчик_заказов}: {', '.join(str(pizza) for pizza in self._заказанные_пиццы)}"

    def добавить(self, пицца: 'Пицца') -> None:
        """Добавляет пиццу в заказ.

        :param пицца: Пицца для добавления.
        """
        self._заказанные_пиццы.append(пицца)

    def сумма(self) -> float:
        """Возвращает общую сумму заказа.

        :return: Общая сумма заказа.
        """
        return sum(pizza.цена for pizza in self._заказанные_пиццы)

    def выполнить(self) -> None:
        """Выполняет заказ, подготавливая, выпекая и упаковывая пиццы."""
        for pizza in self._заказанные_пиццы:
            pizza.подготовить()
            pizza.испечь()
            pizza.порезать()
            pizza.упаковать()
        print("Заказ выполнен!")

    @property
    def заказанные_пиццы(self) -> list['Пицца']:
        """Геттер для получения списка заказанных пицц.

        :return: Список заказанных пицц.
        """
        return self._заказанные_пиццы

    @property
    def счётчик_заказов(self) -> int:
        """Геттер для получения текущего значения счётчика заказов.

        :return: Текущее значение счётчика заказов.
        """
        return self._счётчик_заказов

    @счётчик_заказов.setter
    def счётчик_заказов(self, новое_значение: int) -> None:
        """Сеттер для установки нового значения счётчика заказов.

        :param новое_значение: Новое значение счётчика заказов.
        :raises ValueError: Если значение меньше 0.
        """
        if новое_значение < 0:
            raise ValueError("Счётчик заказов не может быть отрицательным.")
        self._счётчик_заказов = новое_значение
