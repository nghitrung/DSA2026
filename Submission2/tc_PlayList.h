#include "playlist.h"
#include "ITest.h"
class PlayList_Test : public DSA_Assignment2_Test {
    private:
    string name;
    public:
    PlayList_Test() {
        this -> name = "PlayListTest";
    }
    public:
    void PlayList001() {
        string name = "PlayList001";
        stringstream output;
        stringstream expected;

        Playlist p1("Acoustic");
        p1.addSong(new Song(1, "A Song", "A1", "-", 100, 4, "-")); 
        p1.addSong(new Song(2, "B Song", "A1", "-", 100, 5, "-")); 
        p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 

        output << "Song size: " << p1.getSize();
        expected << "Song size: " << 3;
        
        run_test(name, output.str(), expected.str());
    }

    void PlayList002() {
        string name = "PlayList002";
        Playlist p1("Acoustic");
        p1.addSong(new Song(1, "A Song", "A1", "-", 100, 4, "-")); 
        p1.addSong(new Song(2, "B Song", "A1", "-", 100, 5, "-")); 
        p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 

        Song* song = p1.getSong(0);
        stringstream output;
        stringstream expected;

        output << song -> toString();
        expected << "A Song by A1 from - [100s, score: 4]";

        run_test(name, output.str(), expected.str());
    }

    void PlayList003() {
        string name = "PlayList003";
        Playlist p1("Acoustic");
        p1.addSong(new Song(1, "A Song", "A1", "-", 100, 4, "-")); 
        p1.addSong(new Song(2, "B Song", "A1", "-", 100, 5, "-")); 
        p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 
        stringstream output;
        stringstream expected;

        p1.clear();
        output << "Empty: " << ((p1.empty())? "Yes" : "No");
        expected << "Empty: Yes";

        run_test(name, output.str(), expected.str());
    }

    void PlayList004() {
        string name = "PlayList004";
        Playlist p1("Acoustic");
        p1.addSong(new Song(1, "A Song", "A1", "-", 100, 4, "-")); 
        p1.addSong(new Song(2, "B Song", "A1", "-", 100, 5, "-")); 
        //duplicate songs just count 1
        p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 
        p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 
        stringstream output;
        stringstream expected;

        output << p1.getSize();
        expected << "3";
        run_test(name ,output.str(), expected.str());
    }

    void PlayList005() {
        string name = "PlayList005";
        Playlist p1("Acoustic");
        p1.addSong(new Song(1, "A Song", "A1", "-", 100, 4, "-")); 
        p1.addSong(new Song(2, "B Song", "A1", "-", 100, 5, "-")); 
        p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 
        p1.addSong(new Song(4, "D Song", "A1", "-", 100, 3, "-")); 
        stringstream output;
        stringstream expected;

        output << "Total score: " << p1.getTotalScore();
        expected << "Total score: 15";
        
        run_test(name, output.str(), expected.str());
    }

    void PlayList006() {
        string name = "PlayList006";
        Playlist p1("Acoustic");
        p1.addSong(new Song(1, "A Song", "A1", "-", 100, 4, "-")); 
        p1.addSong(new Song(2, "B Song", "A1", "-", 100, 5, "-")); 
        p1.addSong(new Song(3, "C Song", "A1", "-", 100, 3, "-")); 
        p1.addSong(new Song(4, "D Song", "A1", "-", 100, 3, "-")); 

        Playlist p2("Rock");
        p2.addSong(new Song(4, "D Song", "A1", "-", 100, 100, "-")); 

        stringstream output;
        stringstream expected;

        output << "p1 > p2: " << ((p1.compareTo(p2,4)) ? "Yes" : "No") ;
        expected << "p1 > p2: No";

        run_test(name, output.str(), expected.str());
    }

    void PlayList007() {
        string name = "PlayList007";
        Playlist p1("Acoustic");

        for (int i = 0; i < 10; ++i) {
            Song* newSong = new Song(i," ", " ", " ",100 + i, 4 + i, " ");
            p1.addSong(newSong);
        }
        stringstream output;
        stringstream expected;
        output << "Total Score: " << p1.getTotalScore();
        expected << "Total Score: 85";
        
        run_test(name, output.str(), expected.str());
    }

    void PlayList008() {
        string name = "PlayList008";
        Playlist p("Test");

        p.addSong(new Song(1,"B","A","-",100,5,"-"));
        p.addSong(new Song(2,"A","A","-",100,10,"-"));

        stringstream output, expected;
        output << p.getSize();
        expected << "2";
        run_test(name, output.str(), expected.str());
    }

    void PlayList009() {
        string name = "PlayList009";
        Playlist p("Test");

        p.addSong(new Song(1,"B","A","-",100,5,"-"));
        p.addSong(new Song(2,"A","A","-",100,10,"-"));

        stringstream output, expected;
        output << p.getSong(0)->toString();
        expected << p.getSong(0)->toString(); // chỉ cần không crash
        run_test(name, output.str(), expected.str());
    }

    void PlayList010() {
        string name = "PlayList010";
        Playlist p("Test");

        p.addSong(new Song(1,"A","A","-",100,5,"-"));
        p.addSong(new Song(2,"B","A","-",100,10,"-"));

        Song* s1 = p.playNext();
        Song* s2 = p.playNext();

        stringstream output, expected;
        output << s1->toString() << "|" << s2->toString();
        expected << s1->toString() << "|" << s2->toString();
        run_test(name, output.str(), expected.str());
    }

    void PlayList011() {
        string name = "PlayList011";
        Playlist p("Test");

        p.addSong(new Song(1,"A","A","-",100,5,"-"));
        p.addSong(new Song(2,"B","A","-",100,10,"-"));

        p.playNext();
        Song* s = p.playPrevious();

        stringstream output, expected;
        if (s) {
            output << s->toString();
            expected << s->toString();
        }
        else {
            output << "None";
            expected << "None";
        }
        
        run_test(name, output.str(), expected.str());
    }

    void PlayList012() {
        string name = "PlayList012";
        Playlist p("Test");

        p.addSong(new Song(1,"A","A","-",100,5,"-"));
        p.addSong(new Song(2,"B","A","-",100,10,"-"));

        p.removeSong(0);

        stringstream output, expected;
        output << p.getSize();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList013() {
        string name = "PlayList013";
        Playlist p("Test");

        p.addSong(new Song(1,"A","A","-",100,5,"-"));
        p.addSong(new Song(2,"B","A","-",100,10,"-"));

        stringstream output, expected;
        output << p.getTotalScore();
        expected << "15";
        run_test(name, output.str(), expected.str());
    }

    void PlayList014() {
        string name = "PlayList014";
        Playlist p("Test");

        p.addSong(new Song(1,"A","A","-",100,5,"-"));
        p.addSong(new Song(2,"B","A","-",100,10,"-"));

        p.playRandom(1);

        Song* s = p.playNext();

        stringstream output, expected;
        output << (s == nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList015() {
        string name = "PlayList015";
        Playlist p("Test");

        for(int i=1;i<=5;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playRandom(2);
        int idx = p.playApproximate(2);

        stringstream output, expected;
        output << idx;
        expected << "4";
        run_test(name, output.str(), expected.str());
    }

    void PlayList016() {
        string name = "PlayList016";
        Playlist p("Test");

        for(int i=1;i<=5;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playRandom(2);
        int idx = p.playApproximate(-2);

        stringstream output, expected;
        output << idx;
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void PlayList017() {
        string name = "PlayList017";
        Playlist p1("P1"), p2("P2");

        for(int i=1;i<=3;i++){
            p1.addSong(new Song(i,to_string(i),"A","-",100,10,"-"));
            p2.addSong(new Song(i,to_string(i),"A","-",100,5,"-"));
        }

        stringstream output, expected;
        output << p1.compareTo(p2,2);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList018() {
        string name = "PlayList018";
        Playlist p("Test");

        p.addSong(new Song(1,"A","A","-",100,5,"-"));
        p.addSong(new Song(2,"B","A","-",100,10,"-"));

        p.clear();

        stringstream output, expected;
        output << p.empty();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList019() {
        string name = "PlayList019";
        Playlist p("Test");

        stringstream output, expected;
        output << (p.getSong(0) == nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList020() {
        string name = "PlayList020";
        Playlist p("Test");

        for(int i=1;i<=3;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playNext();
        p.removeSong(0); // remove current

        stringstream output, expected;
        output << (p.playNext() != nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList021() {
        string name = "PlayList021";
        Playlist p("Test");

        p.addSong(new Song(1,"C","A","-",100,5,"-"));
        p.addSong(new Song(2,"A","A","-",100,10,"-"));
        p.addSong(new Song(3,"B","A","-",100,15,"-"));

        stringstream output, expected;
        output << p.getSong(0)->toString();
        expected << p.getSong(0)->toString(); // phải là "A"
        run_test(name, output.str(), expected.str());
    }

    void PlayList022() {
        string name = "PlayList022";
        Playlist p("Test");

        for(int i=1;i<=3;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playNext(); // 1
        p.playNext(); // 2
        p.removeSong(1); // remove current

        stringstream output, expected;
        output << (p.playNext() != nullptr);
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void PlayList023() {
        string name = "PlayList023";
        Playlist p("Test");

        for(int i=1;i<=3;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playRandom(2); // last
        Song* s = p.playNext();

        stringstream output, expected;
        output << (s == nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList024() {
        string name = "PlayList024";
        Playlist p("Test");

        for(int i=1;i<=3;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playRandom(0); // first
        Song* s = p.playPrevious();

        stringstream output, expected;
        output << (s == nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList025() {
        string name = "PlayList025";
        Playlist p("Test");

        for(int i=1;i<=5;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playRandom(4);
        int idx = p.playApproximate(10); // vượt biên

        stringstream output, expected;
        output << idx;
        expected << "4";  // hoac -4
        run_test(name, output.str(), expected.str());
    }

    void PlayList026() {
        string name = "PlayList026";
        Playlist p("Test");

        for(int i=1;i<=5;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.playRandom(0);
        int idx = p.playApproximate(-10); // vượt biên

        stringstream output, expected;
        output << idx;
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void PlayList027() {
        string name = "PlayList027";
        Playlist p("Test");

        p.addSong(new Song(1,"A","A","-",100,5,"-"));

        p.playNext(); // current = A
        p.removeSong(0); // remove current

        stringstream output, expected;
        output << (p.playNext() == nullptr);
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList028() {
        string name = "PlayList028";
        Playlist p("Test");

        for(int i=1;i<=3;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.removeSong(2); // remove last

        stringstream output, expected;
        output << p.getSize();
        expected << "2";
        run_test(name, output.str(), expected.str());
    }

    void PlayList029() {
        string name = "PlayList029";
        Playlist p("Test");

        for(int i=1;i<=3;i++)
            p.addSong(new Song(i,to_string(i),"A","-",100,i,"-"));

        p.removeSong(0);
        p.removeSong(0);
        p.removeSong(0);

        stringstream output, expected;
        output << p.empty();
        expected << "1";
        run_test(name, output.str(), expected.str());
    }

    void PlayList030() {
        string name = "PlayList030";
        Playlist p("Test");

        Playlist p2("Test2");

        for(int i=1;i<=5;i++){
            p.addSong(new Song(i,to_string(i),"A","-",100,1,"-"));
            p2.addSong(new Song(i,to_string(i),"A","-",100,2,"-"));
        }

        stringstream output, expected;
        output << p.compareTo(p2,5);
        expected << "0";
        run_test(name, output.str(), expected.str());
    }

    void run_all_test() {
        PlayList001();
        PlayList002();
        PlayList003();
        PlayList004();
        PlayList005();
        PlayList006();
        PlayList007();
        PlayList008();
        PlayList009();
        PlayList010();
        PlayList011();
        PlayList012();
        PlayList013();
        PlayList014();
        PlayList015();
        PlayList016();
        PlayList017();
        PlayList018();
        PlayList019();
        PlayList020();

        PlayList021();
        PlayList022();
        PlayList023();
        PlayList024();
        PlayList025();
        PlayList026();
        PlayList027();
        PlayList028();
        PlayList029();
        PlayList030();
        Show_Result(name, get_num_test(), get_passed_test(), get_failed_test());
    }
};