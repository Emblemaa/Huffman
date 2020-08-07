#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <iostream>
#include <vector>
#include <queue>
#include <map>

class Node
{
public:
	std::vector<bool> code;
	char data;
	Node* left = nullptr, * right = nullptr;
	int freq = 0;
	Node(char dat, int fre);
	Node(Node* left, Node* right);
};

class HuffmanTree
{
private:
	std::queue<Node*> nodes, trees;
	std::string data = "";
	Node* root = nullptr;
	std::map<char, std::vector<bool>> codes;

	void parse_string();
	void build_tree();
	void create_code(Node* current);

public:
	HuffmanTree(std::string dat);

	std::vector<bool> encode(std::string &input);
	bool decode(std::vector<bool> &input, std::string &outputs);

	void del(Node* current);
	void clear();
};

#endif