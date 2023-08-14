#include<bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
/*
    less<int> -> ascending unique
    grater<int> -> descending unique
    less_equal<int> -> ascending with duplicates
    greater_equal<int> -> descending with duplicates

    Note:
    I noticed that using the comparison operator
    " less_equal <data_type> " makes the two functions
     " s.lower_bound(value) , s.upper_bound(value) "
    exchange their functions for any value,
    depending on that to erase one occurrence of some
    value from the set we can write
    " s.erase(s.upper_bound(value)) ",
    just that simple, it will work efficiently.
*/
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order, order_of_key

int main() {
    ordered_set A; // declaration

    // Inserting elements - 1st query
    A.insert(1);
    A.insert(10);
    A.insert(2);
    A.insert(7);
    A.insert(2);  // ordered set only contains unique values

    // A contains
    cout << "A = ";
    for (auto i : A)
        cout << i << " ";
    cout << endl;
    cout << endl;

    // finding kth element - 4th query
    cout << "0th element: " << *A.find_by_order(0) << endl;
    cout << "1st element: " << *A.find_by_order(1) << endl;
    cout << "2nd element: " << *A.find_by_order(2) << endl;
    cout << "3rd element: " << *A.find_by_order(3) << endl;
    cout << endl;

    // finding number of elements smaller than X - 3rd query
    cout << "No. of elems smaller than 6: " << A.order_of_key(6) << endl; // 2
    cout << "No. of elems smaller than 11: " << A.order_of_key(11) << endl; // 4
    cout << "No. of elems smaller than 1: " << A.order_of_key(1) << endl; // 0
    cout << endl;

    // lower bound -> Lower Bound of X = first element >= X in the set
    cout << "Lower Bound of 6: " << *A.lower_bound(6) << endl;
    cout << "Lower Bound of 2: " << *A.lower_bound(2) << endl;
    cout << endl;

    // Upper bound -> Upper Bound of X = first element > X in the set
    cout << "Upper Bound of 6: " << *A.upper_bound(6) << endl;
    cout << "Upper Bound of 1: " << *A.upper_bound(1) << endl;
    cout << endl;

    // // Remove elements - 2nd query
    // works with less<int> or greater<int>
    A.erase(1);
    // for less_equal<int> or greater_equal<int> use 
    // A.erase(A.upper_bound(1)); // remember that upper_bound works as lower bound mentioned int the start

    A.erase(11); // element that is not present is not affected

    // A contains
    cout << "A = ";
    for (auto i : A)
        cout << i << " ";
    cout << endl;
    return 0;
}