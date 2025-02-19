'''Неделя 2, вариант 3
Выполнил: Астраков Борис, ПИЖ-б-о-23-1(1)
Реализация принципов ООП:
-ИНКАПСУЛЯЦИЯ: переменные "size" и "elements" защищены (написаны как _size и _elements);
-НАСЛЕДОВАНИЕ: класс TArray является базовым, и класс ExtTArray наследует его методы;
-ПОЛИМОРФИЗМ: в классе TArray используются методы с перегрузкой операторов сложения и умножения;
-АБСТРАКЦИЯ: класс AbstractCollection является абстрактным;
-КОМПОЗИЦИЯ: класс TArray используется как атрибут в методах класса Matrix
-ИСПОЛЬЗОВАНИЕ CALL: как метод класса TArray для вывода элементов массива'''

from abc import ABC, abstractmethod

class AbstractCollection(ABC):

    '''АБСТРАКТНЫЙ класс для коллекции'''

    @abstractmethod
    def in_data(self):
        pass

    @abstractmethod
    def out_data(self):
        pass

    @abstractmethod
    def minmax(self):
        pass

    @abstractmethod
    def sort_arr(self):
        pass

    @abstractmethod
    def summ_arr(self):
        pass

class TArray:

    '''Базовый класс. Переменные "size" и "elements" ИНКАПСУЛИРОВАНЫ'''

    #Инициализация без параметров и с параметрами
    def __init__(self, size=0):
        self._size = size
        self._elements = [0] * size

    #Конструктор копирования
    def __copy__(self):
        new_arr = TArray(self._size)
        new_arr._elements = self._elements.copy()
        return new_arr

    #Ввод данных
    def in_data(self):
        for i in range(self._size):
            while True:
                try:
                    self._elements[i] = int(input(f"Элемент {i}: "))
                    break  # Выход из цикла, если ввод успешен
                except ValueError:
                    print("Пожалуйста, введите целое число.")

    #Вывод данных (CALL)
    def __call__(self):
        return str(self._elements)

    #Добавление элемента с перегрузкой плюса (ПОЛИМОРФИЗМ)
    def __add__(self, value):
        self._elements.append(value)
        self._size += 1

    #Умножение элемента с перегрузкой умножения (ПОЛИМОРФИЗМ)
    def __mul__(self, value):
        self._elements = [element * value for element in self._elements]

class ExtTArray(TArray):

    '''ExtTArray НАСЛЕДУЕТ все методы из TArray и добавляет
    функции поиска минимального и максимального элементов,
    сортировки и поиска суммы всех элементов массива'''

    #Вывод мин. и макс. элементов
    def minmax(self):
        if self._size > 0:
            print("Минимальный элемент: " + str(min(self._elements)))
            print("Максимальный элемент :" + str(max(self._elements)))
        else:
            return None
    
    #Сортировка
    def sort_arr(self):
        self._elements.sort()

    #Поиск суммы
    def summ_arr(self):
        return sum(self._elements)

class Matrix:

    '''Класс "Матрица", использующий TArray как атрибут (КОМПОЗИЦИЯ)'''

    #Конструктор
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self._data = [TArray(cols) for _ in range(rows)]

    #Ввод данных
    def in_data(self):
        for i in range(self.rows):
            print(f"Введите данные для строки {i}:")
            self._data[i].in_data()

    #Получение строки по индексу
    def __getitem__(self, index):
        return self._data[index]

    #Вывод матрицы
    def display(self):
        for row in self._data:
            print(row())
