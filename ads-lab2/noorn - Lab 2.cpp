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
{
private:
	vertex* head=NULL;

public:
	
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
					cout << " -> " << *it<<',';
				}
			}
			cout << endl;
			temp = temp->next;
		}
		cout << endl<<endl;
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
		vertex* apos=NULL;
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
			if (*it==b)
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
			if (*it==b)
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
			vertex* previousvertex=head;
			while (temp->next)
			{
				if (temp->label == newvlabel)
				{
					temp = temp->next;
					cout << "Removing the vertex." << endl;
					previousvertex->next = temp->next; //maybe use delete here later for temp current
					vertex* tmp2 = head;
					for (int i = 0; i < numberofvertices(); i++)
					{
						for (auto itr = tmp2->edgesgoto.begin(); itr !=tmp2->edgesgoto.end(); itr++)
						{
							if ((*itr)==newvlabel)
							{
								itr = tmp2->edgesgoto.erase(itr);
								break; //should remove when duplicate edges are allowed
							}
						}
						tmp2 = tmp2->next;
					}
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
			return;
		}
		else
		{
			cout << "The list has no vertices." << endl;
			DisplayAdjacencyList();
		}
	}


	//my useful additions:
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







int main(void)
{
	graph wow;
	wow.AddVertex(1);
	wow.AddVertex(5);
	wow.AddVertex(3);
	wow.AddEdge(1, 3);
	wow.RemoveEdge(1, 5);
	wow.AddEdge(5, 5);
	wow.AddVertex(1);
	wow.AddEdge(1, 5);
	wow.RemoveVertex(2);
	wow.RemoveEdge(1, 3);
	wow.RemoveVertex(3);

	//bonus test by me
	cout << endl << endl << "-------------------bonus test (removing 5 to check if edges are deleted):-----------------" << endl;
	wow.RemoveVertex(5);
}