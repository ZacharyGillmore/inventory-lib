#ifndef INVENTORY_H
#define INVENTORY_H

#include <cstddef>
#include <string>
#include <cstdint>

using std::string;

class Inventory
{
    public:
        typedef struct {
            string name;
            uint8_t amount;
            uint8_t type; // 1 is material, 2 is consumable
        } item;
    private:
        unsigned int money;
        int max_size;
        item *inventory = NULL;

    public:
        Inventory(int size);
        ~Inventory();

        void save(string fname);
        void auto_add(item *pickup);
        void add_item(item *pickup, int index);
        void drop_item(item *pickup, int index);
        void load(string fname);
        void print();
};

#endif // INVENTORY_H
