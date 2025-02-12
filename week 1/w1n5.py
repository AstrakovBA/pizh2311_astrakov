class Rectangle:
    def __init__(self, width, height, sign):
        self.width = int(width)
        self.height = int(height)
        self.sign = str(sign)
    def __str__(self):
        rect = []
        for i in range(self.height):
            rect.append(self.sign * self.width)
        rect = '\n'.join(rect)
        return rect
    def __add__(self, other):
        return Rectangle(self.width + other.width, self.height + other.height, self.sign)
a = Rectangle(1, 2, 'A')
print(a)
b = Rectangle(3, 4, 'B')
print(b)
print(a + b)
print(b + a)