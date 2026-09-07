#include <string>
#include <vector>
using namespace std;

class Cinema{
private:
    // Encapsulation: cinema data is private.
    string name;
    vector<Screen*> screens; // Composition: Cinema owns its screens.

public:
    Cinema(string name) : name(name) {}

    ~Cinema(){
        for(Screen* s : screens){
                delete s;
        }
    }

    string getName() const { return name; }

    void addScreen(Screen* screen){
        screens.push_back(screen);
    }

    const vector<Screen*>& getScreens() const { return screens; }
};