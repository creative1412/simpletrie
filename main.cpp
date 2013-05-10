#include <iostream>

using namespace std;
class Trie {
public:
    struct Node {
        Node * parent;
        Node * next;
        Node * child;
        char ch;
        bool data;
        Node(Node * p, char c) : parent(p), next(NULL), child(NULL), ch(c), data(false) {
        }
    };
    typedef Node  node_type;
    node_type* root_;

    ~Trie() {
        /*TODO*/
    }

    void insert(const char* string, size_t length) {
        if (length > 0)
            insert(NULL, &root_, string, length);
    }

    bool findExact(const char* string, size_t length) const {
        if (length == 0 || !root_)
            return false;
        return findExact(root_, string, length);
    }

    bool find_hamming_distance(const char* string, size_t length, int distance ) const {
        bool appender=false;
        if (root_)
            find_hamming_distance(NULL, root_, string, length, distance, appender);
        return appender;
    }
    bool find_edit_distance(const char* string, size_t length, int distance) const {
        bool appender=false;
        if (root_)
            find_edit_distance(NULL, root_, string, length, distance, appender);
        return appender;
    }

private:
    void insert(node_type* parent, node_type** start, const char* string, size_t length) {
        node_type** current = start;

        for (; *current != NULL && (*current)->ch != *string; current = &((*current)->next));

        if (*current == NULL)
            *current = new node_type(parent, *string);

        if (length == 1) {
            (*current)->data = true;
        } else {
            insert(*current, &((*current)->child), string + 1, length - 1);
        }
    }

    bool findExact(node_type* start, const char* string, size_t length) const {
        node_type* current = start;

        for (; current != NULL && current->ch != *string; current = current->next);

        if (current == NULL)
            return false;

        if (length == 1) {
            return current->data;
        } else {
            return findExact(current->child, string + 1, length - 1);
        }
    }

    void find_hamming_distance(node_type* last, node_type* current, const char* string, size_t length, int distance, bool& appender) const {
        if (length == 0 && last && last->data){
            appender=true;
            return;
        }

        if (distance == 0 && length == 0)
            return;

        for (; current != NULL; current = current->next) {
            if (length > 0 && current->ch == *string)
                find_hamming_distance(current, current->child, string + 1, length - 1, distance, appender);

            if (distance > 0 && length > 0 && current->ch != *string)
                find_hamming_distance(current, current->child, string + 1, length - 1, distance - 1, appender);
        }
    }

    void find_edit_distance(node_type* last, node_type* current, const char* string, size_t length, int distance, bool &flag) const {
        if (length > 0 && distance > 0)
            find_edit_distance(last, current, string + 1, length - 1, distance - 1, flag);

        if (length == 0 && last && last->data){
            flag=true;
            return;
        }

        if (distance == 0 && length == 0)
            return;

        for (; current != NULL; current = current->next) {
            if (length > 0 && current->ch == *string)
                find_edit_distance(current, current->child, string + 1, length - 1, distance, flag);

            if (distance > 0 && length > 0 && current->ch != *string)
                find_edit_distance(current, current->child, string + 1, length - 1, distance - 1, flag);

            if (distance > 0)
                find_edit_distance(current, current->child, string, length, distance - 1, flag);
        }
    }

};



int main()
{
    Trie * trie = new Trie();
    std::string input ="Hello";
    std::string input2 ="Hallaa";
    trie->insert(input.c_str(),input.size());
    std::cout << trie->find_edit_distance(input2.c_str(),input2.size(),4)<< endl;
    return 0;
}

