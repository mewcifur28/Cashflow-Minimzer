/* header files */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

/*namespace declaration*/

using namespace std;

/* function declarations */

unordered_map<string, int> calculate_individual_amounts(int, int);
vector<string> minimize_cash_flow(unordered_map<string, int>);
void display_transactions(vector<string>);

/* main function */

int main() {
    
    int total_money = 0;
    int number_of_people = 0;

    cout << "Enter the total money spent: ";
    cin >> total_money;

    cout << "Enter the total number of people involved: ";
    cin >> number_of_people;

    unordered_map<string, int> transactions_graph = calculate_individual_amounts(total_money, number_of_people);
    vector<string> transaction_details = minimize_cash_flow(transactions_graph);
    display_transactions(transaction_details);

    return 0;
}
 
/* classes */

class multisetCompare {
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    }
};

/* function definitions */

unordered_map<string, int> calculate_individual_amounts(int total_money, int num_of_people) {

    unordered_map<string, int> transactions_graph;
    cout << "Enter the name of the person along with the amount spent by them:\nName\tAmount Spent\n";

    for (int i = 0; i < num_of_people; i++) {

        string name;
        int amount;
        cin >> name >> amount;

        transactions_graph[name] += amount - (total_money / num_of_people);
    }

    return transactions_graph;
}

void display_transactions(vector<string> transaction_details) {
    cout << "\nThe total number of transactions to be done are: " << transaction_details.size() << "\n";
    for (string transaction_detail: transaction_details) {
        cout << transaction_detail << "\n";
    }
}

vector<string> minimize_cash_flow(unordered_map<string, int> transactions_graph) {

    multiset<pair<string, int>, multisetCompare> ms;
    vector<string> transaction_details;

    for (pair<string, int> transaction: transactions_graph) {
        if (transaction.second != 0) {
            ms.insert(transaction);
        }
    }

    while (!ms.empty()) {
        auto left = ms.begin();
        auto right = prev(ms.end());

        int debit_amount = left->second;
        string debit_person = left->first;

        int credit_amount = right->second;
        string credit_person = right->first;

        ms.erase(left);
        ms.erase(right);

        int settled_amount = min(-debit_amount, credit_amount);

        debit_amount += settled_amount;
        credit_amount -= settled_amount;

        if (debit_amount != 0) {
            ms.insert({debit_person, debit_amount});
        }
        if (credit_amount != 0) {
            ms.insert({credit_person, credit_amount});
        }

        transaction_details.push_back(debit_person + " will give " + credit_person + " Rs." + to_string(settled_amount));
    }
    return transaction_details;
}