#include "state.h"

//Constructor
state::state(int ML, int CL, int MR,
	int CR, int MB, int CB, bool boatAtLeftIn)
{
	missionariesOnTheLeft = ML;
	cannibalsOnTheLeft = CL;
	missionariesOnTheRight = MR;
	cannibalsOnTheRight = CR;
	missionariesOnTheBoat = MB;
	cannibalsOnTheBoat = CB;
	boatAtLeft = boatAtLeftIn;
	parentPtr = nullptr;
	hasBeenVisited = false;
}

//Constructor for start state (so that we have visited the initial start state)
state::state()
{
	missionariesOnTheLeft = 3;
	cannibalsOnTheLeft = 3;
	missionariesOnTheRight = 0;
	cannibalsOnTheRight = 0;
	missionariesOnTheBoat = 0;
	cannibalsOnTheBoat = 0;
	boatAtLeft = true;
	parentPtr = nullptr;
	hasBeenVisited = true;
}


//Comparison operator
bool state::operator== (const state &inputState) const
{
	if (missionariesOnTheLeft == inputState.missionariesOnTheLeft &&
		cannibalsOnTheLeft == inputState.cannibalsOnTheLeft &&
		missionariesOnTheRight == inputState.missionariesOnTheRight &&
		cannibalsOnTheRight == inputState.cannibalsOnTheRight &&
		cannibalsOnTheBoat == inputState.cannibalsOnTheBoat &&
		missionariesOnTheBoat == inputState.missionariesOnTheBoat &&
		boatAtLeft == inputState.boatAtLeft && hasBeenVisited == inputState.hasBeenVisited)
	{
		return true;
	}
	return false;
}

//Assignment operator
state & state::operator= (const state &inputState)
{
	// do the copy
	missionariesOnTheLeft = inputState.missionariesOnTheLeft;
	missionariesOnTheRight = inputState.missionariesOnTheRight;
	cannibalsOnTheLeft = inputState.cannibalsOnTheLeft;
	cannibalsOnTheRight = inputState.cannibalsOnTheRight;
	missionariesOnTheBoat = inputState.missionariesOnTheBoat;
	cannibalsOnTheBoat = inputState.cannibalsOnTheBoat;
	boatAtLeft = inputState.boatAtLeft;
	parentPtr = inputState.parentPtr;
	hasBeenVisited = inputState.hasBeenVisited;

	// return the existing object
	return *this;
}

//A namespace that contains all of the checks needed for a valid change of states
namespace checkIfValidStateChange
{

	//Check if on either shore cannibals will outnumber the missionaries
	//(MR >= CR) and (ML >= CL)
	bool willCannibalsEat(state inputState)
	{
		if ((inputState.cannibalsOnTheLeft > inputState.missionariesOnTheLeft)
			&& (inputState.missionariesOnTheLeft > 0))
		{
			return true;
		}
		if ((inputState.cannibalsOnTheRight > inputState.missionariesOnTheRight)
			&& (inputState.missionariesOnTheRight > 0))
		{
			return true;
		} 
		else
		{
			return false;
		}

	}

	//This checks if the missionaries are ever a negative value
	//since we are working with integer values
	bool canMissionariesBeRemovedFromShore(state inputState)
	{
		if (inputState.missionariesOnTheLeft < 0)
		{
			return false;
		}
		if (inputState.missionariesOnTheRight < 0)
		{
			return false;
		} else
		{
			return true;
		}

	}
	//Check if cannibals can be removed and a negative value wont
	//be given
	bool canCannibalsBeRemovedFromShore(state inputState)
	{
		if (inputState.cannibalsOnTheLeft < 0)
		{
			return false;
		}
		if (inputState.cannibalsOnTheRight < 0)
		{
			return false;
		} 
		else
		{
			return true;
		}

	}

	//Checks if there are more than 3 cannibals (or however many are defined),
	//just for both shores
	bool tooManyCannibalsOnShore(state inputState)
	{
		if ((inputState.cannibalsOnTheLeft + inputState.cannibalsOnTheRight)
		> totalNumberOfCannibals)
		{
			return true;
		} 
		else
		{
			return false;
		}

	}

	//Checks if there are more than 3 missionaries (or however many are defined)
	//just for both shores
	bool tooManyMissionariesOnShore(state inputState)
	{
		if ((inputState.missionariesOnTheLeft + inputState.missionariesOnTheRight) 
		> totalNumberOfMissionaries)
		{
			return true;
		} 
		else
		{
			return false;
		}
	}

	//There can only ever be a max of 2 missionaries on the boat at once.
	//Also there must be a minimum value of 0 missionaries at any given time
	bool isTheNumberOfMissionariesOnBoatCorrect(state inputState)
	{
		if ((inputState.missionariesOnTheBoat >= totalNumberOfMissionaries) ||
			(inputState.missionariesOnTheBoat < 0))
		{
			return false;
		} 
		else
		{
			return true;
		}
	}

	//There can only ever be a max of 2 cannibals on the boat at once.
	//Also there must be a minimum value of 0 cannibals at any given time
	bool isTheNumberOfCannibalsOnBoatCorrect(state inputState)
	{
		if ((inputState.missionariesOnTheBoat >= totalNumberOfMissionaries) ||
			(inputState.missionariesOnTheBoat < 0))
		{
			return false;
		} 
		else
		{
			return true;
		}
	}

	//This checks if the boat contains more than 2 people, even if one is
	//a missionary and the other is a cannibal
	bool boatCheck(state inputState)
	{
		if ((inputState.missionariesOnTheBoat + inputState.cannibalsOnTheBoat) <= 2)
		{
			return true;
		} 
		else
		{
			return false;
		}
	}

}

//This function just goes through and checks that all of the functions in the
//namespace are met.  If they are met then we have a valid move, if one of them
//is false then we cannot push that move onto the stateQueue.
bool isStateChangeValid(state inputState)
{

	bool isStateChangeValid = true;
	if (checkIfValidStateChange::willCannibalsEat(inputState) == true)
	{
		isStateChangeValid = false;
	}

	if (checkIfValidStateChange::canCannibalsBeRemovedFromShore(inputState) == false)
	{
		isStateChangeValid = false;
	}

	if (checkIfValidStateChange::canMissionariesBeRemovedFromShore(inputState) == false)
	{
		isStateChangeValid = false;
	}

	if (checkIfValidStateChange::tooManyCannibalsOnShore(inputState) == true)
	{
		isStateChangeValid = false;
	}

	if (checkIfValidStateChange::tooManyMissionariesOnShore(inputState) == true)
	{
		isStateChangeValid = false;
	}

	if (checkIfValidStateChange::isTheNumberOfCannibalsOnBoatCorrect(inputState) == false)
	{
		isStateChangeValid = false;
	}

	if (checkIfValidStateChange::isTheNumberOfMissionariesOnBoatCorrect(inputState) == false)
	{
		isStateChangeValid = false;
	}

	if (checkIfValidStateChange::boatCheck(inputState) == false)
	{
		isStateChangeValid = false;
	}

	return isStateChangeValid;
}

//Depending on the integer value passed in using the expandTheActionsForBFS
//function to determine what move will be performed.  It will return this state
//for checking at a later point.
state getNewState(state inputState, int i)
{
	//Cast the incoming integer to get a possible move from the list of enums
	move movePeople = static_cast<move>(i);

	//Assign the new state the input state, so that the move can alter what values
	//will be on either side. 
	state newState(3, 3, 0, 0, 0, 0, true);
	newState = inputState;

	//Here just get the number of people on the boat so that when the boat is
	//toggled from left to right there will always be one person to drive it.
	int peopleOnTheBoat = (newState.cannibalsOnTheBoat + newState.missionariesOnTheBoat);
	bool isThereADriver;
	if ((peopleOnTheBoat <= 2) && (peopleOnTheBoat >= 1))
	{
		isThereADriver = true;
	} 
	else
	{
		isThereADriver = false;
	}

	//State changes regarding missionaries and cannibals. The following
	//list is all of the moves possible. Note that a move could just
	//be putting a person on or taking a person off the boat.
	//Or just toggling the boat from left to right or vice versa.
	if (movePeople == placeOneMissionaryOnBoatFromLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.missionariesOnTheBoat += 1;
			newState.missionariesOnTheLeft -= 1;
			newState.boatAtLeft = true;
		} 
	}

	else if (movePeople == placeTwoMissionariesOnBoatFromLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.missionariesOnTheBoat += 2;
			newState.missionariesOnTheLeft -= 2;
			newState.boatAtLeft = true;
		} 
	}

	else if (movePeople == placeOneCannibalOnBoatFromLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.cannibalsOnTheBoat += 1;
			newState.cannibalsOnTheLeft -= 1;
			newState.boatAtLeft = true;
		}

	}

	else if (movePeople == placeTwoCannibalsOnBoatFromLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.cannibalsOnTheBoat += 2;
			newState.cannibalsOnTheLeft -= 2;
			newState.boatAtLeft = true;
		}
	}

	else if (movePeople == placeOneMissionaryOnBoatFromRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.missionariesOnTheBoat += 1;
			newState.missionariesOnTheRight -= 1;
			newState.boatAtLeft = false;
		} 
	}

	else if (movePeople == placeTwoMissionariesOnBoatFromRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.missionariesOnTheBoat += 2;
			newState.missionariesOnTheRight -= 2;
			newState.boatAtLeft = false;
		} 
	}

	else if (movePeople == placeOneCannibalOnBoatFromRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.cannibalsOnTheBoat += 1;
			newState.cannibalsOnTheRight -= 1;
			newState.boatAtLeft = false;
		}
	}

	else if (movePeople == placeTwoCannibalsOnBoatFromRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.cannibalsOnTheBoat += 2;
			newState.cannibalsOnTheRight -= 2;
			newState.boatAtLeft = false;
		}
	}

	else if (movePeople == placeOneMissionaryOnLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.missionariesOnTheBoat -= 1;
			newState.missionariesOnTheLeft += 1;
			newState.boatAtLeft = true;
		} 
	}

	else if (movePeople == placeTwoMissionariesOnLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.missionariesOnTheBoat -= 2;
			newState.missionariesOnTheLeft += 2;
			newState.boatAtLeft = true;
		} 
	}

	else if (movePeople == placeOneCannibalOnLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.cannibalsOnTheBoat -= 1;
			newState.cannibalsOnTheLeft += 1;
			newState.boatAtLeft = true;
		}
	}

	else if (movePeople == placeTwoCannibalsOnLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.cannibalsOnTheBoat -= 2;
			newState.cannibalsOnTheLeft += 2;
			newState.boatAtLeft = true;
		}
	}

	else if (movePeople == placeOneMissionaryOnRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.missionariesOnTheBoat -= 1;
			newState.missionariesOnTheRight += 1;
			newState.boatAtLeft = false;
		} 
	}

	else if (movePeople == placeTwoMissionariesOnRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.missionariesOnTheRight += 2;
			newState.missionariesOnTheBoat -= 2;
			newState.boatAtLeft = false;
		} 
	}

	else if (movePeople == placeOneCannibalOnRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.cannibalsOnTheBoat -= 1;
			newState.cannibalsOnTheRight += 1;
			newState.boatAtLeft = false;
		}
	}

	else if (movePeople == placeTwoCannibalsOnRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.cannibalsOnTheBoat -= 2;
			newState.cannibalsOnTheRight += 2;
			newState.boatAtLeft = false;
		}
	}

	else if (movePeople == placeOneMissionaryAndOneCannibalOnTheRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.cannibalsOnTheBoat -= 1;
			newState.missionariesOnTheBoat -= 1;
			newState.cannibalsOnTheRight += 1;
			newState.missionariesOnTheRight += 1;
			newState.boatAtLeft = false;
		} 
	}

	else if (movePeople == placeOneMissionaryAndOneCannibalOnTheLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.cannibalsOnTheBoat -= 1;
			newState.missionariesOnTheBoat -= 1;
			newState.cannibalsOnTheLeft += 1;
			newState.missionariesOnTheLeft += 1;
			newState.boatAtLeft = true;
		} 
	}

	else if (movePeople == placeOneMissionaryAndOneCannibalOnTheBoatFromTheRight)
	{
		if (newState.boatAtLeft == false)
		{
			newState.cannibalsOnTheBoat += 1;
			newState.missionariesOnTheBoat += 1;
			newState.cannibalsOnTheRight -= 1;
			newState.missionariesOnTheRight -= 1;
			newState.boatAtLeft = false;
		} 
	}

	else if (movePeople == placeOneMissionaryAndOneCannibalOnTheBoatFromTheLeft)
	{
		if (newState.boatAtLeft == true)
		{
			newState.cannibalsOnTheBoat += 1;
			newState.missionariesOnTheBoat += 1;
			newState.cannibalsOnTheLeft -= 1;
			newState.missionariesOnTheLeft -= 1;
			newState.boatAtLeft = true;
		} 
	}

	else if (movePeople == toggleBoatLeftToRight)
	{
		if ((newState.boatAtLeft == true) && (isThereADriver == true))
		{
			newState.boatAtLeft = false;
		} 
	}

	else if (movePeople == toggleBoatRightToLeft)
	{
		if ((newState.boatAtLeft == false) && (isThereADriver == true))
		{
			newState.boatAtLeft = true;
		} 
	}

	inputState = newState;
	return newState;

}

//This function will take the front state of the state queue, get the new state,
//check if that new state is a proper state.  If it is, it will push it onto the
//main queue that is being used for the breadth first search.  As the new move is
//being pushed onto the main queue it will point to the parent which has been
//pushed onto the back of the queue that contains all of the parents 
//(i.e. the popped queue).
void expandTheActionsForBFS(std::queue<state> & stateQueue,
	std::queue<state> & poppedQueue)
{
	state tempState(3, 3, 0, 0, 0, 0, false);
	std::queue<state> tempStateQueue;
	std::queue<state> tempPoppedQueue;
	bool isInQueue = false;

	//Check all possible child moves, if the move is valid then check for
	//duplicates in the parent queue and in the main state queue.
	for (int i = 1; i <= totalNumberOfMoves; i++)
	{
		tempStateQueue = stateQueue;
		tempPoppedQueue = poppedQueue;
		isInQueue = false;
		tempState = getNewState(stateQueue.front(), i);
		if (isStateChangeValid(tempState))
		{
			while (!tempStateQueue.empty())

			{
				if (tempState == tempStateQueue.front())
				{
					//there is a repeated state so prune that branch
					isInQueue = true;
				}

				tempStateQueue.pop();
			}

			//Also check for backtracking
			if (isInQueue == false)
			{
				while (tempPoppedQueue.size() != 0)
				{
					if (tempState == tempPoppedQueue.front())
					{
						//there is a repeated state so prune that branch
						isInQueue = true;
					}

					tempPoppedQueue.pop();
				}
			}

			if (isInQueue == false)
			{
				//1) Mark which state is the child's parent, before it is popped
				//2) Add the state to the state queue, since we checked if unique
				//3) Reset the flag
				tempState.parentPtr = &(poppedQueue.back()); 
				stateQueue.push(tempState);
				isInQueue = false;
			}
		}
	}
}

//This is our main function that performs the breadth first search.
//So make an initial case for the startState, but otherwise loop through
//until the end state is found.  If it is not found then keep expanding the 
//actions, while pushing and popping the queue appropriately.
void breadthFirstSearch(std::queue<state> stateQueue)
{
	// That is, the end state has 0 M and C's on the left, 
	// 3 M and C's on the Right, 0 M and C's on the boat,
	// and the boat has safely made its way to the right side 
	state endState(0, 0, totalNumberOfMissionaries,
		totalNumberOfCannibals, 0, 0, false);
	endState.hasBeenVisited = true;
	std::queue<state> poppedQueue;
	std::queue<state> tempPoppedQueue;
	bool isInQueue = false;
	state tempState(0, 0, 3, 3, 0, 0, false);

	if ((stateQueue.front() == startState) && (stateQueue.size()) == 1)
	{
		poppedQueue.push(startState);
		poppedQueue.front().hasBeenVisited = true;
		stateQueue.front().hasBeenVisited = true;
		expandTheActionsForBFS(stateQueue, poppedQueue);
		stateQueue.pop();
		isInQueue = false;
	}

	while (stateQueue.size() != 0)
	{
		if (stateQueue.front() == endState)
		{
			//stateQueue.front().parentPtr = &poppedQueue.back();
			stateQueue.front().hasBeenVisited = true;
			printer(stateQueue.front(), poppedQueue);
			return;
		}
		else
		{
			//Check for duplicates in the queue that is full of parent states.
			//if it doesn't exist then we can push that new parent onto the end
			//of the queue with all of the parents.
			tempPoppedQueue = poppedQueue;
			while (tempPoppedQueue.size() != 0)
			{
				if (stateQueue.front() == tempPoppedQueue.front())
				{
					isInQueue = true;
					break;
				}
				tempPoppedQueue.pop();
			}

			//State was not found so add it to queue
			if (isInQueue == false)
			{
				stateQueue.front().hasBeenVisited = true;
				poppedQueue.push(stateQueue.front());
			}

			expandTheActionsForBFS(stateQueue, poppedQueue);
			stateQueue.pop();
			isInQueue = false;
		}
	}
}

//The print takes all of the parent queues, then calls parentFinder to get all of
//parents starting at the end state (which is passed in as the input state).
void printer(state inputState, std::queue<state> parentQueue)
{
	std::vector<state> parentVector;
	std::vector<state> vector;
	std::queue<state> tempParentQueue = parentQueue;

	std::vector<state> vectorForPrinting;
	vectorForPrinting.push_back(inputState);

	//copy the contents from the parent queue into a set for easy looping
	while (tempParentQueue.size() != 0)
	{
		parentVector.push_back(tempParentQueue.front());
		tempParentQueue.pop();
	}

	//So now we have parentVector and vectorForPrinting.
	//The idea is to now push back all of the parent states (in the correct order)
	//into the vectorForPrinting

	parentFinder(inputState, parentVector, vectorForPrinting);

	std::cout << "LEFT SHORE|      BOAT      |RIGHT SHORE\n";
	std::cout << "          |                |\n";
	std::cout << "_______________________________________\n";
	for (unsigned int i = vectorForPrinting.size(); i-- > 0;)
	{

		//Print out the people on the left shore
		std::cout << "(M="  << vectorForPrinting.at(i).missionariesOnTheLeft << ", C="
			<< vectorForPrinting.at(i).cannibalsOnTheLeft << ")";

		if (vectorForPrinting.at(i).boatAtLeft == true)
		{
			std::cout << "|(M=" << vectorForPrinting.at(i).missionariesOnTheBoat
				<< ", C=" << vectorForPrinting.at(i).cannibalsOnTheBoat << ")      |";
		}

		if (vectorForPrinting.at(i).boatAtLeft == false)
		{
			std::cout << "|      (M=" << vectorForPrinting.at(i).missionariesOnTheBoat
				<< ", C=" << vectorForPrinting.at(i).cannibalsOnTheBoat << ")|";
		}

		//Print out the people on the left shore
		std::cout << "(M=" << vectorForPrinting.at(i).missionariesOnTheRight << ", C="
			<< vectorForPrinting.at(i).cannibalsOnTheRight << ")";
		std::cout << "\n          |                |\n"; 
	}
}

//Use recursion to trace back to the starting state. This is actually called a 
//spaghetti stack: https://en.wikipedia.org/wiki/Parent_pointer_tree (hahaha).
//So we recurse until we find the root. 
void parentFinder(state inputState, std::vector<state> parentVector,
	std::vector<state> & vectorForPrinting)
{
	state parentState = *(inputState.parentPtr);

	if (parentState == startState)
	{
		vectorForPrinting.push_back(startState);
	} 
	else if (inputState.hasBeenVisited == true)
	{
		vectorForPrinting.push_back(parentState);
		parentFinder(parentState, parentVector, vectorForPrinting);
	}
}

