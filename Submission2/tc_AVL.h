#include "ITest.h"
#include "AVL.h"
class AVL_Test: public DSA_Assignment2_Test {
    private:
    string name;
    public:
    AVL_Test() {
        this -> name = "AVL_Test";
    }
    public:
    void AVL_001() {
        string name = "AVL_001";
        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(20, "B");
        tree.insert(30, "C");
        stringstream output;
        stringstream expected;

        output << "Tree size: " << tree.size() << "\n";
        list<int> asc;
        asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "Tree size: 3" << "\n" << "10 20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_002() {
        string name = "AVL_002";
        stringstream output;
        stringstream expected;

        AVL<int, string> tree;
        tree.insert(30, "A");
        tree.insert(30, "B");
        tree.insert(30, "C");
        tree.erase(30);
        output << "Tree size: " << tree.size();
        expected << "Tree size: 0";
        
        run_test(name, output.str(), expected.str());
    }

    void AVL_003() {
        string name = "AVL_003";
        stringstream output;
        stringstream expected;

        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(20, "B");
        tree.insert(30, "C");

        output << "Tree height: " << tree.height();
        expected << "Tree height: 2";

        run_test(name, output.str(), expected.str());
    }

    void AVL_004() {
        string name = "AVL_004";
        stringstream output;
        stringstream expected;

        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(20, "B");
        tree.insert(30, "C");

        tree.clear();
        output << tree.empty();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_005() {
        string name = "AVL_005";
        stringstream output;
        stringstream expected;

        AVL<int, string> tree;
        tree.insert(20, "A");
        tree.insert(10, "B");
        tree.insert(30, "C");
        tree.insert(5, "D");
        tree.insert(15, "E");
        tree.insert(25, "F");
        tree.insert(35, "G");

        output << "Tree height: " << tree.height() << endl;
        output << "Tree size: " << tree.size() << endl;
        list<int> des;
        des = tree.descendingList();
        output << "Descending List: ";
        for (int de : des) {
            output << de << " ";
        }

        expected << "Tree height: 3" << "\n" << "Tree size: 7" << "\n";
        expected << "Descending List: 35 30 25 20 15 10 5 ";

        run_test(name, output.str(), expected.str());
    }

     void AVL_006() {
        string name = "AVL_006";
        stringstream output;
        stringstream expected;

        AVL<int, string> tree;
        tree.insert(20, "A");
        tree.insert(10, "B");
        tree.insert(30, "C");
        tree.insert(5, "D");
        tree.insert(15, "E");
        tree.insert(25, "F");
        tree.insert(35, "G");

        output << "Value of 20: " << *tree.find(20) << endl;
        output << "Value of 10: " << *tree.find(10);

        expected << "Value of 20: A" << "\n" << "Value of 10: B"; 

        run_test(name, output.str(), expected.str());
    }

    void AVL_007() {
        string name = "AVL_007";
        stringstream output;
        stringstream expected;

        AVL<int, string> tree;
        tree.insert(20, "A");
        tree.insert(10, "B");
        tree.insert(30, "C");
        tree.insert(5, "D");
        tree.insert(15, "E");
        tree.insert(25, "F");
        tree.insert(35, "G");

        output << tree.contains(35);
        expected << 1;
        run_test(name, output.str(), expected.str());
    }

    void AVL_008() {
        string name = "AVL_008";
        stringstream output;
        stringstream expected;

        AVL<int, string> tree;
        output << (tree.empty() ? "Empty tree" : "Non-empty tree") << endl ;
        tree.insert(30, "A");
        output << "Tree height: " << tree.height();

        expected << "Empty tree" << "\n" << "Tree height: 1";

        run_test(name, output.str(), expected.str());
    }

    void AVL_009() {
        string name = "AVL_009";
        stringstream output;
        stringstream expected;
        AVL<int,string> tree;
        for (int i = 0; i < 5; ++i) {
            tree.insert(i,"Node");
        }

        output << tree.toString();
        expected << " (<1, Node>:-1[<0, Node>:0] (<3, Node>:0[<2, Node>:0][<4, Node>:0]) ) ";
        run_test(name, output.str(), expected.str());
    }   

    void AVL_010() {
        string name = "AVL_010";
        stringstream output;
        stringstream expected;
        AVL<int,string> tree;
        for (int i = 0; i < 5; ++i) tree.insert(i*i,"Node");
        bool removed = tree.erase(100);
        output << "Remove 100: " << (removed ? "Yes" : "No");
        expected << "Remove 100: No";
        run_test(name, output.str(), expected.str());
    }

    void AVL_011() {
        string name = "AVL_011";
        stringstream output;
        stringstream expected;

        AVL<int,string> tree;
        for (int i = 0; i<5; ++i) tree.insert(i, "Node");
        tree.erase(0);
        output << tree.toString();
        expected << " (<3, Node>:1 (<1, Node>:-1[.][<2, Node>:0])[<4, Node>:0]) ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_012() {
        string name = "AVL_012";
        stringstream output;
        stringstream expected;
        AVL<int,string> tree;

        for (int i = 0; i<=5; ++i) tree.insert(i,"Node");
        output << tree.toString();
        expected << " (<3, Node>:0 (<1, Node>:0[<0, Node>:0][<2, Node>:0])  (<4, Node>:-1[.][<5, Node>:0])) ";

        run_test(name, output.str(), expected.str());
    }

    void AVL_013() {
        string name = "AVL_013";
        stringstream output;
        stringstream expected;
        AVL<int,string> tree;
        for (int i = 0; i<5; ++i) {
            tree.insert(i,"");
        }

        output << "Tree height: " << tree.height();
        expected << "Tree height: 3";
        
        run_test(name, output.str(), expected.str());
    }

    void AVL_014() {
        string name = "AVL_014";
        stringstream output;
        stringstream expected;

        AVL<int,string> tree;
        for (int i = 0; i<5;++i) tree.insert(i,"");
        tree.erase(0);
        tree.erase(2);
        output << "Tree height: " << tree.height();
        expected << "Tree height: 2";

        run_test(name, output.str(), expected.str());
    }

    void AVL_015() {
        string name = "AVL_015";
        stringstream output;
        stringstream expected;

        AVL<int,string> tree;
        for (int i = 0; i<5; ++i) tree.insert(i,"");
        for (int i = 0; i<5; ++i) tree.erase(i);

        output << "Tree is empty? " << (tree.empty() ? "Yes" : "No");
        expected << "Tree is empty? Yes";

        run_test(name, output.str(), expected.str());
    }

    void AVL_016() {
        string name = "AVL_016";
        stringstream output;
        stringstream expected;

        AVL<int,int> tree;
        for (int i = 0; i < 10000; ++i) tree.insert(100,i);

        output << "Tree height: " << tree.height() << "\n" << "Tree size: " << tree.size();
        expected << "Tree height: 1" << "\n" << "Tree size: 1";
        run_test(name, output.str(), expected.str()); 
    }

    void AVL_017() {
        string name = "AVL_017";
        stringstream output;
        stringstream expected;

        AVL<char, int> tree;
        int idx = 1;
        for (char i='A'; i <= 'Z'; ++i) {
            tree.insert(i, idx);
            idx+=10;
        } 
        output << "Find key Z: " << *tree.find('Z');
        expected << "Find key Z: 251";

        run_test(name, output.str(), expected.str());
    }

    void AVL_018() {
        string name = "AVL_018";
        stringstream output;
        stringstream expected;
        
        AVL<int,int> tree;
        for (int i = 0; i <= 10; ++i) tree.insert(i, i*i);
        list<int> ascList = tree.ascendingList();
        list<int> descList = tree.descendingList();

        output << "Asc List: ";
        for (int asc : ascList) output << asc << " ";
        output << "\n";
        
        output << "Desc List: ";
        for (int des: descList) output << des << " ";

        expected << "Asc List: 0 1 2 3 4 5 6 7 8 9 10 " 
                 << "\n" << "Desc List: 10 9 8 7 6 5 4 3 2 1 0 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_019() {
        string name = "AVL_019";
        stringstream output;
        stringstream expected;
        AVL<int,int> tree;

        for (int i = 0; i <= 100; ++i) {
            tree.insert(i, i*i);
        }

        for (int i = 0; i <= 100; ++i) {
            if (i%2 != 0) {
                tree.erase(i);
            }
        }

        list<int> ascList;
        ascList = tree.ascendingList();
        output << "Asc List: ";
        
        for (int asc : ascList) output << asc << " ";
        expected << "Asc List: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46 48 50 52 54 56 58 60 62 64 66 68 70 72 74 76 78 80 82 84 86 88 90 92 94 96 98 100 ";

        run_test(name, output.str(), expected.str());
    }

    void AVL_020() {
        string name = "AVL_020";
        stringstream output;
        stringstream expected;

        AVL<int, int>tree;
        for (int i = 0; i < 100; ++i) {
            tree.insert(i, i+1);
            if(i%2 == 0) tree.erase(i);
        }

        if (tree.find(52)) output << "Value of key 53: " << *tree.find(52);
        else output << "Value of key 52 does not exist";

        expected << "Value of key 52 does not exist";
        run_test(name, output.str(), expected.str());
    }


        void AVL_021() {
        string name = "AVL_021";
        AVL<int, string> tree;
        tree.insert(30, "A");
        tree.insert(20, "B");
        tree.insert(10, "C"); // LL rotation

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "10 20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_022() {
        string name = "AVL_022";
        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(20, "B");
        tree.insert(30, "C"); // RR rotation

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "10 20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_023() {
        string name = "AVL_023";
        AVL<int, string> tree;
        tree.insert(30, "A");
        tree.insert(10, "B");
        tree.insert(20, "C"); // LR rotation

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "10 20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_024() {
        string name = "AVL_024";
        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(30, "B");
        tree.insert(20, "C"); // RL rotation

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "10 20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_025() {
        string name = "AVL_025";
        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(10, "B"); // duplicate

        stringstream output, expected;
        output << tree.size();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_026() {
        string name = "AVL_026";
        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.erase(10);

        stringstream output, expected;
        output << tree.empty();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_027() {
        string name = "AVL_027";
        AVL<int, string> tree;
        tree.insert(20, "A");
        tree.insert(10, "B");
        tree.insert(30, "C");
        tree.erase(10); // leaf

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "20 30 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_028() {
        string name = "AVL_028";
        AVL<int, string> tree;
        tree.insert(20, "A");
        tree.insert(10, "B");
        tree.insert(30, "C");
        tree.insert(25, "D");
        tree.erase(30); // 1 child

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "10 20 25 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_029() {
        string name = "AVL_029";
        AVL<int, string> tree;
        tree.insert(20, "A");
        tree.insert(10, "B");
        tree.insert(30, "C");
        tree.insert(25, "D");
        tree.insert(40, "E");

        tree.erase(30); // 2 children

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "10 20 25 40 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_030() {
        string name = "AVL_030";
        AVL<int, string> tree;

        stringstream output, expected;
        output << tree.height();
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void AVL_031() {
        string name = "AVL_031";
        AVL<int, string> tree;
        tree.insert(10, "A");

        stringstream output, expected;
        output << tree.height();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_032() {
        string name = "AVL_032";
        AVL<int, string> tree;
        for (int i = 1; i <= 7; i++) tree.insert(i, "A");

        stringstream output, expected;
        output << tree.height();
        expected << "3";
        run_test(name, output.str(), expected.str());
    }

    void AVL_033() {
        string name = "AVL_033";
        AVL<int, string> tree;
        tree.insert(5, "A");
        tree.insert(3, "B");
        tree.insert(7, "C");

        stringstream output, expected;
        output << (tree.find(3) != nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_034() {
        string name = "AVL_034";
        AVL<int, string> tree;

        stringstream output, expected;
        output << (tree.find(100) == nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_035() {
        string name = "AVL_035";
        AVL<int, string> tree;
        tree.insert(5, "A");

        stringstream output, expected;
        output << tree.contains(5);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_036() {
        string name = "AVL_036";
        AVL<int, string> tree;

        stringstream output, expected;
        output << tree.contains(5);
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void AVL_037() {
        string name = "AVL_037";
        AVL<int, string> tree;
        for (int i = 1; i <= 5; i++) tree.insert(i, "A");

        tree.clear();

        stringstream output, expected;
        output << tree.size();
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void AVL_038() {
        string name = "AVL_038";
        AVL<int, string> tree;
        tree.insert(3, "A");
        tree.insert(1, "B");
        tree.insert(5, "C");

        stringstream output, expected;
        list<int> desc = tree.descendingList();

        for (int a : desc) output << a << " ";
        expected << "5 3 1 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_039() {
        string name = "AVL_039";
        AVL<int, string> tree;
        tree.insert(1, "A");
        tree.insert(2, "B");
        tree.insert(3, "C");
        tree.erase(2);

        stringstream output, expected;
        list<int> asc = tree.ascendingList();

        for (int a : asc) output << a << " ";
        expected << "1 3 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_040() {
        string name = "AVL_040";
        AVL<int, string> tree;
        for (int i = 1; i <= 100; i++) tree.insert(i, "A");

        stringstream output, expected;
        output << tree.size();
        expected << "100";
        run_test(name, output.str(), expected.str());
    }

    void AVL_041() {
        string name = "AVL_041";
        AVL<int, string> tree;
        for (int i = 100; i >= 1; i--) tree.insert(i, "A");

        stringstream output, expected;
        output << tree.size();
        expected << "100";
        run_test(name, output.str(), expected.str());
    }

    void AVL_042() {
        string name = "AVL_042";
        AVL<int, string> tree;
        for (int i = 1; i <= 10; i++) tree.insert(i, "A");

        tree.erase(5);

        stringstream output, expected;
        output << tree.contains(5);
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void AVL_043() {
        string name = "AVL_043";
        AVL<int, string> tree;
        tree.insert(10, "A");

        tree.erase(20);

        stringstream output, expected;
        output << tree.size();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_044() {
        string name = "AVL_044";
        AVL<int, string> tree;
        tree.insert(50, "A");
        tree.insert(30, "B");
        tree.insert(70, "C");

        tree.erase(50);

        stringstream output, expected;
        list<int> asc = tree.ascendingList();
        for (int a : asc) output << a << " ";
        expected << "30 70 ";
        run_test(name, output.str(), expected.str());
    }

    void AVL_045() {
        string name = "AVL_045";
        AVL<int, string> tree;
        tree.insert(2, "A");
        tree.insert(1, "B");
        tree.insert(3, "C");

        stringstream output, expected;
        output << tree.height();
        expected << "2";
        run_test(name, output.str(), expected.str());
    }

    void AVL_046() {
        string name = "AVL_046";
        AVL<int, string> tree;

        stringstream output, expected;
        output << tree.empty();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_047() {
        string name = "AVL_047";
        AVL<int, string> tree;
        tree.insert(1, "A");

        stringstream output, expected;
        output << tree.empty();
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void AVL_048() {
        string name = "AVL_048";
        AVL<int, string> tree;
        for (int i = 1; i <= 5; i++) tree.insert(i, "A");

        tree.erase(1);
        tree.erase(2);
        tree.erase(3);
        tree.erase(4);
        tree.erase(5);

        stringstream output, expected;
        output << tree.empty();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void AVL_049() {
        string name = "AVL_049";
        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(5, "B");
        tree.insert(15, "C");

        stringstream output, expected;
        output << tree.size();
        expected << "3";
        run_test(name, output.str(), expected.str());
    }

    void AVL_050() {
        string name = "AVL_050";
        AVL<int, string> tree;
        tree.insert(10, "A");
        tree.insert(20, "B");
        tree.insert(5, "C");

        tree.clear();

        stringstream output, expected;
        output << tree.height();
        expected << "0";
        run_test(name, output.str(), expected.str());
    }
    void run_all_test() override {
        AVL_001();
        AVL_002();
        AVL_003();
        AVL_004();
        AVL_005();
        AVL_006();
        AVL_007();
        AVL_008();
        AVL_009();
        AVL_010();
        AVL_011();
        AVL_012();
        AVL_013();
        AVL_014();
        AVL_015();
        AVL_016();
        AVL_017();
        AVL_018();
        AVL_019();
        AVL_020();
        AVL_021();
        AVL_022();
        AVL_023();
        AVL_024();
        AVL_025();
        AVL_026();
        AVL_027();
        AVL_028();
        AVL_029();
        AVL_030();
        AVL_031();
        AVL_032();
        AVL_033();
        AVL_034();
        AVL_035();
        AVL_036();
        AVL_037();
        AVL_038();
        AVL_039();
        AVL_040();
        AVL_041();
        AVL_042();
        AVL_043();
        AVL_044();
        AVL_045();
        AVL_046();
        AVL_047();
        AVL_048();
        AVL_049();
        AVL_050();
        Show_Result(name, get_num_test(), get_passed_test(), get_failed_test());
    }
};