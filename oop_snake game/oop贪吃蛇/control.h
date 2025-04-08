#pragma once
#include<iostream>
#include<fstream>
#include "objects.h"


int start(Game& G, Wall& W, Food& F, Snake& S, int mode);
int play_one(Game& G, Wall& W, Food& F, Snake& S);
int play_two(Game& G, Wall& W, Food& F, Snake& S);
int play_three(Game& G, Wall& W, Food& F, Snake& S);
int key_monitor();
