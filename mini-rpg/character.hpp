#ifndef characterclassdef
#define characterclassdef

#include <string>

class Character 
{
    public:
    

    Character(std::string name, int health, int strength); // constructor?
    void takeDamage(int damage);
    bool IsAlive() const;
    std::string GetName() const;
    void PrintStatus() const;
    int GetHealth() const;
    void PrintHealth() const;
    virtual void Attack(Character& target);


    protected:
        std::string name;
        int health;
        int strength;
};

class Player : public Character
{
    public:
        Player(std::string name, int health, int strength);
        void Heal(int amount);
};

class Vampire : public Character
{
    public: 
        Vampire(std::string name, int health, int strength);
        void Attack(Character& target) override;
};



#endif