#ifndef _STATE_H_
#define _STATE_H_
#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>

//To define the possible moves more explicitly
enum move 
{
	placeOneMissionaryOnBoatFromLeft = 1, placeTwoMissionariesOnBoatFromLeft = 2,
	placeOneCannibalOnBoatFromLeft = 3, placeTwoCannibalsOnBoatFromLeft = 4,
	placeOneMissionaryOnBoatFromRight = 5, placeTwoMissionariesOnBoatFromRight = 6,
	placeOneCannibalOnBoatFromRight = 7, placeTwoCannibalsOnBoatFromRight = 8,
	placeOneMissionaryOnLeft = 9, placeTwoMissionariesOnLeft = 10,
	placeOneCannibalOnLeft = 11, placeTwoCannibalsOnLeft = 12,
	placeOneMissionaryOnRight = 13, placeTwoMissionariesOnRight = 14,
	placeOneCannibalOnRight = 15, placeTwoCannibalsOnRight = 16,
	placeOneMissionaryAndOneCannibalOnTheRight = 17, 
	placeOneMissionaryAndOneCannibalOnTheLeft = 18, 
	placeOneMissionaryAndOneCannibalOnTheBoatFromTheRight = 19,
	placeOneMissionaryAndOneCannibalOnTheBoatFromTheLeft = 20,
	toggleBoatLeftToRight = 21, toggleBoatRightToLeft = 22
};

//Every state must have a certain number of cannibals or missionaries on either
//side. Each state will make the boat move one way or the other if true then
//the boat is on the left, if false then it's on the right
struct state
{
	//Member variables
	int missionariesOnTheLeft;
	int cannibalsOnTheLeft;
	int missionariesOnTheRight;
	int cannibalsOnTheRight;
	int missionariesOnTheBoat;
	int cannibalsOnTheBoat;
	bool boatAtLeft;
	state * parentPtr;
	bool hasBeenVisited;

	//Constructor
	state(int, int, int, int, int, int, bool);

	//Constructor for the start state
	state();

	//Overloaded operators
	state& operator= (const state &);
	bool operator== (const state &) const;

};

//There should only ever be 3 missionaries and 3 cannibals. With 22 possible
//moves.  Note that if these constants are changed to any N value the program 
//will still find the most optimized path between the start and the end state.
//We only need to change the constructor for the initial state and change these
//constants.
const int totalNumberOfMissionaries = 3;
const int totalNumberOfCannibals = 3;
const int totalNumberOfMoves = 22;
const static state startState;

//Helper Functions for the struct
bool isStateChangeValid(state);
state getNewState(state&, move);
void expandTheActionsForBFS(std::queue<state> &, std::queue<state>&);
void breadthFirstSearch(std::queue<state>);
void parentFinder(state, std::vector<state>, std::vector<state>&);
void printer(state, std::queue<state>);

#endif