"""
Программирование на языке высокого уровня (Python).
Задание №3
Выполнил: Астраков Б. А.
Группа: ПИЖ-б-о-23-1
E-Mail: bororo8918@gmail.com
"""

def main():
    while True:
        deposit_type = input("Выберите тип вклада (fixed, bonus, capitalization) или 'exit' для выхода: ").strip().lower()
        
        if deposit_type == 'exit':
            print("Завершение работы...")
            break
        
        if deposit_type not in ['fixed', 'bonus', 'capitalization']:
            print("Некорректный тип вклада. Пожалуйста, попробуйте снова.")
            continue
        
        try:
            amount = float(input("Введите сумму вклада (в рублях): "))
            rate = float(input("Введите годовую процентную ставку (в десятичной форме, например 0.05 для 5%): "))
            period = int(input("Введите срок вклада в годах: "))
        except ValueError:
            print("Некорректный ввод. Пожалуйста, введите числовые значения.")
            continue
        
        kwargs = {}
        if deposit_type == 'bonus':
            try:
                kwargs['bonus_threshold'] = float(input("Введите пороговую сумму для начисления бонуса: "))
                kwargs['bonus_rate'] = float(input("Введите процент бонуса от прибыли (в десятичной форме, например 0.1 для 10%): "))
            except ValueError:
                print("Некорректный ввод. Пожалуйста, введите числовые значения.")
                continue
        
        # Создаем вклад на основе выбранного типа
        deposit = choose_deposit(deposit_type, amount, rate, period, **kwargs)
        
        # Выводим прибыль по вкладу
        print(f"Прибыль по вкладу: {deposit.calculate_profit():.2f} руб. 🎉")

if __name__ == "__main__":
    main()
