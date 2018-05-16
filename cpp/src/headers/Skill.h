//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_SKILL_H
#define PROJECT_SKILL_H


#include "Plane.h"
class Plane;

/**
 * @brief Base class for every plane ability
 *
 * Every special action a Plane can perform such as boosting and shooting
 */
class Skill {

protected:

    /**
     * @brief how long it takes to 'reload' the skill
     *
     * For example, it can take 5 seconds to use boost again after using it
     */
    double cooldownTime;

    /**
     * @brief Clock used to calculate the cooldown time
     */
    sf::Clock cooldown;

public:


    /**
     * @brief returns how many seconds are left before cooldown ends and the skill can be used again
     * @return the time until cooldown ends
     */
    double getCooldownTime();

    /**
     * sets the cooldown time
     * @param t new cooldown time, in seconds
     */
    void setCooldownTime(double t);

    /**
     * @brief shows if the skill is currently on cooldown
     * @return true - is on cooldown, false - no cooldown
     */
    bool isOnCooldown();

    /**
     * @brief puts the skill on cooldown
     */
    void startCooldown();

    /**
     * @brief resets the cooldown clock
     */
    void resetCooldown();

    /**
     * @brief the action that the skill does, customised for each inheriting skill
     * @param plane pointer to the plane that activated the skill
     */
    virtual void activate(Plane & plane) = 0;
};



#endif //PROJECT_SKILL_H
