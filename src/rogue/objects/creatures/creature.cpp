#include "creature.h"

#include <rogue/objects/hero/hero.h>

std::mt19937 AbstractCreature::kRandomGen(65478);

AbstractCreature::AbstractCreature(Dungeon *dungeon, int y_pos, int x_pos)
    : y_pos_(y_pos), x_pos_(x_pos), dungeon_(dungeon) {
}

bool AbstractCreature::IsTransparent() const {
    return true;
}

bool AbstractCreature::CanMove() const {
    return true;
}

void AbstractCreature::Interact(Hero &hero) {
    hero.Attack(*this);
}

int AbstractCreature::GetYPos() const {
    return y_pos_;
}

int AbstractCreature::GetXPos() const {
    return x_pos_;
}

bool AbstractCreature::IsDead() const {
    return health_ <= 0;
}

bool AbstractCreature::Move(const Direction &direction) {
    return Move(y_pos_ + direction.GetDY(), x_pos_ + direction.GetDX());
}

bool AbstractCreature::Move(int y_pos, int x_pos) {
    if (dungeon_->GetObject(y_pos, x_pos)) {
        return false;
    }
    dungeon_->SpawnObject(y_pos, x_pos, dungeon_->RemoveObject(y_pos_, x_pos_));
    y_pos_ = y_pos;
    x_pos_ = x_pos;
    return true;
}

int AbstractCreature::Attack(AbstractCreature &other) {
    int deviation =
        std::uniform_int_distribution<int>(-damage_scatter_, damage_scatter_)(kRandomGen);
    return other.GetDamaged(damage_ + deviation);
}

int AbstractCreature::GetDamaged(int damage) {
    bool missed = std::bernoulli_distribution(evasion_)(kRandomGen);
    if (missed) {
        return 0;
    }
    double effective_armor = kArmorFactor * armor_;
    double damage_multiplier = 1 - effective_armor / (1 + std::abs(effective_armor));
    damage *= damage_multiplier;
    health_ -= damage;
    return damage;
}

int AbstractCreature::GetHealed(int health) {
    health_ += health;
    return health;
}
