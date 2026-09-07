#include <vector>
#include <string>
using namespace std;

class Movie{
private:
    string title;
    string language;
    float duration;

public:
    Movie(string title, string language, float duration) :
        title(title), language(language), duration(duration) {}

    string getTitle() { return title; }
    string getLanguage() const { return language; }
    float getDuration() const { return duration; }
};