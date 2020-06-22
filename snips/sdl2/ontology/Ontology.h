#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <map>
using namespace std;
struct substance;    //predeclare to enable circule refs

//nice use of union, to avoud thinking about cpp classes and OOP. Union is purely an area of computer memory.
union Argument {
	int val_int;
	float val_float;
	void* val_substancePtr;   //TODO how to give a circular substance* here ?
};

typedef struct{
	bool isExclusive;
	std::map<string, Argument> arguments;
} Predicate;

typedef struct substance {
	std::map<string, Predicate> properties;
} Substance;


/*
//(maybe we actually need the world to become global like bush said?)
typedef struct{
	std::vector<Substance*> substances;
} World;
*/

/*
typedef struct{
	int senderSubstanceID;
	int msgType;
} msg;
*/

