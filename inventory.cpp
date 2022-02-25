#include "inventory.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <type_traits>

Inventory::Inventory(int size)
{
	inventory = (item*)malloc(sizeof(item)*size);
	max_size = size;
	money = 0;
	for (int i = 0; i < max_size; i ++) {
		inventory[i].name = "blank";
		inventory[i].amount = 0;
		inventory[i].type = 0;
	}
}

Inventory::~Inventory()
{
	free(inventory);
}

void Inventory::auto_add(item *pickup)
{
	/* automaticly adds an item to an empty spot in the inventory*/
	for (int i = 0; i < max_size; i++) {
		if (pickup->name == inventory[i].name) {
			int m_add = 255 - inventory[i].amount;
			if (m_add >= pickup->amount) {
				inventory[i].amount += pickup->amount;
				pickup->type = 0;
				pickup->amount = 0;
			}
			else {
				inventory[i].amount += m_add;
				pickup->amount -= m_add;
			}
		}
	}
	if (pickup->amount > 0) {
		for (int i = 0; i < max_size; i++) {
			if (inventory[i].type == 0) {
				inventory[i] = *pickup;
				return;
			}
		}
	}
	if (pickup->amount > 0) {
		std::cout << "Inventory full!" << std::endl;
	}
	return;
}

void Inventory::add_item(item *pickup, int index)
{
	/* adds an item to a spot in the inventory*/
	if (index >= max_size) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	else if (inventory[index].type == 0) {
		inventory[index] = *pickup;
		return;
	}
	else if (pickup->name == inventory[index].name) {
		int m_add = 255 - inventory[index].amount;
		if (m_add >= pickup->amount) {
				inventory[index].amount += pickup->amount;
				pickup->type = 0;
				pickup->amount = 0;
		}
		else {
			inventory[index].amount += m_add;
			pickup->amount -= m_add;
		}
		return;
	}
	else {
		std::cout << "Space already filled!" << std::endl;
		return;
	}
}

void Inventory::drop_item(item *pickup, int index)
{
	/* removes an item from a spot in the inventory*/
	if (index >= max_size) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	else if (inventory[index].type == 0) {
		std::cout << "Item doesn't exist!" << std::endl;
		return;
	}
	else if (pickup->type == 0){
		*pickup = inventory[index];
		return;
	}
	else if (pickup->name == inventory[index].name) {
		int m_add = 255 - pickup->amount;
		if (m_add >= inventory[index].amount) {
				pickup->amount += inventory[index].amount;
				inventory[index].amount = 0;
				inventory[index].type = 0;
		}
		else {
			pickup->amount += m_add;
			inventory[index].amount -= m_add;
		}
		return;
	}
	else {
		std::cout << "Hand full!" << std::endl;
		return;
	}
}

void Inventory::save(string fname)
{
	std::ofstream s_file(fname);
	for (int i = 0; i < max_size; i ++) {
		s_file << "[";
		s_file << inventory[i].name;
		s_file << ",";
		s_file << inventory[i].type;
		s_file << ",";
		s_file << inventory[i].amount;
		s_file << "]";
	}
	s_file.close();
}

void Inventory::load(string fname) {
	//file format is name, type, amount
	std::ifstream s_file(fname);
	int counter = 0;
	while(s_file.eof() == false) {
		char c = s_file.get();
		item tmp;
		if (c == '[') {
			string name = "";
			c = s_file.get();
			while (c != ',') {
				name += c;
				c = s_file.get();
			}
			tmp.name = name;
			tmp.type = (uint8_t)s_file.get();
			c = s_file.get();
			tmp.amount = (uint8_t)s_file.get();
			c = s_file.get();
		}
		inventory[counter] = tmp;
		counter++;
		if (counter == max_size) {
			break;
		}
	}
	if (counter != max_size) {
		std::cout << "could not fill inventory" << std::endl;
	}

	s_file.close();
	return;
}

void Inventory::print() {
	std::cout << "--------INVENTORY--------" << std::endl;
	for (int i = 0; i < max_size; i++) {
		std::cout << inventory[i].name;
		std::cout << ", " + std::to_string(inventory[i].type);
		std::cout << ", " + std::to_string(inventory[i].amount) << std::endl;
	}
	std::cout << "------INVENTORY-END------" << std::endl;
}