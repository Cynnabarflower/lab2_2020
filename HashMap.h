#ifndef UNTITLED56_HSET_H
#define UNTITLED56_HSET_H


#include <vector>
#include <fstream>
#include "Codon.h"
#include "Amino.h"

using namespace std;
template <class K, class V>
class HashMap {

private:

    static const int DEFAULT_CAPACITY = 4;
    static const int MAXIMUM_CAPACITY = 100;

    class Entry {
    public:
        Entry(K key, V value):key(key), value(value) {}
        K key;
        V value;
    };

    std::vector<std::vector<Entry>> *table;
    const double loadFactor = 0.75;
    int m_size = 0;
    int capacity = 0;
    int threshold = 0;

    size_t getPosition(size_t hash, int  capacity1) const {
        return hash % capacity1;
    }

    void transfer(std::vector<std::vector<Entry>> *tempTable, int newCapacity) {
        for (auto a : *table)
            for (auto e : a) {
                size_t pos = getPosition(e.key.hash(), newCapacity);
                (*tempTable)[pos].push_back(e);
            }
    }

    void resize(int newCapacity)
    {
        if (this->capacity == MAXIMUM_CAPACITY)
        {
            threshold = 999999999;
            return;
        }

        auto tempTable = new std::vector<std::vector<Entry>>(newCapacity);
        capacity = newCapacity;
        transfer(tempTable, capacity);
        delete table;
        table = tempTable;
        threshold = (int)(capacity * loadFactor);
    }

public:
    HashMap(){
        capacity = DEFAULT_CAPACITY;
        threshold = (int)(capacity * loadFactor);
        table = new std::vector<std::vector<Entry>>(capacity);
    }

    bool put(const K &key, const V &value) {
        size_t hash = key.hash();
        int pos = getPosition(hash, capacity);
        for (auto &a : (*table)[pos])
            if (a.key == key) {
                a.value = value;
                return true;
            }
        (*table)[pos].push_back(Entry(key, value));
        m_size++;
        if (m_size == threshold) {
            resize(capacity * 2);
        }
        return false;
    }

    int size() const {
        return m_size;
    }

    bool contains(K key) const {
        int hash = key.hash();
        int pos = getPosition(hash, capacity);
        for (auto a : (*this->table)[pos])
            if (a.key == key)
                return true;
        return false;
    }

    bool remove(K const &key) {
        int hash = key.hash();
        int pos = getPosition(hash, capacity);
        for (auto a = (*this->table)[pos].begin(); a != (*this->table)[pos].end(); a++)
            if (a->key == key) {
                (*this->table)[pos].erase(a);
                m_size--;
                return true;
            }
        return false;
    }

    void clear() {
        delete table;
        capacity = DEFAULT_CAPACITY;
        table = new std::vector<std::vector<Entry>>(capacity);
        m_size = 0;
    }

    bool operator==(HashMap &other) const {
        if (size() != other.size())
            return false;
        for (auto a : *table)
            for (auto e : a)
                if (!other.contains(e.key) || other[e.key] != e.value)
                    return false;

        for (auto a : *other.table)
            for (auto e : a)
                if (!contains(e.key) || (*this)[e.key] != e.value)
                    return false;
        return true;
    }

    std::string toString() const {
        std::string s = "";
        bool first = true;
        for (auto a : *table)
            for (auto e : a) {
                if (!first)
                    s += ", ";
                first = false;
                s += e.key.toString() +" : "+ e.value.toString();
            }
        return s;
    }

    void saveToFile(const std::string& filename) const
    {

        std::ofstream fs(filename, std::ios::out | std::ios::binary);
        fs.write((char *) &m_size, sizeof(m_size) );
        for (auto a : *table)
            for (auto e : a) {
                int s;
                std::string ks = e.key.toString();
                s = ks.size();
                fs.write((char *) &(s), sizeof(int));
                fs.write((char *) ks.c_str(), ks.size());
                std::string vs = e.value.toString();
                s = vs.size();
                fs.write((char *) &(s), sizeof(int));
                fs.write((char *) vs.c_str(), vs.size());
            }
                fs.close();
    }

    void loadFromFile(const std::string& filename)
    {
        std::ifstream fs(filename, std::ios::in | std::ios::binary);
        int newSize = 0;
        fs.read(reinterpret_cast<char *>(&newSize), sizeof(m_size) );
        for (int i = 0; i < newSize; i++) {
            int ksSize, vsSize;
            K k;
            V v;
            fs.read((char *) &ksSize, sizeof(int));
            char* temp = new char[ksSize+1];
            fs.read((char *) temp, (ksSize));
            temp[ksSize] = '\0';
            k = temp;
            fs.read((char *) &vsSize, sizeof(int));
            temp = new char[vsSize+1];
            fs.read((char *) temp, (vsSize));
            temp[vsSize] = '\0';
            v = temp;
            put(k, v);
        }
        fs.close();
    }

    ~HashMap() {
        delete table;
    }

    HashMap(const HashMap &other) {
        capacity = DEFAULT_CAPACITY;
        threshold = (int)(capacity * loadFactor);
        table = new std::vector<std::vector<Entry>>(capacity);
        for (const auto& a : *other.table)
            for (const auto& e : a) {
                this->put(e.key,  e.value);
            }
    }

    vector<V> get(const std::vector<K> keys) const {
        auto v = std::vector<V>();
            for (auto &k : keys)
            v.push_back((*this)[k]);
        return v;
    }

    V &operator[](const K &key) const {
        size_t hash = key.hash();
        int pos = getPosition(hash, capacity);
        for (auto &a : (*(this->table))[pos])
            if (a.key == key) {
            return a.value;
        }
        throw std::runtime_error(std::string("No such key "+key.toString()));
    }

    std::vector<K> keys() {
        std::vector<K> keys;
        for (const auto& a : *table)
            for (const auto& e : a) {
                keys.push_back(e.key);
            }
        return keys;
    }


};


#endif //UNTITLED56_HSET_H
