#include "ITest.h"
#include "MusicGraph.h"

class Graph_Test: public ITest {
    private:
    string name;
    public:
    Graph_Test() {
        this -> name = "Graph Test";
    }

    void Graph01() {
        string name = "Graph01";

        MusicGraph dag;
        dag.addSong("A01", "Song A", "Artist A", "Pop");
        dag.addSong("A02", "Song B", "Artist B", "Rock");
        dag.addSong("A03", "Song C", "Artist C", "Jazz");

        // A01 -> A02 -> A03 (no back edges, no cycle)
        dag.addEdge("A01", "A02", 1.0, false);
        dag.addEdge("A02", "A03", 2.0, false);

        // Expected output: "No music loop detected."
        //dag.detectMusicLoop();

        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n" 
                 << "-------------------------------------------------\n" 
                 << "No music loop detected.\n";
        string output = captureOutput([&]() {
            dag.detectMusicLoop();
        });

        run_test(name, output, expected.str());
    }

    void Graph02() {
        string name = "Graph02";

        MusicGraph botkify;
        botkify.addSong("S01", "Chung Ta Cua Tuong Lai", "Son Tung M-TP", "Pop");
        botkify.addSong("S02", "Muon Roi Ma Sao Con", "Son Tung M-TP", "Pop");
        botkify.addSong("S03", "Don't Coi", "RPT Orijinn", "Rap");
        botkify.addSong("S04", "Thuy Trieu", "Quang Hung MasterD", "Pop-Dance");
        botkify.addSong("S05", "Waiting For You", "MONO", "Pop");
        botkify.addSong("S06", "Co Don Tren Sofa", "Ho Ngoc Ha", "Ballad");

        // Define connections
        botkify.addEdge("S01", "S02", 1.5, true);    // Bidirectional
        botkify.addEdge("S02", "S04", 3.0, false);   // Unidirectional: S02 -> S04
        botkify.addEdge("S04", "S03", 2.0, true);    // Bidirectional
        botkify.addEdge("S01", "S05", 2.5, true);    // Bidirectional
        botkify.addEdge("S05", "S04", 1.0, true);    // Bidirectional

        stringstream expected;
        expected    << "\n[1] SUGGEST RELATED SONGS FOR: [S01] Chung Ta Cua Tuong Lai - Son Tung M-TP"
                    << "\n-------------------------------------------------\n"
                    << "-> [S02] Muon Roi Ma Sao Con - Son Tung M-TP\n"
                    << "-> [S05] Waiting For You - MONO\n" 
                    << "-> [S04] Thuy Trieu - Quang Hung MasterD\n"
                    << "-> [S03] Don't Coi - RPT Orijinn\n";

        string output = captureOutput([&]() {
            botkify.recommendRelatedSongs("S01");
        });

        run_test(name, output, expected.str());
    }

    void Graph03() {
        string name = "Graph03";
        
        MusicGraph g;
        g.addSong("B01", "Song 1", "Artist 1", "Pop");
        g.addSong("B02", "Song 2", "Artist 2", "Rock");
        g.addSong("B03", "Song 3", "Artist 3", "Jazz");
        g.addSong("B04", "Song 4", "Artist 4", "Pop");
        
        // Linear chain: B01 -> B02 -> B03 -> B04
        g.addEdge("B01", "B02", 1.0, false);
        g.addEdge("B02", "B03", 1.5, false);
        g.addEdge("B03", "B04", 2.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [B01] Song 1 - Artist 1"
                 << "\n-------------------------------------------------\n"
                 << "-> [B02] Song 2 - Artist 2\n"
                 << "-> [B03] Song 3 - Artist 3\n"
                 << "-> [B04] Song 4 - Artist 4\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("B01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph04() {
        string name = "Graph04";
        
        MusicGraph g;
        g.addSong("C01", "Lonely Song", "Sad Artist", "Ballad");
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [C01] Lonely Song - Sad Artist"
                 << "\n-------------------------------------------------\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("C01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph05() {
        string name = "Graph05";
        
        MusicGraph g;
        g.addSong("D01", "Song D1", "Artist D", "Pop");
        g.addSong("D02", "Song D2", "Artist D", "Rock");
        g.addSong("D03", "Song D3", "Artist D", "Jazz");
        
        // D01 -> D02 <- D03 (diamond-like)
        g.addEdge("D01", "D02", 1.5, false);
        g.addEdge("D03", "D02", 2.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [D01] Song D1 - Artist D"
                 << "\n-------------------------------------------------\n"
                 << "-> [D02] Song D2 - Artist D\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("D01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph06() {
        string name = "Graph06";
        
        MusicGraph g;
        g.addSong("E01", "Song E1", "Artist E", "Pop");
        g.addSong("E02", "Song E2", "Artist E", "Rock");
        g.addSong("E03", "Song E3", "Artist E", "Jazz");
        
        // Bidirectional edges: E01 <-> E02 <-> E03
        g.addEdge("E01", "E02", 1.0, true);
        g.addEdge("E02", "E03", 1.5, true);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [E01] Song E1 - Artist E"
                 << "\n-------------------------------------------------\n"
                 << "-> [E02] Song E2 - Artist E\n"
                 << "-> [E03] Song E3 - Artist E\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("E01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph07() {
        string name = "Graph07";
        
        MusicGraph g;
        g.addSong("F01", "Song F1", "Artist F", "Pop");
        g.addSong("F02", "Song F2", "Artist F", "Rock");
        g.addSong("F03", "Song F3", "Artist F", "Jazz");
        g.addSong("F04", "Song F4", "Artist F", "Rap");
        
        // Two separate components: F01->F02 and F03->F04
        g.addEdge("F01", "F02", 1.0, false);
        g.addEdge("F03", "F04", 1.5, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [F01] Song F1 - Artist F\n"
                 << "  * [F02] Song F2 - Artist F\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [F03] Song F3 - Artist F\n"
                 << "  * [F04] Song F4 - Artist F\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph08() {
        string name = "Graph08";
        
        MusicGraph g;
        g.addSong("G01", "Song G1", "Artist G", "Pop");
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [G01] Song G1 - Artist G\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph09() {
        string name = "Graph09";
        
        MusicGraph g;
        g.addSong("H01", "Song H1", "Artist H", "Pop");
        g.addSong("H02", "Song H2", "Artist H", "Rock");
        g.addSong("H03", "Song H3", "Artist H", "Jazz");
        
        // H01 -> H02 -> H03 (all connected in one component)
        g.addEdge("H01", "H02", 1.0, false);
        g.addEdge("H02", "H03", 1.5, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [H01] Song H1 - Artist H\n"
                 << "  * [H02] Song H2 - Artist H\n"
                 << "  * [H03] Song H3 - Artist H\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph10() {
        string name = "Graph10";
        
        MusicGraph g;
        g.addSong("I01", "Song I1", "Artist I", "Pop");
        g.addSong("I02", "Song I2", "Artist I", "Rock");
        
        // I01 -> I02, weighted edge
        g.addEdge("I01", "I02", 2.5, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [I01] Song I1 - Artist I\n"
                 << "To: [I02] Song I2 - Artist I\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 2.5\n"
                 << "-> Playback Order:\n"
                 << "   1. [I01] Song I1 - Artist I\n"
                 << "   2. [I02] Song I2 - Artist I\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("I01", "I02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph11() {
        string name = "Graph11";
        
        MusicGraph g;
        g.addSong("J01", "Song J1", "Artist J", "Pop");
        g.addSong("J02", "Song J2", "Artist J", "Rock");
        g.addSong("J03", "Song J3", "Artist J", "Jazz");
        
        // J01 -> J02 -> J03 (path with 2 edges)
        g.addEdge("J01", "J02", 1.0, false);
        g.addEdge("J02", "J03", 2.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [J01] Song J1 - Artist J\n"
                 << "To: [J03] Song J3 - Artist J\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 3\n"
                 << "-> Playback Order:\n"
                 << "   1. [J01] Song J1 - Artist J\n"
                 << "   2. [J02] Song J2 - Artist J\n"
                 << "   3. [J03] Song J3 - Artist J\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("J01", "J03");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph12() {
        string name = "Graph12";
        
        MusicGraph g;
        g.addSong("K01", "Song K1", "Artist K", "Pop");
        g.addSong("K02", "Song K2", "Artist K", "Rock");
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [K01] Song K1 - Artist K\n"
                 << "To: [K02] Song K2 - Artist K\n"
                 << "-------------------------------------------------\n"
                 << "No transition path between these two songs.";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("K01", "K02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph13() {
        string name = "Graph13";
        
        MusicGraph g;
        g.addSong("L01", "Song L1", "Artist L", "Pop");
        g.addSong("L02", "Song L2", "Artist L", "Rock");
        g.addSong("L03", "Song L3", "Artist L", "Jazz");
        
        // L01 -> L02, L01 -> L03, L02 -> L03 (multiple paths, test Dijkstra finds shortest)
        g.addEdge("L01", "L02", 5.0, false);
        g.addEdge("L01", "L03", 1.0, false);
        g.addEdge("L02", "L03", 1.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [L01] Song L1 - Artist L\n"
                 << "To: [L03] Song L3 - Artist L\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 1\n"
                 << "-> Playback Order:\n"
                 << "   1. [L01] Song L1 - Artist L\n"
                 << "   2. [L03] Song L3 - Artist L\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("L01", "L03");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph14() {
        string name = "Graph14";
        
        MusicGraph g;
        g.addSong("M01", "Song M1", "Artist M", "Pop");
        g.addSong("M02", "Song M2", "Artist M", "Rock");
        g.addSong("M03", "Song M3", "Artist M", "Jazz");
        
        // M02 -> M01, M03 -> M01, M03 -> M02 (test in-degree calculation)
        g.addEdge("M02", "M01", 1.0, false);
        g.addEdge("M03", "M01", 1.5, false);
        g.addEdge("M03", "M02", 2.0, false);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [M01] Song M1 - Artist M\n"
                 << "   (In-degree: 2)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph15() {
        string name = "Graph15";
        
        MusicGraph g;
        g.addSong("N01", "Song N1", "Artist N", "Pop");
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [N01] Song N1 - Artist N\n"
                 << "   (In-degree: 0)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph16() {
        string name = "Graph16";
        
        MusicGraph g;
        g.addSong("O01", "Song O1", "Artist O", "Pop");
        g.addSong("O02", "Song O2", "Artist O", "Rock");
        g.addSong("O03", "Song O3", "Artist O", "Jazz");
        g.addSong("O04", "Song O4", "Artist O", "Rap");
        
        // O01, O02, O03 all connect to O04
        g.addEdge("O01", "O04", 1.0, false);
        g.addEdge("O02", "O04", 1.5, false);
        g.addEdge("O03", "O04", 2.0, false);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [O04] Song O4 - Artist O\n"
                 << "   (In-degree: 3)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph17() {
        string name = "Graph17";
        
        MusicGraph g;
        g.addSong("P01", "Song P1", "Artist P", "Pop");
        g.addSong("P02", "Song P2", "Artist P", "Rock");
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "No music loop detected.\n";
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph18() {
        string name = "Graph18";
        
        MusicGraph g;
        g.addSong("Q01", "Song Q1", "Artist Q", "Pop");
        g.addSong("Q02", "Song Q2", "Artist Q", "Rock");
        g.addSong("Q03", "Song Q3", "Artist Q", "Jazz");
        
        // Q01 -> Q02 -> Q03 -> Q01 (cycle of 3)
        g.addEdge("Q01", "Q02", 1.0, false);
        g.addEdge("Q02", "Q03", 1.5, false);
        g.addEdge("Q03", "Q01", 2.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                    << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [Q01] Song Q1 - Artist Q\n"
                 << "   [Q02] Song Q2 - Artist Q\n"
                 << "   [Q03] Song Q3 - Artist Q\n"
                 << "   [Q01] Song Q1 - Artist Q\n";

        
        string output;
        // Just check if loop is detected, output format may vary
        output = captureOutput([&](){
            g.detectMusicLoop();
        });

        run_test(name, output, expected.str());
    }

    void Graph19() {
        string name = "Graph19";
        
        MusicGraph g;
        g.addSong("R01", "Song R1", "Artist R", "Pop");
        g.addSong("R02", "Song R2", "Artist R", "Rock");
        
        // R01 -> R02 -> R01 (simple 2-node cycle)
        g.addEdge("R01", "R02", 1.0, false);
        g.addEdge("R02", "R01", 1.5, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [R01] Song R1 - Artist R\n"
                 << "   [R02] Song R2 - Artist R\n"
                 << "   [R01] Song R1 - Artist R\n";
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph20() {
        string name = "Graph20";
        
        MusicGraph g;
        g.addSong("T01", "Song T1", "Artist T", "Pop");
        
        // T01 -> T01 (self-loop)
        g.addEdge("T01", "T01", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [T01] Song T1 - Artist T\n"
                 << "   [T01] Song T1 - Artist T\n";
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph21() {
        string name = "Graph21";
        
        MusicGraph g;
        g.addSong("U01", "Song U1", "Artist U", "Pop");
        g.addSong("U02", "Song U2", "Artist U", "Rock");
        g.addSong("U03", "Song U3", "Artist U", "Jazz");
        g.addSong("U04", "Song U4", "Artist U", "Rap");
        
        // Complex graph with multiple connections
        g.addEdge("U01", "U02", 1.0, false);
        g.addEdge("U01", "U03", 2.0, false);
        g.addEdge("U02", "U04", 1.5, false);
        g.addEdge("U03", "U04", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [U01] Song U1 - Artist U"
                 << "\n-------------------------------------------------\n"
                 << "-> [U02] Song U2 - Artist U\n"
                 << "-> [U03] Song U3 - Artist U\n"
                 << "-> [U04] Song U4 - Artist U\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("U01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph22() {
        string name = "Graph22";
        
        MusicGraph g;
        g.addSong("V01", "Song V1", "Artist V", "Pop");
        g.addSong("V02", "Song V2", "Artist V", "Rock");
        g.addSong("V03", "Song V3", "Artist V", "Jazz");
        g.addSong("V04", "Song V4", "Artist V", "Rap");
        
        // Complex graph with multiple connections
        g.addEdge("V01", "V02", 1.0, false);
        g.addEdge("V01", "V03", 2.0, false);
        g.addEdge("V02", "V04", 1.5, false);
        g.addEdge("V03", "V04", 1.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [V01] Song V1 - Artist V\n"
                 << "To: [V04] Song V4 - Artist V\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 2.5\n"
                 << "-> Playback Order:\n"
                 << "   1. [V01] Song V1 - Artist V\n"
                 << "   2. [V02] Song V2 - Artist V\n"
                 << "   3. [V04] Song V4 - Artist V\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("V01", "V04");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph23() {
        string name = "Graph23";
        
        MusicGraph g;
        g.addSong("W01", "Song W1", "Artist W", "Pop");
        g.addSong("W02", "Song W2", "Artist W", "Rock");
        g.addSong("W03", "Song W3", "Artist W", "Jazz");
        g.addSong("W04", "Song W4", "Artist W", "Rap");
        g.addSong("W05", "Song W5", "Artist W", "Ballad");
        
        // Three separate components
        g.addEdge("W01", "W02", 1.0, false);
        g.addEdge("W03", "W04", 1.5, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [W01] Song W1 - Artist W\n"
                 << "  * [W02] Song W2 - Artist W\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [W03] Song W3 - Artist W\n"
                 << "  * [W04] Song W4 - Artist W\n"
                 << "=== Playlist 3 ===" << endl
                 << "  * [W05] Song W5 - Artist W\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph24() {
        string name = "Graph24";
        
        MusicGraph g;
        g.addSong("X01", "Popular", "X Artist", "Pop");
        g.addSong("X02", "Song2", "X Artist", "Rock");
        g.addSong("X03", "Song3", "X Artist", "Jazz");
        g.addSong("X04", "Song4", "X Artist", "Rap");
        
        // X01 is the hub - all edges point to it
        g.addEdge("X02", "X01", 1.0, false);
        g.addEdge("X03", "X01", 1.5, false);
        g.addEdge("X04", "X01", 2.0, false);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [X01] Popular - X Artist\n"
                 << "   (In-degree: 3)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph25() {
        string name = "Graph25";
        
        MusicGraph g;
        g.addSong("Y01", "Song Y1", "Artist Y", "Pop");
        g.addSong("Y02", "Song Y2", "Artist Y", "Rock");
        g.addSong("Y03", "Song Y3", "Artist Y", "Jazz");
        
        // Star graph: Y02, Y03 connect to Y01
        g.addEdge("Y02", "Y01", 1.0, false);
        g.addEdge("Y03", "Y01", 1.5, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [Y02] Song Y2 - Artist Y"
                 << "\n-------------------------------------------------\n"
                 << "-> [Y01] Song Y1 - Artist Y\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("Y02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph26() {
        string name = "Graph26";
        
        MusicGraph g;
        g.addSong("Z01", "Song Z1", "Artist Z", "Pop");
        g.addSong("Z02", "Song Z2", "Artist Z", "Rock");
        g.addSong("Z03", "Song Z3", "Artist Z", "Jazz");
        g.addSong("Z04", "Song Z4", "Artist Z", "Rap");
        g.addSong("Z05", "Song Z5", "Artist Z", "Ballad");
        
        // Complex network with various weights
        g.addEdge("Z01", "Z02", 2.0, false);
        g.addEdge("Z02", "Z03", 1.0, false);
        g.addEdge("Z01", "Z04", 5.0, false);
        g.addEdge("Z04", "Z05", 1.0, false);
        g.addEdge("Z03", "Z05", 3.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [Z01] Song Z1 - Artist Z\n"
                 << "To: [Z05] Song Z5 - Artist Z\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 6\n"
                 << "-> Playback Order:\n"
                 << "   1. [Z01] Song Z1 - Artist Z\n"
                 << "   2. [Z02] Song Z2 - Artist Z\n"
                 << "   3. [Z03] Song Z3 - Artist Z\n"
                 << "   4. [Z05] Song Z5 - Artist Z\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("Z01", "Z05");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph27() {
        string name = "Graph27";
        
        MusicGraph g;
        g.addSong("AA01", "Song AA1", "Artist AA", "Pop");
        g.addSong("AA02", "Song AA2", "Artist AA", "Rock");
        g.addSong("AA03", "Song AA3", "Artist AA", "Jazz");
        
        // Bidirectional edges - test with undirected graph
        g.addEdge("AA01", "AA02", 1.5, true);
        g.addEdge("AA02", "AA03", 2.0, true);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [AA03] Song AA3 - Artist AA\n"
                 << "To: [AA01] Song AA1 - Artist AA\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 3.5\n"
                 << "-> Playback Order:\n"
                 << "   1. [AA03] Song AA3 - Artist AA\n"
                 << "   2. [AA02] Song AA2 - Artist AA\n"
                 << "   3. [AA01] Song AA1 - Artist AA\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("AA03", "AA01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph28() {
        string name = "Graph28";
        
        MusicGraph g;
        g.addSong("AB01", "Song AB1", "Artist AB", "Pop");
        g.addSong("AB02", "Song AB2", "Artist AB", "Rock");
        g.addSong("AB03", "Song AB3", "Artist AB", "Jazz");
        g.addSong("AB04", "Song AB4", "Artist AB", "Rap");
        
        // Bidirectional connections - test clusters with undirected edges
        g.addEdge("AB01", "AB02", 1.0, true);
        g.addEdge("AB03", "AB04", 1.5, true);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [AB01] Song AB1 - Artist AB\n"
                 << "  * [AB02] Song AB2 - Artist AB\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [AB03] Song AB3 - Artist AB\n"
                 << "  * [AB04] Song AB4 - Artist AB\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph29() {
        string name = "Graph29";
        
        MusicGraph g;
        g.addSong("AC01", "Song AC1", "Artist AC", "Pop");
        g.addSong("AC02", "Song AC2", "Artist AC", "Rock");
        g.addSong("AC03", "Song AC3", "Artist AC", "Jazz");
        
        // AC01 -> AC02 -> AC03 -> AC02 (cycle at AC02 and AC03)
        g.addEdge("AC01", "AC02", 1.0, false);
        g.addEdge("AC02", "AC03", 1.5, false);
        g.addEdge("AC03", "AC02", 2.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [AC02] Song AC2 - Artist AC\n"
                 << "   [AC03] Song AC3 - Artist AC\n"
                 << "   [AC02] Song AC2 - Artist AC\n";
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph30() {
        string name = "Graph30";
        
        MusicGraph g;
        g.addSong("AD01", "Song AD1", "Artist AD", "Pop");
        g.addSong("AD02", "Song AD2", "Artist AD", "Rock");
        g.addSong("AD03", "Song AD3", "Artist AD", "Jazz");
        g.addSong("AD04", "Song AD4", "Artist AD", "Rap");
        g.addSong("AD05", "Song AD5", "Artist AD", "Ballad");
        
        // Complex: Multiple components with various configurations
        g.addEdge("AD01", "AD02", 1.0, true);   // Bidirectional
        g.addEdge("AD02", "AD03", 1.5, false);  // Unidirectional
        g.addEdge("AD04", "AD05", 2.0, false);  // Unidirectional
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [AD01] Song AD1 - Artist AD\n"
                 << "  * [AD02] Song AD2 - Artist AD\n"
                 << "  * [AD03] Song AD3 - Artist AD\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [AD04] Song AD4 - Artist AD\n"
                 << "  * [AD05] Song AD5 - Artist AD\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph31() {
        string name = "Graph31";
        MusicGraph g;
        g.addSong("S01", "Song S01", "Artist AD", "Pop");
        g.addSong("S02", "Song S02", "Artist AD", "Pop");
        g.addSong("S03", "Song S03", "Artist AD", "Pop");
        g.addSong("S04", "Song S04", "Artist AD", "Pop");

        g.addEdge("S01","S02", 1.5, false);
        g.addEdge("S01","S03", 1.5, false);
        g.addEdge("S03","S04", 1.5, false);

        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                    << "-------------------------------------------------\n"
                    << "=== Playlist 1 ===" << endl
                    << "  * [S01] Song S01 - Artist AD\n"
                    << "  * [S02] Song S02 - Artist AD\n"
                    << "  * [S03] Song S03 - Artist AD\n"
                    << "  * [S04] Song S04 - Artist AD\n";
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });

        run_test(name, output, expected.str());
    }

    void Graph32() {
        string name = "Graph32";
        MusicGraph g;
        g.addSong("S01", "Song S01", "Artist AD", "Pop");
        g.addSong("S02", "Song S02", "Artist AD", "Pop");
        g.addSong("S03", "Song S03", "Artist AD", "Pop");
        g.addSong("S04", "Song S04", "Artist AD", "Pop");

        g.addEdge("S01", "S02", 0, false);
        g.addEdge("S03", "S04", 0, false);

        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                    << "-------------------------------------------------\n"
                    << "=== Playlist 1 ===" << endl
                    << "  * [S01] Song S01 - Artist AD\n"
                    << "  * [S02] Song S02 - Artist AD\n"
                    << "=== Playlist 2 ===" << endl
                    << "  * [S03] Song S03 - Artist AD\n"
                    << "  * [S04] Song S04 - Artist AD\n";
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });

        run_test(name, output, expected.str());
    }

    void Graph33() {
        string name = "Graph33";
        MusicGraph g;
        g.addSong("P01", "Perfect Day", "Lou Reed", "Rock");
        
        stringstream expected;
        expected << "[P01] Perfect Day - Lou Reed";
        
        string output = captureOutput([&]() {
            g.printSongInfo("P01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph34() {
        string name = "Graph34";
        MusicGraph g;
        g.addSong("P02", "Bohemian Rhapsody", "Queen", "Rock");
        g.addSong("P03", "Stairway to Heaven", "Led Zeppelin", "Rock");
        
        stringstream expected;
        expected << "[P02] Bohemian Rhapsody - Queen";
        
        string output = captureOutput([&]() {
            g.printSongInfo("P02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph35() {
        string name = "Graph35";
        MusicGraph g;
        g.addSong("P04", "Song Name", "Artist Name", "Jazz");
        
        stringstream expected;
        expected << "[P04] Song Name - Artist Name";
        
        string output = captureOutput([&]() {
            g.printSongInfo("P04");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph36() {
        string name = "Graph36";
        MusicGraph g;
        g.addSong("Q01", "Track Q1", "Artist Q", "Pop");
        g.addSong("Q02", "Track Q2", "Artist Q", "Pop");
        g.addSong("Q03", "Track Q3", "Artist Q", "Pop");
        g.addSong("Q04", "Track Q4", "Artist Q", "Pop");
        g.addSong("Q05", "Track Q5", "Artist Q", "Pop");
        
        // Q01 -> Q02 -> Q03 -> Q04 -> Q05 (linear chain)
        g.addEdge("Q01", "Q02", 1.0, false);
        g.addEdge("Q02", "Q03", 1.0, false);
        g.addEdge("Q03", "Q04", 1.0, false);
        g.addEdge("Q04", "Q05", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [Q01] Track Q1 - Artist Q"
                 << "\n-------------------------------------------------\n"
                 << "-> [Q02] Track Q2 - Artist Q\n"
                 << "-> [Q03] Track Q3 - Artist Q\n"
                 << "-> [Q04] Track Q4 - Artist Q\n"
                 << "-> [Q05] Track Q5 - Artist Q\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("Q01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph37() {
        string name = "Graph37";
        MusicGraph g;
        g.addSong("R01", "Track R1", "Artist R", "Pop");
        g.addSong("R02", "Track R2", "Artist R", "Pop");
        g.addSong("R03", "Track R3", "Artist R", "Pop");
        
        // R01 -> R02, R01 -> R03 (one node connecting to multiple)
        g.addEdge("R01", "R02", 1.0, false);
        g.addEdge("R01", "R03", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [R01] Track R1 - Artist R"
                 << "\n-------------------------------------------------\n"
                 << "-> [R02] Track R2 - Artist R\n"
                 << "-> [R03] Track R3 - Artist R\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("R01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph38() {
        string name = "Graph38";
        MusicGraph g;
        g.addSong("S02", "Track S1", "Artist S", "Pop");
        g.addSong("S03", "Track S2", "Artist S", "Pop");
        g.addSong("S04", "Track S3", "Artist S", "Pop");
        g.addSong("S05", "Track S4", "Artist S", "Pop");
        
        // Multiple nodes connect to S02 (S02 is hub in terms of out-edges)
        g.addEdge("S02", "S03", 1.0, false);
        g.addEdge("S02", "S04", 1.0, false);
        g.addEdge("S02", "S05", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [S02] Track S1 - Artist S"
                 << "\n-------------------------------------------------\n"
                 << "-> [S03] Track S2 - Artist S\n"
                 << "-> [S04] Track S3 - Artist S\n"
                 << "-> [S05] Track S4 - Artist S\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("S02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph39() {
        string name = "Graph39";
        MusicGraph g;
        g.addSong("T02", "Track T1", "Artist T", "Pop");
        g.addSong("T03", "Track T2", "Artist T", "Pop");
        g.addSong("T04", "Track T3", "Artist T", "Pop");
        g.addSong("T05", "Track T4", "Artist T", "Pop");
        
        // Complex graph with multiple paths
        g.addEdge("T02", "T03", 1.0, false);
        g.addEdge("T02", "T04", 1.0, false);
        g.addEdge("T03", "T05", 1.0, false);
        g.addEdge("T04", "T05", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [T02] Track T1 - Artist T"
                 << "\n-------------------------------------------------\n"
                 << "-> [T03] Track T2 - Artist T\n"
                 << "-> [T04] Track T3 - Artist T\n"
                 << "-> [T05] Track T4 - Artist T\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("T02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph40() {
        string name = "Graph40";
        MusicGraph g;
        g.addSong("U02", "Track U1", "Artist U", "Pop");
        g.addSong("U03", "Track U2", "Artist U", "Pop");
        g.addSong("U04", "Track U3", "Artist U", "Pop");
        g.addSong("U05", "Track U4", "Artist U", "Pop");
        
        // U02 and U03 are disconnected from U04 and U05
        g.addEdge("U02", "U03", 1.0, false);
        g.addEdge("U04", "U05", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [U02] Track U1 - Artist U"
                 << "\n-------------------------------------------------\n"
                 << "-> [U03] Track U2 - Artist U\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("U02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph41() {
        string name = "Graph41";
        MusicGraph g;
        g.addSong("V02", "Song V1", "Artist V", "Pop");
        g.addSong("V03", "Song V2", "Artist V", "Pop");
        g.addSong("V04", "Song V3", "Artist V", "Pop");
        g.addSong("V05", "Song V4", "Artist V", "Pop");
        g.addSong("V06", "Song V5", "Artist V", "Pop");
        
        // Three clusters: V02-V03, V04-V05, V06 isolated
        g.addEdge("V02", "V03", 1.0, true);
        g.addEdge("V04", "V05", 1.5, true);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [V02] Song V1 - Artist V\n"
                 << "  * [V03] Song V2 - Artist V\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [V04] Song V3 - Artist V\n"
                 << "  * [V05] Song V4 - Artist V\n"
                 << "=== Playlist 3 ===" << endl
                 << "  * [V06] Song V5 - Artist V\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph42() {
        string name = "Graph42";
        MusicGraph g;
        g.addSong("W02", "Song W1", "Artist W", "Pop");
        g.addSong("W03", "Song W2", "Artist W", "Pop");
        g.addSong("W04", "Song W3", "Artist W", "Pop");
        
        // Large component with directed edges
        g.addEdge("W02", "W03", 1.0, false);
        g.addEdge("W03", "W04", 1.0, false);
        g.addEdge("W02", "W04", 1.5, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [W02] Song W1 - Artist W\n"
                 << "  * [W03] Song W2 - Artist W\n"
                 << "  * [W04] Song W3 - Artist W\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph43() {
        string name = "Graph43";
        MusicGraph g;
        g.addSong("X02", "Song X1", "Artist X", "Pop");
        g.addSong("X03", "Song X2", "Artist X", "Pop");
        g.addSong("X04", "Song X3", "Artist X", "Pop");
        g.addSong("X05", "Song X4", "Artist X", "Pop");
        g.addSong("X06", "Song X5", "Artist X", "Pop");
        g.addSong("X07", "Song X6", "Artist X", "Pop");
        
        // Two large bidirectional clusters
        g.addEdge("X02", "X03", 1.0, true);
        g.addEdge("X03", "X04", 1.0, true);
        g.addEdge("X05", "X06", 1.0, true);
        g.addEdge("X06", "X07", 1.0, true);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [X02] Song X1 - Artist X\n"
                 << "  * [X03] Song X2 - Artist X\n"
                 << "  * [X04] Song X3 - Artist X\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [X05] Song X4 - Artist X\n"
                 << "  * [X06] Song X5 - Artist X\n"
                 << "  * [X07] Song X6 - Artist X\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph44() {
        string name = "Graph44";
        MusicGraph g;
        g.addSong("Y02", "Song Y1", "Artist Y", "Pop");
        g.addSong("Y03", "Song Y2", "Artist Y", "Pop");
        g.addSong("Y04", "Song Y3", "Artist Y", "Pop");
        g.addSong("Y05", "Song Y4", "Artist Y", "Pop");
        
        // All songs isolated (no edges)
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [Y02] Song Y1 - Artist Y\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [Y03] Song Y2 - Artist Y\n"
                 << "=== Playlist 3 ===" << endl
                 << "  * [Y04] Song Y3 - Artist Y\n"
                 << "=== Playlist 4 ===" << endl
                 << "  * [Y05] Song Y4 - Artist Y\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph45() {
        string name = "Graph45";
        MusicGraph g;
        g.addSong("Z02", "Song Z1", "Artist Z", "Pop");
        g.addSong("Z03", "Song Z2", "Artist Z", "Pop");
        g.addSong("Z04", "Song Z3", "Artist Z", "Pop");
        g.addSong("Z05", "Song Z4", "Artist Z", "Pop");
        g.addSong("Z06", "Song Z5", "Artist Z", "Pop");
        
        // Complex network with multiple paths of different weights
        g.addEdge("Z02", "Z03", 1.0, false);
        g.addEdge("Z02", "Z04", 10.0, false);
        g.addEdge("Z03", "Z05", 1.0, false);
        g.addEdge("Z04", "Z05", 1.0, false);
        g.addEdge("Z05", "Z06", 1.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [Z02] Song Z1 - Artist Z\n"
                 << "To: [Z06] Song Z5 - Artist Z\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 3\n"
                 << "-> Playback Order:\n"
                 << "   1. [Z02] Song Z1 - Artist Z\n"
                 << "   2. [Z03] Song Z2 - Artist Z\n"
                 << "   3. [Z05] Song Z4 - Artist Z\n"
                 << "   4. [Z06] Song Z5 - Artist Z\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("Z02", "Z06");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph46() {
        string name = "Graph46";
        MusicGraph g;
        g.addSong("AA02", "Song AA1", "Artist AA", "Pop");
        g.addSong("AA03", "Song AA2", "Artist AA", "Pop");
        g.addSong("AA04", "Song AA3", "Artist AA", "Pop");
        g.addSong("AA05", "Song AA4", "Artist AA", "Pop");
        
        // Star graph with center AA02
        g.addEdge("AA02", "AA03", 2.0, false);
        g.addEdge("AA02", "AA04", 3.0, false);
        g.addEdge("AA02", "AA05", 1.5, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [AA02] Song AA1 - Artist AA\n"
                 << "To: [AA05] Song AA4 - Artist AA\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 1.5\n"
                 << "-> Playback Order:\n"
                 << "   1. [AA02] Song AA1 - Artist AA\n"
                 << "   2. [AA05] Song AA4 - Artist AA\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("AA02", "AA05");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph47() {
        string name = "Graph47";
        MusicGraph g;
        g.addSong("AB02", "Song AB1", "Artist AB", "Pop");
        g.addSong("AB03", "Song AB2", "Artist AB", "Pop");
        g.addSong("AB04", "Song AB3", "Artist AB", "Pop");
        g.addSong("AB05", "Song AB4", "Artist AB", "Pop");
        
        // Bidirectional graph - test reverse path
        g.addEdge("AB02", "AB03", 2.0, true);
        g.addEdge("AB03", "AB04", 3.0, true);
        g.addEdge("AB04", "AB05", 1.5, true);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [AB05] Song AB4 - Artist AB\n"
                 << "To: [AB02] Song AB1 - Artist AB\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 6.5\n"
                 << "-> Playback Order:\n"
                 << "   1. [AB05] Song AB4 - Artist AB\n"
                 << "   2. [AB04] Song AB3 - Artist AB\n"
                 << "   3. [AB03] Song AB2 - Artist AB\n"
                 << "   4. [AB02] Song AB1 - Artist AB\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("AB05", "AB02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph48() {
        string name = "Graph48";
        MusicGraph g;
        g.addSong("AC02", "Song AC1", "Artist AC", "Pop");
        g.addSong("AC03", "Song AC2", "Artist AC", "Pop");
        g.addSong("AC04", "Song AC3", "Artist AC", "Pop");
        g.addSong("AC05", "Song AC4", "Artist AC", "Pop");
        
        // Bidirectional edges - equal in-degree
        g.addEdge("AC02", "AC03", 1.0, true);
        g.addEdge("AC02", "AC04", 1.0, true);
        g.addEdge("AC02", "AC05", 1.0, true);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [AC02] Song AC1 - Artist AC\n"
                 << "   (In-degree: 3)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph49() {
        string name = "Graph49";
        MusicGraph g;
        g.addSong("AD02", "Song AD1", "Artist AD", "Pop");
        g.addSong("AD03", "Song AD2", "Artist AD", "Pop");
        g.addSong("AD04", "Song AD3", "Artist AD", "Pop");
        g.addSong("AD05", "Song AD4", "Artist AD", "Pop");
        g.addSong("AD06", "Song AD5", "Artist AD", "Pop");
        
        // Multiple songs with same in-degree (tie scenario)
        g.addEdge("AD02", "AD05", 1.0, false);
        g.addEdge("AD03", "AD05", 1.0, false);
        g.addEdge("AD04", "AD06", 1.0, false);
        g.addEdge("AD02", "AD06", 1.0, false);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [AD06] Song AD5 - Artist AD\n"
                 << "   (In-degree: 2)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph50() {
        string name = "Graph50";
        MusicGraph g;
        g.addSong("AE02", "Song AE1", "Artist AE", "Pop");
        g.addSong("AE03", "Song AE2", "Artist AE", "Pop");
        g.addSong("AE04", "Song AE3", "Artist AE", "Pop");
        g.addSong("AE05", "Song AE4", "Artist AE", "Pop");
        
        // Long cycle: AE02 -> AE03 -> AE04 -> AE05 -> AE02
        g.addEdge("AE02", "AE03", 1.0, false);
        g.addEdge("AE03", "AE04", 1.0, false);
        g.addEdge("AE04", "AE05", 1.0, false);
        g.addEdge("AE05", "AE02", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [AE02] Song AE1 - Artist AE\n"
                 << "   [AE03] Song AE2 - Artist AE\n"
                 << "   [AE04] Song AE3 - Artist AE\n"
                 << "   [AE05] Song AE4 - Artist AE\n"
                 << "   [AE02] Song AE1 - Artist AE\n";
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    //empty graph
    void Graph51() {
        string name = "Graph51";
        MusicGraph g;

        string expected = "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n-------------------------------------------------\n";
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });

        run_test(name, output, expected);
    }

    void Graph52() {
        string name = "Graph52";
        MusicGraph g;
        g.addSong("AE02", "Song AE1", "Artist AE", "Pop");
        g.addSong("AE03", "Song AE2", "Artist AE", "Pop");
        g.addSong("AE04", "Song AE3", "Artist AE", "Pop");
        g.addSong("AE05", "Song AE4", "Artist AE", "Pop");

        g.addEdge("AE02", "AE03", 0, false);
        g.addEdge("AE04", "AE03", 0, false);
        g.addEdge("AE05", "AE03", 0, false);

        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                    << "-------------------------------------------------\n"
                    << "-> Network Hub Song:\n"
                    << "   [AE03] Song AE2 - Artist AE\n"
                    << "   (In-degree: 3)";

        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });

        run_test(name, output, expected.str());
    }

    void Graph53() {
        string name = "Graph53";
        MusicGraph g;
        g.addSong("AE02", "Song AE1", "Artist AE", "Pop");
        g.addSong("AE03", "Song AE2", "Artist AE", "Pop");
        g.addSong("AE04", "Song AE3", "Artist AE", "Pop");
        g.addSong("AE05", "Song AE4", "Artist AE", "Pop");

        g.addEdge("AE02", "AE03", 0, false);
        g.addEdge("AE03", "AE04", 0, false);
        g.addEdge("AE04", "AE05", 0, false);

        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "No music loop detected.\n";

        string output = captureOutput([&](){
            g.detectMusicLoop();
        });

        run_test(name, output, expected.str());
    }

    // ===== GRAPH54-GRAPH100: NEW TEST CASES (47 Tests) =====

    // ===== NHÓM 1: recommendRelatedSongs() Edge Cases =====
    void Graph54() {
        string name = "Graph54";
        MusicGraph g;
        g.addSong("BA01", "Track BA1", "Artist BA", "Pop");
        g.addSong("BA02", "Track BA2", "Artist BA", "Rock");
        g.addSong("BA03", "Track BA3", "Artist BA", "Jazz");
        g.addSong("BA04", "Track BA4", "Artist BA", "Rap");
        g.addSong("BA05", "Track BA5", "Artist BA", "Classical");
        g.addSong("BA06", "Track BA6", "Artist BA", "Electronic");
        
        // Long chain: BA01 -> BA02 -> BA03 -> BA04 -> BA05 -> BA06
        g.addEdge("BA01", "BA02", 1.0, false);
        g.addEdge("BA02", "BA03", 1.0, false);
        g.addEdge("BA03", "BA04", 1.0, false);
        g.addEdge("BA04", "BA05", 1.0, false);
        g.addEdge("BA05", "BA06", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BA01] Track BA1 - Artist BA"
                 << "\n-------------------------------------------------\n"
                 << "-> [BA02] Track BA2 - Artist BA\n"
                 << "-> [BA03] Track BA3 - Artist BA\n"
                 << "-> [BA04] Track BA4 - Artist BA\n"
                 << "-> [BA05] Track BA5 - Artist BA\n"
                 << "-> [BA06] Track BA6 - Artist BA\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BA01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph55() {
        string name = "Graph55";
        MusicGraph g;
        g.addSong("BB01", "Root", "Artist BB", "Pop");
        g.addSong("BB02", "Branch1", "Artist BB", "Rock");
        g.addSong("BB03", "Branch2", "Artist BB", "Jazz");
        g.addSong("BB04", "Branch3", "Artist BB", "Rap");
        g.addSong("BB05", "Branch4", "Artist BB", "Classical");
        
        // Wide branching: BB01 -> BB02, BB03, BB04, BB05
        g.addEdge("BB01", "BB02", 1.0, false);
        g.addEdge("BB01", "BB03", 1.0, false);
        g.addEdge("BB01", "BB04", 1.0, false);
        g.addEdge("BB01", "BB05", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BB01] Root - Artist BB"
                 << "\n-------------------------------------------------\n"
                 << "-> [BB02] Branch1 - Artist BB\n"
                 << "-> [BB03] Branch2 - Artist BB\n"
                 << "-> [BB04] Branch3 - Artist BB\n"
                 << "-> [BB05] Branch4 - Artist BB\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BB01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph56() {
        string name = "Graph56";
        MusicGraph g;
        g.addSong("BC01", "Level0", "Artist BC", "Pop");
        g.addSong("BC02", "Level1A", "Artist BC", "Rock");
        g.addSong("BC03", "Level1B", "Artist BC", "Jazz");
        g.addSong("BC04", "Level2A", "Artist BC", "Rap");
        
        // Tree: BC01 -> BC02 -> BC04, BC01 -> BC03
        g.addEdge("BC01", "BC02", 1.0, false);
        g.addEdge("BC01", "BC03", 1.0, false);
        g.addEdge("BC02", "BC04", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BC01] Level0 - Artist BC"
                 << "\n-------------------------------------------------\n"
                 << "-> [BC02] Level1A - Artist BC\n"
                 << "-> [BC03] Level1B - Artist BC\n"
                 << "-> [BC04] Level2A - Artist BC\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BC01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph57() {
        string name = "Graph57";
        MusicGraph g;
        g.addSong("BD01", "Song BD1", "Artist BD", "Pop");
        g.addSong("BD02", "Song BD2", "Artist BD", "Rock");
        g.addSong("BD03", "Song BD3", "Artist BD", "Jazz");
        
        // Bidirectional cycle: BD01 <-> BD02 <-> BD03 <-> BD01
        g.addEdge("BD01", "BD02", 1.0, true);
        g.addEdge("BD02", "BD03", 1.0, true);
        g.addEdge("BD03", "BD01", 1.0, true);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BD01] Song BD1 - Artist BD"
                 << "\n-------------------------------------------------\n"
                 << "-> [BD02] Song BD2 - Artist BD\n"
                 << "-> [BD03] Song BD3 - Artist BD\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BD01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph58() {
        string name = "Graph58";
        MusicGraph g;
        g.addSong("BE01", "Hub", "Artist BE", "Pop");
        g.addSong("BE02", "Solo1", "Artist BE", "Rock");
        g.addSong("BE03", "Solo2", "Artist BE", "Jazz");
        
        // Very sparse: Only BE01 -> BE02, BE03 isolated
        g.addEdge("BE01", "BE02", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BE03] Solo2 - Artist BE"
                 << "\n-------------------------------------------------\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BE03");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph59() {
        string name = "Graph59";
        MusicGraph g;
        g.addSong("BF01", "T1", "Artist BF", "Pop");
        g.addSong("BF02", "T2", "Artist BF", "Rock");
        g.addSong("BF03", "T3", "Artist BF", "Jazz");
        g.addSong("BF04", "T4", "Artist BF", "Rap");
        
        // Linear all bidirectional: BF01 <-> BF02 <-> BF03 <-> BF04
        g.addEdge("BF01", "BF02", 1.0, true);
        g.addEdge("BF02", "BF03", 1.0, true);
        g.addEdge("BF03", "BF04", 1.0, true);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BF02] T2 - Artist BF"
                 << "\n-------------------------------------------------\n"
                 << "-> [BF01] T1 - Artist BF\n"
                 << "-> [BF03] T3 - Artist BF\n"
                 << "-> [BF04] T4 - Artist BF\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BF02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph60() {
        string name = "Graph60";
        MusicGraph g;
        g.addSong("BG01", "S1", "Artist BG", "Pop");
        g.addSong("BG02", "S2", "Artist BG", "Rock");
        g.addSong("BG03", "S3", "Artist BG", "Jazz");
        g.addSong("BG04", "S4", "Artist BG", "Rap");
        g.addSong("BG05", "S5", "Artist BG", "Classical");
        
        // Diamond + Extra: BG01 -> BG02,BG03 -> BG04 <- BG03,BG05 -> BG04
        g.addEdge("BG01", "BG02", 1.0, false);
        g.addEdge("BG01", "BG03", 1.0, false);
        g.addEdge("BG02", "BG04", 1.0, false);
        g.addEdge("BG03", "BG04", 1.0, false);
        g.addEdge("BG05", "BG04", 1.0, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BG01] S1 - Artist BG"
                 << "\n-------------------------------------------------\n"
                 << "-> [BG02] S2 - Artist BG\n"
                 << "-> [BG03] S3 - Artist BG\n"
                 << "-> [BG04] S4 - Artist BG\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BG01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph61() {
        string name = "Graph61";
        MusicGraph g;
        g.addSong("BH01", "S1", "Artist BH", "Pop");
        g.addSong("BH02", "S2", "Artist BH", "Rock");
        g.addSong("BH03", "S3", "Artist BH", "Jazz");
        g.addSong("BH04", "S4", "Artist BH", "Rap");
        
        // Different weights (edge case)
        g.addEdge("BH01", "BH02", 0.5, false);
        g.addEdge("BH01", "BH03", 100.0, false);
        g.addEdge("BH02", "BH04", 0.01, false);
        
        stringstream expected;
        expected << "\n[1] SUGGEST RELATED SONGS FOR: [BH01] S1 - Artist BH"
                 << "\n-------------------------------------------------\n"
                 << "-> [BH02] S2 - Artist BH\n"
                 << "-> [BH03] S3 - Artist BH\n"
                 << "-> [BH04] S4 - Artist BH\n";
        
        string output = captureOutput([&]() {
            g.recommendRelatedSongs("BH01");
        });
        
        run_test(name, output, expected.str());
    }

    // ===== NHÓM 2: generatePlaylistsByClusters() Edge Cases =====
    void Graph62() {
        string name = "Graph62";
        MusicGraph g;
        g.addSong("BI01", "C1N1", "Artist BI", "Pop");
        g.addSong("BI02", "C1N2", "Artist BI", "Rock");
        g.addSong("BI03", "C2N1", "Artist BI", "Jazz");
        g.addSong("BI04", "C2N2", "Artist BI", "Rap");
        g.addSong("BI05", "C2N3", "Artist BI", "Classical");
        
        // 2 clusters: sizes 2 and 3
        g.addEdge("BI01", "BI02", 1.0, false);
        g.addEdge("BI03", "BI04", 1.0, true);
        g.addEdge("BI04", "BI05", 1.0, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BI01] C1N1 - Artist BI\n"
                 << "  * [BI02] C1N2 - Artist BI\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [BI03] C2N1 - Artist BI\n"
                 << "  * [BI04] C2N2 - Artist BI\n"
                 << "  * [BI05] C2N3 - Artist BI\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph63() {
        string name = "Graph63";
        MusicGraph g;
        g.addSong("BJ01", "Song1", "Artist BJ", "Pop");
        g.addSong("BJ02", "Song2", "Artist BJ", "Rock");
        g.addSong("BJ03", "Song3", "Artist BJ", "Jazz");
        
        // Self-loops in clusters
        g.addEdge("BJ01", "BJ01", 1.0, false);
        g.addEdge("BJ02", "BJ03", 1.0, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BJ01] Song1 - Artist BJ\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [BJ02] Song2 - Artist BJ\n"
                 << "  * [BJ03] Song3 - Artist BJ\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph64() {
        string name = "Graph64";
        MusicGraph g;
        g.addSong("BK01", "L0", "Artist BK", "Pop");
        g.addSong("BK02", "L1", "Artist BK", "Rock");
        g.addSong("BK03", "L2", "Artist BK", "Jazz");
        g.addSong("BK04", "L3", "Artist BK", "Rap");
        g.addSong("BK05", "L4", "Artist BK", "Classical");
        
        // Very deep single cluster
        g.addEdge("BK01", "BK02", 1.0, false);
        g.addEdge("BK02", "BK03", 1.0, false);
        g.addEdge("BK03", "BK04", 1.0, false);
        g.addEdge("BK04", "BK05", 1.0, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BK01] L0 - Artist BK\n"
                 << "  * [BK02] L1 - Artist BK\n"
                 << "  * [BK03] L2 - Artist BK\n"
                 << "  * [BK04] L3 - Artist BK\n"
                 << "  * [BK05] L4 - Artist BK\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph65() {
        string name = "Graph65";
        MusicGraph g;
        g.addSong("BL1", "I1", "Artist BL", "Pop");
        g.addSong("BL2", "I2", "Artist BL", "Rock");
        g.addSong("BL3", "I3", "Artist BL", "Jazz");
        g.addSong("BL4", "I4", "Artist BL", "Rap");
        g.addSong("BL5", "I5", "Artist BL", "Classical");
        g.addSong("BL6", "I6", "Artist BL", "Electronic");
        g.addSong("BL7", "I7", "Artist BL", "Acoustic");
        g.addSong("BL8", "I8", "Artist BL", "Soul");
        g.addSong("BL9", "I9", "Artist BL", "Blues");
        g.addSong("BL10", "I10", "Artist BL", "Folk");
        
        // Many isolated nodes
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n";
        for (int i = 1; i <= 10; i++) {
            expected << "=== Playlist " << i << " ===" << endl
                     << "  * [BL" << i << "] I" << i << " - Artist BL\n";
        }
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph66() {
        string name = "Graph66";
        MusicGraph g;
        g.addSong("BM01", "S1", "Artist BM", "Pop");
        g.addSong("BM02", "S2", "Artist BM", "Rock");
        g.addSong("BM03", "S3", "Artist BM", "Jazz");
        g.addSong("BM04", "S4", "Artist BM", "Rap");
        
        // Mixed: Bidirectional and unidirectional
        g.addEdge("BM01", "BM02", 1.0, true);
        g.addEdge("BM02", "BM03", 1.0, false);
        g.addEdge("BM03", "BM04", 1.0, true);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BM01] S1 - Artist BM\n"
                 << "  * [BM02] S2 - Artist BM\n"
                 << "  * [BM03] S3 - Artist BM\n"
                 << "  * [BM04] S4 - Artist BM\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph67() {
        string name = "Graph67";
        MusicGraph g;
        g.addSong("BN01", "C1A", "Artist BN", "Pop");
        g.addSong("BN02", "C1B", "Artist BN", "Rock");
        g.addSong("BN03", "C2A", "Artist BN", "Jazz");
        g.addSong("BN04", "C2B", "Artist BN", "Rap");
        g.addSong("BN05", "C3A", "Artist BN", "Classical");
        g.addSong("BN06", "C3B", "Artist BN", "Electronic");
        
        // 3 clusters with equal node counts
        g.addEdge("BN01", "BN02", 1.0, false);
        g.addEdge("BN03", "BN04", 1.0, false);
        g.addEdge("BN05", "BN06", 1.0, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BN01] C1A - Artist BN\n"
                 << "  * [BN02] C1B - Artist BN\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [BN03] C2A - Artist BN\n"
                 << "  * [BN04] C2B - Artist BN\n"
                 << "=== Playlist 3 ===" << endl
                 << "  * [BN05] C3A - Artist BN\n"
                 << "  * [BN06] C3B - Artist BN\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph68() {
        string name = "Graph68";
        MusicGraph g;
        g.addSong("BO01", "Giant1", "Artist BO", "Pop");
        g.addSong("BO02", "Giant2", "Artist BO", "Rock");
        g.addSong("BO03", "Giant3", "Artist BO", "Jazz");
        g.addSong("BO04", "Giant4", "Artist BO", "Rap");
        g.addSong("BO05", "Isolated1", "Artist BO", "Classical");
        g.addSong("BO06", "Isolated2", "Artist BO", "Electronic");
        
        // One giant cluster + 2 isolated
        g.addEdge("BO01", "BO02", 1.0, false);
        g.addEdge("BO02", "BO03", 1.0, false);
        g.addEdge("BO03", "BO04", 1.0, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BO01] Giant1 - Artist BO\n"
                 << "  * [BO02] Giant2 - Artist BO\n"
                 << "  * [BO03] Giant3 - Artist BO\n"
                 << "  * [BO04] Giant4 - Artist BO\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [BO05] Isolated1 - Artist BO\n"
                 << "=== Playlist 3 ===" << endl
                 << "  * [BO06] Isolated2 - Artist BO\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph69() {
        string name = "Graph69";
        MusicGraph g;
        g.addSong("BP01", "T1A", "Artist BP", "Pop");
        g.addSong("BP02", "T1B", "Artist BP", "Rock");
        g.addSong("BP03", "T1C", "Artist BP", "Jazz");
        g.addSong("BP04", "T2A", "Artist BP", "Rap");
        g.addSong("BP05", "T2B", "Artist BP", "Classical");
        g.addSong("BP06", "T2C", "Artist BP", "Electronic");
        
        // 3 bidirectional triangles
        g.addEdge("BP01", "BP02", 1.0, true);
        g.addEdge("BP02", "BP03", 1.0, true);
        g.addEdge("BP03", "BP01", 1.0, true);
        
        g.addEdge("BP04", "BP05", 1.0, true);
        g.addEdge("BP05", "BP06", 1.0, true);
        g.addEdge("BP06", "BP04", 1.0, true);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BP01] T1A - Artist BP\n"
                 << "  * [BP02] T1B - Artist BP\n"
                 << "  * [BP03] T1C - Artist BP\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [BP04] T2A - Artist BP\n"
                 << "  * [BP05] T2B - Artist BP\n"
                 << "  * [BP06] T2C - Artist BP\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph70() {
        string name = "Graph70";
        MusicGraph g;
        g.addSong("BQ01", "C1", "Artist BQ", "Pop");
        g.addSong("BQ02", "C1-C2", "Artist BQ", "Rock");
        g.addSong("BQ03", "C2", "Artist BQ", "Jazz");
        g.addSong("BQ04", "C2-C3", "Artist BQ", "Rap");
        g.addSong("BQ05", "C3", "Artist BQ", "Classical");
        
        // Chain of clusters connected
        g.addEdge("BQ01", "BQ02", 1.0, false);
        g.addEdge("BQ02", "BQ03", 1.0, false);
        g.addEdge("BQ03", "BQ04", 1.0, false);
        g.addEdge("BQ04", "BQ05", 1.0, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BQ01] C1 - Artist BQ\n"
                 << "  * [BQ02] C1-C2 - Artist BQ\n"
                 << "  * [BQ03] C2 - Artist BQ\n"
                 << "  * [BQ04] C2-C3 - Artist BQ\n"
                 << "  * [BQ05] C3 - Artist BQ\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph71() {
        string name = "Graph71";
        MusicGraph g;
        g.addSong("BR01", "M1", "Artist BR", "Pop");
        g.addSong("BR02", "M2", "Artist BR", "Rock");
        g.addSong("BR03", "M3", "Artist BR", "Jazz");
        g.addSong("BR04", "M4", "Artist BR", "Rap");
        g.addSong("BR05", "M5", "Artist BR", "Classical");
        
        // Complex: BR01 -> BR02 <- BR03, BR04 -> BR05
        g.addEdge("BR01", "BR02", 1.0, false);
        g.addEdge("BR03", "BR02", 1.0, false);
        g.addEdge("BR04", "BR05", 1.0, false);
        
        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===" << endl
                 << "  * [BR01] M1 - Artist BR\n"
                 << "  * [BR02] M2 - Artist BR\n"
                 << "  * [BR03] M3 - Artist BR\n"
                 << "=== Playlist 2 ===" << endl
                 << "  * [BR04] M4 - Artist BR\n"
                 << "  * [BR05] M5 - Artist BR\n";
        
        string output = captureOutput([&]() {
            g.generatePlaylistsByClusters();
        });
        
        run_test(name, output, expected.str());
    }

    // ===== NHÓM 3: findSmoothTransition() Edge Cases =====
    void Graph72() {
        string name = "Graph72";
        MusicGraph g;
        g.addSong("BS01", "Source", "Artist BS", "Pop");
        g.addSong("BS02", "Path1Mid", "Artist BS", "Rock");
        g.addSong("BS03", "Path2Mid", "Artist BS", "Jazz");
        g.addSong("BS04", "Destination", "Artist BS", "Rap");
        
        // Multiple equal-weight paths
        g.addEdge("BS01", "BS02", 2.0, false);
        g.addEdge("BS02", "BS04", 2.0, false);
        g.addEdge("BS01", "BS03", 2.0, false);
        g.addEdge("BS03", "BS04", 2.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BS01] Source - Artist BS\n"
                 << "To: [BS04] Destination - Artist BS\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 4\n"
                 << "-> Playback Order:\n"
                 << "   1. [BS01] Source - Artist BS\n"
                 << "   2. [BS02] Path1Mid - Artist BS\n"
                 << "   3. [BS04] Destination - Artist BS\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BS01", "BS04");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph73() {
        string name = "Graph73";
        MusicGraph g;
        g.addSong("BT01", "Start", "Artist BT", "Pop");
        g.addSong("BT02", "End", "Artist BT", "Rock");
        
        // Single path with very high weight
        g.addEdge("BT01", "BT02", 999.99, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BT01] Start - Artist BT\n"
                 << "To: [BT02] End - Artist BT\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 999.99\n"
                 << "-> Playback Order:\n"
                 << "   1. [BT01] Start - Artist BT\n"
                 << "   2. [BT02] End - Artist BT\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BT01", "BT02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph74() {
        string name = "Graph74";
        MusicGraph g;
        g.addSong("BU01", "S", "Artist BU", "Pop");
        g.addSong("BU02", "M1", "Artist BU", "Rock");
        g.addSong("BU03", "M2", "Artist BU", "Jazz");
        g.addSong("BU04", "E", "Artist BU", "Rap");
        
        // Dijkstra chooses alternate route
        g.addEdge("BU01", "BU02", 5.0, false);
        g.addEdge("BU02", "BU04", 5.0, false);
        g.addEdge("BU01", "BU03", 2.0, false);
        g.addEdge("BU03", "BU04", 2.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BU01] S - Artist BU\n"
                 << "To: [BU04] E - Artist BU\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 4\n"
                 << "-> Playback Order:\n"
                 << "   1. [BU01] S - Artist BU\n"
                 << "   2. [BU03] M2 - Artist BU\n"
                 << "   3. [BU04] E - Artist BU\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BU01", "BU04");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph75() {
        string name = "Graph75";
        MusicGraph g;
        g.addSong("BV01", "Start", "Artist BV", "Pop");
        g.addSong("BV02", "Middle", "Artist BV", "Rock");
        g.addSong("BV03", "Dead", "Artist BV", "Jazz");
        
        // No path from middle node
        g.addEdge("BV01", "BV02", 1.0, false);
        // BV02 and BV03 are disconnected
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BV02] Middle - Artist BV\n"
                 << "To: [BV03] Dead - Artist BV\n"
                 << "-------------------------------------------------\n"
                 << "No transition path between these two songs.";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BV02", "BV03");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph76() {
        string name = "Graph76";
        MusicGraph g;
        g.addSong("BW01", "Hub", "Artist BW", "Pop");
        g.addSong("BW02", "Branch1", "Artist BW", "Rock");
        g.addSong("BW03", "Branch2", "Artist BW", "Jazz");
        g.addSong("BW04", "End", "Artist BW", "Rap");
        
        // Circular with shortcut
        g.addEdge("BW01", "BW02", 1.0, false);
        g.addEdge("BW02", "BW03", 1.0, false);
        g.addEdge("BW03", "BW04", 1.0, false);
        g.addEdge("BW01", "BW04", 5.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BW01] Hub - Artist BW\n"
                 << "To: [BW04] End - Artist BW\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 3\n"
                 << "-> Playback Order:\n"
                 << "   1. [BW01] Hub - Artist BW\n"
                 << "   2. [BW02] Branch1 - Artist BW\n"
                 << "   3. [BW03] Branch2 - Artist BW\n"
                 << "   4. [BW04] End - Artist BW\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BW01", "BW04");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph77() {
        string name = "Graph77";
        MusicGraph g;
        g.addSong("BX01", "Hub", "Artist BX", "Pop");
        g.addSong("BX02", "Spoke1", "Artist BX", "Rock");
        g.addSong("BX03", "Spoke2", "Artist BX", "Jazz");
        
        // Star topology - hub to spoke
        g.addEdge("BX01", "BX02", 3.0, false);
        g.addEdge("BX01", "BX03", 5.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BX01] Hub - Artist BX\n"
                 << "To: [BX02] Spoke1 - Artist BX\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 3\n"
                 << "-> Playback Order:\n"
                 << "   1. [BX01] Hub - Artist BX\n"
                 << "   2. [BX02] Spoke1 - Artist BX\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BX01", "BX02");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph78() {
        string name = "Graph78";
        MusicGraph g;
        g.addSong("BY01", "S1", "Artist BY", "Pop");
        g.addSong("BY02", "S2", "Artist BY", "Rock");
        g.addSong("BY03", "S3", "Artist BY", "Jazz");
        
        // Decimal precision test
        g.addEdge("BY01", "BY02", 0.1, false);
        g.addEdge("BY02", "BY03", 0.2, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BY01] S1 - Artist BY\n"
                 << "To: [BY03] S3 - Artist BY\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 0.3\n"
                 << "-> Playback Order:\n"
                 << "   1. [BY01] S1 - Artist BY\n"
                 << "   2. [BY02] S2 - Artist BY\n"
                 << "   3. [BY03] S3 - Artist BY\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BY01", "BY03");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph79() {
        string name = "Graph79";
        MusicGraph g;
        g.addSong("BZ01", "Same", "Artist BZ", "Pop");
        
        // Source and destination are the same
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [BZ01] Same - Artist BZ\n"
                 << "To: [BZ01] Same - Artist BZ\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 0\n"
                 << "-> Playback Order:\n"
                 << "   1. [BZ01] Same - Artist BZ\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("BZ01", "BZ01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph80() {
        string name = "Graph80";
        MusicGraph g;
        g.addSong("CA01", "S", "Artist CA", "Pop");
        g.addSong("CA02", "M1", "Artist CA", "Rock");
        g.addSong("CA03", "M2", "Artist CA", "Jazz");
        g.addSong("CA04", "E", "Artist CA", "Rap");
        
        // Large vs small weights
        g.addEdge("CA01", "CA02", 0.001, false);
        g.addEdge("CA02", "CA04", 0.001, false);
        g.addEdge("CA01", "CA03", 1000.0, false);
        g.addEdge("CA03", "CA04", 0.001, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [CA01] S - Artist CA\n"
                 << "To: [CA04] E - Artist CA\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 0.002\n"
                 << "-> Playback Order:\n"
                 << "   1. [CA01] S - Artist CA\n"
                 << "   2. [CA02] M1 - Artist CA\n"
                 << "   3. [CA04] E - Artist CA\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("CA01", "CA04");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph81() {
        string name = "Graph81";
        MusicGraph g;
        g.addSong("CB01", "D1", "Artist CB", "Pop");
        g.addSong("CB02", "D2", "Artist CB", "Rock");
        g.addSong("CB03", "D3", "Artist CB", "Jazz");
        g.addSong("CB04", "D4", "Artist CB", "Rap");
        g.addSong("CB05", "D5", "Artist CB", "Classical");
        
        // Very deep path (5 nodes)
        g.addEdge("CB01", "CB02", 1.0, false);
        g.addEdge("CB02", "CB03", 1.0, false);
        g.addEdge("CB03", "CB04", 1.0, false);
        g.addEdge("CB04", "CB05", 1.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [CB01] D1 - Artist CB\n"
                 << "To: [CB05] D5 - Artist CB\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 4\n"
                 << "-> Playback Order:\n"
                 << "   1. [CB01] D1 - Artist CB\n"
                 << "   2. [CB02] D2 - Artist CB\n"
                 << "   3. [CB03] D3 - Artist CB\n"
                 << "   4. [CB04] D4 - Artist CB\n"
                 << "   5. [CB05] D5 - Artist CB\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("CB01", "CB05");
        });
        
        run_test(name, output, expected.str());
    }

    // ===== NHÓM 4: findMostPopularSong() Edge Cases =====
    void Graph82() {
        string name = "Graph82";
        MusicGraph g;
        g.addSong("CC01", "Hub", "Artist CC", "Pop");
        g.addSong("CC02", "S1", "Artist CC", "Rock");
        g.addSong("CC03", "S2", "Artist CC", "Jazz");
        g.addSong("CC04", "S3", "Artist CC", "Rap");
        g.addSong("CC05", "S4", "Artist CC", "Classical");
        g.addSong("CC06", "S5", "Artist CC", "Electronic");
        
        // Clear hub with in-degree 5
        g.addEdge("CC02", "CC01", 1.0, false);
        g.addEdge("CC03", "CC01", 1.0, false);
        g.addEdge("CC04", "CC01", 1.0, false);
        g.addEdge("CC05", "CC01", 1.0, false);
        g.addEdge("CC06", "CC01", 1.0, false);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CC01] Hub - Artist CC\n"
                 << "   (In-degree: 5)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph83() {
        string name = "Graph83";
        MusicGraph g;
        g.addSong("CD01", "Hub1", "Artist CD", "Pop");
        g.addSong("CD02", "Hub2", "Artist CD", "Rock");
        g.addSong("CD03", "S1", "Artist CD", "Jazz");
        g.addSong("CD04", "S2", "Artist CD", "Rap");
        g.addSong("CD05", "S3", "Artist CD", "Classical");
        
        // Hub CD01 with higher in-degree than CD02
        g.addEdge("CD03", "CD01", 1.0, false);
        g.addEdge("CD04", "CD01", 1.0, false);
        g.addEdge("CD05", "CD01", 1.0, false);
        g.addEdge("CD03", "CD02", 1.0, false);
        g.addEdge("CD04", "CD02", 1.0, false);
        g.addEdge("CD02", "CD01", 1.0, false);
        
        // CD01 has in-degree 4 (from CD03, CD04, CD05, CD02), CD02 has in-degree 2
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CD01] Hub1 - Artist CD\n"
                 << "   (In-degree: 4)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph84() {
        string name = "Graph84";
        MusicGraph g;
        g.addSong("CE01", "S1", "Artist CE", "Pop");
        g.addSong("CE02", "S2", "Artist CE", "Rock");
        g.addSong("CE03", "S3", "Artist CE", "Jazz");
        g.addSong("CE04", "Hub", "Artist CE", "Rap");
        
        // Linear chain with one clear hub
        g.addEdge("CE01", "CE02", 1.0, false);
        g.addEdge("CE02", "CE03", 1.0, false);
        g.addEdge("CE03", "CE04", 1.0, false);
        g.addEdge("CE01", "CE04", 1.0, false);
        
        // CE04 has in-degree 2 (from CE03, CE01)
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CE04] Hub - Artist CE\n"
                 << "   (In-degree: 2)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph85() {
        string name = "Graph85";
        MusicGraph g;
        g.addSong("CF01", "S1", "Artist CF", "Pop");
        g.addSong("CF02", "S2", "Artist CF", "Rock");
        g.addSong("CF03", "S3", "Artist CF", "Jazz");
        g.addSong("CF04", "S4", "Artist CF", "Rap");
        g.addSong("CF05", "Hub", "Artist CF", "Classical");
        
        // Chain with unique max hub
        g.addEdge("CF02", "CF03", 1.0, false);
        g.addEdge("CF03", "CF04", 1.0, false);
        g.addEdge("CF01", "CF03", 1.0, false);
        g.addEdge("CF02", "CF05", 1.0, false);
        g.addEdge("CF03", "CF05", 1.0, false);
        g.addEdge("CF04", "CF05", 1.0, false);
        
        // CF05 has in-degree 3 (from CF02, CF03, CF04)
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CF05] Hub - Artist CF\n"
                 << "   (In-degree: 3)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph86() {
        string name = "Graph86";
        MusicGraph g;
        g.addSong("CG01", "Hub", "Artist CG", "Pop");
        g.addSong("CG02", "S1", "Artist CG", "Rock");
        g.addSong("CG03", "S2", "Artist CG", "Jazz");
        g.addSong("CG04", "Dest", "Artist CG", "Rap");
        
        // Hub with unique max in-degree
        g.addEdge("CG01", "CG02", 1.0, false);
        g.addEdge("CG01", "CG03", 1.0, false);
        g.addEdge("CG02", "CG04", 1.0, false);
        g.addEdge("CG03", "CG04", 1.0, false);
        g.addEdge("CG01", "CG04", 1.0, false);
        
        // CG04 has in-degree 3 (from CG02, CG03, CG01)
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CG04] Dest - Artist CG\n"
                 << "   (In-degree: 3)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph87() {
        string name = "Graph87";
        MusicGraph g;
        g.addSong("CH01", "HUB", "Artist CH", "Pop");
        g.addSong("CH02", "N1", "Artist CH", "Rock");
        g.addSong("CH03", "N2", "Artist CH", "Jazz");
        g.addSong("CH04", "N3", "Artist CH", "Rap");
        g.addSong("CH05", "N4", "Artist CH", "Classical");
        g.addSong("CH06", "N5", "Artist CH", "Electronic");
        
        // One hub among many nodes
        g.addEdge("CH02", "CH01", 1.0, false);
        g.addEdge("CH03", "CH01", 1.0, false);
        g.addEdge("CH04", "CH01", 1.0, false);
        g.addEdge("CH05", "CH01", 1.0, false);
        g.addEdge("CH06", "CH01", 1.0, false);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CH01] HUB - Artist CH\n"
                 << "   (In-degree: 5)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph88() {
        string name = "Graph88";
        MusicGraph g;
        g.addSong("CI01", "Center", "Artist CI", "Pop");
        g.addSong("CI02", "S1", "Artist CI", "Rock");
        g.addSong("CI03", "S2", "Artist CI", "Jazz");
        g.addSong("CI04", "S3", "Artist CI", "Rap");
        
        // Bidirectional star - center has high in-degree
        g.addEdge("CI01", "CI02", 1.0, true);
        g.addEdge("CI01", "CI03", 1.0, true);
        g.addEdge("CI01", "CI04", 1.0, true);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CI01] Center - Artist CI\n"
                 << "   (In-degree: 3)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph89() {
        string name = "Graph89";
        MusicGraph g;
        g.addSong("CJ01", "S1", "Artist CJ", "Pop");
        g.addSong("CJ02", "S2", "Artist CJ", "Rock");
        g.addSong("CJ03", "Hub", "Artist CJ", "Jazz");
        g.addSong("CJ04", "S3", "Artist CJ", "Rap");
        g.addSong("CJ05", "S4", "Artist CJ", "Classical");
        
        // Hub receives from multiple sources
        g.addEdge("CJ01", "CJ03", 1.0, false);
        g.addEdge("CJ02", "CJ03", 1.0, false);
        g.addEdge("CJ04", "CJ03", 1.0, false);
        g.addEdge("CJ05", "CJ03", 1.0, false);
        
        stringstream expected;
        expected << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n"
                 << "-------------------------------------------------\n"
                 << "-> Network Hub Song:\n"
                 << "   [CJ03] Hub - Artist CJ\n"
                 << "   (In-degree: 4)";
        
        string output = captureOutput([&]() {
            g.findMostPopularSong();
        });
        
        run_test(name, output, expected.str());
    }

    // ===== NHÓM 5: detectMusicLoop() Edge Cases =====
    void Graph90() {
        string name = "Graph90";
        MusicGraph g;
        g.addSong("CK01", "S1", "Artist CK", "Pop");
        g.addSong("CK02", "S2", "Artist CK", "Rock");
        g.addSong("CK03", "S3", "Artist CK", "Jazz");
        g.addSong("CK04", "S4", "Artist CK", "Rap");
        g.addSong("CK05", "S5", "Artist CK", "Classical");
        
        // Complex DAG (no cycle)
        g.addEdge("CK01", "CK02", 1.0, false);
        g.addEdge("CK01", "CK03", 1.0, false);
        g.addEdge("CK02", "CK04", 1.0, false);
        g.addEdge("CK03", "CK05", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "No music loop detected.\n";
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        run_test(name, output, expected.str());
    }

    void Graph91() {
        string name = "Graph91";
        MusicGraph g;
        g.addSong("CL01", "SelfLoop", "Artist CL", "Pop");
        g.addSong("CL02", "S2", "Artist CL", "Rock");
        g.addSong("CL03", "S3", "Artist CL", "Jazz");
        
        // Self-loop with others
        g.addEdge("CL01", "CL01", 1.0, false);
        g.addEdge("CL02", "CL03", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [CL01] SelfLoop - Artist CL\n"
                 << "   [CL01] SelfLoop - Artist CL\n";
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph92() {
        string name = "Graph92";
        MusicGraph g;
        g.addSong("CM01", "C1N1", "Artist CM", "Pop");
        g.addSong("CM02", "C1N2", "Artist CM", "Rock");
        g.addSong("CM03", "C2N1", "Artist CM", "Jazz");
        g.addSong("CM04", "C2N2", "Artist CM", "Rap");
        
        // Multiple separate cycles
        g.addEdge("CM01", "CM02", 1.0, false);
        g.addEdge("CM02", "CM01", 1.0, false);
        g.addEdge("CM03", "CM04", 1.0, false);
        g.addEdge("CM04", "CM03", 1.0, false);  
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [CM01] C1N1 - Artist CM\n"
                 << "   [CM02] C1N2 - Artist CM\n"
                 << "   [CM01] C1N1 - Artist CM\n"
                 ;
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph93() {
        string name = "Graph93";
        MusicGraph g;
        g.addSong("CN01", "S1", "Artist CN", "Pop");
        g.addSong("CN02", "S2", "Artist CN", "Rock");
        g.addSong("CN03", "S3", "Artist CN", "Jazz");
        g.addSong("CN04", "S4", "Artist CN", "Rap");
        g.addSong("CN05", "S5", "Artist CN", "Classical");
        
        // Deep cycle (5 nodes)
        g.addEdge("CN01", "CN02", 1.0, false);
        g.addEdge("CN02", "CN03", 1.0, false);
        g.addEdge("CN03", "CN04", 1.0, false);
        g.addEdge("CN04", "CN05", 1.0, false);
        g.addEdge("CN05", "CN01", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [CN01] S1 - Artist CN\n"
                 << "   [CN02] S2 - Artist CN\n"
                 << "   [CN03] S3 - Artist CN\n"
                 << "   [CN04] S4 - Artist CN\n"
                 << "   [CN05] S5 - Artist CN\n"
                 << "   [CN01] S1 - Artist CN\n"
            
                 ;
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph94() {
        string name = "Graph94";
        MusicGraph g;
        g.addSong("CO01", "S1", "Artist CO", "Pop");
        g.addSong("CO02", "S2", "Artist CO", "Rock");
        g.addSong("CO03", "CycleStart", "Artist CO", "Jazz");
        g.addSong("CO04", "CycleEnd", "Artist CO", "Rap");
        
        // Cycle hidden in middle
        g.addEdge("CO01", "CO02", 1.0, false);
        g.addEdge("CO02", "CO03", 1.0, false);
        g.addEdge("CO03", "CO04", 1.0, false);
        g.addEdge("CO04", "CO03", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [CO03] CycleStart - Artist CO\n"
                 << "   [CO04] CycleEnd - Artist CO\n"
                 << "   [CO03] CycleStart - Artist CO\n"
                 
                 ;
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph95() {
        string name = "Graph95";
        MusicGraph g;
        g.addSong("CP01", "Hub", "Artist CP", "Pop");
        g.addSong("CP02", "B1", "Artist CP", "Rock");
        g.addSong("CP03", "B2", "Artist CP", "Jazz");
        g.addSong("CP04", "B3", "Artist CP", "Rap");
        
        // Star with backedge cycle
        g.addEdge("CP01", "CP02", 1.0, false);
        g.addEdge("CP01", "CP03", 1.0, false);
        g.addEdge("CP01", "CP04", 1.0, false);
        g.addEdge("CP04", "CP01", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [CP01] Hub - Artist CP\n"
                 << "   [CP04] B3 - Artist CP\n"
                 << "   [CP01] Hub - Artist CP\n"
                 ;
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph96() {
        string name = "Graph96";
        MusicGraph g;
        g.addSong("CQ01", "S1", "Artist CQ", "Pop");
        g.addSong("CQ02", "S2", "Artist CQ", "Rock");
        g.addSong("CQ03", "S3", "Artist CQ", "Jazz");
        g.addSong("CQ04", "S4", "Artist CQ", "Rap");
        
        // Multiple back edges
        g.addEdge("CQ01", "CQ02", 1.0, false);
        g.addEdge("CQ02", "CQ03", 1.0, false);
        g.addEdge("CQ02", "CQ01", 1.0, false);
        g.addEdge("CQ03", "CQ04", 1.0, false);
        g.addEdge("CQ04", "CQ02", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [CQ02] S2 - Artist CQ\n"
                 << "   [CQ03] S3 - Artist CQ\n"
                 << "   [CQ04] S4 - Artist CQ\n"
                 << "   [CQ02] S2 - Artist CQ\n"
 
                 ;
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    void Graph97() {
        string name = "Graph97";
        MusicGraph g;
        g.addSong("CR01", "CycleNode", "Artist CR", "Pop");
        g.addSong("CR02", "Branch1", "Artist CR", "Rock");
        g.addSong("CR03", "Branch2", "Artist CR", "Jazz");
        
        // Cycle with branches
        g.addEdge("CR01", "CR02", 1.0, false);
        g.addEdge("CR01", "CR03", 1.0, false);
        g.addEdge("CR02", "CR01", 1.0, false);
        
        stringstream expected;
        expected << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n"
                 << "-------------------------------------------------\n"
                 << "-> Music loop detected!\n"
                 << "-> Loop:\n"
                 << "   [CR01] CycleNode - Artist CR\n"
                    "   [CR02] Branch1 - Artist CR\n"
                    "   [CR01] CycleNode - Artist CR\n";    
        
        string output = captureOutput([&]() {
            g.detectMusicLoop();
        });
        
        if (output.find("Music loop detected!") != string::npos) {
            run_test(name, output, expected.str());
        } else {
            run_test(name, output, expected.str());
        }
    }

    // ===== NHÓM 6: printSongInfo() Additional Cases =====
    void Graph98() {
        string name = "Graph98";
        MusicGraph g;
        g.addSong("CS01", "Song-With-Dash", "Artist-Name", "Pop");
        
        stringstream expected;
        expected << "[CS01] Song-With-Dash - Artist-Name";
        
        string output = captureOutput([&]() {
            g.printSongInfo("CS01");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph99() {
        string name = "Graph99";
        MusicGraph g;
        g.addSong("CT01", "Song With Spaces", "Artist With Spaces", "Pop");
        
        stringstream expected;
        expected << "[CT01] Song With Spaces - Artist With Spaces";
        
        string output = captureOutput([&]() {
            g.printSongInfo("CT01");
        });
        
        run_test(name, output, expected.str());
    }

    // ===== NHÓM 7: Integration Test =====
    void Graph100() {
        string name = "Graph100";
        MusicGraph g;
        g.addSong("CU01", "Inception", "Artist CU", "Inception");
        g.addSong("CU02", "Middle", "Artist CU", "Middle");
        g.addSong("CU03", "Dream", "Artist CU", "Dream");
        g.addSong("CU04", "Reality", "Artist CU", "Reality");
        g.addSong("CU05", "End", "Artist CU", "End");
        
        // Complex integration test
        g.addEdge("CU01", "CU02", 1.0, false);
        g.addEdge("CU02", "CU03", 2.0, false);
        g.addEdge("CU01", "CU04", 5.0, false);
        g.addEdge("CU04", "CU05", 1.0, false);
        g.addEdge("CU03", "CU05", 1.0, false);
        g.addEdge("CU05", "CU02", 1.0, false);
        
        stringstream expected;
        expected << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n"
                 << "From: [CU01] Inception - Artist CU\n"
                 << "To: [CU05] End - Artist CU\n"
                 << "-------------------------------------------------\n"
                 << "-> Total Deviation (Cost): 4\n"
                 << "-> Playback Order:\n"
                 << "   1. [CU01] Inception - Artist CU\n"
                 << "   2. [CU02] Middle - Artist CU\n"
                 << "   3. [CU03] Dream - Artist CU\n"
                 << "   4. [CU05] End - Artist CU\n";
        
        string output = captureOutput([&]() {
            g.findSmoothTransition("CU01", "CU05");
        });
        
        run_test(name, output, expected.str());
    }

    void Graph101() {
        string name = "Graph101";
        MusicGraph g;
        g.addSong("CU01", "Inception", "Artist CU", "Inception");
        g.addSong("CU02", "Middle", "Artist CU", "Middle");
        g.addSong("CU03", "Dream", "Artist CU", "Dream");
        g.addSong("CU04", "Reality", "Artist CU", "Reality");
    
        g.addEdge("CU02", "CU01", 0, false);
        g.addEdge("CU03", "CU01", 0, false);
        g.addEdge("CU03", "CU04", 0, false);

        string output = captureOutput([&](){
            g.generatePlaylistsByClusters();
        });

        stringstream expected;
        expected << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n"
                 << "-------------------------------------------------\n"
                 << "=== Playlist 1 ===\n"
                 << "  * [CU01] Inception - Artist CU\n"
                 << "  * [CU02] Middle - Artist CU\n"
                 << "  * [CU03] Dream - Artist CU\n"
                 << "  * [CU04] Reality - Artist CU\n";

        run_test(name, output, expected.str());
    }

    void run_all_test() override {
        Graph01();
        Graph02();
        Graph03();
        Graph04();
        Graph05();
        Graph06();
        Graph07();
        Graph08();
        Graph09();
        Graph10();
        Graph11();
        Graph12();
        Graph13();
        Graph14();
        Graph15();
        Graph16();
        Graph17();
        Graph18();
        Graph19();
        Graph20();
        Graph21();
        Graph22();
        Graph23();
        Graph24();
        Graph25();
        Graph26();
        Graph27();
        Graph28();
        Graph29();
        Graph30();
        Graph31();
        Graph32();
        Graph33();
        Graph34();
        Graph35();
        Graph36();
        Graph37();
        Graph38();
        Graph39();
        Graph40();
        Graph41();
        Graph42();
        Graph43();
        Graph44();
        Graph45();
        Graph46();
        Graph47();
        Graph48();
        Graph49();
        Graph50();
        Graph51();
        Graph52();
        Graph53();
        Graph54();
        Graph55();
        Graph56();
        Graph57();
        Graph58();
        Graph59();
        Graph60();
        Graph61();
        Graph62();
        Graph63();
        Graph64();
        Graph65();
        Graph66();
        Graph67();
        Graph68();
        Graph69();
        Graph70();
        Graph71();
        Graph72();
        Graph73();
        Graph74();
        Graph75();
        Graph76();
        Graph77();
        Graph78();
        Graph79();
        Graph80();
        Graph81();
        Graph82();
        Graph83();
        Graph84();
        Graph85();
        Graph86();
        Graph87();
        Graph88();
        Graph89();
        Graph90();
        Graph91();
        Graph92();
        Graph93();
        Graph94();
        Graph95();
        Graph96();
        Graph97();
        Graph98();
        Graph99();
        Graph100();
        Graph101();
        Show_Result(name, get_num_test(), get_passed_test(), get_failed_test());
    }
};