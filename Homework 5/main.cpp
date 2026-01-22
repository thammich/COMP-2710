#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
#include <random>
using namespace std;

// Constants
const double A_accuracy = 1.0 / 3.0;
const double B_accuracy = 0.5;
const double C_accuracy = 1.0;
const int total_duels = 10000;

/*
shoot order
    aaron -> bob -> charlie (a -> b -> c)

strategy 1
    shoot the most accurate first

strategy 2
    aaron intentionally misses first shot
    continue strategy 1
*/
double generateChance(){
    static std::mt19937 rng(std::random_device{}());
    uniform_real_distribution<double> dist(0.0, 1.0);
    double randomValue = dist(rng);
     
    return randomValue;
}

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
 /*Checks to see whether any two of the three duelist are still alive.
   * Retures false if only one person is left
   */
    if(A_alive && B_alive){
        return true;
    }
    else if(A_alive && C_alive){
      return true;
    }
    else if(B_alive && C_alive){
      return true;
    }
    else{
      return false;
    }
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    //if charlie else bob
    double chance = generateChance();
    if(C_alive){
        if(chance < A_accuracy){
            C_alive = false;
        }
    }
    else if(B_alive){
        if(chance < A_accuracy){
            B_alive = false;
        }
    }
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
    //if charlie else aaron 
    double chance = generateChance();
    if(C_alive){
        if(chance < B_accuracy){
            C_alive = false;
        }
    }
    else if(A_alive){
        if(chance < B_accuracy){
            A_alive = false;
        }
    }
    
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {
    if(B_alive){
        B_alive = false;   
    }
    else if(A_alive){
        A_alive = false;
    }   
    
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    //if both bob and charlie are both alive aaron ittentionally misses
    double chance = generateChance();
    if(!B_alive && C_alive){
        if(chance < A_accuracy){
            C_alive= false;
        }
    }
    else if(B_alive && !C_alive){
        if(chance < A_accuracy){
            B_alive = false;
        }
    }
    
        
    
}
int simulate_strategy_1(bool A_alive, bool B_alive, bool C_alive){
    //return 1 if Aaron wins 
    //return 2 if Bob wins
    //return 3 if Charlie wins 
    
    
    while(at_least_two_alive(A_alive,B_alive,C_alive)){
        if(A_alive){
            Aaron_shoots1(B_alive, C_alive);
        }
        if(B_alive){
            Bob_shoots(A_alive, C_alive);
        }
        if(C_alive){
            Charlie_shoots(A_alive, B_alive);
        }
    }
    if(A_alive){
        return 1;
    }
    else if(B_alive){
        return 2;
    }
    else {
        return 3;
    }

}
int simulate_strategy_2(bool A_alive, bool B_alive, bool C_alive){
    Aaron_shoots2(B_alive,C_alive);
    if(B_alive){
        Bob_shoots(A_alive, C_alive);
        }
    if(C_alive){
        Charlie_shoots(A_alive,B_alive);
    }

    while(at_least_two_alive(A_alive, B_alive,C_alive)){
        if(A_alive){
            Aaron_shoots1(B_alive, C_alive);
        }
        if(B_alive){
            Bob_shoots(A_alive, C_alive);
        }
        if(C_alive){
            Charlie_shoots(A_alive,B_alive);
        }
    }
    if(A_alive){
        return 1;
    }
    else if(B_alive){
        return 2;
    }
    else {
        return 3;
    }

}

void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive ()\n";

    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";
    
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";

    cout << endl;
}

void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";

    // Case 1 Both Alive
    bool bob_alive = true;
    bool charlie_alive = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_alive, charlie_alive);
    // Since Aaron is shooting at Charlie Bob can not die
    assert(true == bob_alive);
    if (charlie_alive) {
        cout << "\t\tAaron misses.\n";
    } else {
        cout << "\t\tCharlie is dead.\n";
    }

    // Case 2 Bob Dead + Charlie Alive
    bob_alive = false;
    charlie_alive = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots1(bob_alive, charlie_alive);
    // Bob is already dead
    assert(false == bob_alive);
    if (charlie_alive) {
        cout << "\t\tAaron misses.\n"; 
    } else {
        cout << "\t\tCharlie is dead.\n";
    }

    // Case 3 Bob Alive + Charlie Dead
    bob_alive = true;
    charlie_alive = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    cout << "\t\tAaron is shooting at Bob\n";
    Aaron_shoots1(bob_alive, charlie_alive);
    // Charlie is already dead
    assert(false == charlie_alive);
    if (bob_alive) {
        cout << "\t\tAaron misses.\n";
    } else {
        cout << "\t\tBob is dead.\n";
    }

    cout << endl;
}

void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";

    // Case 1 Both Alive
    bool aaron_alive = true;
    bool charlie_alive = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    cout << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_alive, charlie_alive);
    // Since Bob is shooting at Charlie Aaron can not die
    assert(true == aaron_alive);
    if (charlie_alive) {
        cout << "\t\tBob misses.\n";
    } else {
        cout << "\t\tCharlie is dead.\n";
    }

    // Case 2 Aaron Dead + Charlie Alive
    aaron_alive = false;
    charlie_alive = true;
    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    cout << "\t\tBob is shooting at Charlie\n";
    Bob_shoots(aaron_alive, charlie_alive);
    // Aaron is already dead
    assert(false == aaron_alive);
    if (charlie_alive) {
        cout << "\t\tBob misses.\n";
    } else {
        cout << "\t\tCharlie is dead.\n";
    }

    // Case 3 Aaron Alive + Charlie Deads
    aaron_alive = true;
    charlie_alive = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    cout << "\t\tBob is shooting at Aaron\n";
    Bob_shoots(aaron_alive, charlie_alive);
    // Charlie is already dead
    assert(false == charlie_alive);
    if (aaron_alive) {
        cout << "\t\tBob misses.\n";
    } else {
        cout << "\t\tAaron is dead.\n";
    }

    cout << endl;
}

void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";

    // Case 1 Both Alive
    bool aaron_alive = true;
    bool bob_alive = true;
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    cout << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_alive, bob_alive);
    // Since Charlie is shooting at Bob Aaron can not die
    assert(true == aaron_alive);
    // Since Charlie can't miss Bob is dead
    assert(false == bob_alive);
	cout << "\t\tBob is dead.\n";


    // Case 2 Aaron Dead + Bob Alive
    aaron_alive = false;
    bob_alive = true;
    cout << "\tCase 2: Aaron dead, Bob alive\n";
    cout << "\t\tCharlie is shooting at Bob\n";
    Charlie_shoots(aaron_alive, bob_alive);
    // Aaron is already dead
    assert(false == aaron_alive);
    // Since Charlie can't miss Bob is dead
    assert(false == bob_alive);
	cout << "\t\tBob is dead.\n";

    // Case 3 Aaron Alive + Bob Dead
    aaron_alive = true;
    bob_alive = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n";
    cout << "\t\tCharlie is shooting at Aaron\n";
    Charlie_shoots(aaron_alive, bob_alive);
    // Bob is already dead
    assert(false == bob_alive);
    // Since Charlie can't miss Aaron is dead
    assert(false == aaron_alive);
	cout << "\t\tAaron is dead.\n";

    cout << endl;
}

void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";

    // Case 1 Both Alive
    bool bob_alive = true;
    bool charlie_alive = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    cout << "\t\tAaron intentionally misses his first shot\n";
    Aaron_shoots2(bob_alive, charlie_alive);
    // Since Aaron intentionally misses his first shot, Bob and Charlie stay alive
    assert(true == bob_alive);
    assert(true == charlie_alive);
    cout << "\t\tBoth Bob and Charlie are alive.\n";

    // Case 2 Bob Dead + Charlie Alive
    bob_alive = false;
    charlie_alive = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";
    Aaron_shoots2(bob_alive, charlie_alive);
    // Bob is already dead
    assert(false == bob_alive);
    if (charlie_alive) {
        cout << "\t\tAaron misses.\n";
    } else {
        cout << "\t\tCharlie is dead.\n";
    }

    // Case 3 Bob Alive + Charlie False
    bob_alive = true;
    charlie_alive = false;
    cout << "\tCase 3: Bob alive, Charlie false\n";
    cout << "\t\tAaron is shooting at Bob\n";
    Aaron_shoots2(bob_alive, charlie_alive);
    // Charlie is already dead
    assert(false == charlie_alive);
    if (bob_alive) {
        cout << "\t\tAaron misses.\n";
    } else {
        cout << "\t\tBob is dead.\n";
    }

    cout << endl;
}

int test_duel(int strategy) {
    cout << "Ready to test strategy " << strategy << " (run 10000 times):\n";
    
    int aaron_wins = 0;
    int bob_wins = 0;
    int charlie_wins = 0;

    for (int i = 0; i < total_duels; i++) {
        int result;
        if (strategy == 1) {
            result = simulate_strategy_1(true, true, true);
        } else if (strategy == 2) {
            result = simulate_strategy_2(true, true, true);
        }
        switch (result) {
            case 1:
                aaron_wins++;
                break;
            case 2:
                bob_wins++;
                break;
            case 3:
                charlie_wins++;
                break;
        }
    }

    cout << "Aaron won " << aaron_wins << "/" << total_duels << " duels or " << (aaron_wins * 100 / total_duels) << "%\n";
    cout << "Bob won " << bob_wins << "/" << total_duels << " duels or " << (bob_wins * 100 / total_duels) << "%\n";
    cout << "Charlie won " << charlie_wins << "/" << total_duels << " duels or " << (charlie_wins * 100 / total_duels) << "%\n";

    cout << endl;
    return aaron_wins;
}

int main() {
    // Format to 2 Decimal Places
    cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

    // Initialize Random
    srand(time(0));

    cout << "*** Welcome to Group 4's Duel Simulator ***" << endl;

    // Run Test Drivers
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots();
    test_Charlie_shoots();
    test_Aaron_shoots2();

    int aaron_wins1 = test_duel(1);
    int aaron_wins2 = test_duel(2);

    // Decides which strategy is better for Aaron
    if (aaron_wins2 > aaron_wins1) {
        cout << "Strategy 2 is better than Strategy 1.";
    } else {
        cout << "Strategy 1 is better than Strategy 2";
    }

    cout << endl;
}