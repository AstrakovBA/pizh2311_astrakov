from abc import ABC, abstractmethod
from typing import Union
import deposits
# Пример использования
deposit = choose_deposit('bonus', amount=100000, rate=0.05, period=3, bonus_threshold=50000, bonus_rate=0.1)
print(f"Прибыль по вкладу: {deposit.calculate_profit():.2f} руб.")
