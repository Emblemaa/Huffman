#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include "Timing.h"

const double coef = 1.e3 / (double)CLOCKS_PER_SEC;

void single(std::ofstream &fo, std::string inputs, int num)
{
	double build = 0, enc = 0, dec = 0;
	std::string temp;

	for (int i = 0; i < num; ++i)
	{
		std::clock_t start = std::clock();
		HuffmanTree huff = HuffmanTree(inputs);
		build += double(std::clock() - start) * coef;

		start = std::clock();
		std::vector<bool> result = huff.encode(inputs);
		enc += double(std::clock() - start) * coef;
	
		start = std::clock();
		if (!huff.decode(result, temp))
			std::cout << "Error occured at " << i << std::endl;
		dec += double(std::clock() - start) * coef;

		huff.clear();
	}

	fo << inputs.size() << ',' << 0 << ',' << build / num << std::endl;
	fo << inputs.size() << ',' << 1 << ',' << enc / num << std::endl;
	fo << inputs.size() << ',' << 2 << ',' << dec / num << std::endl;
}

void fixed(std::ofstream &fo, size_t len, int num, int loop)
{
	const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, int(CHARACTERS.size()) - 1);

	for (int i = 0; i < loop; ++i)
	{
		std::string inputs;

		for (int j = 0; j < len; ++j)
		{
			inputs += CHARACTERS[distribution(generator)];
		}

		single(fo, inputs, num);
	}
}

void test(std::string file_name, int len_mag)
{
	std::ofstream fo(file_name);
	fo.precision(5);
	size_t base = 10;

	fo << "length,type,time" << std::endl;

	for (int i = 0; i < len_mag; ++i)
	{
		for (int j = 1; j < 10; ++j)
		{
			size_t len = base * j;
			std::cout << "Processing length: " << len << "..." << std::endl;
			fixed(fo, len, 4, 7 - i);
		}

		base *= 10;
	}

	fo.close();
}