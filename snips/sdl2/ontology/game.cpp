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




//(maybe we actually need the world to become global like bush said?)

//for eachISA, copy in each of the parent's propertes
//(don't recurse to grandparents, assume the parent already did that)
//(NB this can introduce contradictins, both with existing properties and with multuple inheritence)
void inheritPropertiesFromIsas(Substance s) {
	cout << "inheriting..." << endl;
	for (auto& kv : s.properties) {       //key value pair
		if (kv.first=="ISA") {         //convention: special pred names in caps
			cout << "found ISA" << kv.first  << endl;
			Argument* a = ((SubstanceName*)(kv.second.arguments["parent"]));
			Substance* parent = ((SubstanceName*)a)->pSubstance;
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
SubstanceName SubstanceName_init(Substance* sp) {
	SubstanceName x;
	x.pSubstance=sp;
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
	Int cow_age_int = Int_init(2);
	cow_age.arguments.insert(pair<string, Argument*>(string("number_of_years"), (Argument*) &cow_age_int));
	Substance_addProperty(cow, cow_age, string("age"));

	Predicate cow_legs = Predicate_init(); 
	Int cow_legs_int = Int_init(4);
	cow_age.arguments.insert(pair<string, Argument*>(string("number"), (Argument*) &cow_legs_int));
	Substance_addProperty(cow, cow_age, string("legs"));
	
	//recover a property predicate, an argument from it, and cast the argument to a pre-known type.
	Predicate pp = cow.properties["age"];
	Argument* arg0 = pp.arguments["number_of_years"];
	cout << arg0 << endl;
	cout << ((Int*)arg0)->val << endl;

	Substance fresian = Substance_init();

	Predicate fresian_ISA1 = Predicate_init(); 
	SubstanceName fresian_parent1 = SubstanceName_init(&cow);
	fresian_ISA1.arguments.insert(pair<string, Argument*>(string("parent"), (Argument*) &fresian_parent1));
	Substance_addProperty(fresian, fresian_ISA1, string("ISA"));

/*
	Predicate fresian_age = Predicate_init(); 
	Int fresian_age_int = Int_init(5);
	fresian_age.arguments.insert(pair<string, Argument*>(string("number_of_years"), (Argument*) &fresian_age_int));
	Substance_addProperty(fresian, fresian_age, string("age"));
*/

	inheritPropertiesFromIsas(fresian);



	cout << "---" << endl;
	for (auto& kv : fresian.properties) {
		cout << "x" << kv.first << endl;
	}

	union U {
		int val_int;
		float val_float;
		Substance* val_sp;
	};


}
