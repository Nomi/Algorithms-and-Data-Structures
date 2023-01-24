#include <iostream>
#include <list>
using namespace std;

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
{public:
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
		vertex* temp=head;
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
//To Do: Make remove vertex remove all the connected edges; Since it's not needed here, I'll only fix it in lab 2;

int depthfirstsearch(graph);	//int
vertex* vertexwithsmallestindex(graph);
vertex* addressofvertexwithlabel(int,graph);



int main(void)
{
	graph wow;
	wow.AddVertex(1);
	wow.AddVertex(2);
	wow.AddVertex(3);
	wow.AddVertex(4);
	wow.AddVertex(5);
	wow.AddEdge(1,3 );
	wow.AddEdge(1,4 );
	wow.AddEdge(2, 3);
	wow.AddEdge(3, 2);
	wow.AddEdge(4, 3);
	int finishcode = -2;
	finishcode = depthfirstsearch(wow);
	return finishcode;
}





int depthfirstsearch(graph a) //intsearchfor
{
	list<int> verticesvisited;
	vertex* startingvertex = vertexwithsmallestindex(a);
	if (!startingvertex)
	{
		cout << "The given graph does not have any vertices." << endl;
		return -1;	//null earlier
	}
	cout << endl << "Beginning search. Visited: " << startingvertex->label; verticesvisited.emplace_back(startingvertex->label);
	//if (searchfor == startingvertex->label)
	//{
	//	return startingvertex;
	//}

	for (int i = 0;i<a.numberofvertices();i++)
	{
//		if (find(verticesvisited.begin(),verticesvisited.end(),startingvertex->label)==verticesvisited.end())
//		{
			int smallestconnectedlabel = startingvertex->label;
			bool firsttimerunninginthisloop = true;
//		}
		for (auto itr = startingvertex->edgesgoto.begin(); itr!=startingvertex->edgesgoto.end();itr++)
		{
			if (firsttimerunninginthisloop)
			{
				smallestconnectedlabel = startingvertex->edgesgoto.front();
				firsttimerunninginthisloop = false;

			}
			if (((*itr) < smallestconnectedlabel)&&(find(verticesvisited.begin(), verticesvisited.end(), *itr) == verticesvisited.end()))
			{
				smallestconnectedlabel = (*itr);
			}
		}
		if (!(find(verticesvisited.begin(), verticesvisited.end(), smallestconnectedlabel) == verticesvisited.end()))
		{
			startingvertex = startingvertex->next;
			break;
		}
		startingvertex=addressofvertexwithlabel(smallestconnectedlabel,a); verticesvisited.emplace_back(startingvertex->label);
		cout<<", "<<startingvertex->label;
	}
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
	list<int>remainingverticesvisited;
	while (temp)
	{
		if ((find(verticesvisited.begin(), verticesvisited.end(), temp->label) == verticesvisited.end()))
		{
			remainingverticesvisited.emplace_back(temp->label);
			temp = temp->next;
		}
		else
		{
			temp = temp->next;
			continue;
		}
	}
	remainingverticesvisited.sort();
	for (auto itr = remainingverticesvisited.begin(); itr != remainingverticesvisited.end(); itr++)
	{
		verticesvisited.emplace_back(*itr);
		cout << ", " << (*itr);
	}
	cout <<'.'<< endl;
	return 0;
}

vertex* vertexwithsmallestindex(graph a)
{
	if (!a.head)
	{
		return NULL; // assuming indices have to be positive.
	}
	vertex* curr=a.head;
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

vertex* addressofvertexwithlabel(int label, graph a)
{
	if (!a.head)
	{
		return NULL; // assuming indices have to be positive.
	}
	vertex* curr = a.head;
	vertex* vertexwithgivenlabel = NULL;
	while (curr->next&&!vertexwithgivenlabel)
	{
		if (curr->label==label)
		{
			vertexwithgivenlabel = curr;
		}
		curr = curr->next;
	}
	return vertexwithgivenlabel;
}