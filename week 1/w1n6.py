class Rectangle:
    def __init__(self, width, height):
        self._w = Rectangle._test(width)
        self._h = Rectangle._test(height)
        print(self)
    def setWidth(self, width):
        self._w = Rectangle._test(width)
    def setHeight(self, height):
        self._h = Rectangle._test(height)
    def getWidth(self):
        return self._w
    def getHeight(self):
        return self._h
    def _test(self, value):
        if value < 0:
            return abs(value)
        else:
            return value
    def __str__(self):
        return "Rectangle {0}x{1}".format(self._w, self._h)
a = Rectangle(3, 4)
print(a.getWidth())
a.setWidth(5)
print(a)
b = Rectangle(-2, 4)