#include "Card.h"

Card::Card(string name, int attack, int defense, int heal, int defenseHeal, StatusEffect effect)
    : name(name), attack(attack), defense(defense), heal(heal), defenseHeal(defenseHeal), effect(effect) {}
