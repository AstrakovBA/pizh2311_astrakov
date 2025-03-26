"""
Программирование на языке высокого уровня (Python).
Задание №1
Выполнил: Астраков Б. А.
Группа: ПИЖ-б-о-23-1
E-Mail: bororo8918@gmail.com
"""

import roman
# Примеры использования
r1 = Roman("X")  # 10
r2 = Roman("V")  # 5

print(r1 + r2)  # XV (15)
print(r1 - r2)  # V (5)

print(Roman.arabic_to_roman(8)) # VIII
print(Roman.roman_to_arabic('MCMXLV')) # 1945

# Вывод программы:
# 
# r1: X (10)
# r2: V (5)
# r1 + r2: XV (15)
# r1 - r2: V (5)
# 8 in Roman: VIII
# MCMXLV in Arabic: 1945
