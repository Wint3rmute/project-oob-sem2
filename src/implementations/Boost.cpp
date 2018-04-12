//
// Created by shiro on 11.04.18.
//
#include "../headers/Boost.h"

void Boost::activate(Plane &plane) {

    if(!isOnCooldown()) {
        if (boostTimeRemaining > 0) {
            plane.setSpeed(plane.getSpeed()+BOOST_SPEED);
            boostTimeRemaining -= FRAME_TIME;
            setCooldownTime(FRAME_TIME);

            startCooldown();
        } else {
            setCooldownTime(BOOST_COOLDOWN);
            boostTimeRemaining=BOOST_DURATION;
            startCooldown();
        }
    }
}
