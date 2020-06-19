#include <SDL2/SDL.h>
#include <vector>

//My rules: OOP is not allowed for any ontological objects. 
//OOP is allowed only for computational objects.

//PhysicalSubstances are those which extend Aristotelian Substance with the ontology and laws of physics, ie space, time, motion, newton's laws.
//(other substances might not, eg. love, greenness, and Beethoven's 5th don't)

typedef struct{
	int senderSubstanceID;
	int msgType;
} msg;

typedef struct{
	int substanceID;
	int x;
	int y;
	int dx;
	int dy;
	int mass;
	int species;     //TODO this isnt physical, should be a property of Substabce not PhysicalSubstance. Need to create new model of Substance with list of properties to do right
			 // then all the properties of PhysicalSuvbsces should be modelled using that stucture rather than C's own structure members..
	SDL_Surface* costume;
} PhysicalSubstance;


typedef struct{
	std::vector<PhysicalSubstance*> physicalSubstances;
} PhysicalWorld;


typedef struct{
	PhysicalSubstance* physicalSubstance;
	int stamina;
} Farmer;

typedef struct{
	PhysicalSubstance* physicalSubstance;
	int stamina;
} Cow;
