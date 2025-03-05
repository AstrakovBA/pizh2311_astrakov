'''Файл содержит реализации всех видов депозита с единым интерфейсом'''
from abc import ABC, abstractmethod
from typing import Union

class Deposit(ABC):
    """
    Абстрактный базовый класс для всех типов вкладов.
    """
    def __init__(self, amount: float, rate: float, period: int):
        """
        Инициализация базового класса вклада.

        :param amount: Сумма вклада.
        :param rate: Годовая процентная ставка.
        :param period: Срок вклада в годах.
        """
        self.amount = amount
        self.rate = rate
        self.period = period

    @abstractmethod
    def calculate_profit(self) -> float:
        """
        Абстрактный метод для расчета прибыли по вкладу.
        Должен быть реализован в подклассах.

        :return: Прибыль по вкладу.
        """
        pass

class FixedDeposit(Deposit):
    """
    Класс для срочного вклада с расчетом по формуле простых процентов.
    """
    def calculate_profit(self) -> float:
        """
        Рассчитывает прибыль по формуле простых процентов.

        :return: Прибыль по вкладу.
        """
        return self.amount * self.rate * self.period

class BonusDeposit(Deposit):
    """
    Класс для бонусного вклада с начислением бонуса в конце периода.
    """
    def __init__(self, amount: float, rate: float, period: int, bonus_threshold: float, bonus_rate: float):
        """
        Инициализация бонусного вклада.

        :param amount: Сумма вклада.
        :param rate: Годовая процентная ставка.
        :param period: Срок вклада в годах.
        :param bonus_threshold: Пороговая сумма для начисления бонуса.
        :param bonus_rate: Процент бонуса от прибыли.
        """
        super().__init__(amount, rate, period)
        self.bonus_threshold = bonus_threshold
        self.bonus_rate = bonus_rate

    def calculate_profit(self) -> float:
        """
        Рассчитывает прибыль с учетом бонуса, если сумма вклада превышает порог.

        :return: Прибыль по вкладу с учетом бонуса.
        """
        profit = self.amount * self.rate * self.period
        if self.amount > self.bonus_threshold:
            profit += profit * self.bonus_rate
        return profit

class CapitalizationDeposit(Deposit):
    """
    Класс для вклада с капитализацией процентов.
    """
    def calculate_profit(self) -> float:
        """
        Рассчитывает прибыль с учетом капитализации процентов.

        :return: Прибыль по вкладу с капитализацией.
        """
        return self.amount * (1 + self.rate) ** self.period - self.amount

def choose_deposit(deposit_type: str, amount: float, rate: float, period: int, **kwargs) -> Union[FixedDeposit, BonusDeposit, CapitalizationDeposit]:
    """
    Функция для выбора типа вклада на основе заданных параметров.

    :param deposit_type: Тип вклада ('fixed', 'bonus', 'capitalization').
    :param amount: Сумма вклада.
    :param rate: Годовая процентная ставка.
    :param period: Срок вклада в годах.
    :param kwargs: Дополнительные параметры для бонусного вклада.
    :return: Объект выбранного типа вклада.
    """
    if deposit_type == 'fixed':
        return FixedDeposit(amount, rate, period)
    elif deposit_type == 'bonus':
        return BonusDeposit(amount, rate, period, kwargs.get('bonus_threshold', 0), kwargs.get('bonus_rate', 0))
    elif deposit_type == 'capitalization':
        return CapitalizationDeposit(amount, rate, period)
    else:
        raise ValueError("Неизвестный тип вклада")
