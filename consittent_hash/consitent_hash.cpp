#include <string>
#include <algorithm>
#include <map>
#include <time.h>
#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
	string server_name;
	int replicas;
	Node();
 	Node(string name, int rep);
 	
};

Node::Node(void) : server_name(), replicas(0)
{

}

Node::Node(string name, int rep) : server_name(name), replicas(rep)
{

}


class HashRing
{
public:
    map<size_t, Node> hash_ring;	//hash_value ---> hash_ndoe
	void node_add(Node &node);
	void node_delete(Node &node);
	Node get_server_node(string &key);
};


void HashRing::node_add(Node &node)
{
	string node_name = node.server_name;

	for(int i=0; i<node.replicas; i++)
	{
		string vnode_name = node_name + "num" + std::to_string(i);
		size_t hash_value = std::hash<std::string>()(vnode_name);
		hash_ring[hash_value] = node;
	}
}

void HashRing::node_delete(Node &node)
{
	string node_name = node.server_name;

	for(int i=0; i<node.replicas; i++)
	{
		string vnode_name = node_name + "num"+ std::to_string(i);
		size_t hash_value = std::hash<std::string>()(vnode_name);
		hash_ring.erase(hash_value);
	}
}

Node HashRing::get_server_node(string &key)
{
	if(this->hash_ring.empty())
	{
		return Node("",0); 
	}
	size_t hash_value = std::hash<std::string>()(key);  

	map<size_t, Node>::iterator it = this->hash_ring.upper_bound(hash_value);
	if(it == this->hash_ring.end()) it=this->hash_ring.begin();
	return it->second;
}

int rand_number(int low, int high)
{
	return rand()%(high-low)+low;
}

std::string rand_string()
{
	std::string str = "";

	 int len = rand_number(10,50);

	 for(int i=0; i<len; i++)
	 {
	 	char s;
	 	if(i&2) s = rand_number('a', 'z');
	 	else s = rand_number('A', 'Z');
	 	str = str + s;
	 }
	return str;
}

int main()
{

	int move_count = 0;
	Node delete_node ;
	map<string, int > node_stat;
	node_stat.clear();

	srand(time(0));

	HashRing ring;
	HashRing new_ring;

	for(int i=0; i<100; i++)
	{
		Node node(rand_string(), 100);
		ring.node_add(node);
		new_ring.node_add(node);
		if(i == 2) delete_node = node;
	}

	new_ring.node_delete(delete_node);


	for(int i=0; i<100000; i++)
	{
		string str = rand_string();
		Node node1 = ring.get_server_node(str);
		Node node2 = new_ring.get_server_node(str);

		node_stat[node1.server_name]++;

		if(node1.server_name != node2.server_name)
		{
			move_count++;
		}
	}
	
	printf("the move percent is %lf\n", 1.0*move_count/100000); 

	printf("hash distribution situation ");
	for(map<string,int>::iterator it = node_stat.begin(); it!=node_stat.end(); it++)
	{
		printf("%d ", node_stat[it->first]);
	} 
	
	printf("\n");
	return 0;
}
