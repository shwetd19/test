#include<iostream>
#include<cstdlib>
#include<ctime>
#include<unistd.h>
#include<math.h>
#define TOT_FRAMES 500
#define FRAMES_SEND 10

using namespace std;

class stop_wait_arq {
	public:
		void execute() {
			srand(time(0));

			int frameNumber = 1, n;
			int receiverAck;

			cout << "Enter the number of frames: " << endl;
			cin >> n;
			while (frameNumber <= n) {
				sleep(1);
				cout << "Sender: Sending Frame " << frameNumber << endl;
				sleep(1);

				receiverAck = rand() % 2;
				if (receiverAck == 1) {
					cout << "Sender: Frame " << frameNumber << " Acknowledged by Receiver" << endl;
					frameNumber++;
				} else {
					cout << "Sender: Frame " << frameNumber << " Not Acknowledged, Resending..." << endl;
				}

				sleep(1);
			}
		}
};

class go_back_n_arq {
	public:
		void execute() {
			int n,N;
			int no = 0;
			srand(time(NULL));

			cout<<"Enter the number of frames: ";
			cin>>n;

			cout<<"Enter the window size: ";
			cin>>N;

			int i=1;
			while(i<=n) {
				int x=0;
				for(int j = i; j < i+N && j <= n; j++) {
					cout << "Sent frame " << j << endl;
					sleep(1);
					no++;
				}
				for(int j = i; j < i+N && j <= n; j++) {
					int flag = rand() % 2;
					if(!flag) {
						cout << "Acknowledgment for frame " << j << " received." << endl;
						sleep(1);
						x++;
					} else {
						cout << "Frame " << j << " not received." << endl;
						sleep(1);
						cout << "Retransmitting window" << endl;
						break;
					}
				}
				cout<<endl;
				i+=x;
			}
			cout << "Total number of transmissions: " << no << endl;
		}
};

class selective_repeat_arq {
	private:
		int f,N;

	public:
		void execute() {
			printf("Enter the number of bits for the sequence number: ");
			scanf("%d", &N);
			
			f=pow(2, N-1);
			
			for(int j = 0; j < f; j++) {
				printf("\nSender: Frame %d is sent.", j);
				sleep(1);
			}
			
			for(int i=0; i<f; i++) {
				printf("\n");
				int flag = rand() % 2;
				if(!flag) {
					printf("\nReceiver: Frame %d received correctly.\nAcknowledgement for Frame %d received.", i, i);
					sleep(1);
				} else {
					printf("\nReceiver: Frame %d received correctly.\nAcknowledgement for Frame %d lost.",i,i);
					printf("\nSender timeout.\nResending the frame...");
					sleep(1);
				}
			}
		}
};

int main() {
	selective_repeat_arq sr;
	stop_wait_arq st;
	go_back_n_arq gb;

	int ch=0;

	do {
		cout<<"\n1.Stop and Wait ARQ\n2.Go Back N ARQ\n3.Selective Repeat ARQ\n4.Exit\nEnter your choice: ";
		cin>>ch;
		switch(ch) {
			case 1:
				st.execute();
				break;
			case 2:
				gb.execute();
				break;
			case 3:
				sr.execute();
				break;
			default:
				cout<<"\nInvalid Choice. Please try again!";
		}
	} while(ch!=4);
}