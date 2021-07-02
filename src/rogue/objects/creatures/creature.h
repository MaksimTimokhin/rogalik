#pragma once

#include <rogue/direction/direction.h>
#include <rogue/dungeon/dungeon.h>
#include <rogue/objects/object.h>

#include <memory>
#include <random>

class AbstractCreature : public IObject {
public:
    AbstractCreature(Dungeon *dungeon, int y_pos, int x_pos);

    bool IsTransparent() const override final;
    bool CanMove() const override final;
    void Interact(Hero &hero) override;

    int GetYPos() const;
    int GetXPos() const;

    bool IsDead() const;

    bool Move(const Direction &direction);
    bool Move(int y_pos, int x_pos);
    int Attack(AbstractCreature &other);
    int GetDamaged(int damage);
    int GetHealed(int health);

    virtual ~AbstractCreature() = default;

protected:
    int y_pos_;
    int x_pos_;

    int health_ = 100;
    int damage_ = 10;
    int armor_ = 2;
    int damage_scatter_ = 4;
    double evasion_ = 0.15;
    double accuracy_ = 0.95;

    static std::mt19937 kRandomGen;

private:
    constexpr static double kArmorFactor = 0.02;
    Dungeon *dungeon_;
};