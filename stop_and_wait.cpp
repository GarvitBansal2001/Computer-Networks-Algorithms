#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct frame
{
	int data;
	int error;
};

class receiver
{
	private:
		int *frames;
		int n;
	public:
		receiver()
		{
			n = 0;
			frames = new int[100];
		}
		bool receive(frame f)
		{
			if(f.error == 0)
			{
				frames[n++] = f.data;
				cout<<"Data received : "<<frames[n-1]<<endl;
				return true;
			}
			if(f.error == 1)
				cout<<"Errror in transfer of frame"<<n+1<<"!!"<<endl;
			else
			{
				for(int i=0 ; i<200000000 ; i++)
					;
				cout<<"Timer out error in frame"<<n+1<<"!!"<<endl;
			}
			return false;
		}
};

class sender
{
	private:
		int *frames;
		int n;
	public:
		sender()
		{
			n = 0;
			frames = new int[100];
		}
		void input()
		{
			cout<<"How many frames are there : ";
			cin>>n;
			for(int i=0 ; i<n ;)
			{
				cout<<"Enter data of frame "<<i+1<<"(in integers) : ";
				cin>>frames[i++];
			}
		}
		void send (receiver r)
		{
			srand(time(0));
			bool cansend = true;
			int i = 0;
			while(i<n)
			{
				frame f;
				if(cansend)
				{
					int error = rand() % 3;
					f.data = frames[i];
					f.error = error;
				}
				if(r.receive(f))
					i++;
			}
		}
};

int main()
{
	receiver r;
	sender s;
	s.input();
	s.send(r);
	return 0;
}
