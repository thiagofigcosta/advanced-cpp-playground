#include <iostream>
#include <string>
#include <list>
#include <iterator>

using std::prev;
using std::cout;
using std::list;
using std::endl;
using std::next;
using std::distance;
using std::string;
using std::iter_swap;
using std::to_string;

struct Container {
    int priority;
    string person;

    auto ToString() {
        return "priority = " + to_string(priority) + ", person = " + person;
    }
};

void PrintList(list<Container> the_list){
    for (auto it = the_list.begin(); it!=the_list.end(); it++){
        cout << it->ToString() <<endl;
    }
}

void BubbleSort(list<Container> &the_list){
    for (auto it = the_list.begin(); it!=the_list.end(); it++){
        for (int i=0; i< distance(it, the_list.end())-1; i++){
            auto it_a = next(the_list.begin(), i);
            auto it_b = next(the_list.begin(), i+1);
            if (it_a->priority > it_b->priority){
                iter_swap(it_a, it_b);
            }
        }
    }
}

int main (){
    Container c0{0, "Thiago"};
    Container c1{5, "Jojo Toddynho"};
    Container c2{1, "Jorge Vercillo"};
    
    list<Container> l {c0, c1, c2};

    cout << c0.ToString();
    cout<<endl<<endl<<endl<<endl;
    PrintList(l);
    cout<<endl<<endl<<endl<<endl;
    BubbleSort(l);
    PrintList(l);
    return 0;
}