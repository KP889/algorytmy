#include <algorithm>
#include <array>
#include <forward_list>
#include <iostream>
#include <iostream>
#include <iterator>
#include <string.h>
#include <utility>
#include <vector>
#include<iostream>
#include <iomanip>



constexpr size_t width = 32;
constexpr size_t height = 32;


std::vector<std::pair<uint8_t, uint8_t>>
compressGrayscale(std::array<std::array<uint8_t, width>, height> &A);
std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>> &V);
void printMap(std::array<std::array<uint8_t, width>, height> &A);