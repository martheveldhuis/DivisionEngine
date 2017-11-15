#pragma once
#include <string>

struct ListItem {
	std::string voornaam;
	std::string achternaam;
	std::string woonplaats;
	std::string telefoonnummer;
	std::string adres;
	ListItem* nextNode;
};