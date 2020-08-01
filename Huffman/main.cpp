#include "Huffman.h"

int main()
{
	std::string str = "A DEAD DAD CEDED A BAD BABE A BEADED ABACA BED";
	HuffmanTree huff = HuffmanTree(str);
	std::vector<bool> result = huff.encode(str);

	for (auto bools : result)
		std::cout << bools;
	std::cout << "\n" << huff.decode(result);

	return 0;
}