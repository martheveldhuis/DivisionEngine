#include "List.h"
#include <iostream>

int main() 
{
	List* list = new List();
	list->CreateListItem("Marthe", "Veldhuis", "Den Haag", "06", "Van Limburg Stirumstraat 228 a");
	list->CreateListItem("Marthe2", "Veldhuis", "Den Haag", "06", "Van Limburg Stirumstraat 228 b");
	list->CreateListItem("Marthe3", "Veldhuis", "Den Haag", "06", "Van Limburg Stirumstraat 228 c");
	//list->CreateListItem("Marthe4", "Veldhuis", "Den Haag", "06", "Van Limburg Stirumstraat 228 d");
	//list->CreateListItem("Marthe5", "Veldhuis", "Den Haag", "06", "Van Limburg Stirumstraat 228 e");

	list->DisplayAllListItems();
	//list->RemoveFirstListItem();
	//list->RemoveLastListItem();
	
	//list->DisplayListItemAt(1);
	list->RemoveListItemAt(1);
	list->DisplayAllListItems();

	list->DisplayListItemSize();

	std::getchar();
	return 0;
}