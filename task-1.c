#include <iostream>
#include <fstream>
using namespace std;

int main() {
	int a,b,c;
	char filename[9];
	cout<<"Please input two numbers\n";
	cin>>a>>b;
	c=a*b;
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
    cout<<"c="<<c<<endl;
    cout<<"Please input file name:\n";
    cin>>filename;
    ofstream myfile(filename,ios::out);
    if(!myfile)
 {
  cout<<"error !";
 }
 else
 {
  myfile<<a<<"*"<<b<<"="<<c;
  myfile.close();
 }	
 system("pause");
 return 0;
}
