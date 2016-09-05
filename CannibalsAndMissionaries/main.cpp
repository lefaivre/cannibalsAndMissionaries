#include "state.h"

int main()
{
	//Perform the breadth first search by first passing in the startState
	std::queue<state> stateQueue;
	stateQueue.push(startState);
	breadthFirstSearch(stateQueue);
	
	return 0;
}


