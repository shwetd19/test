#include<iostream>

using namespace std;

string xorfun( string encoded, string crc) {						//Bitwise XOR operation
	int crclen = crc.length();

	for ( int i = 0 ; i <= (encoded.length() - crclen) ; ) {
		for( int j=0 ; j < crclen ; j++) {
			encoded[i+j] = encoded[i+j] == crc[j] ? '0' : '1' ;
		}
		for( ; i< encoded.length() && encoded[i] != '1' ; i++) ;

	}

	return encoded;
}

int main() {
	string data, crc, encoded = "";
	cout << "SENDER SIDE" << endl;
	cout << "Enter the data: " << endl;
	cin>>data;

	cout<<"Enter the generator: "<<endl;
	cin>>crc;

	encoded += data;

	int datalen = data.length();
	int crclen = crc.length();

	for(int i=1 ; i <= (crclen - 1) ; i++)
		encoded += '0';

	encoded = xorfun(encoded, crc);

	cout<<"The checkbits generated are: ";
	cout<<encoded.substr(encoded.length() - crclen + 1)<<endl<<endl;
	cout<<"The message to be transmitted is: ";
	cout<<data + encoded.substr(encoded.length() - crclen + 1);




	cout<<endl<<"RECEIVER SIDE"<<endl;



	cout<<"Enter the message received: "<<endl;
	string msg;
	cin>>msg;

	msg = xorfun( msg, crc);												//bitwise xor is performed between received bits and the generator crc bits

	for( char i : msg.substr(msg.length() - crclen + 1))					//after performing xor , if the last few bits are zero then there's no error in transmission
		if( i != '0' ) {
			cout<<"Error in communication."<<endl;						//if bits not zero ; ERROR IN TRANSMISSION
			return 0;
		}

	cout<<"No Error in transmission!"<<endl;
	return 0;
}