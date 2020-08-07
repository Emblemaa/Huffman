#include "Huffman.h"
#include <map>
#include <set>
#include <iostream>

Node::Node(char dat, int freq)
{
	Node::data = dat;
	Node::freq = freq;
	left = right = nullptr;
}

Node::Node(Node* left, Node* right)
{
	Node::left = left;
	Node::right = right;
	Node::freq = left->freq + right->freq;
	Node::data = char(0);
}

void HuffmanTree::parse_string()
{
	std::map<char, int> freq;
	std::set<std::pair<int, char>> list;

	for (auto ch : HuffmanTree::data)
	{
		if (freq[ch] <= 0)
			freq[ch] = 1;
		else ++freq[ch];
	}

	for (auto ch : freq)
		list.insert({ ch.second, ch.first });

	freq.clear();

	for (auto ch : list)
	{
		Node* current = new Node(ch.second, ch.first);
		HuffmanTree::nodes.push(current);
	}

	list.clear();
}

void HuffmanTree::build_tree()
{
	while (nodes.size() + trees.size() > 1)
	{
		Node* a[2] = {};

		for (int i = 0; i < 2; ++i)
			if (trees.empty())
			{
				a[i] = nodes.front();
				nodes.pop();
			}
			else if (nodes.empty())
			{
				a[i] = trees.front();
				trees.pop();
			}
			else if (trees.front()->freq > nodes.front()->freq)
			{
				a[i] = nodes.front();
				nodes.pop();
			}
			else
			{
				a[i] = trees.front();
				trees.pop();
			}

		Node* newNode = new Node(a[0], a[1]);
		trees.push(newNode);
	}

	if (nodes.empty())
		root = trees.front();
	else root = nodes.front();
}

void HuffmanTree::create_code(Node* current)
{
	if (current->left != nullptr)
	{
		current->left->code = current->code;
		current->left->code.push_back(0);
		HuffmanTree::create_code(current->left);

		current->right->code = current->code;
		current->right->code.push_back(1);
		HuffmanTree::create_code(current->right);
	}
	else HuffmanTree::codes[current->data] = current->code;
}

HuffmanTree::HuffmanTree(std::string dat)
{
	HuffmanTree::data = dat;
	HuffmanTree::parse_string();
	HuffmanTree::build_tree();
	HuffmanTree::create_code(HuffmanTree::root);
}

std::vector<bool> HuffmanTree::encode(std::string &inputs)
{
	std::vector<bool> results;

	for (auto input : inputs)
		results.insert(results.end(), HuffmanTree::codes[input].begin(), HuffmanTree::codes[input].end());

	return results;
}

bool HuffmanTree::decode(std::vector<bool> &inputs, std::string &outputs)
{
	Node* current = HuffmanTree::root;
	outputs = "";

	for (auto input : inputs)
	{
		if (current == nullptr)
		{
			std::cout << "Decoding Error: Code does not comply with internal encoding scheme." << std::endl;
			return false;
		}

		if (input)
			current = current->right;
		else current = current->left;
		
		if (current->left == nullptr)
		{
			outputs += current->data;
			current = HuffmanTree::root;
		}
	}

	return true;
}

void HuffmanTree::del(Node* current)
{
	if (current != nullptr)
	{
		current->code.clear();
		HuffmanTree::del(current->left);
		HuffmanTree::del(current->right);
	}
}

void HuffmanTree::clear()
{
	data = "";
	codes.clear();
	HuffmanTree::del(HuffmanTree::root);

	while (!nodes.empty()) nodes.pop();
	while (!trees.empty()) trees.pop();
}