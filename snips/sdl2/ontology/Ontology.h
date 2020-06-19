#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <map>
using namespace std;
struct substance;    //predeclare to enable circule refs


class Argument {
	public:
		virtual std::string toString()=0;
};
class Int : public Argument {
	public:
		int val;
		virtual std::string toString();
};
class Float : public Argument {
	public:
		float val;
		virtual std::string toString();
};
class SubstanceName : public Argument {
	public:
		substance* pSubstance;
		virtual std::string toString();
};




//here pointers are used only to allow polymorphism on the arguments
typedef struct{
	bool isExclusive;
	std::map<string, Argument*> arguments;
} Predicate;

typedef struct substance {
	std::map<string, Predicate> properties;
} Substance;



typedef struct{
	std::vector<Substance*> substances;
} World;



typedef struct{
	int senderSubstanceID;
	int msgType;
} msg;



