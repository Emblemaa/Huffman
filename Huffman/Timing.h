#pragma once

#ifndef _GEN_H_
#define _GEN_H_

#include <fstream>
#include <string>
#include "Huffman.h"

void single(std::ofstream &fo, std::string inputs, int num);
void fixed(std::ofstream &fo, size_t len, int num, int loop);
void test(std::string file_name, int len_mag);

#endif