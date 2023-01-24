#include <iostream>
#include <list>
using namespace std;
//#define MAXVERTICES 9999

struct vertex
{
	int label;
	list<int> edgesgoto; //was list<vertex> earlier
	vertex* next;
};

//struct vnode
//{
//	vertex vertex;
//	vnode* nextvn;
//};

class graph
{
public:
	//private:
	vertex* head = NULL;

	//public:

	void DisplayAdjacencyList()
	{
		if (!head)
		{
			cout << "The list is empty." << endl;
			return;
		}
		cout << endl << endl << "The adjacency list looks like:" << endl;
		vertex* temp = head;
		while (temp)
		{
			cout << temp->label << " : ";
			if (!(temp->edgesgoto.empty()))
			{
				for (auto it = temp->edgesgoto.begin(); it != temp->edgesgoto.end(); it++)
				{
					cout << " -> " << *it << ',';
				}
			}
			cout << endl;
			temp = temp->next;
		}
		cout << endl << endl;
	}

	void AddVertex(int newvlabel)
	{
		if (head)
		{
			vertex* temp = head;
			if (temp->label == newvlabel)
			{
				cout << "Vertices with the label already exists! No modifications made." << endl;
				return;
			}
			while (temp->next)
			{
				if (temp->label == newvlabel)
				{
					temp = temp->next;
					cout << "Vertices with the label already exists! No modifications made." << endl;
					return;
				}
				temp = temp->next;
			}
			vertex* toinsert = new vertex;
			toinsert->label = newvlabel;
			toinsert->next = NULL;
			//			toinsert->edgesgoto.begin
			temp->next = toinsert;
		}
		else
		{
			vertex* toinsert = new vertex;
			toinsert->label = newvlabel;
			toinsert->next = NULL;
			head = toinsert;
		}
		DisplayAdjacencyList();
	}


	void AddEdge(int a, int b)
	{
		if (!head)
		{
			cout << "There are no vertices in graph." << endl;
			return;
		}
		vertex* temp = head;
		bool bexists = false;
		vertex* apos = NULL;
		bool aexists = false;
		while (temp)
		{
			if (temp->label == a)
			{
				aexists = true;
				apos = temp;
			}
			if (temp->label == b)
			{
				bexists = true;
			}
			if (!(temp->next))
			{
				break;
			}
			temp = temp->next;
		}
		if (!aexists || !bexists)
		{
			cout << "At least one of the given vertices don't exist." << endl;
			return;
		}
		for (auto it = apos->edgesgoto.begin(); it != apos->edgesgoto.end(); it++)
		{
			if (*it == b)
			{
				cout << "The edge already exists." << endl;
				return;
			}
		}
		apos->edgesgoto.emplace_back(b);
		DisplayAdjacencyList();
	}

	void RemoveEdge(int a, int b)
	{
		if (!head)
		{
			cout << "There are no vertices in graph." << endl;
			return;
		}
		vertex* temp = head;
		bool bexists = false;
		vertex* apos = NULL;
		bool aexists = false;
		while (temp)
		{
			if (temp->label == a)
			{
				aexists = true;
				apos = temp;
			}
			if (temp->label == b)
			{
				bexists = true;
			}
			if (!(temp->next))
			{
				break;
			}
			temp = temp->next;
		}
		if (!aexists || !bexists)
		{
			cout << "At least one of the given vertices don't exist." << endl;
			return;
		}
		auto it = apos->edgesgoto.begin();
		for (; it != apos->edgesgoto.end(); it++)
		{
			if (*it == b)
			{
				cout << "Deleting the edge!" << endl;
				apos->edgesgoto.erase(it);
				DisplayAdjacencyList();
				return;
			}
		}
		//will only reach if edge not found:
		cout << "Such an edge does not exist" << endl;
	}

	void RemoveVertex(int newvlabel)
	{
		if (head)
		{
			vertex* temp = head;
			if (temp->label == newvlabel)
			{
				cout << "Removing the vertex." << endl;
				head = head->next;
				DisplayAdjacencyList();
				return;
			}
			vertex* previousvertex = head;
			while (temp->next)
			{
				if (temp->label == newvlabel)
				{
					temp = temp->next;
					cout << "Removing the vertex." << endl;
					previousvertex->next = temp->next; //maybe use delete here later for temp current

					DisplayAdjacencyList();
					return;
				}
				previousvertex = temp;
				temp = temp->next;
				if (!(temp->next))
				{
					cout << "No such vertex exists." << endl;
					return;
				}
			}

			vertex* toinsert = new vertex;
			toinsert->label = newvlabel;
			toinsert->next = NULL;
			//			toinsert->edgesgoto.begin
			temp->next = toinsert;
		}
		else
		{
			cout << "The list has no vertices." << endl;
			DisplayAdjacencyList();
		}
	}

	int numberofvertices()
	{
		if (!head)
		{
			return 0;
		}
		vertex* temp = head;
		int counter = 1;		//this is 1, not 0: because the next loop won't count last element
		while (temp->next)
		{
			counter++;
			temp = temp->next;
		}
		return counter;
	}
};



//end of graph implementation



//To Do: Make remove vertex remove all the connected edges; Since it's not needed here, I'll only fix it in lab 2; FIXED IT IN LAB 2 FILES;




bool containsEulerCycle(graph a);
bool  canGoToEveryOtherVertex(graph a, vertex* startingvertex);
vertex* vertexwithsmallestindex(graph);
vertex* vertexwithlargestindex(graph);
vertex* addressofvertexwithlabel(int, graph);
bool wholeGraphIsStrongyConnected(graph a);


int main(void)
{
	graph wow;
	wow.AddVertex(1);
	wow.AddVertex(2);
	wow.AddVertex(3);
	wow.AddVertex(4);
	wow.AddVertex(5);
	wow.AddEdge(1, 3);
	wow.AddEdge(1, 4);
	wow.AddEdge(2, 1);
	wow.AddEdge(3, 2);
	wow.AddEdge(3, 4);
	wow.AddEdge(4, 1);
	wow.AddEdge(4, 5);
	wow.AddEdge(5, 3);

	if (containsEulerCycle(wow))
	{
		cout<< endl << "Yes, the graph contains a directed Euler cycle." << endl;
	}
	else
	{
		cout << endl << "No, the graph does not contain a directed Euler cycle." << endl;
	}
	return 0;
}

bool containsEulerCycle(graph a)
{
	if (!wholeGraphIsStrongyConnected(a))
	{
		return false;
	}
	vertex* temp1 = a.head;
	vertex* temp2 = a.head; //since temp1 and temp2 both reference the same vertex at times, I will take special care not to modify any of them, and just read them.
	while (temp1) 
	{
		int incomingedges = 0;
		int outgoingedges = temp1->edgesgoto.size();
		while (temp2)//loop for tracking number of incoming edges to temp1 vertex
		{
			//if (temp2 == temp1) //commented this out because edgesgoto.size() would include a self attached edge.
			//{
			//	temp2 = temp2->next;
			//	continue;
			//}
			if (!(find(temp2->edgesgoto.begin(), temp2->edgesgoto.end(), temp1->label) == temp2->edgesgoto.end())) //only works when only one connection is allowed in each direction
			{
				incomingedges++;
			}
			temp2 = temp2->next;

		}
		if (outgoingedges != incomingedges)
		{
			return false;
		}
		temp1 = temp1->next;
	}
	return true;
}

bool wholeGraphIsStrongyConnected(graph a)
{
	vertex* temp = a.head;
	while (temp)
	{
		if (!(canGoToEveryOtherVertex(a, temp)))
		{
			return false;
		}
		temp = temp->next;
	}
	return true;
}


bool canGoToEveryOtherVertex(graph a, vertex* startingvertex)
{
	list<int> verticesvisited;
	if (!startingvertex)
	{
		cout << "Error: The program tried to pass null in the startingvertex field in the  canGoToEveryOtherVertex function." << endl;
		return false;
	}
	cout << endl << "Beginning search. Visited: " << startingvertex->label; //delete after debugging
	verticesvisited.emplace_back(startingvertex->label);
	for (int j = 0; j < startingvertex->edgesgoto.size(); j++)
	{
		vertex* temp = startingvertex;
		for (int i = 0; i < a.numberofvertices(); i++)
		{
			startingvertex->edgesgoto.sort();
			int smallestconnectedlabel = startingvertex->label;		//remember that startingvertex = vertexwithsmallestindex(a);
			bool firsttimerunninginthisloop = true;
			for (auto itr = startingvertex->edgesgoto.begin(); itr != startingvertex->edgesgoto.end(); itr++) //selects the smallest connected label for the first element
			{
				if (firsttimerunninginthisloop)		//this loop ensures that if the current vertice is smaller than it's elements, even then only the smallest element connected to it is picked, not the current vertice itself
				{
					smallestconnectedlabel = ((vertexwithlargestindex(a)->label) + 1); //ensures that if no vertices are connected we can detect it while not breaking the rest of the part for finding the smallest connected label. 
					firsttimerunninginthisloop = false;
				}
				if (((*itr) < smallestconnectedlabel) && (find(verticesvisited.begin(), verticesvisited.end(), *itr) == verticesvisited.end())) //checks if it's smaller than last value of smallestconnectedlabel and hasn't been found already.
				{
					smallestconnectedlabel = (*itr);		//sets smallest connected vertex which hasn't already been found
				}
			}
			if (!smallestconnectedlabel || smallestconnectedlabel == ((vertexwithlargestindex(a)->label) + 1))
			{
				break;
			}
			//if (!(find(verticesvisited.begin(), verticesvisited.end(), smallestconnectedlabel) == verticesvisited.end())) //The vertice only has no connected vertex other than itself, if any (since it's run for cehcking if an element has been found for the first time after placing the first element).
			//{
			//	startingvertex = startingvertex->next;//just in case we'll need to refer to the next vertice which we haven't changed yet.
			//	break; //closes the loop so that the next lines don't cause the glitch of finding a vertex which has already been found.
			//}
			startingvertex = addressofvertexwithlabel(smallestconnectedlabel, a); verticesvisited.emplace_back(startingvertex->label); //this sets the loop's next iteration to work on the smallest connected vertex we just found in this iteration 
			cout << ", " << startingvertex->label;	//prints the vertex label we just found.
		}
		startingvertex = temp;
	}
	//vertex* temp = a.head;
	//list<int>remainingverticestovisit;
	//while (temp)
	//{
	//	if ((find(verticesvisited.begin(), verticesvisited.end(), temp->label) == verticesvisited.end()))
	//	{
	//		remainingverticestovisit.emplace_back(temp->label);
	//		temp = temp->next;
	//	}
	//	else
	//	{
	//		temp = temp->next;
	//		continue;
	//	}
	//}
	//if (remainingverticestovisit.empty())
	//{
	//	return 0;
	//}
	if (verticesvisited.size() == a.numberofvertices())	//might need to debug
	{
		return true;
	}
	//could have put else here, but works the same way
	return false;
}

vertex* vertexwithsmallestindex(graph a)
{
	if (!a.head)
	{
		return NULL; // assuming indices have to be positive.
	}
	vertex* curr = a.head;
	vertex* minlabel = a.head;
	while (curr->next)
	{
		if (curr->label < minlabel->label)
		{
			minlabel = curr;
		}
		curr = curr->next;
	}
	return minlabel;
}

vertex* vertexwithlargestindex(graph a)
{
	if (!a.head)
	{
		return NULL; // assuming indices have to be positive.
	}
	vertex* curr = a.head;
	vertex* maxlabel = a.head;
	while (curr->next)
	{
		if (curr->label > maxlabel->label)
		{
			maxlabel = curr;
		}
		curr = curr->next;
	}
	if (curr->label > maxlabel->label)	//the upper loop misses the last vertex
	{
		maxlabel = curr;
	}
	return maxlabel;
}

vertex* addressofvertexwithlabel(int label, graph a)
{
	if (!a.head)
	{
		return NULL; // assuming indices have to be positive.
	}
	vertex* curr = a.head;
	vertex* vertexwithgivenlabel = NULL;
	while (curr->next && !vertexwithgivenlabel)
	{
		if (curr->label == label)
		{
			vertexwithgivenlabel = curr;
		}
		curr = curr->next;
	}
	if (curr->label == label)	//the upper loop misses the last vertex
	{
		vertexwithgivenlabel = curr;
	}
	return vertexwithgivenlabel;
}
