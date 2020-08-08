#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include "Sizing.h"

double conv(std::string inputs)
{	
	std::cout << inputs.size() << ": " << inputs.size() * sizeof(inputs[0]) << ", ";
	HuffmanTree huff = HuffmanTree(inputs);

	std::vector<bool> result = huff.encode(inputs);
	if (!huff.decode(result, inputs))
		std::cout << "Error occured!!!" << std::endl;
	huff.clear();

	size_t ele = sizeof(int), size = result.size() / (8 * ele) + 1;
	std::cout << result.size() << ": " << size * ele << std::endl;
	return size * ele * 1.0 / inputs.size();
}

void sing(std::ofstream &fo, size_t len, int loop)
{
	const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::random_device random_device;
	std::mt19937 generator(random_device());

	for (int i = 0; i < loop; ++i)
	{
		for (double p = .1; p < .55; p += .1)
		{
			std::binomial_distribution<> distribution(int(CHARACTERS.size()) - 1, p);
			std::string inputs;

			for (int j = 0; j < len; ++j)
				inputs += CHARACTERS[distribution(generator)];

			fo << conv(inputs) << "," << std::to_string(p) << std::endl;
		}
	}
}

void meas(std::string file_name, int len_mag)
{
	std::ofstream fo(file_name);
	fo.precision(5);
	fo << "ratio,p" << std::endl;
	size_t len = 10;

	for (int i = 0; i < len_mag; ++i)
	{
		std::cout << "Processing length: " << len << "..." << std::endl;
		sing(fo, len, 4);
		len *= 10;
	}

	fo.close();
}