#include <iostream>
#include "trie.hh"
using namespace std;

int main()
{
    Trie * trie = new Trie();
    std::string input ="Hello";
    std::string input2 ="Hallaa";
    trie->insert(input.c_str(),input.size());
    std::cout << trie->find_edit_distance(input2.c_str(),input2.size(),4)<<std::endl;
    return 0;
}

