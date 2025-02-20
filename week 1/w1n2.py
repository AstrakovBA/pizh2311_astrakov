from random import randint

class Soldier:
    def __init__(self):
        self.health = 100
    def kick(self, enemy):
        enemy.health -= 20

first = Soldier()
second = Soldier()

while first.health > 0 and second.health > 0:
    c = randint(0, 1)
    if c == 0:
        first.kick(second)
        print("(#) Первый воин наносит удар, у противника остаётся " + str(second.health) + " ОЗ")
    else:
        second.kick(first)
        print("($) Второй воин наносит удар, у противника остаётся " + str(first.health) + " ОЗ")

if second.health <= 0 and first.health > 0:
    print("Первый воин победил!")
if first.health <= 0 and second.health > 0:
    print("Второй воин победил!")