#pragma once

#ifndef _SIZE_H_
#define _SIZE_H_

#include <fstream>
#include <string>
#include "Huffman.h"

double conv(std::string inputs);
void sing(std::ofstream &fo, size_t len, int loop);
void meas(std::string file_name, int len_mag);

#endif