#ifndef KEYVALUEPAIR_HXX
#define KEYVALUEPAIR_HXX
template <typename T>
struct keyvaluePair{
std::string key;
T value;
keyvaluePair *next;
};
#endif // KEYVALUEPAIR_HXX

