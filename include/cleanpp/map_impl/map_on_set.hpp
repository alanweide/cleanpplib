#ifndef map_on_set_h
#define map_on_set_h

#include <sstream>

#include "map_impl.hpp"

#include <set.hpp>

namespace cleanpp
{

template <typename K, typename V>
class map_on_set : public map_impl<K, V> {
private:



    set<pair<K, V>> rep;

    void createNewRep() {
        this->rep = set<pair<K, V>>();
    }

    /**
     * Constructors--------------------------------------------------------------------
     **/

    public:

    map_on_set() {
        this->createNewRep();
    }

    map_on_set<K, V>& operator=(const map_on_set<K, V>& other) = delete;

    map_on_set<K, V>& operator=(map_on_set<K, V>&& other) {
        if (&other == this) {
            return *this;
        }

        this->rep = std::move(other.rep);
        other.clear();

        return *this;
    }

    void clear() {
        this->rep.clear();
    }

    /**
     * Kernel methods-------------------------------------------------------
     **/

    void add(K&& key, V&& value) {
        pair<K, V> element(std::move(key), std::move(value));
        this->rep.add(std::move(element));

    }

    pair<K, V> remove(K&& key) {
        set<pair<K, V>> temp;
        pair<K, V> result;
        while (this->rep.getSize() != 0) {
            pair<K, V> element = this->rep.removeAny();

            if (element == key) {
                result = std::move(element);
            } else {
                temp.add(std::move(element));
            }

        }
        this->rep = std::move(temp);
        return result;
    }

    pair<K, V> removeAny() {
        return this->rep.removeAny();
    }

    bool hasKey(K&& key) {

        bool hasKey = false;
        set<pair<K, V>> temp;
        while (this->rep.getSize() != 0 && !hasKey) {
            pair<K, V> element = this->rep.removeAny();
            if (element == key) {
                hasKey = true;
            }
            temp.add(std::move(element));
        }
        while (temp.getSize() != 0) {
            this->rep.add(temp.removeAny());
        }

        return hasKey;
    }

    V value(K&& key) {
        set<pair<K, V>> temp;
        V result;

        while (this->rep.getSize() != 0) {
            pair<K, V> element = this->rep.removeAny();
            if (element == key) {
                result = element.getValue(std::move(key));
            }
        }

        while (temp.getSize() != 0) {
            this->rep.add(temp.removeAny());
        }

        return result;
    }

    int size() {
        return this->rep.getSize();
    }

private:
    std::string to_str() {

        std::stringstream out;

        out << this->rep;

        return out.str();
    }


};


}




#endif /* map_on_set_h */