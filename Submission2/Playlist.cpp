#include "Playlist.h"

// =======================
// Song implementation (TODO)
// =======================

Song::Song(int id,
           string title,
           string artist,
           string album,
           int duration,
           int score,
           string url)
    : id(id),
      title(title),
      artist(artist),
      album(album),
      duration(duration),
      score(score),
      url(url),
      play_count(0)
{
}

std::string Song::toString() const {
    std::ostringstream oss;
    oss << "Song[id=" << id 
        << ", title=\"" << title << "\""
        << ", artist=\"" << artist << "\""
        << ", album=\"" << album << "\""
        << ", duration=" << duration
        << ", score=" << score
        << ", url=\"" << url << "\""
        << ", play_count=" << play_count
        << "]";
    return oss.str();
}

// TODO: Student can implement additional methods for Song here

// =======================
// Playlist implementation (TODO)
// =======================

Playlist::Playlist(string name)
    : name(name),
      size(0),
      currentIndex(-1)
#ifdef USE_THREADED_AVL
    , currentIt(songs.endIt()),
      hasCurrent(false)
#endif
{
    // TODO
}

SongKey Playlist::makeKey(Song* s) const {
    // TODO
    if (!s) return {"", -1};
    return {s->getTitle(), s->getID()};
}

void Playlist::resetPlayback() {
    // TODO
    currentIndex = -1;
#ifdef USE_THREADED_AVL
    hasCurrent = false;
    currentIt = songs.endIt();
#endif
}

int Playlist::getSize() const {
    // TODO
    return size;
}

bool Playlist::empty() const {
    // TODO
    return size == 0;
}

void Playlist::clear() {
    // TODO: delete Song* if Playlist owns them + clear the tree
    std::list<SongKey> keys = songs.ascendingList();
    for (const auto& key : keys) {
        Song** sPtr = songs.find(key);
        if (sPtr && *sPtr) {
            delete *sPtr;
        }
    }

    songs.clear();
    size = 0;
    resetPlayback();
}

void Playlist::addSong(Song* s) {
    // TODO
    if (!s) return;
    if (songs.insert(makeKey(s), s)) {
        size++;
    }
}

void Playlist::removeSong(int index) {
    // TODO
    if (index < 0 || index >= size) return;

    std::list<SongKey> keys = songs.ascendingList();
    auto it = keys.begin();
    std::advance(it, index);
    
    Song** sPtr = songs.find(*it);

    if (sPtr && *sPtr) {
        if (currentIndex == index) resetPlayback();
        else if (index < currentIndex) currentIndex--;

        delete *sPtr;
        songs.erase(*it);
        size--;
    }
}

Song* Playlist::getSong(int index) const {
    // TODO

    if (index < 0 || index >= size) return nullptr;
#ifdef USE_THREADED_AVL
    std::list<SongKey> keys = const_cast<ThreadedAVL<SongKey, Song*>&>(songs).ascendingList();
#else
    std::list<SongKey> keys = const_cast<AVL<SongKey, Song*>&>(songs).ascendingList();
#endif

    if (index >= (int)keys.size()) return nullptr;

    auto it = keys.begin();
    for (int i = 0; i < index; i++) {
        ++it;
    }

#ifdef USE_THREADED_AVL
    Song** sPtr = const_cast<ThreadedAVL<SongKey, Song*>&>(songs).find(*it);
#else
    Song** sPtr = const_cast<AVL<SongKey, Song*>&>(songs).find(*it);
#endif

    return (sPtr != nullptr) ? *sPtr : nullptr;
}

// =======================
// Playing control (TODO)
// =======================

Song* Playlist::playNext() {
    if (empty()) return nullptr;

#ifdef USE_THREADED_AVL
    if (!hasCurrent) { 
        currentIt = songs.beginIt();
        currentIndex = 0;
        hasCurrent = true;
    } else {
        ++currentIt;
        currentIndex++;
        if (currentIt.isNull()) { 
            currentIt = songs.beginIt();
            currentIndex = 0;
        }
    }
    return currentIt.value();
#else
    currentIndex++;

    if (currentIndex >= size) {
        currentIndex = 0;
    }

    return getSong(currentIndex);
#endif
}

Song* Playlist::playPrevious() {
    if (empty()) {
        return nullptr; 
    }

#ifdef USE_THREADED_AVL
    if (!hasCurrent) {
        currentIt = songs.rbeginIt();
        currentIndex = size - 1;
        hasCurrent = true;
    } else {
        --currentIt;
        currentIndex--;
        if (currentIt.isNull()) {
            currentIt = songs.rbeginIt();
            currentIndex = size - 1;
        }
    }
    return currentIt.value();
#else
    currentIndex--;

    if (currentIndex < 0 ) {
        currentIndex = size - 1;
    }

    return getSong(currentIndex);
#endif
}

// =======================
// Score-related (TODO)
// =======================

int Playlist::getTotalScore() {
    // TODO
    int total = 0;
    std::list<SongKey> keys = songs.ascendingList();
    for (const auto& key : keys) {
        Song** sPtr = songs.find(key);
        if (sPtr && *sPtr) total += (*sPtr)->getScore(); 
    }
    return total;
}

bool Playlist::compareTo(const Playlist& p, int numSong) {
    // TODO
    int score1 = 0, score2 = 0;
    for (int i = 0; i < numSong; i++) {
        Song* s1 = this->getSong(i);
        if (s1) score1 += s1->getScore();
        
        Song* s2 = p.getSong(i);
        if (s2) score2 += s2->getScore();
    }
    return score1 >= score2;
}

// =======================
// Advanced playing modes (TODO)
// =======================

void Playlist::playRandom(int index) {
    // TODO
    if (index < 0 || index >= size) return;
    currentIndex = index;
#ifdef USE_THREADED_AVL
    currentIt = songs.findIt(*(std::next(songs.ascendingList().begin(), index)));
    hasCurrent = !currentIt.isNull();
#endif
}

int Playlist::playApproximate(int step) {
    // TODO
    int startIdx = (currentIndex == -1) ? 0 : currentIndex;
    int newIndex = startIdx + step;

    if (newIndex < 0) newIndex = 0;
    if (newIndex >= size) newIndex = size - 1;
    
    playRandom(newIndex);
    return currentIndex;
}