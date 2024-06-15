# The first 'Mario' assignment of Problem Set 1 of Harvard's CS50

Comprised of a singular C file ('mario.c') utlising the CS50 library.

# The Assignment:

## World 1-1
Toward the end of World 1-1 in Nintendo’s Super Mario Brothers, Mario must ascend right-aligned pyramid of blocks, a la the below.

![image](https://github.com/Ed-Flack/CS50-2023/assets/44028291/477a81fc-3136-44eb-b970-37900b28d6ab)

Let’s recreate that pyramid in C, albeit in text, using hashes (#) for bricks, a la the below. Each hash is a bit taller than it is wide, so the pyramid itself will also be taller than it is wide.
```
       #
      ##
     ###
    ####
   #####
  ######
 #######
########
```
The program we’ll write will be called mario. And let’s allow the user to decide just how tall the pyramid should be by first prompting them for a positive integer between, say, 1 and 8, inclusive.

Here’s how the program might work if the user inputs 8 when prompted:
```
$ ./mario
Height: 8
       #
      ##
     ###
    ####
   #####
  ######
 #######
########
```
Here’s how the program might work if the user inputs 4 when prompted:
```
$ ./mario
Height: 4
   #
  ##
 ###
####
```
Here’s how the program might work if the user inputs 2 when prompted:
```
$ ./mario
Height: 2
 #
##
```
And here’s how the program might work if the user inputs 1 when prompted:
```
$ ./mario
Height: 1
#
```
If the user doesn’t, in fact, input a positive integer between 1 and 8, inclusive, when prompted, the program should re-prompt the user until they cooperate:
```
$ ./mario
Height: -1
Height: 0
Height: 42
Height: 50
Height: 4
   #
  ##
 ###
####
```
