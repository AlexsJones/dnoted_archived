Dnoted
=======

Dnoted is a program that will allow you to leave yourself notes in selected directories that will pop up when you re-enter those directories.


````
$ cd ~/Projects/game_in_progress/
$ dnoted -a "I really have to finish level 43"
dnoted: "Added"
$ cd ../
$ cd game_in_progress
dnoted says: "I really have to finish level 43 (~/Projects/game_in_progress)"
````

Installation
============

````
./configure
make
sudo make install
````

Usage
=====

````
For help: 

$dnoted -h 

To add a message about the current directory:

$dnoted -a This directory is rubbish

To remove a message:

$dnoted -d

````