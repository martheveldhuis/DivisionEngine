#pragma once

#include "ListItem.h"
#include <string>
#include <iostream>

class List
{
public:
	List();
	~List();

	void CreateListItem(std::string voornaam, std::string achternaam, std::string woonplaats, std::string telefoonnummer, std::string adres);

	void RemoveFirstListItem();
	void RemoveListItemAt(int index);
	void RemoveLastListItem();

	void DisplayListItemAt(int index);
	void DisplayAllListItems();

	void DisplayListItemSize();
private:
	ListItem *root, *tail;
};
