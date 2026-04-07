#include "main.h"
#include "AVL.h"
#include "ThreadedAVL.h"
#include "Playlist.h"
#include "tc_AVL.h"
#include "tc_ThreadAVL.h"
#include "tc_PlayList.h"

void tc1() {
    cout << "=== TC1: Basic AVL Insertion & Traversal ===" << endl;
    AVL<int, string> tree;
    
    tree.insert(50, "Song_A");
    tree.insert(30, "Song_B");
    tree.insert(70, "Song_C");
    tree.insert(20, "Song_D");
    tree.insert(40, "Song_E");
    tree.insert(35, "Song_F"); 

    cout << "Tree size: " << tree.size() << endl;
    cout << tree.toString() << endl;
    list<int> asc = tree.ascendingList();
    cout << "Ascending keys: ";
    for (int key : asc) {
        cout << key << " ";
    }
    cout << endl; 
}

void tc_bonus_avl() {
    cout << "=================tc bonus==================\n";
    AVL<int, string> tree;
    tree.insert(30, "A");
    tree.insert(30, "A");
    cout << tree.size() << "\n";
    
    list<int> asc = tree.ascendingList();
    cout << "Ascending keys: ";
    for (int key: asc) {
        cout << key << " ";
    }
    cout << endl;
}

void tc_bonus_avl2() {
    cout << "=================tc bonus 2==================\n";
    AVL<int, string> tree;
    tree.insert(30, "A");
    tree.insert(40, "B");
    cout << tree.size() << "\n";
    cout << *tree.find(30) << endl;
    cout << endl;
}

void tc_bonus_avl3() {
    cout << "=================tc bonus 3==================\n";
    AVL<int, string> tree;
    tree.insert(30, "A");
    tree.insert(40, "B");
    cout << tree.contains(30);

    cout << endl;
}

void tc_bonus_erase() {
    cout << "=== TC erase: Basic AVL Insertion & Traversal ===" << endl;
    AVL<int, string> tree;
    
    tree.insert(50, "Song_A");
    tree.insert(30, "Song_B");
    tree.insert(70, "Song_C");
    tree.insert(20, "Song_D");
    tree.insert(40, "Song_E");
    tree.insert(35, "Song_F"); 

    tree.erase(35);
    cout << "Tree size: " << tree.size() << endl;
    cout << tree.toString() << endl;
    list<int> asc = tree.ascendingList();
    cout << "Ascending keys: ";
    for (int key : asc) {
        cout << key << " ";
    }
    cout << endl; 
}

void tc2() {
    cout << "=== TC2: AVL Deletion (Node with 2 children) ===" << endl;
    AVL<int, string> tree;
    tree.insert(50, "A");
    tree.insert(30, "B");
    tree.insert(70, "C");
    tree.insert(20, "D");
    tree.insert(40, "E");
    tree.insert(60, "F");
    tree.insert(80, "G");

    bool removed = tree.erase(30);
    cout << "Removed 30? " << (removed ? "Yes" : "No") << endl;

    list<int> asc = tree.ascendingList();
    cout << "Ascending keys after erase: ";
    for (int key : asc) {
        cout << key << " ";
    }
    cout << endl;
}

void tc3() {
    cout << "=== TC3: Playlist Add & Get (Alphabetical Order) ===" << endl;
    Playlist p("My Favorites");
    
    p.addSong(new Song(1, "Shape of You", "Ed Sheeran", "Divide", 233, 5, "url1"));
    p.addSong(new Song(2, "Blinding Lights", "The Weeknd", "After Hours", 200, 4, "url2"));
    p.addSong(new Song(3, "Levitating", "Dua Lipa", "Future Nostalgia", 203, 5, "url3"));
    p.addSong(new Song(4, "Blinding Lights", "Cover Artist", "Cover Album", 190, 3, "url4")); // Cùng title, khác ID

    cout << "Playlist size: " << p.getSize() << endl;
    for (int i = 0; i < p.getSize(); i++) {
        Song* s = p.getSong(i);
        if (s) {
            cout << i << ": " << s->toString() << endl;
        }
    }
}


void tc4() {
    cout << "=== TC4: Playlist Continuous Playback ===" << endl;
    Playlist p("Pop Hits");
    p.addSong(new Song(1, "Shape of You", "Ed Sheeran", "-", 233, 5, "-"));
    p.addSong(new Song(2, "Blinding Lights", "The Weeknd", "-", 200, 4, "-"));
    p.addSong(new Song(3, "Levitating", "Dua Lipa", "-", 203, 5, "-"));

    Song* current = p.playNext(); 
    if (current) cout << "Playing Next: " << current->toString() << endl;
    
    current = p.playNext(); 
    if (current) cout << "Playing Next: " << current->toString() << endl;
    
    current = p.playPrevious(); 
    if (current) cout << "Playing Prev: " << current->toString() << endl;
}

void tc5() {
    cout << "=== TC5: Playlist Advanced Operations ===" << endl;
    
    Playlist p1("Acoustic");
    p1.addSong(new Song(1, "A Song", "A1", "-", 100, 4, "-")); 
    p1.addSong(new Song(2, "B Song", "A1", "-", 100, 5, "-")); 
    p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 

    Playlist p2("Rock");
    p2.addSong(new Song(4, "A Song", "A2", "-", 100, 3, "-")); 
    p2.addSong(new Song(5, "B Song", "A2", "-", 100, 4, "-"));
    p2.addSong(new Song(6, "Z Song", "A2", "-", 100, 5, "-"));

    cout << "P1 Total Score: " << p1.getTotalScore() << endl;
    cout << "P2 Total Score: " << p2.getTotalScore() << endl;
    
    bool isGreaterOrEqual = p1.compareTo(p2, 2);
    cout << "P1 >= P2 (for first 2 songs)? " << (isGreaterOrEqual ? "Yes" : "No") << endl; 
}

void stressTest_Playlist() {
    Playlist p("Stress");

    // add 1000 bài
    for (int i = 1; i <= 1000; i++) {
        p.addSong(new Song(i, to_string(i), "A", "-", 100, i, "-"));
    }

    // random operations
    for (int i = 0; i < 1000; i++) {
        int op = rand() % 4;

        if (op == 0) p.playNext();
        else if (op == 1) p.playPrevious();
        else if (op == 2 && p.getSize() > 0)
            p.removeSong(rand() % p.getSize());
        else if (op == 3)
            p.playRandom(rand() % (p.getSize() + 1));
    }

    cout << "Stress test done\n";
}

int main(int argc, char* argv[]) {
    //tc1();
    // cout << "--------------------" << endl;
    // tc2();
    // cout << "--------------------" << endl;
    // tc3();
    // cout << "--------------------" << endl;
    // tc4();
    // cout << "--------------------" << endl;
    // tc5();
    // cout << "--------------------" << endl;


    /*USE COMMAND: <g++ -std=c++17 -DUSE_THREADED_AVL main.cpp Playlist.cpp -o app> to run all tests of 3 parts */
    //AVL Test
    AVL_Test avl_test;
    avl_test.run_all_test();

    // //Threaded_AVL test
    ThreadAVL_Test thread_test;
    thread_test.run_all_test();

    // //PlayList Test
    PlayList_Test playlist_test;
    playlist_test.run_all_test();

    return 0;
}