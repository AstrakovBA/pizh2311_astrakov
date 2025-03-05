'''Модуль с классом Roman'''

class Roman:
    """Класс для работы с римскими числами и поддержкой арифметических операций."""

    # Словарь для преобразования римских чисел в арабские
    _roman_to_arabic_map: dict[str, int] = {
        'I': 1, 'V': 5, 'X': 10, 'L': 50,
        'C': 100, 'D': 500, 'M': 1000
    }
    # Словарь для преобразования арабских чисел в римские
    _arabic_to_roman_map: dict[int, str] = {
        1: 'I', 4: 'IV', 5: 'V', 9: 'IX',
        10: 'X', 40: 'XL', 50: 'L', 90: 'XC',
        100: 'C', 400: 'CD', 500: 'D', 900: 'CM',
        1000: 'M'
    }

    def __init__(self, value: str | int):
        if isinstance(value, str):
            self._value: int = self.roman_to_arabic(value)
        elif isinstance(value, int):
            self._value: int = value
        else:
            raise ValueError("Неверное значение! Введите арабское или римское число")

    @staticmethod
    def roman_to_arabic(roman: str) -> int:
        """
        Преобразует римское число в арабское.

        :param roman: Римское число (str).
        :return: Арабское число (int).
        """
        total: int = 0
        prev_value: int = 0
        for char in reversed(roman):
            value: int = Roman._roman_to_arabic_map.get(char, 0)
            if value < prev_value:
                total -= value
            else:
                total += value
            prev_value = value
        return total

    @staticmethod
    def arabic_to_roman(arabic: int) -> str:
        """
        Преобразует арабское число в римское.

        :param arabic: Арабское число (int).
        :return: Римское число (str).
        """
        if arabic <= 0:
            return ""
        roman: str = ""
        for value in sorted(Roman._arabic_to_roman_map.keys(), reverse=True):
            while arabic >= value:
                roman += Roman._arabic_to_roman_map[value]
                arabic -= value
        return roman

    def __add__(self, other: 'Roman') -> 'Roman':
        return Roman(self._value + other._value)

    def __sub__(self, other: 'Roman') -> 'Roman':
        return Roman(self._value - other._value)

    def __mul__(self, other: 'Roman') -> 'Roman':
        return Roman(self._value * other._value)

    def __truediv__(self, other: 'Roman') -> 'Roman':
        return Roman(self._value // other._value)

    def __str__(self) -> str:
        return self.arabic_to_roman(self._value)
