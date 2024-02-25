#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct frame
{
	int data;
	int error;
	int frame_no;
};

class receiver
{
	private:
		int sf;
		int n;
		int *frames;
	public:
		receiver()
		{
			sf = n = 0;
			frames = new int[100];
		}
		frame* receive(frame *f,int size,int start)
		{
			int i=0;
			sf = start;
			while(i<size)
			{
				if(f[i].error!=0)
				{
					if(f[i].error == 1)
						cout<<"Transfer error in frame"<<i+sf+1<<endl;
					else
					{
						for(int i=0 ; i<200000000 ; i++);
						cout<<"Timeout error in frame"<<i+sf+1<<endl;
					}
				}
				i++;
			}
			i=start;
			while(f[i].error == 0 && i<size)
			{
				frames[sf++] = f[i].data;
				i++;
			}
			return f;
		}
};

class sender
{
	private:
		int n;
		int *frames;
		int sn;
		int sf;
		int winsn;
	public:
		sender()
		{
			n = sn = sf = 0;
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
		void send(receiver r)
		{
			srand(time(0));
			bool cansend = true;
			frame *f;
			while(sf<n)
			{
				cout<<"Window : ";
				for(int j=sf ; j<min(4,n-sf)+sf ; j++)
					cout<<frames[j]<<"\t";
				cout<<endl;
				int size = rand()%4+1;
				size = min(size,n-sf);
				f = new frame[size];
				for(int i=0 ; i<size ; i++)
				{
					f[i].data = frames[sf+i];
					f[i].error = rand() % 3;
				}
				r.receive(f,size,sf);
				int start = 0;
				for(int i=0 ; i<size; i++)
				{
					if(f[i].error!=0)
					{
						break;
					}
					else
					{
						sf++;
					}
				}
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
