#pragma once
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#include "main.h"

template<typename Func>
string captureOutput(Func func) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    try {
        func();
    } catch (...) {
        cout.rdbuf(old); // đảm bảo restore
        throw;
    }

    cout.rdbuf(old);
    return buffer.str();
}

class ITest {
    private:
    int passed_test;
    int failed_test;
    int Num_Of_Test;
    public:
    ITest() {
        this -> passed_test = 0;
        this -> failed_test = 0;
        this -> Num_Of_Test = 0;
    }
    void run_test(string name, string output, string expected) {
        Num_Of_Test += 1;
        stringstream passed_string; 
        passed_string << GREEN << name << " PASSED " << RESET << "\n";
        stringstream failed_string;
        failed_string << RED << name << " FAILED " << RESET << "\n";
    
        if (expected == output) {
            ++passed_test;
            cout << passed_string.str();
        }

        else {
            ++failed_test;
            cout << "****************************************************************************\n";
            cout << failed_string.str();
            cout << "Your result: \n" << output << "\n";
            cout << "Expected result: \n" << expected << "\n"; 
            cout << "****************************************************************************\n\n\n";
        }
    }

    int get_num_test() {
        return Num_Of_Test;
    }

    int get_passed_test() {
        return passed_test;
    }

    int get_failed_test() {
        return failed_test;
    }

    void Show_Result(string name, int num_test, int passed_test, int failed_test) {
        cout << "================================================================================\n";
        cout << name << " Result\n" << "Passed Test: " << passed_test << "/" << num_test << "\n" << "Failed Test: " << failed_test << "/" << num_test << endl;
        cout << "================================================================================\n";
    }

    virtual void run_all_test() {}
};