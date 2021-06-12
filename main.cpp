#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"hdr.h"
using namespace std;


int main(){
	srand(time(NULL));
	Forum A("Object Oriented Programming");
	A.print();
	A.print_Thread("Rules and Tips");
	A.print_Post(get_random_id());
	A.print_sorted();
}
