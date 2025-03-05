from complex_number import ComplexNumber

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

if __name__ == "__main__":
    main()
  
