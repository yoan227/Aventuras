//
// Created by zunig on 6/11/2026.
//

#ifndef AVENTURAS_EVENT_H
#define AVENTURAS_EVENT_H

#include <string>

// Abstract base class for events that occur inside rooms
class Event {
public:
    Event(const std::string& id, const std::string& description);
    virtual ~Event() = default;

    std::string getId() const;
    std::string getDescription() const;
    bool isTriggered() const;
    void markTriggered();

    // Returns the effect on health (negative = damage, positive = heal)
    // Returns the effect on oxygen (negative = drain, positive = refill)
    virtual int healthEffect() const = 0;
    virtual int oxygenEffect() const = 0;
    virtual std::string getTypeName() const = 0;

protected:
    std::string id;
    std::string description;
    bool triggered;
};

// -------------------------------------------------------------------
// A hostile alien or robot that attacks the character
class EnemyEvent : public Event {
public:
    EnemyEvent(const std::string& id, const std::string& description, int damage);
    int healthEffect() const override;
    int oxygenEffect() const override;
    std::string getTypeName() const override;
private:
    int damage;
};

// -------------------------------------------------------------------
// A broken pipe or vacuum breach that drains oxygen
class HazardEvent : public Event {
public:
    HazardEvent(const std::string& id, const std::string& description, int oxygenDrain);
    int healthEffect() const override;
    int oxygenEffect() const override;
    std::string getTypeName() const override;
private:
    int oxygenDrain;
};

// -------------------------------------------------------------------
// An emergency station that restores health or oxygen
class BonusEvent : public Event {
public:
    BonusEvent(const std::string& id, const std::string& description,
               int healthGain, int oxygenGain);
    int healthEffect() const override;
    int oxygenEffect() const override;
    std::string getTypeName() const override;
private:
    int healthGain;
    int oxygenGain;
};

#endif //AVENTURAS_EVENT_H
