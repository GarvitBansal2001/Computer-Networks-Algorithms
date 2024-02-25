//g(x) = x^3 + x
//r = 3

#include<iostream>

using namespace std;

void input (bool arr[])
{
	cout<<"Enter a 6 bit binary code(add space in between) : ";
	for(int i=0 ; i<9 ; i++)
		cin>>arr[i];
}

void display (bool arr[])
{
	cout<<"Code : ";
	for(int i=0 ; i<9 ; i++)
		cout<<arr[i];
}

void shift (bool arr[])
{
	for(int i=0 ; i<3 ; i++)
		arr[i] = arr[i+1];
}

void receiver (bool arr[])
{
	bool result[4];
	for(int i=0 ; i<4 ;i++)
		result[i] = arr[i];
	for(int i=4 ; i<9 ; i++)
	{
		while(result[0] == false && i<9)
		{
			shift(result);
			result[3] = arr[i];
			i++;
		}
		if(result[0] != false)
		{
			result[0] = result[0]^true;
			result[1] = result[1]^false;
			result[2] = result[2]^true;
			result[3] = result[3]^false;
			i--;
		}
	}
	bool flag = true;
	for(int i=0 ; i<4 ; i++)
		if(result[i] == true)
			flag = false;
	if(flag)
		cout<<"Successfull!!";
	else
		cout<<"Failed!!";
	
}

int main ()
{
	bool arr[9];
	input(arr);
	receiver(arr);
	return 0;
}
