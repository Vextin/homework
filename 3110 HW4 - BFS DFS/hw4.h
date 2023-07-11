#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
int highestNum;
void display(std::vector<std::vector<int>> matrix);
void dfs(int start, bool visited[], std::vector<std::vector<int>> matrix);
void bfs(std::vector<std::vector<int>> matrix);
bool contains(int size, bool list[]);