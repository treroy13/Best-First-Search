#include<iostream>
#include<fstream>
#include<string>
#include <stdio.h>   
#include <stdlib.h>
#include<vector>
#include<sstream>
#include <cstring>
#include <limits>
#include <algorithm>  
#include <queue> 

using namespace std;

struct Sack{

	int weight =0; //weight of the item
	int profit=0; //profit of the item 

};

struct Node{

	int index; //index of node in array	
	int profit; //sum of profits of all items included in knapsack
	int upperBound; //max benefit found by expanding whole subtree of state space tree
	int weight; //sum of weights of all items included in knapsack
	vector<int>opt; //holds all the instances child was used

	bool operator<(const Node &rhs) const{
		return (upperBound < rhs.bound);
	}

};
/*bool compSack has parameters Sack one and Sack two. This function finds the largest of two Items based on the profit/weight and returns the larger of the two Items.*/
bool compSack(Sack one, Sack two){

	bool ret = false;
	double a;
	double b;

	a = (double) one.profit / one.weight;
	b = (double) two.profit / two.weight;

	return a > b;
	
}
/* int UpperBound takes in the max capacity, the size of the array thats holding all the items, the array of items, and the node we're considering. We calculate the upper bound to check if the node is promising. Int p is the bound that will be returned. Count includes value from all the indexes. And w is equal to the nodes weight.*/
//finds the upper bound on highest prof
int upperBound(int size, int C, Sack myItems[], Node first){

	if(first.weight >= C) //0 returned if weight is greater than C
		return 0; 

	int p = first.profit; //initialize p to current profit (p will be bound returned)
	int count = first.index + 1; //including items from all indexes 
	int w = first.weight;

	//not full items and more items
	while((count < size) && (w + myItems[count].weight <= C)){
		w+= myItems[count].weight;
		p+=myItems[count].profit;
		//cout<<"weight: "<<myItems[count].weight<<" profit: "<<myItems[count].profit<<endl;
		count++;
	}

        //add fraction of item into knapsack
	if(count < size){
		p = p+(C - w)*(myItems[count].profit/myItems[count].weight);
		//cout<<"weightF: "<<myItems[count].weight<<" profitF: "<<myItems[count].profit<<endl;
	} 
	 
	return p;
}


/*kwf has parameters for the max capacity, the size of the array of items, the array of items, and a string for the output file name. The capacity cannot be negative, the size of the array should be greater than 0 along with the items in the array. The string for the file should not be null. Int leaves is the amount of leaf nodes there are, path holds all the optimal nodes, temp is the total number of nodes, max is the max profit to be returned, node first and second are the nodes that are to be compared and queue myQ is the queue that holds all the nodes. This function creates an empty queue. While the queue is not empty, extract node first. Find the profit of the next node and if its larger than max, then update max. Next we compute the bound of the node and add it to the next node (called second) if its more than max. */
int kwf(int C, int size, Sack myItems[], string out){
	vector<Sack>path;//final optimal path
	int prom = 0;
	int nonProm = 0;
	Node first, second;
	priority_queue<Node> myQ; //queue used to go through all the nodes

	first.weight =0;
	first.index = 0;
	first.profit = 0;
	first.opt.resize(size,0);
	second.opt.resize(size,0);

	myQ.push(first); //push first dummy node into the queue

	//go through the tree and find the profits 
	while(!myQ.empty()){ //loop through the queue while its not empty
		temp++;
		first = myQ.top();
		myQ.pop(); //popping off the node (dequeing it)

		if(first.upperBound > max){
			second.index = first.index + 1; //find profit of child
			second.weight = first.weight + myItems[second.index-1].weight;
			second.profit = first.profit + myItems[second.index-1].profit;
			second.opt = first.opt;
			second.opt.at(second.index ) = 1;

			Sack it;
			//updating max if its greater than old profit
			if(second.weight <= C && second.profit > max){
				temp++;
				max = second.profit;
				it.weight = myItems[second.index].weight;

				it.profit = myItems[second.index].profit;
				path.push_back(it);
				cout<<"weight: "<<myItems[second.index].weight<<" profit: "<<myItems[second.index].profit<<endl;
			
			}

			second.upperBound = upperBound(size, C, myItems, second);


			//bound > profit so put back into queue
			if(second.upperBound > max)
				myQ.push(second);
			else
				leaves++;
		
			second.weight = first.weight;
			second.profit = first.profit;
			second.upperBound = upperBound(size, C, myItems, second);
			second.opt.at(second.index-1) = 0;

			if(second.upperBound > max)
				myQ.push(second);
			else
				leaves++;
		}
		else
			leaves++;


	}
	 
	//placing final values into the output file
	ofstream output;
	output.open(out);
	output<< size<<","<<max<<","<<path.size()<<endl;
	output<<temp<<","<<leaves<<endl;
	for(int i = 0; i< path.size(); i++){
		//if(path.at(1) == 1)
		output<<path[i].weight<<","<<path[i].profit<<endl; 

	}

	output.close();
	
	return max;
	

}


int main(int argc, char *argv[]){

	int count = 0;//counter used to retrieve size and c

	string strSize; //size of the problem
	string strSize1; //size of the problem
	string strC; // total weight limit

	int size = 0; //size of the problem
	int totalWeight = 0; // total weight limit	 		
	 
	//input filed retrieved from argv 
	ifstream input(argv[1]);

	 
	//open input file to get string size, c
	while (input){
	
		if (!getline( input, strSize )) 
			break;

		istringstream ss(strSize);

		while(ss){

			if(count <2){
				
				if(count == 0){
					
					if(!getline(ss,strSize, ',')){						 
						break;
					}
					 strSize1 = strSize;
					//cout<<"size1: "<<strSize<<endl;
				}
				else if(count == 1){
					if(!getline(ss,strSize, ',')){
						break;
					}

					strC = strSize;
					//cout<<"size2: "<<strC<<endl;
					count++;
					input.close();
					break;

				}
				else{

					break;
				}
				count++;
			}

			
		}
 
		 
	}

	Sack myItems[size];//an array called myItems that holds 
	int i = 0;
	 
	input.open(argv[1]); //open file
	input.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); //ignoring first line of file


		//parsing the file and putting values into struct/ array myItems
		while(input){
			string cNum;
   		        if (!getline( input, cNum )) 
				break;

   		        istringstream ss( cNum );

			while(ss){
				string cNum;
				if (!getline( ss, cNum, ',' ))
					break;		
				
				istringstream ( cNum ) >> myItems[i].weight;			
				
				if (!getline( ss, cNum, ',' )) 
					break;

				istringstream ( cNum ) >> myItems[i].profit;			 
			}
			i++;

		}
		
	
	input.close();

	
	//converting string size and totalWeight into ints 	
	stringstream convert(strSize1);
	stringstream convert2(strC);
	if( !(convert >> size))
		size = 0;	
	if( !(convert2 >> totalWeight))
		totalWeight = 0;
	
	sort(myItems, myItems + size,compSack); //sort the array 

	cout<<"Max: "<<kwf(totalWeight, size, myItems,argv[2])<<endl;

	
	
}
