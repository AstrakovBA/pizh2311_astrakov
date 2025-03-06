"""
Программирование на языке высокого уровня (Python).
Задание №4, вариант 3
Выполнил: Астраков Б. А.
Группа: ПИЖ-б-о-23-1
E-Mail: bororo8918@gmail.com
"""

from collections import deque
import complex_number

def main():
    # Создание комплексных чисел
    cn1 = ComplexNumber(3, 4)
    cn2 = ComplexNumber(1, 2)

    # Тестирование арифметических операций
    print(f"cn1: {cn1}")
    print(f"cn2: {cn2}")
    print(f"cn1 + cn2: {cn1 + cn2}")
    print(f"cn1 - cn2: {cn1 - cn2}")
    print(f"cn1 * cn2: {cn1 * cn2}")
    print(f"cn1 / cn2: {cn1 / cn2}")

    # Создание комплексного числа из строки
    cn3 = ComplexNumber.from_string("5 + 6i")
    print(f"cn3 from string: {cn3}")

    # Сохранение и загрузка комплексного числа
    cn1.save("complex_number.json")
    cn4 = ComplexNumber.load("complex_number.json")
    print(f"cn4 loaded from file: {cn4}")

    # Реализация очереди с помощью deque
    queue = deque()

    # Добавление комплексных чисел в очередь
    queue.append(cn1)
    queue.append(cn2)
    queue.append(cn3)

    print("\nПервый элемент в очереди:", queue[0])  # Показать первый элемент
    print("Размер очереди:", len(queue))            # Показать размер очереди

    # Удаление элементов из очереди
    while queue:
        print("Удаляем элемент:", queue.popleft())   # Удалить и показать первый элемент

if __name__ == "__main__":
    main()
    
# Пример вывода:
# cn1: 3.0 + 4.0i
# cn2: 1.0 + 2.0i
# cn1 + cn2: 4.0 + 6.0i
# cn1 - cn2: 2.0 + 2.0i
# cn1 * cn2: -5.0 + 10.0i
# cn1 / cn2: 2.2 + 0.4i
# cn3 from string: 5.0 + 6.0i
# cn4 loaded from file: 3.0 + 4.0i
# Первый элемент в очереди: 3.0 + 4.0i
# Размер очереди: 3
# Удаляем элемент: 3.0 + 4.0i
# Удаляем элемент: 1.0 + 2.0i
# Удаляем элемент: 5.0 + 6.0i
