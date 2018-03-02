# TODO

## Controller
 - `Controller` base abstract class
    - `controll(Plane &plane, /* TODO referencja do listy obiektów z silnika gry */)`

 - `HumanController` -> `Controller`
    - controll uses inputs from keyboard

 - `NNController` -> `Controller`
    - controls the plane with *AI wizardry*
 
 - `DummyController`
    - Spins around and keeps shooting
    - *wins anyway*

## Class `skill` - a base class for each skill, eg. shoot, boost, EMP
 - `activate()` - fucking do this
 - `float cooldown` - cooldown time
 - `bool isOnCooldown()`
 - `startCooldown()`
 - `resetCooldown()`

## `GameObject` enhancements
 - property enum CollisionsAffected - True is objects is a plane - and is affected by collisions

## create a `GameEngine`
 - `GameEngine` class
    - Has a **dynamic list** of objects currently in scene - objectsList
        - ***TODO*** - ask someone who knows cpp well what is the base choice for this structure 
    - `addObject(GameObject & object)`
    - `removeOjbect(GameObject & object)`
    - `performStep()` - simulates each object in objectsList
    - Has to count time in some way - to show the match time
    - Needs some gamestates eg `blue_won`, `red_won`, `blue_crashed`, `menu_show` etc

 ## Plane enhancements
 
  - New skills
    -  Boost - put speed to max for some time
    -  EMP - put speed to minimum for anyone that enters the EMP field
