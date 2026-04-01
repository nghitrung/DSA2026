#ifndef AVL_H
#define AVL_H

#include "IBST.h"

#include <list>
#include <string>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename K, typename V>
class AVL : public IBST<K, V> {
public:
    struct Node {
        K key;
        V value;

        int bfactor; 

        Node* pLeft;
        Node* pRight;

        Node(const K& k, const V& v)
            : key(k), value(v), bfactor(0),
              pLeft(nullptr), pRight(nullptr) {}

        virtual ~Node() = default;

        // Default formatter must compile for any K,V.
        static std::string defaultEntry2Str(const K& k, const V& v) {
            std::ostringstream oss;
            oss << "<" << k << ", " << v << ">";
            return oss.str();
        }

        std::string toString(std::string (*entry2str)(const K&, const V&) = nullptr) const {
            auto entryStr = [&](const K& kk, const V& vv) -> std::string {
                return entry2str ? entry2str(kk, vv) : defaultEntry2Str(kk, vv);
            };

            std::ostringstream out;
            // AVL luôn in kèm balance cho debug
            if (!pLeft && !pRight) {
                out << "[" << entryStr(key, value) << ":" << balance() << "]";
            }
            else if (!pLeft && pRight) {
                out << " (" << entryStr(key, value) << ":" << balance()
                    << "[.]" << pRight->toString(entry2str) << ")";
            }
            else if (pLeft && !pRight) {
                out << " (" << entryStr(key, value) << ":" << balance()
                    << pLeft->toString(entry2str) << "[.]" << ")";
            }
            else {
                out << " (" << entryStr(key, value) << ":" << balance()
                    << pLeft->toString(entry2str)
                    << pRight->toString(entry2str)
                    << ") ";
            }
            return out.str();
        }

        int balance() const {
            return bfactor;
        }
    };

protected:
    Node* pRoot;

    // HELPER FUNCTION

    int getHeight(Node* node) const {
        if (!node) return 0;

        return getHeight(node->pLeft) - getHeight(node->pRight);
    }

    // Update balance factor
    void updateBF(Node* node) {
        if (node) node->bfactor = getHeight(node->pLeft) - getHeight(node->pRight);
    }

    Node* rotateRight(Node* root) {
        Node* L = root->pLeft;
        root->pLeft = L->pRight;
        L->pRight = root;
        updateBF(root);
        updateBF(L);

        return L;
    } 

    Node* rotateLeft(Node* root) {
        Node* R = root->pRight;
        root->pRight = R->pLeft;
        R->pLeft = root;
        updateBF(root);
        updateBF(R);

        return R;
    }

    Node* balance(Node* node) {
        updateBF(node);

        if (node->bfactor > 1) {
            if (getHeight(node->pLeft->pLeft) < getHeight(node->pLeft->pRight)) 
                node->pLeft = rotateLeft(node->pLeft); 
            return rotateRight(node);
        } 

        if (node->bfactor < -1) {
            if (getHeight(node->pRight->pRight) < getHeight(node->pRight->pLeft)) 
                node->pRight = rotateRight(node->pRight);
            return rotateLeft(node); 
        }

        return node;
    }

    void findPredSucc(Node* root, const K& key, Node*& pred, Node*& succ) {
        Node* curr = root;
        while (curr) {
            if (key < curr->key) {
                succ = curr;
                curr = curr->pLeft;
            } else if (key > curr->key) {
                pred = curr;
                curr = curr->pRight;
            } else return;
        }
    }

protected:
    // =======================
    // Hooks for ThreadedAVL
    // =======================
    // Base AVL does nothing. ThreadedAVL overrides these to maintain prev/next threading.

    virtual void onInserted(Node* /*newNode*/, Node* /*pred*/, Node* /*succ*/) {}
    virtual void onErasing(Node* /*delNode*/, Node* /*pred*/, Node* /*succ*/) {}
    virtual void onReplaceBySuccessor(Node* /*target*/, Node* /*successor*/, Node* /*successorNext*/) {}

    // Factory for subclasses to create extended node types
    virtual Node* createNode(const K& key, const V& value) { return new Node(key, value); }

private:
    Node* insert(Node* node, const K& key, const V& value, bool& res, Node*& newNode) {
        if (!node) {
            newNode = createNode(key, value);
            res = true;
            return newNode;
        }

        if (key < node->key) node->pLeft = insert(node->pLeft, key, value, res, newNode);
        else if (key > node->key) node->pRight = insert(node->pRight, key, value, res, newNode);
        else { res = false; return node; }
        return balance(node);
    }

    Node* erase(Node* node, const K& key, bool& res) {
        if (!node) {
            res = false;
            return nullptr;
        }

        if (key < node->key) node->pLeft = erase(node->pLeft, key, res);
        else if (key > node->key) node->pRight = erase(node->pRight, key, res);
        else {
            res = true;
            if (!node->pLeft || !node->pRight) {
                Node* temp = node->pLeft ? node->pLeft: node->pRight;

                onErasing(node, nullptr, nullptr);
                delete node;
                return temp;
            } else {
                Node* s = node->pRight;
                while (s->pLeft) s = s->pLeft;
                Node* sNext = s->pRight;
                onReplaceBySuccessor(node, s, sNext);
                node->key = s->key;
                node->value = s->value;
                node->pRight = erase(node->pRight, s->key, res);
            }
        }

        return balance(node);
    }

    void clear (Node* node) {
        if (node) {
            clear(node->pLeft);
            clear(node->pRight);
            delete node;
        }
    }

    void inOrder(Node* node, std::list<K>& l) {
        if (!node) return;
        inOrder(node->pLeft, l);
        l.push_back(node->key);
        inOrder(node->pRight, l);
    }

    void revOrder(Node* node, std::list<K>& l) {
        if (!node) return;
        revOrder(node->pRight, l);
        l.push_back(node->key);
        revOrder(node->pLeft, l);
    }

public:
    AVL() : pRoot(nullptr) {}
    virtual ~AVL() { clear(); }

    // =======================
    // IBST implementation (TODO)
    // =======================

    bool insert(const K& key, const V& value) override {
        // TODO
        bool res = false;
        Node* newNode = nullptr, *pred = nullptr, *succ = nullptr;
        findPredSucc(pRoot, key, pred, succ);
        pRoot = insert(pRoot, key, value, res, newNode);
        if (res) onInserted(newNode, pred, succ);
        return res;
    }

    bool erase(const K& key) override {
        // TODO
        bool res = false;
        pRoot = erase(pRoot, key, res);

        return res;
    }

    V* find(const K& key) override {
        // TODO
        Node* curr = pRoot;
        while (curr) {
            if (key == curr->key) return &(curr->value);
            curr = (key < curr->key) ? curr->pLeft : curr->pRight;
        }
        return nullptr;
    }

    bool contains(const K& key) const override {
        // TODO
        Node* curr = pRoot;
        while (curr) {
            if (key == curr->key) return true;
            curr = (key < curr->key) ? curr->pLeft : curr->pRight;
        }
        return false;
    }

    int size() const override {
        // TODO
        std::list<K> l;
        const_cast<AVL*>(this)->inOrder(pRoot, l);
        return (int)l.size();
    }

    bool empty() const override {
        // TODO
        return pRoot == nullptr;
    }

    void clear() override {
        // TODO
        clear(pRoot); 
        pRoot = nullptr;
    }

    int height() const override {
        // TODO
        return getHeight(this->pRoot);
    }

    std::list<K> ascendingList() override {
        // TODO
        std::list<K> l;
        inOrder(pRoot, l);
        return l;
    }

    std::list<K> descendingList() override {
        // TODO
        std::list<K> l;
        revOrder(pRoot, l);
        return l;
    }

    std::string toString(std::string (*entry2str)(const K&, const V&) = nullptr) const override {
        if (!pRoot) return "(NULL)";
        return pRoot->toString(entry2str);
    }
};

#endif /* AVL_H */
