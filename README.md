# Homeward-Bound
Survival game loosely based on the children movie series "Homeward Bound"

## Story ##
You take on the role of one of the dogs from the Homeward Bound movie series who, along with your companion Fluffy the cat, have become seperate from your family. Just like the movie, you must journey cross country to be reunited with your family!

## Game-Play ##
* You have a limited amount of turns to reach home before winter arrives.
* Each turn you have a set number of movements.
* You must also maintain your food rations which deplete depending on how you move along the game board.
  * Each tile progression taks away 2 movements and 2 food.
* The game board is a pseudo-random generation of forest, plains, and desert tiles.
  * Forest tiles provide 3 food.
  * Plains tiles provide 2 food.
  * Desert Tiles provide 0 food.
* Randomized events are dispersed across the board, each of which provides you some benefit.
* You and fluffy are seperated to begin the game and you must find her at one of the events before returning home!

## Design ##
The emphasis of this project was to practice class inheritance, polymorphism, and managing interactions with object member variables. Each tile inherits it's polymorphic interactive functions from a parent class, but contain unique contructors and overriding functions for printed appearance.

Beyond the basic requirements I chose to experiment with random board generation as a part of my project. As a fan of Civ and other turn based strategy games, I was interested in the generation of unique maps for every play-through. I learned that truely random autogeneration would result in a checkered board that did not meet the expectations of what we expect when looking at a map. I played with additional conditions that would prioritize creating the same tile type as it's neighbors as the number of same tile types surrounding it increased. I settled upon conditional odds that creates sufficient regions of a certain type without excessive checkering, but prioritizes continuing regions longitudinally slightly more than laterally. The events were also randomized for each play through, and not every event will show up every game with the exception of the win condition of finding Fluffy.

## Set-Up ##
```
$ make
$ make run
```
