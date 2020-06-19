#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Ontology.h"
using namespace std;

Substance Substance_init() {
	Substance s;
	return s;
}
Predicate Predicate_init() {
	Predicate p;
	return p;
}
Int Int_init(int i) {
	Int x;
	x.val=i;
	return x;
}
Float Float_init(float f) {
	Float x;
	x.val=f;
	return x;
}
std::string Int::toString() {
	return string("hh");
}
std::string Float::toString() {
	return string("hh");
}
std::string SubstanceName::toString() {
	return string("hh");
}


int main( int argc, char* args[] ) {

	//create a substance and give it a property predicate
	Substance cow = Substance_init();
	Predicate cow_age = Predicate_init(); 
	Int cow_age_int = Int_init(45);
	cow_age.arguments.insert(pair<string, Argument*>(string("number_of_years"), (Argument*) &cow_age_int));
	cow.properties.insert(pair<string, Predicate>(string("age"), cow_age));

	//recover a property predicate, an argument from it, and cast the argument to a pre-known type.
	Predicate pp = cow.properties["age"];
	Argument* arg0 = pp.arguments["number_of_years"];
	cout << arg0 << endl;
	cout << ((Int*)arg0)->val << endl;

	Substance farmer = Substance_init();
}
