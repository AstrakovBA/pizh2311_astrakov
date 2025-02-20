class Person:
    def __init__(self, name, surname, qualify = 1):
        self.name = name
        self.surname = surname
        self.qualify = qualify
    def __del__(self):
        print("До свидания, мистер " + str(self.surname))
    def stat(self):
        return "{0} {1}, {2}".format(self.name, self.surname, self.qualify)
    
first = Person("Густав", "Фринг", 7)
second = Person("Майкл", "Эрмантраут", 8)
third = Person("Джесси", "Пинкман", 5)

print(first.stat())
print(second.stat())
print(third.stat())

del third
input()