//Hidden Markov Model Solver
//Machine Input: State Transition Matrix
//               Symbol Spitting Para-Matrix
//               Symbol Spit
//Machine Output: State Transition String

#include <iostream>
#include <string>

using namespace std;

class markovModelSolver
{
	private:
	 string symbolSpit;
	 //string symbolStore;
	 float** transitionMatrix;
	 float** symbolParaMatrix;
	 int* stateTransitionArray;
	 bool initialStateBool;
	 int initialState;
	 int symbolCount;
	 int stateCount;
	 //void symbolStore(int);
	 bool markovStringCheck(string);
	 bool markovProbUnityCheck(float*, int);
	 void createStateTransitionString(void);

	public:
	 string stateTransition;
	 markovModelSolver()
	 {
		cout<<"\nEnter the no of states:\n";
		cin>>stateCount;
		while(stateCount<0)
		{
			cout<<"\nPlease input a value > 0:\n";
			cin>>stateCount;
		}

		cout<<"\nEnter the no of symbols:\n";
		cin>>symbolCount;
		while(symbolCount>26 || symbolCount<=0)
		{
			cout<<"\nPlease input a value < 26 & >0:\n";
			cin>>symbolCount;
		}

		//symbolStore(symbolCount);
		char ch;
		do
		{
			cout<<"\nWould you like to input an initial state?\n";
			cin>>ch;
			if(ch=='y'|| ch=='Y')
			{
				initialStateBool=true;
				cout<<"\nEnter the initial state:\n";
				cin>>initialState;
				while(!(initialState<stateCount&&initialState>=0))
				{
					cout<<"\nPlease input a value between 0 and "<<stateCount<<":\n";
					cin>>initialState;
				}
			}
			else if(ch=='n'||ch=='N')
			{
				initialStateBool=false;
				initialState=0;
			}
		}while(!(ch=='y'|| ch=='Y' || ch=='n'|| ch=='N'));
		

		transitionMatrix=new float*[stateCount];
		symbolParaMatrix=new float*[stateCount];
		for(int i=0;i<stateCount;i++)
		{
			transitionMatrix[i]=new float[stateCount];
			symbolParaMatrix[i]=new float[symbolCount];
		}

		for(int i=0;i<stateCount;i++)
		{
			do
			{
				for(int j=0;j<stateCount;j++)
				{
					cout<<"\nFill in the state transition matrix details for state "<<i<<":\n";
					cin>>transitionMatrix[i][j];
				}
			} while(!markovProbUnityCheck(transitionMatrix[i],stateCount));
		}
		for(int i=0;i<stateCount;i++)
		{
			do
			{
				for(int j=0;j<symbolCount;j++)
				{
					cout<<"\nFill in the symbol spit parameter matrix details for state "<<i<<":\n";
					cin>>symbolParaMatrix[i][j];
				}
			} while(!markovProbUnityCheck(symbolParaMatrix[i],symbolCount));
		}

		cout<<"\nEnter the symbol spit string:\n";
		cin>>symbolSpit;
		//cout<<"sexy";
		while(!markovStringCheck(symbolSpit))
		{
			cout<<"\nEnter a valid symbol spit string:\n";
			cin>>symbolSpit;
			cout<<"sexy2";
		}
		stateTransitionArray=new int[symbolSpit.length()];
		for(int i=0;i<symbolCount;i++)
                stateTransitionArray[i]=0;
	 }

	 ~markovModelSolver()
	 {
		//cout<<"Ending:";
		for(int i=0;i<stateCount;i++)
		{
			delete[] transitionMatrix[i];
			delete[] symbolParaMatrix[i];
		}
		delete[] transitionMatrix;
		delete[] symbolParaMatrix;
		delete[] stateTransitionArray;
	 }

	 void modelSolver(void);
};

int main()
{
    markovModelSolver _SOLVER;
    _SOLVER.modelSolver();
	return 0;
}

void markovModelSolver::modelSolver()
{
	//cout<<"sexy3";
	if(markovStringCheck(symbolSpit))
	{
		int stringLength=symbolSpit.length();
		if(!initialStateBool)
		{
			int currentSymbol= (int) symbolSpit[0]; currentSymbol-=65;
			float probHolder=0;float tempProbHolder=0;
			//cout<<"\n"<<currentSymbol<<"\n";
			for(int i=0;i<stateCount;i++)
			{
				tempProbHolder=symbolParaMatrix[i][currentSymbol];
				if(tempProbHolder>=probHolder)
				{
					probHolder=tempProbHolder;
					stateTransitionArray[0]=i;
					//cout<<"\nST:"<<stateTransitionArray[0]<<"\n";
				}
			}
		}
		else
		{
			stateTransitionArray[0]=initialState;
			//cout<<"\nST:"<<stateTransitionArray[0]<<"\n";
		}
		for(int i=1;i<stringLength;i++)
		{
			int currentSymbol= (int) symbolSpit[i]; currentSymbol-=65;
			//cout<<"\n"<<currentSymbol<<"\n";
			float probHolder=0; float tempProbHolder=0;
			for(int j=0;j<stateCount;j++)
			{
				//cout<<"\nEvaluating state "<<j<<"\n";
				//cout<<stateTransitionArray[i-1];
				int temp=stateTransitionArray[i-1];
				//cout<<"\n"<<transitionMatrix[temp][j]<<" "<<symbolParaMatrix[j][currentSymbol]<<"\n";
				tempProbHolder=transitionMatrix[temp][j]*symbolParaMatrix[j][currentSymbol];
				if(tempProbHolder>=probHolder)
				{
					probHolder=tempProbHolder;
					stateTransitionArray[i]=j;
					//cout<<"\nST:"<<stateTransitionArray[i]<<"\n";
				}
			}
		}
		cout<<symbolSpit;
		createStateTransitionString();
	}
}

void markovModelSolver::createStateTransitionString()
{
	for(int i=0;i<symbolCount;i++)
	{
		int temp=stateTransitionArray[i]; temp+=97;
		char tempChar=(char)temp;
		stateTransition.append(&tempChar);
	}
	cout<<"\n"<<stateTransition<<"\n";
	return;
}

bool markovModelSolver::markovStringCheck(string x)
{
	int stringLength=x.length();
	bool funcValue=false;
	for(int i=0;i<stringLength;i++)
	{
		char temp=x[i];
		//char temp2=symbolStore(i,1);
		if(!(temp<=65+symbolCount && temp>=65))
		{
		//if(temp==temp2)
			funcValue=false;
		}
		else funcValue=true;
	}
	return funcValue;
}

bool markovModelSolver::markovProbUnityCheck(float* checkArray, int checkArrayLength)
{
	float temp=0;
	for(int i=0;i<checkArrayLength;i++)
	{
		if(checkArray[i]<=1 && checkArray[i]>=0)
			temp+=checkArray[i];
	}
	if(temp==1)
		return true;
	else return false;
}



