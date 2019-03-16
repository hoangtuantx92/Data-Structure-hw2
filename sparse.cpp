#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

struct node{
	double row;
	double column;
	double value;
	node *next;
	node *previous;
};

class matrix {
public:
	void readData(int count, ifstream &input);
	void print();
	matrix(); //default constructor;
	friend void addMatrix(matrix matrixA, matrix matrixB, ofstream &output); 
	friend void addMatrixRecursive(matrix matrixA, matrix matrixB, node *tempA, node *tempB, ofstream &output); 
	friend int checkSize(matrix matrixA, matrix matrixB);
	void sort (int count);
private:
	node *head;
	node *tail;
	node *n;
};


int main()
{
	int countA =0;
	int countB =0;
	ifstream inputA;
	ifstream inputB;
	ofstream output;
	string line;
	double check[3];
	for(int i=0; i<3; i++)
		check[i] = 0;
	int col;
	double temp = 0;
	matrix matrixA;
	matrix matrixB;

	inputA.open("a1.txt");
	if(inputA.fail())
	{
		cout<< "Error opening file.No file found" << endl;
		cout <<"Note that the program will halt" <<endl;
	}else if(inputA.peek() == std::ifstream::traits_type::eof())
	{
		cout << "File is empty" << endl;
		cout << "Note that program will halt" << endl; // error prompt
	}else
	{
	if(!inputA.eof())
	{
		while(getline(inputA,line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			istringstream ss(line);
			col = 0;
			while(ss >> temp)
			{
				check[col] = temp;
				col++;
			}
			if(check[0] < 1 || check[1] <1)
			{
				countA--;
			}
			countA++;
		}
	}
	inputA.close();



	inputB.open("b1.txt");
	if(!inputB.eof())
	{
		while(getline(inputB,line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			istringstream ss(line);
			col =0;
			while(ss >> temp)
			{
				check[col] = temp;
				col++;
			}
			if(check[0] < 1 || check[1] < 1)
			{
				countB--;
			}
			countB++;
		}
	}
	inputB.close();



	inputA.open("a1.txt");
	matrixA.readData(countA,inputA);
	inputA.close();

	inputB.open("b1.txt");
	matrixB.readData(countB,inputB);
	inputB.close();


	matrixA.sort(countA);
	matrixB.sort(countB);
	/*matrixA.print();
	matrixB.print();*/

	output.open("c.txt");
	if(checkSize(matrixA, matrixB) == 1)
	{
	node *tempA =NULL;
	node *tempB =NULL;

	addMatrixRecursive(matrixA,matrixB,tempA,tempB,output);
	
	//addMatrix(matrixA, matrixB,output);
	}else
	{
		cout<<"the two matrix is not compariable" <<endl;

	}
	output.close();
	}
	system("pause");
	return 0;
}

void matrix::readData(int count, ifstream &input)
{
	string line;
	double temp =0;
	int col;
	int row =0;
	double check[3];
	for(int i=0; i<3; i++)
		check[i] = 0;

	if(!input.eof())
	{
		while(getline(input,line))
		{
			if(line.empty() || line.at(0) == '#')
				continue;
			col =0;
			istringstream ss(line);
			
			while(ss>>temp)
			{
				check[col] = temp;
				col++;
			}
			if(check[0] <1 || check[1] <1)
			{
				row--;
			}else
			{
				n = new node;
				n->row = check[0];
				n->column= check[1];
				n ->value = check[2];

				if(row ==0)
				{
					n->previous= NULL;
					head = n ;
					tail = n;
					
				
				}else if(row == count - 1)
				{
					n->previous =tail;
					tail->next = n;
					tail = n;
					tail -> next = NULL;
			
				} else
				{
					n->previous = tail;
					tail ->next = n;
					tail = n;
					
				}
			}
			row++;
		}
	}
}

void matrix::print()
{
	node *temp;
	temp = head;

	while(temp !=NULL)
	{
		cout<< temp ->row << "   ";
		cout<<temp->column << "   ";
		cout << temp -> value<<endl;
		temp = temp ->next;
	}
	cout << endl;
}

matrix::matrix()
{
	head =NULL;
	n = NULL;
	tail =NULL;
}

void addMatrix(matrix matrixA, matrix matrixB, ofstream &output)
{
	node *tempA = matrixA.head;
	node *tempB = matrixB.head;
	
	while(tempA != NULL)
	{
		if(tempA->row > tempB ->row)
		{
			if(tempB -> value !=0)
			{
				output <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
				cout <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
			}
			tempB = tempB ->next;
		}
		else if (tempA ->row == tempB ->row && tempA -> column > tempB->column)
		{
			if(tempB -> value !=0)
			{
				output <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
				cout <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
			}
			tempB = tempB -> next;
		}
		else if (tempA ->row == tempB->row && tempA -> column == tempB ->column)
		{
			if(tempA -> value + tempB -> value != 0 || tempA ->next == NULL)
			{
				output <<setw(10)<<left<<tempB->row << " "<<setw(10) << left << tempB -> column << " " <<setw(10) << left<<fixed<<setprecision(2)<< tempA->value + tempB ->value<<setprecision(0)<<endl;
				cout <<setw(10)<<left<<tempB->row << " "<<setw(10) << left << tempB -> column << " " <<setw(10) << left<<fixed<<setprecision(2)<< tempA->value + tempB ->value<<setprecision(0)<<endl;
			}
			tempA = tempA->next;
			tempB = tempB ->next;
		} else
		{
			if(tempA ->value != 0)
			{
				output <<setw(10)<<left<<tempA->row<<" "<<setw(10)<< left << tempA -> column << " " << setw(10)<< left<<fixed<<setprecision(2)<<tempA ->value <<setprecision(0) <<endl;
				cout <<setw(10)<<left<<tempA->row<<" "<<setw(10)<< left << tempA -> column << " " << setw(10)<< left<<fixed<<setprecision(2)<<tempA ->value <<setprecision(0) <<endl;
			}
			tempA = tempA ->next;
		}
	}
}

void matrix::sort(int count)
{
	double tem =0;
	node *temp = head;
	
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<count-1;j++)
		{
			if(temp->row > temp->next->row)
			{
				tem = temp->next->row;
				temp->next -> row = temp ->row;
				temp ->row = tem;
				tem = temp->next ->column;
				temp->next -> column = temp ->column;
				temp ->column = tem;
				tem = temp->next ->value;
				temp->next -> value = temp ->value;
				temp->value = tem;
			}
			else if(temp ->row == temp->next ->row && temp ->column == temp->next ->column)
			{
				tem = temp->next ->column;
				temp->next -> column = temp ->column;
				temp ->column = tem;
				tem = temp->next ->value;
				temp->next -> value = temp ->value;
				temp->value = tem;
			}
			temp = temp ->next;
		}
		temp = head;
	}
}



void addMatrixRecursive(matrix matrixA, matrix matrixB, node *tempA, node *tempB,ofstream &output)
{
	tempA = matrixA.head;
	tempB = matrixB.head;

	if(tempA->next ==NULL && tempB->next ==NULL)
	{
		output << setw(10)<<left<<tempB->row << " "<<setw(10) << left << tempB -> column << " " <<setw(10) << left<<fixed<<setprecision(2)<< tempA->value + tempB ->value<<setprecision(0)<<endl;
		cout <<setw(10)<<left<<tempB->row << " "<<setw(10) << left << tempB -> column << " " <<setw(10) << left<<fixed<<setprecision(2)<< tempA->value + tempB ->value<<setprecision(0)<<endl;
	}
	else
	{
		if(tempA->row > tempB->row)
		{
			if(tempB -> value !=0)
			{
				output <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
				cout <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
			}
			matrixB.head = tempB ->next;
			addMatrixRecursive(matrixA, matrixB, tempA,tempB,output);
		}else if (tempA ->row == tempB ->row && tempA -> column > tempB->column)
		{
			if(tempB -> value !=0)
			{
				output <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
				cout <<setw(10) << left << tempB ->row <<" "<<setw(10) <<left << tempB -> column << " "<<setw(10)<<left <<fixed<<setprecision(2) <<tempB ->value <<setprecision(0)<<endl;
			}
			matrixB.head = tempB -> next;
			addMatrixRecursive(matrixA, matrixB, tempA,tempB,output);
		}
		else if (tempA ->row == tempB->row && tempA -> column == tempB ->column)
		{
			if(tempA -> value + tempB -> value != 0 || tempA ->next == NULL)
			{
				output <<setw(10)<<left<<tempB->row << " "<<setw(10) << left << tempB -> column << " " <<setw(10) << left<<fixed<<setprecision(2)<< tempA->value + tempB ->value<<setprecision(0)<<endl;
				cout <<setw(10)<<left<<tempB->row << " "<<setw(10) << left << tempB -> column << " " <<setw(10) << left<<fixed<<setprecision(2)<< tempA->value + tempB ->value<<setprecision(0)<<endl;
			}
			matrixA.head = tempA->next;
			matrixB.head = tempB ->next;
			addMatrixRecursive(matrixA, matrixB, tempA,tempB,output);
		} else
		{
			if(tempA ->value != 0)
			{
				output <<setw(10)<<left<<tempA->row<<" "<<setw(10)<< left << tempA -> column << " " << setw(10)<< left<<fixed<<setprecision(2)<<tempA ->value <<setprecision(0) <<endl;
				cout <<setw(10)<<left<<tempA->row<<" "<<setw(10)<< left << tempA -> column << " " << setw(10)<< left<<fixed<<setprecision(2)<<tempA ->value <<setprecision(0) <<endl;
			}
			matrixA.head = tempA ->next;
			addMatrixRecursive(matrixA, matrixB, tempA,tempB,output);
		}
	}
}

 int checkSize(matrix matrixA, matrix matrixB)
 {
	 if(matrixA.tail->row == matrixB.tail ->row && matrixA.tail->column == matrixB.tail ->column)
	 {
		 return 1;
	 }else
	 {
		 return 0;
	 }
 }