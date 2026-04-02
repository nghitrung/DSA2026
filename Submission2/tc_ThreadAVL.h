#include "ITest.h"
#include "ThreadedAVL.h"

class ThreadAVL_Test: public DSA_Assignment2_Test {
    private:
    string name;
    public:
    ThreadAVL_Test() {
        this -> name = "Threaded_AVL";
    }
    void TAVL_001() {
        string name = "TAVL_001";
        ThreadedAVL<int, string> tree;
        tree.insert(20, "A"); tree.insert(10, "B"); tree.insert(30, "C");

        stringstream output, expected;
        auto it = tree.beginIt();
        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "10 20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_002() {
        string name = "TAVL_002";
        ThreadedAVL<int, string> tree;
        tree.insert(20, "A"); tree.insert(10, "B"); tree.insert(30, "C");

        stringstream output, expected;
        auto it = tree.rbeginIt();
        while (!it.isNull()) { output << it.key() << " "; --it; }

        expected << "30 20 10 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_003() {
        string name = "TAVL_003";
        ThreadedAVL<int, string> tree;
        tree.insert(10, "A"); tree.insert(30, "B"); tree.insert(20, "C");

        stringstream output, expected;
        auto it = tree.beginIt();
        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "10 20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_004() {
        string name = "TAVL_004";
        ThreadedAVL<int, string> tree;
        tree.insert(10, "A"); tree.insert(20, "B"); tree.insert(30, "C");

        tree.erase(20);

        stringstream output, expected;
        auto it = tree.beginIt();
        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "10 30 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_005() {
        string name = "TAVL_005";
        ThreadedAVL<int, string> tree;
        tree.insert(20, "A"); tree.insert(10, "B"); tree.insert(30, "C");
        tree.insert(25, "D"); tree.insert(40, "E");

        tree.erase(30);

        stringstream output, expected;
        auto it = tree.beginIt();
        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "10 20 25 40 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_006() {
        string name = "TAVL_006";
        ThreadedAVL<int, string> tree;
        tree.insert(20, "A"); tree.insert(10, "B"); tree.insert(30, "C");

        stringstream output, expected;
        auto it1 = tree.beginIt();
        auto it2 = tree.rbeginIt();

        output << it1.key() << " " << it2.key();
        expected << "10 30";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_007() {
        string name = "TAVL_007";
        ThreadedAVL<int, string> tree;
        for (int i = 1; i <= 5; i++) tree.insert(i, "A");

        tree.erase(3);

        stringstream output, expected;
        auto it = tree.beginIt();
        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "1 2 4 5 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_008() {
        string name = "TAVL_008";
        ThreadedAVL<int, string> tree;
        tree.insert(5, "A"); tree.insert(3, "B"); tree.insert(7, "C");

        stringstream output, expected;
        auto it = tree.findIt(5);

        output << it.key();
        expected << "5";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_009() {
        string name = "TAVL_009";
        ThreadedAVL<int, string> tree;

        stringstream output, expected;
        auto it = tree.beginIt();

        output << it.isNull();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_010() {
        string name = "TAVL_010";
        ThreadedAVL<int, string> tree;
        tree.insert(1, "A");

        stringstream output, expected;
        auto it = tree.beginIt();

        output << it.key();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_011() {
        string name = "TAVL_011";
        ThreadedAVL<int, string> tree;
        for (int i = 1; i <= 5; i++) tree.insert(i, "A");

        stringstream output, expected;
        auto it = tree.beginIt();
        ++it; ++it;

        output << it.key();
        expected << "3";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_012() {
        string name = "TAVL_012";
        ThreadedAVL<int, string> tree;
        for (int i = 1; i <= 5; i++) tree.insert(i, "A");

        stringstream output, expected;
        auto it = tree.rbeginIt();
        --it; --it;

        output << it.key();
        expected << "3";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_013() {
        string name = "TAVL_013";
        ThreadedAVL<int, string> tree;
        tree.insert(10, "A"); tree.insert(20, "B"); tree.insert(30, "C");

        tree.erase(10);

        stringstream output, expected;
        auto it = tree.beginIt();

        output << it.key();
        expected << "20";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_014() {
        string name = "TAVL_014";
        ThreadedAVL<int, string> tree;
        tree.insert(10, "A"); tree.insert(20, "B"); tree.insert(30, "C");

        tree.erase(30);

        stringstream output, expected;
        auto it = tree.rbeginIt();

        output << it.key();
        expected << "20";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_015() {
        string name = "TAVL_015";
        ThreadedAVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(10, "B");

        stringstream output, expected;
        output << tree.size();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_016() {
        string name = "TAVL_016";
        ThreadedAVL<int, string> tree;
        for (int i = 1; i <= 10; i++) tree.insert(i, "A");

        stringstream output, expected;
        auto it = tree.beginIt();

        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "1 2 3 4 5 6 7 8 9 10 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_017() {
        string name = "TAVL_017";
        ThreadedAVL<int, string> tree;
        for (int i = 10; i >= 1; i--) tree.insert(i, "A");

        stringstream output, expected;
        auto it = tree.beginIt();

        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "1 2 3 4 5 6 7 8 9 10 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_018() {
        string name = "TAVL_018";
        ThreadedAVL<int, string> tree;
        for (int i = 1; i <= 5; i++) tree.insert(i, "A");

        tree.clear();

        stringstream output, expected;
        auto it = tree.beginIt();

        output << it.isNull();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_019() {
        string name = "TAVL_019";
        ThreadedAVL<int, string> tree;
        tree.insert(2, "A"); tree.insert(1, "B"); tree.insert(3, "C");

        tree.erase(2);

        stringstream output, expected;
        auto it = tree.beginIt();

        while (!it.isNull()) { output << it.key() << " "; ++it; }

        expected << "1 3 ";
        run_test(name, output.str(), expected.str());
    }

    void TAVL_020() {
        string name = "TAVL_020";
        ThreadedAVL<int, string> tree;
        for (int i = 1; i <= 100; i++) tree.insert(i, "A");

        stringstream output, expected;
        auto it = tree.beginIt();

        int count = 0;
        while (!it.isNull()) { count++; ++it; }

        output << count;
        expected << "100";
        run_test(name, output.str(), expected.str());
    }
    void run_all_test() override {
        TAVL_001();
        TAVL_002();
        TAVL_003();
        TAVL_004();
        TAVL_005();
        TAVL_006();
        TAVL_007();
        TAVL_008();
        TAVL_009();
        TAVL_010();
        TAVL_011();
        TAVL_012();
        TAVL_013();
        TAVL_014();
        TAVL_015();
        TAVL_016();
        TAVL_017();
        TAVL_018();
        TAVL_019();
        TAVL_020();
        Show_Result(name, get_num_test(), get_passed_test(), get_failed_test());
    }
};