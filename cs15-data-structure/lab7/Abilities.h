/*
 * Abilities.h
 * Comp 15 Fall 2018 
 * Lab Session 6
 * 
 */
#ifndef ABILITIES_H_
#define ABILITIES_H_

#include <string>

// an Ability has a weapon and a strength
struct Ability {
	std::string weapon;
	int         strength;
};

// linked-list based AbilityList class
class AbilityList {
public:
	// constructor
	AbilityList();

	// copy constructor
	AbilityList(const AbilityList &source);

	// assignment (=) overload
	AbilityList &operator=(const AbilityList &source);

	// destructor
	~AbilityList();

	// updates the strength of weapon called "name" to "amount"
	void updateAbility(std::string name, int amount);

	// determine the strength of a weapon based on the name
	// returns -1 if the pirate does not have this ability
	int getStrength(std::string name) const;

	// print the abilities list for a pirate
	void printAbilityList() const;

	// return total strength: the total strength is the sum
	// of all the strengths for the pirate's weapons
	int totalStrength() const;

	// returns the number of abilities the a pirate has
	int abilityCount() const;

	// returns the ability by the index
	Ability &abilityByIndex(int index) const;

private:
	struct AbilityNode {
		Ability      ability;
		AbilityNode *next;
	};

	AbilityNode *front;  	// the front of the linked list

	void         deleteList    ();
    AbilityNode *newAbilityNode(std::string weapon, int strength,
                                    AbilityNode *nextNode) const;
};

#endif
