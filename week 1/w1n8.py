class Snow:
    def __init__(self, qty):
        self.snow = qty

    def __call__(self, qty):
        self.snow = qty

    def __add__(self, n):
        self.snow += n

    def __sub__(self, n):
        self.snow -= n

    def __mul__(self, n):
        self.snow *= n

    def __truediv__(self, n):
        self.snow = round(self.snow / n)

    def makeSnow(self, row):
        qty_row = int(self.snow / row)  # количество целых строк
        s = ''
        for i in range(qty_row):
            s += '*' * row + '\n'  # добавляется очередная строка
        s += (self.snow - qty_row * row) * '*'  # добавляются оставшиеся символы
        if s[-1] == '\n':  # если количество снежинок кратно row,
            s = s[:-1]  # надо удалить последний переход на новую строку
        return s