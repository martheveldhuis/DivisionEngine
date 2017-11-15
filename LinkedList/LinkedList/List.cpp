#include "stdafx.h"
#include "List.h"
#include <iostream>

List::List()
{
}


List::~List()
{
}

void List::CreateListItem(std::string voornaam, std::string achternaam, std::string woonplaats, std::string telefoonnummer, std::string adres)
{
	ListItem* newItem =new ListItem;
	newItem->voornaam = voornaam;
	newItem->achternaam = achternaam;
	newItem->woonplaats = woonplaats;
	newItem->telefoonnummer = telefoonnummer;
	newItem->adres = adres;
	newItem->nextNode = NULL;

	if (root == NULL)
	{
		root = newItem;
		tail = newItem;
		newItem = NULL;
	}
	else
	{
		tail->nextNode = newItem;
		tail = newItem;
	}
}

void List::RemoveFirstListItem()
{
	ListItem *first = root;
	root = first->nextNode;
	delete first;
}

void List::RemoveListItemAt(int index)
{
	if (root == NULL) {
		std::cout << "There are no items in the list" << std::endl;
		return;
	}

	ListItem* current = root;
	ListItem* previous = root;

	for (int i = 0; i < index; i++) {
		previous = current;
		current = current->nextNode;
	}

	if (current != NULL) {
		previous->nextNode = current->nextNode;
	}
	else {
		previous = NULL;
	}
}

void List::RemoveLastListItem()
{
	ListItem *current = root;
	ListItem *previous = root;

	if (root->nextNode == NULL) {
		root = NULL;
		tail = NULL;
		return;
	}

	while (current->nextNode != NULL) {
		previous = current;
		current = current->nextNode;
	}

	tail = previous;
	previous->nextNode = NULL;
	delete current;
}

void List::DisplayListItemAt(int index)
{
	if (root == NULL)
		return;

	ListItem* current = root;

	int curIndex = 0;

	while (curIndex <= index) 
	{
		if (curIndex++ == index) {
			std::cout << current->voornaam << " " << current->achternaam << std::endl;
			std::cout << current->adres << " " << current->woonplaats << std::endl;
			std::cout << current->telefoonnummer << std::endl << std::endl;
			return;
		}
		if (current->nextNode != NULL) {
			current = current->nextNode;
		}
		else {
			break;
		}
	}

	std::cout << "Node with index " << index << " does not exist" << std::endl;
}

void List::DisplayAllListItems()
{
	if (root == NULL)
		return;

	ListItem* current = root;

	do {
		std::cout << current->voornaam << " " << current->achternaam << std::endl;
		std::cout << current->adres << " " << current->woonplaats << std::endl;
		std::cout << current->telefoonnummer << std::endl << std::endl;

	} while ((current = current->nextNode) != NULL);

}

void List::DisplayListItemSize()
{
	std::printf("%d", sizeof(ListItem));
}


