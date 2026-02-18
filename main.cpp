#include "Playlist.h"
#include <assert.h>
#include "BotkifyLinkedList.h"

using namespace std;

void printTestHeader(string title) {
    cout << "========================================" << endl;
    cout << "RUNNING TEST: " << title << endl;
    cout << "========================================" << endl;
}

void testSongClass() {
    printTestHeader("Song Class Methods");
    Song s(101, "See Tinh", "Hoang Thuy Linh", "Link", 185, 900, "url_see_tinh");
    
    assert(s.getID() == 101);
    assert(s.getDuration() == 185);
    assert(s.getScore() == 900);
    assert(s.toString() == "See Tinh-Hoang Thuy Linh");
    
    cout << "Song info: " << s.toString() << " -> PASSED" << endl;
}

void testPlaylistBasic() {
    printTestHeader("Playlist Basic Management");
    Playlist p("V-Pop 2026");
    
    assert(p.empty() == true);
    assert(p.size() == 0);
    
    p.addSong(new Song(1, "Song A", "Artist A", "Album A", 100, 50, "u1"));
    p.addSong(new Song(2, "Song B", "Artist B", "Album B", 200, 80, "u2"));
    
    assert(p.size() == 2);
    assert(p.getSong(1)->getID() == 2);
    p.removeSong(0);
    
    assert(p.size() == 1);
    assert(p.getSong(0)->getID() == 2);
    p.clear();
    assert(p.empty() == true);
    cout << "Basic management -> PASSED" << endl;
}

void testPlayingControl() {
    printTestHeader("Playing Control (Circular)");
    Playlist p("Test Play");
    p.addSong(new Song(1, "S1", "A1", "AL1", 100, 10, "u1"));
    p.addSong(new Song(2, "S2", "A2", "AL2", 120, 20, "u2"));
    p.addSong(new Song(3, "S3", "A3", "AL3", 140, 30, "u3"));

    // Mặc định ban đầu currentIndex = -1, playNext sẽ về 0
    assert(p.playNext()->getID() == 1); 
    assert(p.playNext()->getID() == 2);
    assert(p.playNext()->getID() == 3);
    assert(p.playNext()->getID() == 1); // Quay vòng về đầu (Circular) [cite: 187]

    assert(p.playPrevious()->getID() == 3); // Quay vòng về cuối [cite: 193]
    assert(p.playPrevious()->getID() == 2);
    
    cout << "Circular Playing Control -> PASSED" << endl;
}

void testGetTotalScore() {
    printTestHeader("Total Score Calculation (Example 3.3)");
    Playlist p("ScoreTest");
    // Dữ liệu theo ví dụ 3.3 trong đề bài: 4, 1, 3, 5 [cite: 208]
    p.addSong(new Song(1, "S1", "A1", "AL1", 100, 4, "u1"));
    p.addSong(new Song(2, "S2", "A2", "AL2", 100, 1, "u2"));
    p.addSong(new Song(3, "S3", "A3", "AL3", 100, 3, "u3"));
    p.addSong(new Song(4, "S4", "A4", "AL4", 100, 5, "u4"));

    int result = p.getTotalScore();
    cout << "Calculated Total Score: " << result << " (Expected: 114)" << endl;
    assert(result == 114); // [cite: 213]
    cout << "getTotalScore Algorithm -> PASSED" << endl;
}

void testAdvancedModes() {
    printTestHeader("Advanced Playing Modes");
    Playlist p("Advanced");
    // Dữ liệu ví dụ 3.5: 50, 60, 30, 90, 100 [cite: 255]
    p.addSong(new Song(1, "S1", "A1", "AL1", 50, 10, "u1"));
    p.addSong(new Song(2, "S2", "A2", "AL2", 60, 10, "u2"));
    p.addSong(new Song(3, "S3", "A3", "AL3", 30, 10, "u3"));
    p.addSong(new Song(4, "S4", "A4", "AL4", 90, 10, "u4"));
    p.addSong(new Song(5, "S5", "A5", "AL5", 100, 10, "u5"));

    cout << "Testing playRandom(0): ";
    p.playRandom(0); // Kết quả in ra kỳ vọng: S1-A1,S2-A2,S4-A4,S5-A5 [cite: 257]

    int diff = p.playApproximate(1); // step = 1 [cite: 256]
    cout << "Testing playApproximate(1): " << diff << " (Expected: 50)" << endl;
    assert(diff == 50); // [cite: 258]
    
    cout << "Advanced Modes -> PASSED" << endl;
}

int main() {
    try {
        testSongClass();
        testPlaylistBasic();
        testPlayingControl();
        testGetTotalScore();
        testAdvancedModes();
        
        cout << "\n========================================" << endl;
        cout << "CONGRATS: ALL TESTS PASSED SUCCESSFULLY!" << endl;
        cout << "========================================" << endl;
    } catch (const exception& e) {
        cerr << "FATAL ERROR: " << e.what() << endl;
        return 1;
    }
    return 0;
}