'''Неделя 2, вариант 3
Выполнил: Астраков Борис, ПИЖ-б-о-23-1(1)
Реализация принципов ООП:
-ИНКАПСУЛЯЦИЯ: переменные "size" и "elements" защищены (написаны как _size и _elements);
-НАСЛЕДОВАНИЕ: класс TArray является базовым, и класс ExtTArray наследует его методы;
-ПОЛИМОРФИЗМ: в классе TArray используются методы с перегрузкой операторов сложения и умножения;
-АБСТРАКЦИЯ: класс AbstractCollection является абстрактным;
-КОМПОЗИЦИЯ: класс TArray используется как атрибут в методах класса Matrix.
Использование CALL: как метод класса TArray для вывода элементов массива'''

from abc import ABC, abstractmethod

class AbstractCollection(ABC):

    '''АБСТРАКТНЫЙ класс для коллекции'''

    @abstractmethod
    def in_data(self):
        '''см. TArray'''

    @abstractmethod
    def out_data(self):
        '''см. TArray'''

    @abstractmethod
    def minmax(self):
        '''см. ExtTArray'''

    @abstractmethod
    def sort_arr(self):
        '''см. ExtTArray'''

    @abstractmethod
    def summ_arr(self):
        '''см. ExtTArray'''

class TArray:

    '''Базовый класс. Переменные "size" и "elements" ИНКАПСУЛИРОВАНЫ'''

    def __init__(self, size=0):
        '''Инициализация экземпляра класса без параметров и с параметром size'''
        self._size = size
        self._elements = [0] * size

    def __copy__(self):
        '''Конструктор копирования'''
        new_arr = TArray(self._size)
        new_arr._elements = self._elements.copy()
        return new_arr

    def in_data(self):
        '''Ввод данных c защитой от ошибок'''
        for i in range(self._size):
            while True:
                try:
                    self._elements[i] = int(input(f"Элемент {i}: "))
                    break
                except ValueError:
                    print("Пожалуйста, введите целое число.")

    def __call__(self):
        '''Вывод данных (CALL)'''
        return str(self._elements)

    def __add__(self, value):
        '''Добавление элемента с перегрузкой плюса (ПОЛИМОРФИЗМ)'''
        self._elements.append(value)
        self._size += 1

    def __mul__(self, value):
        '''Умножение элемента с перегрузкой умножения (ПОЛИМОРФИЗМ)'''
        self._elements = [element * value for element in self._elements]

class ExtTArray(TArray):

    '''ExtTArray НАСЛЕДУЕТ все методы из TArray и добавляет
    функции поиска минимального и максимального элементов,
    сортировки и поиска суммы всех элементов массива'''

    def minmax(self):
        '''Вывод мин. и макс. элементов в массиве'''
        if self._size > 0:
            print("Минимальный элемент: " + str(min(self._elements)))
            print("Максимальный элемент :" + str(max(self._elements)))
        else:
            return None

    def sort_arr(self):
        '''Сортировка массива'''
        self._elements.sort()

    def summ_arr(self):
        '''Поиск суммы всех элементов массива'''
        return sum(self._elements)

class Matrix:

    '''Класс "Матрица", использующий TArray как атрибут (КОМПОЗИЦИЯ)'''

    def __init__(self, rows, cols):
        '''Конструктор экземпляра класса
        с параметрами размеров строк и столбцов.
        Берёт данные из класса TArray'''
        self.rows = rows
        self.cols = cols
        self._data = [TArray(cols) for _ in range(rows)]

    def in_data(self):
        '''Ввод данных'''
        for i in range(self.rows):
            print(f"Введите данные для строки {i}:")
            self._data[i].in_data()

    def __getitem__(self, index):
        '''Получение строки по индексу'''
        return self._data[index]

    def display(self):
        '''Вывод матрицы'''
        for row in self._data:
            print(row())

'''Ниже приведён пример использования основных функций'''

# Создаётся экземпляр массива из 5 элементов
array = ExtTArray(5)

# В массив через консоль вводятся данные
array.in_data()

# Содержимое массива выводится в консоль
print("Массив:", array())

# В консоль выводятся минимальный и максимальный элементы массива
array.minmax()

# Массив сортируется по возрастанию
array.sort_arr()
print("Отсортированный массив:", array())

# В консоль выводится сумма всех элементов массива
total_sum = array.summ_arr()
print("Сумма всех элементов массива:", total_sum)

# Создаётся экземпляр квадратной матрицы 3х3
matrix = Matrix(3, 3)

# В матрицу вводятся данные из экземпляра массива
matrix.in_data()

# Содержимое матрицы выводится в консоль
print("Матрица:")
matrix.display()
