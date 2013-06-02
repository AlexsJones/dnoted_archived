Dnoted
=======

[![Build Status](https://travis-ci.org/AlexsJones/dnoted.png)](https://travis-ci.org/AlexsJones/dnoted)


Video of use: http://showterm.io/cf02e0c5a0c979a14b0c6

Dnoted is a program that will allow you to leave yourself notes in selected directories that will pop up when you re-enter those directories.


````
$ cd ~/Projects/game_in_progress/
$ dnoted -a "I really have to finish level 43"
dnoted: "Added"
$ cd ../
$ cd game_in_progress
dnoted says: "I really have to finish level 43 (~/Projects/game_in_progress)"
````

Platforms
=========

GNU/Linux & Mac OS X

Installation
============

````
./build_and_install.sh
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
