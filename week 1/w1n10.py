"""Этот модуль предназначен для расчета площади
обработанной поверхности и
количества необходимых рулонов обоев."""
class WinDoor:
    """Класс для хранения площади прямоугольника, который не обрабатывается.
    Конструктор принимает длину и ширину, объекту присваивается поле "площадь".
    """
    def __init__(self, width, height):
        self.square = width * height
class Room:
    """Этот класс создает комнаты."""
    def __init__(self, length, width, height):
        """Конструктор принимает размеры комнаты."""
        self.length = length
        self.width = width
        self.height = height
        self.windows = []
    def addWD(self, width, height):
        """Метод добавляет объект класса WinDoor."""
        self.windows.append(WinDoor(width, height))
    def fullSerface(self):
        """Метод рассчитывает полную площадь стен."""
        return 2 * self.height * (self.length + self.width)
    def workSurface(self):
        """Метод рассчитывает площадь стен, которые не
        обрабатываются."""
        new_square = self.fullSerface()
        for i in self.windows:
            new_square -= i.square
        return new_square
    def wallpapers(self, length, width):
        """Метод определяет количество необходимых рулонов."""
        return int(self.workSurface() / (width * 1)) + 1
