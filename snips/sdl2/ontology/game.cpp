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
Predicate Predicate_init(bool isExclusive=false) {
	Predicate p;
	p.isExclusive=isExclusive;
	return p;
}

void inheritPropertiesFromIsas(Substance s) {
	//TODO go through s's properties checking for isas
	//for each isa, copy in each of the parent's propertes
	//(don't recurse to grandparents, assume the parent already did that)
	//(NB this can introduce contradictins, both with existing properties and with multuple inheritence)
	for (auto& kv : s.properties) {       //key value pair
		cout << "x" << kv.first << endl;
		if (kv.first=="ISA") {         //convention: special pred names in caps
			//TODO need a pointer to the world to look up the parent ...
			//for each property in the parent, copy it
			//maybe we actually need the world to become global like bush said ...
		}
	}
}

void Substance_addProperty(Substance& s, Predicate p, string propertyName) {
	s.properties.insert(pair<string, Predicate>(propertyName, p));
	//not checking for contradictions, might want to call from here later
}

void resolveContradictions(Substance s) {
	//check s's properties for any contradictions, ie. exclusive properties with 2+ values
	//if this happens, remove all of them (as we can't infer anything)
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
	Substance_addProperty(cow, cow_age, string("age"));

	//recover a property predicate, an argument from it, and cast the argument to a pre-known type.
	Predicate pp = cow.properties["age"];
	Argument* arg0 = pp.arguments["number_of_years"];
	cout << arg0 << endl;
	cout << ((Int*)arg0)->val << endl;

	Substance farmer = Substance_init();



	for (auto& kv : cow.properties) {
		cout << "x" << kv.first << endl;
	}

}
