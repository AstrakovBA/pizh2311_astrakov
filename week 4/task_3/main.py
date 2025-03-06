"""
Программирование на языке высокого уровня (Python).
Задание №3
Выполнил: Астраков Б. А.
Группа: ПИЖ-б-о-23-1
E-Mail: bororo8918@gmail.com
"""

import deposits
# Пример использования
deposit = choose_deposit('bonus', amount=100000, rate=0.05, period=3, bonus_threshold=50000, bonus_rate=0.1)
print(f"Прибыль по вкладу: {deposit.calculate_profit():.2f} руб.")
