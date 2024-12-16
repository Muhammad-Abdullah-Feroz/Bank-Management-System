#include <iostream>
#include <string>
#include <fstream>
#include <climits>
using namespace std;

class ListNode
{
public:
    string data;
    int weight;
    ListNode *next;

    ListNode(const string &data, int weight) : data(data), weight(weight), next(nullptr) {}
};

class CustomList
{
private:
    ListNode *head;

public:
    CustomList() : head(nullptr) {}

    void add(const string &data, int weight)
    {
        if (!head)
        {
            head = new ListNode(data, weight);
        }
        else
        {
            ListNode *current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = new ListNode(data, weight);
        }
    }

    bool contains(const string &data) const
    {
        ListNode *current = head;
        while (current)
        {
            if (current->data == data)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(const string &data)
    {
        if (!head)
            return;

        if (head->data == data)
        {
            ListNode *toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        ListNode *current = head;
        while (current->next && current->next->data != data)
        {
            current = current->next;
        }

        if (current->next)
        {
            ListNode *toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        }
    }

    void display() const
    {
        ListNode *current = head;
        while (current)
        {
            cout << "(" << current->data << ", weight: " << current->weight << ") ";
            current = current->next;
        }
    }

    ListNode *getHead() const
    {
        return head;
    }

    ~CustomList()
    {
        ListNode *current = head;
        while (current)
        {
            ListNode *toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

// BankGraph class
class BankGraph
{
private:
    // Node class for branches
    class BranchNode
    {
    public:
        string branchName;
        CustomList connections;
        BranchNode *next;

        BranchNode(const string &name) : branchName(name), next(nullptr) {}
    };

    BranchNode *head;

    BranchNode *findBranchNode(const string &branchName) const
    {
        BranchNode *current = head;
        while (current)
        {
            if (current->branchName == branchName)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void removeConnectionsTo(const string &branchName)
    {
        BranchNode *current = head;
        while (current)
        {
            current->connections.remove(branchName);
            current = current->next;
        }
    }

    int findIndex(const string &branchName, string branchArray[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            if (branchArray[i] == branchName)
            {
                return i;
            }
        }
        return -1;
    }

    int extractMin(int distances[], bool visited[], int size)
    {
        int minIndex = -1;
        int minValue = INT_MAX;
        for (int i = 0; i < size; i++)
        {
            if (!visited[i] && distances[i] < minValue)
            {
                minValue = distances[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

public:
    BankGraph() : head(nullptr) {}

    void addBranch(const string &branchName)
    {
        cout<<endl<<"Adding Branch : "<<branchName;
        if (!findBranchNode(branchName))
        {
            BranchNode *newBranch = new BranchNode(branchName);
            newBranch->next = head;
            head = newBranch;
            cout<<endl<<"Branch Added Successfully";
        }
    }

    void addConnection(const string &branch1, const string &branch2, int weight)
    {
        addBranch(branch1);
        addBranch(branch2);

        BranchNode *node1 = findBranchNode(branch1);
        BranchNode *node2 = findBranchNode(branch2);

        if (node1 && !node1->connections.contains(branch2))
        {
            node1->connections.add(branch2, weight);
        }
        if (node2 && !node2->connections.contains(branch1))
        {
            node2->connections.add(branch1, weight);
        }
    }

    void removeBranch(const string &branchName)
    {
        removeConnectionsTo(branchName);

        if (!head)
            return;

        if (head->branchName == branchName)
        {
            BranchNode *toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        BranchNode *current = head;
        while (current->next && current->next->branchName != branchName)
        {
            current = current->next;
        }

        if (current->next)
        {
            BranchNode *toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        }
    }

    void displayGraph() const
    {
        BranchNode *current = head;
        while (current)
        {
            cout << current->branchName << " -> ";
            current->connections.display();
            cout << endl;
            current = current->next;
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void displayBranches() const
    {
        BranchNode* current = head;
        int count = 1;
        while(current){
            cout<<count<<" . "<<current->branchName<<endl;
            current = current->next;
            count++;
        }
    }

    bool exists(const string &branch){
        // bool exist = false;
        BranchNode* current = head;
        while(current){
            if(current->branchName == branch){
                return true;
            }
            current = current->next;
        }
        return false;
    }

    string& findBranch(int idx){
        int count = 0;
        BranchNode* current = head;
        while(current){
            count++;
            if(count == idx){
                return current->branchName;
            }
            current = current->next;

        }
        string *branch = new string ("");
        return *branch;
    }

    int shortestPath(const string &startBranch, const string &endBranch)
    {
        int size = 0;
        BranchNode *temp = head;
        while (temp)
        {
            size++;
            temp = temp->next;
        }

        string *branchArray = new string[size];
        int *distances = new int[size];
        bool *visited = new bool[size];
        string *previous = new string[size];

        temp = head;
        for (int i = 0; i < size; i++)
        {
            branchArray[i] = temp->branchName;
            distances[i] = INT_MAX;
            visited[i] = false;
            previous[i] = "";
            temp = temp->next;
        }

        int startIndex = findIndex(startBranch, branchArray, size);
        if (startIndex == -1)
        {
            cout << "Start branch not found." << endl;
            return -1;
        }

        distances[startIndex] = 0;

        // Dijkstra's Algorithm
        for (int i = 0; i < size; i++)
        {
            int currentIndex = extractMin(distances, visited, size);
            if (currentIndex == -1)
                break;

            visited[currentIndex] = true;
            string currentBranch = branchArray[currentIndex];

            BranchNode *currentNode = findBranchNode(currentBranch);
            if (currentNode)
            {
                ListNode *neighbor = currentNode->connections.getHead();
                while (neighbor)
                {
                    int neighborIndex = findIndex(neighbor->data, branchArray, size);
                    if (neighborIndex != -1 && !visited[neighborIndex] && distances[currentIndex] + neighbor->weight < distances[neighborIndex])
                    {
                        distances[neighborIndex] = distances[currentIndex] + neighbor->weight;
                        previous[neighborIndex] = currentBranch;
                    }
                    neighbor = neighbor->next;
                }
            }
        }

        // Find the index of the end branch
        int endIndex = findIndex(endBranch, branchArray, size);
        if (endIndex == -1 || distances[endIndex] == INT_MAX)
        {
            cout << "No path exists between " << startBranch << " and " << endBranch << "." << endl;
            return -1;
        }

        // Print shortest path
        cout << "Shortest path from " << startBranch << " to " << endBranch << " is " << distances[endIndex] << "." << endl;
        cout << "Path: ";

        string path = endBranch;
        string current = previous[endIndex];
        while (!current.empty())
        {
            path = current + " -> " + path;
            current = previous[findIndex(current, branchArray, size)];
        }

        cout << path << endl;
        return distances[endIndex];
    }

    void writeGraphToFile(const string &filename) const
    {
        ofstream file(filename);
        if (!file)
        {
            cout << "Error opening file for writing." << endl;
            return;
        }

        BranchNode *current = head;
        while (current)
        {
            file << current->branchName << endl;
            ListNode *neighbor = current->connections.getHead();
            while (neighbor)
            {
                file << neighbor->data << endl
                     << neighbor->weight << endl;
                neighbor = neighbor->next;
            }
            file << endl; // Newline to separate branches
            current = current->next;
        }

        file.close();
        cout << "Graph has been written to " << filename << endl;
    }

    void readGraphFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "Error opening file for reading." << endl;
            return;
        }

        string branchName;
        while (getline(file, branchName)) // Read branch name
        {
            cout << branchName << endl;
            addBranch(branchName); // Add the branch to the graph
            string neighborName;
            int weight;

            while (getline(file, neighborName)) 
            {
                if (neighborName.empty())
                    break; 

                file >> weight; 
                file.ignore(); 

                addConnection(branchName, neighborName, weight);
            }
        }

        file.close();
        cout << "Graph has been read from " << filename << endl;
    }

    ~BankGraph()
    {
        BranchNode *current = head;
        while (current)
        {
            BranchNode *toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};