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

int depthfirstsearch(graph);	//int
vertex* vertexwithsmallestindex(graph);
vertex* vertexwithlargestindex(graph);
vertex* addressofvertexwithlabel(int, graph);
void dfsSubAlgorithmSearchFor1VertexBranch(graph a, vertex* givenvertex, list<int>* verticesvisisted);


int main(void)
{
	graph wow;
	wow.AddVertex(1);
	wow.AddVertex(2);
	wow.AddVertex(3);
	wow.AddVertex(4);
	wow.AddEdge(1, 3);
	wow.AddEdge(1, 4);
	wow.AddEdge(3, 2);
	wow.AddEdge(2, 2);
	wow.AddEdge(3, 4);
	int finishcode = -2;
	finishcode = depthfirstsearch(wow);
	return finishcode;
}





int depthfirstsearch(graph a)
{
	int** verticesthatcanbereachedwithdfsfrom;
	verticesthatcanbereachedwithdfsfrom = new int* [a.numberofvertices()];
	for (int i = 0; i < a.numberofvertices(); i++)
	{
		verticesthatcanbereachedwithdfsfrom[i] = new int[a.numberofvertices()];
	}
	int nextentrytoarrayat = 0;
	list<int> verticesvisited;
	vertex* startingvertex = vertexwithsmallestindex(a);
	if (!startingvertex)
	{
		cout << "The given graph does not have any vertices." << endl;
		return 0;
	}
	cout << endl << "Beginning search. Visited: " << startingvertex->label;
	verticesvisited.emplace_back(startingvertex->label);  	verticesthatcanbereachedwithdfsfrom[0][nextentrytoarrayat] = startingvertex->label; nextentrytoarrayat++;
	//if (searchfor == startingvertex->label)
	//{
	//	return startingvertex;
	//}
	for (int j = 0; j < startingvertex->edgesgoto.size();j++)
	{
		vertex* temp= startingvertex;
		for (int i = 0; i < a.numberofvertices(); i++)
		{
			startingvertex->edgesgoto.sort();
			//		if (find(verticesvisited.begin(),verticesvisited.end(),startingvertex->label)==verticesvisited.end())
			//		{
			int smallestconnectedlabel = startingvertex->label;		//remember that startingvertex = vertexwithsmallestindex(a);
			bool firsttimerunninginthisloop = true;
			//		}
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
			if (!smallestconnectedlabel || smallestconnectedlabel== ((vertexwithlargestindex(a)->label) + 1))
			{
				startingvertex = startingvertex->next;
				break;
			}
			if (!(find(verticesvisited.begin(), verticesvisited.end(), smallestconnectedlabel) == verticesvisited.end())) //The vertice only has no connected vertex other than itself, if any (since it's run for cehcking if an element has been found for the first time after placing the first element).
			{
				startingvertex = startingvertex->next;//just in case we'll need to refer to the next vertice which we haven't changed yet.
				break; //closes the loop so that the next lines don't cause the glitch of finding a vertex which has already been found.
			}
			startingvertex = addressofvertexwithlabel(smallestconnectedlabel, a); verticesvisited.emplace_back(startingvertex->label); //this sets the loop's next iteration to work on the smallest connected vertex we just found in this iteration 
			cout << ", " << startingvertex->label;	//prints the vertex label we just found.
		}
		startingvertex = temp;
	}
	nextentrytoarrayat = 0;
	vertex* temp = a.head;
	//while (temp)
	//{
	//	if ((find(verticesvisited.begin(), verticesvisited.end(),temp->label) == verticesvisited.end()))
	//	{
	//		verticesvisited.emplace_back(startingvertex->label);
	//		cout << ", " << startingvertex->label;
	//		temp = temp->next;
	//	}
	//	else
	//	{
	//		temp = temp->next;
	//		continue;
	//	}
	//}
	list<int>remainingverticestovisit;
	while (temp)
	{
		if ((find(verticesvisited.begin(), verticesvisited.end(), temp->label) == verticesvisited.end()))
		{
			remainingverticestovisit.emplace_back(temp->label);
			//TODAY: write loop to make sure that the connected component for each such vertex is also added to the remaining vertices.
			temp = temp->next;
		}
		else
		{
			temp = temp->next;
			continue;
		}
	}
	remainingverticestovisit.sort();
	for (auto itr = remainingverticestovisit.begin(); itr != remainingverticestovisit.end(); itr++)
	{
		bool alreadypartofcollection = false;
		if (find(verticesvisited.begin(), verticesvisited.end(), *itr) == verticesvisited.end())//this loop is only entered when the vertice hasn't been visited
		{
			for (auto it = addressofvertexwithlabel(*itr, a)->edgesgoto.begin(); it != addressofvertexwithlabel(*itr, a)->edgesgoto.end(); it++)
			{
				if (find(verticesvisited.begin(), verticesvisited.end(), *it) != verticesvisited.end())
				{
					alreadypartofcollection = true;
					break; //not neccessary but saves resources  because extra iterations just don't happen.
				}
			}
			if (!alreadypartofcollection)
			{

			}

			verticesvisited.emplace_back(*itr); cout << ", " << (*itr);
			dfsSubAlgorithmSearchFor1VertexBranch(a, addressofvertexwithlabel(*itr, a), &verticesvisited);
		}
	}
	cout << '.' << endl;
	return 0;
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


void dfsSubAlgorithmSearchFor1VertexBranch(graph a, vertex* givenvertex,list<int>* verticesvisited)
{
	for (int j = 0; j < givenvertex->edgesgoto.size(); j++)
	{
		vertex* temp = givenvertex;
		for (int i = 0; i < a.numberofvertices(); i++)
		{
			givenvertex->edgesgoto.sort();
			if (givenvertex->edgesgoto.empty())
			{
				break;
			}
			int smallestconnectedlabel = givenvertex->label;		//remember that startingvertex = vertexwithsmallestindex(a);
			bool firsttimerunninginthisloop = true;
			for (auto itr = givenvertex->edgesgoto.begin(); itr != givenvertex->edgesgoto.end(); itr++) //selects the smallest connected label for the first element
			{
				if (firsttimerunninginthisloop)		//this loop ensures that if the current vertice is smaller than it's elements, even then only the smallest element connected to it is picked, not the current vertice itself
				{
					smallestconnectedlabel = ((vertexwithlargestindex(a)->label) + 1); //ensures that if no vertices are connected we can detect it while not breaking the rest of the part for finding the smallest connected label. 
					firsttimerunninginthisloop = false;
				}
				if (((*itr) < smallestconnectedlabel) && (find(verticesvisited->begin(), verticesvisited->end(), *itr) == verticesvisited->end())) //checks if it's smaller than last value of smallestconnectedlabel and hasn't been found already.
				{
					smallestconnectedlabel = (*itr);		//sets smallest connected vertex which hasn't already been found
				}
			}
			if (!smallestconnectedlabel || smallestconnectedlabel == ((vertexwithlargestindex(a)->label) + 1))
			{
				givenvertex = givenvertex->next;
				break;
			}
			if (!(find(verticesvisited->begin(), verticesvisited->end(), smallestconnectedlabel) == verticesvisited->end())) //The vertice only has no connected vertex other than itself, if any (since it's run for cehcking if an element has been found for the first time after placing the first element).
			{
				givenvertex = givenvertex->next;//just in case we'll need to refer to the next vertice which we haven't changed yet.
				break; //closes the loop so that the next lines don't cause the glitch of finding a vertex which has already been found.
			}
			givenvertex = addressofvertexwithlabel(smallestconnectedlabel, a); verticesvisited->emplace_back(givenvertex->label); //this sets the loop's next iteration to work on the smallest connected vertex we just found in this iteration 
			cout << ", " << givenvertex->label;	//prints the vertex label we just found.
		}
		givenvertex = temp;
	}
}