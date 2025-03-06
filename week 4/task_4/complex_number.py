"""
Программирование на языке высокого уровня (Python).
Задание №4, вариант 3
Выполнил: Астраков Б. А.
Группа: ПИЖ-б-о-23-1
E-Mail: bororo8918@gmail.com
"""

import json
from typing import Union

class ComplexNumber:
    """
    Класс для представления комплексных чисел.

    Атрибуты:
        real (float): Вещественная часть комплексного числа.
        imaginary (float): Мнимая часть комплексного числа.
    """

    def __init__(self, real: float, imaginary: float):
        """
        Инициализация комплексного числа.

        Аргументы:
            real (float): Вещественная часть.
            imaginary (float): Мнимая часть.
        """
        self.real = real
        self.imaginary = imaginary

    def __str__(self) -> str:
        """
        Возвращает строковое представление комплексного числа.

        Возвращает:
            str: Строковое представление комплексного числа.
        """
        return f"{self.real} + {self.imaginary}i"

    def __add__(self, other: 'ComplexNumber') -> 'ComplexNumber':
        """
        Сложение двух комплексных чисел.

        Аргументы:
            other (ComplexNumber): Другое комплексное число.

        Возвращает:
            ComplexNumber: Результат сложения.
        """
        return ComplexNumber(self.real + other.real, self.imaginary + other.imaginary)

    def __sub__(self, other: 'ComplexNumber') -> 'ComplexNumber':
        """
        Вычитание двух комплексных чисел.

        Аргументы:
            other (ComplexNumber): Другое комплексное число.

        Возвращает:
            ComplexNumber: Результат вычитания.
        """
        return ComplexNumber(self.real - other.real, self.imaginary - other.imaginary)

    def __mul__(self, other: 'ComplexNumber') -> 'ComplexNumber':
        """
        Умножение двух комплексных чисел.

        Аргументы:
            other (ComplexNumber): Другое комплексное число.

        Возвращает:
            ComplexNumber: Результат умножения.
        """
        return ComplexNumber(
            self.real * other.real - self.imaginary * other.imaginary,
            self.real * other.imaginary + self.imaginary * other.real
        )

    def __truediv__(self, other: 'ComplexNumber') -> 'ComplexNumber':
        """
        Деление двух комплексных чисел.

        Аргументы:
            other (ComplexNumber): Другое комплексное число.

        Возвращает:
            ComplexNumber: Результат деления.
        """
        denominator = other.real**2 + other.imaginary**2
        return ComplexNumber(
            (self.real * other.real + self.imaginary * other.imaginary) / denominator,
            (self.imaginary * other.real - self.real * other.imaginary) / denominator
        )

    @classmethod
    def from_string(cls, str_value: str) -> 'ComplexNumber':
        """
        Создает объект ComplexNumber из строки.

        Аргументы:
            str_value (str): Строка в формате "a + bi".

        Возвращает:
            ComplexNumber: Объект комплексного числа.
        """
        parts = str_value.split('+')
        real = float(parts[0].strip())
        imaginary = float(parts[1].strip().rstrip('i'))
        return cls(real, imaginary)

    def save(self, filename: str) -> None:
        """
        Сохраняет комплексное число в JSON-файл.

        Аргументы:
            filename (str): Имя файла для сохранения.
        """
        with open(filename, 'w') as file:
            json.dump({'real': self.real, 'imaginary': self.imaginary}, file)

    @classmethod
    def load(cls, filename: str) -> 'ComplexNumber':
        """
        Загружает комплексное число из JSON-файла.

        Аргументы:
            filename (str): Имя файла для загрузки.

        Возвращает:
            ComplexNumber: Объект комплексного числа.
        """
        with open(filename, 'r') as file:
            data = json.load(file)
        return cls(data['real'], data['imaginary'])
      
