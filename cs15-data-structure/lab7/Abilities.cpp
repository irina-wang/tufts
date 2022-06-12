/*
 * Abilities.cpp
 * Comp 15 Fall 2018 
 * Lab Session 6
 * 
 */

#include <iostream>

#include "Abilities.h"

using namespace std;

//
// Allocate and initialize a new AbilityNode
// and return pointer to new node
//
AbilityList::AbilityNode *AbilityList::newAbilityNode(string weapon,
                                                      int strength,
                                                      AbilityNode *nextNode)
        const
{
        AbilityNode *newNode      = new AbilityNode();
        newNode->ability.weapon   = weapon;
        newNode->ability.strength = strength;
        newNode->next             = nextNode;
        return newNode;
}


// constructor
AbilityList::AbilityList()
{
	// start with only your hand
	front = newAbilityNode("hand", 1, NULL);
}

// copy constructor
AbilityList::AbilityList(const AbilityList &source)
{
	if (source.front == NULL)
		return;

	front = newAbilityNode(source.front->ability.weapon,
						   source.front->ability.strength,
						   NULL);
	
	AbilityNode *aux = front;
	AbilityNode *temp = source.front;

	while(temp->next != NULL){
		aux->next = newAbilityNode(temp->ability.weapon,
								   temp->ability.strength,
								   NULL);
		aux = aux->next;
		temp = temp->next;
	}
}


// assignment (=) overload
AbilityList &AbilityList::operator=(const AbilityList &source)
{
	if (this != &source) {
		deleteList(); //delete 
		if (source.front == NULL)
			return *this;
		front = newAbilityNode(source.front->ability.weapon,
						   source.front->ability.strength,
						   NULL);
	
	AbilityNode *aux = front;
	AbilityNode *temp = source.front;

	while(temp->next != NULL){
		aux->next = newAbilityNode(temp->ability.weapon,
								   temp->ability.strength,
								   NULL);
		aux = aux->next;
		temp = temp->next;
		}
	}
	return *this;
}

// destructor
AbilityList::~AbilityList()
{
	deleteList();
}

// Function invoked on the destructor. Releases all memory
void AbilityList::deleteList()
{
	if(front == NULL)
		return;
	while(front != NULL){
		AbilityNode *aux = front;
		front = front->next; 
		delete aux;
	}
}

// updates the strength of weapon called "name" to "amount"
void AbilityList::updateAbility(std::string name, int amount)
{
	AbilityNode *curr = front;
	AbilityNode *prev = NULL;

	while (curr != NULL) {
		if (curr->ability.weapon == name) {
			// found the node to update
			curr->ability.strength = amount;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	// not found, create new node to populate
	curr = newAbilityNode(name, amount, NULL);

	if (prev == NULL) {     // if at front
		front = curr;
	} else {
		prev->next = curr;
	}
}

// determine the strength of a weapon based on the name
// returns -1 if the pirate does not have this ability
int AbilityList::getStrength(std::string name) const
{
	// returns -1 if the name does not exist in the list
	AbilityNode *curr = front;
	while (curr != NULL) {
		if (curr->ability.weapon == name) {
			return curr->ability.strength;
		}
		curr = curr->next;
	}
	return -1;
}

// returns the number of abilities the a pirate has
int AbilityList::abilityCount() const
{
	AbilityNode *curr = front;
	int count = 0;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}

// returns the ability by the index
Ability &AbilityList::abilityByIndex(int index) const
{
	// does not do error checking on index!
	AbilityNode *curr = front;
	for (int i = 0; i < index;i++) {
		curr = curr->next;
	}
	return curr->ability;
}

// print the abilities list for a pirate
void AbilityList::printAbilityList() const
{
	// walk the list and print all weapons and abilities
	AbilityNode *curr = front;
	while (curr != NULL) {
		cout << "\t" << curr->ability.weapon << " : "
				<< curr->ability.strength << "\n";
		curr = curr->next;
	}
}

// return total strength: the total strength is the sum
// of all the strengths for the pirate's weapons
int AbilityList::totalStrength() const
{
	int totalStrength = 0;

	// walk the list and calculate total strength
	AbilityNode *curr = front;
	while (curr != NULL) {
		totalStrength += curr->ability.strength;
		curr = curr->next;
	}
	return totalStrength;
}
