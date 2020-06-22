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
Predicate Predicate_copy(Predicate& p) {
	Predicate pnew;
	pnew.isExclusive=p.isExclusive;
	//TODO copy each arg
	return pnew;
}




//for eachISA, copy in each of the parent's propertes
//(don't recurse to grandparents, assume the parent already did that)
//(NB this can introduce contradictins, both with existing properties and with multuple inheritence)
void inheritPropertiesFromIsas(Substance s) {
	cout << "inheriting..." << endl;
	for (auto& kv : s.properties) {       //key value pair
		if (kv.first=="ISA") {         //convention: special pred names in caps
			cout << "found ISA" << kv.first  << endl;
			Argument& a = kv.second.arguments["parent"];
			Substance* parent = (Substance*)(a.val_substancePtr);
			
			for (auto& kvp : parent->properties) {   
				cout << "parent prop" << kvp.first << endl;
				//TODO copy it (including if its an ISA?)
				//pnew = Predicate_copy(p);
				//s.propertes.insert(pnew);
			}			
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


int main( int argc, char* args[] ) {

	//create a substance and give it a property predicate
	Substance cow = Substance_init();

	Predicate cow_age = Predicate_init(); 
	Argument cow_age_arg0;
	cow_age_arg0.val_int = 10;
	cow_age.arguments.insert(pair<string, Argument>(string("number_of_years"), cow_age_arg0));
	Substance_addProperty(cow, cow_age, string("age"));


	Predicate cow_legs = Predicate_init(); 
	Argument cow_legs_arg0;
	cow_legs_arg0.val_int = 4;
	cow_age.arguments.insert(pair<string, Argument>(string("number_of_legs"), cow_legs_arg0));
	Substance_addProperty(cow, cow_legs, string("legs"));

	//recover a property predicate, an argument from it, and cast the argument to a pre-known type.
	Predicate pp = cow.properties["age"];
	Argument arg0 = pp.arguments["number_of_years"];
	cout << arg0.val_int << endl;


	Substance fresian = Substance_init();

	Predicate fresian_ISA1 = Predicate_init(); 
	Argument fresian_isa0_arg0;
	fresian_isa0_arg0.val_substancePtr = (void*)(&cow);
	fresian_ISA1.arguments.insert(pair<string, Argument>(string("parent"), fresian_isa0_arg0));
	Substance_addProperty(fresian, fresian_ISA1, string("ISA"));

	Predicate fresian_age = Predicate_init(); 
	Argument fresian_age_arg0;
	fresian_age_arg0.val_int = 5;
	fresian_age.arguments.insert(pair<string, Argument>(string("number_of_years"), fresian_age_arg0));
	Substance_addProperty(fresian, fresian_age, string("age"));


	inheritPropertiesFromIsas(fresian);


	cout << "---" << endl;
	for (auto& kv : fresian.properties) {
		cout << "x" << kv.first << endl;
	}

}
