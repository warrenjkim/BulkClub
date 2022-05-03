#include "itemlist.h"

//==========================================PRIVATE MEMBER FUNCTIONS==========================================

//indexof
int ItemList::indexOf(const QString& name) {
    for(size_t i = 0; i < this->m_ItemList.size(); i++) {
        if((this->m_ItemList[i])->name() == name) {
            return i;
        }
    }
    return -1;
}

//=============================================================================================================


//===========================================PUBLIC MEMBER FUNCTIONS===========================================

//constructor
ItemList::ItemList() {

}

//copy constructor
ItemList::ItemList(const ItemList& other) {
    for(const auto& x : other.itemList()) {
        Item* temp = new Item(*x);
        this->m_ItemList.push_back(temp);
    }
    //this->m_ItemList = other.itemList();
}

//overloaded constructor
ItemList::ItemList(const std::vector<Item*>& itemList) {
    for(size_t i = 0; i < itemList.size(); i++) {
        *(this->m_ItemList[i]) = *(itemList[i]);
    }
}

//destructor
ItemList::~ItemList() {
    this->m_ItemList.clear();
}

// vector functoins


std::vector<Item*>::const_iterator ItemList::begin() const {
    return this->m_ItemList.begin();
}

std::vector<Item*>::const_iterator ItemList::end() const {
    return this->m_ItemList.begin();
}

Item* ItemList::at(const int& index) const {
    return this->m_ItemList[index];
}

Item*& ItemList::operator[](const int& index) const {
    Item* item = this->m_ItemList[index];
    return item;
}

//itemList
std::vector<Item*> ItemList::itemList() const {
    return this->m_ItemList;
}

//size
size_t ItemList::size() const {
    return this->m_ItemList.size();
}

//insert
void ItemList::insert(Item* item) {
    this->m_ItemList.push_back(item);
}

void ItemList::insertInventory(Item* item) {
    for(auto& tempItem : this->m_ItemList) {
        if(tempItem->name() == item->name()) {
            tempItem->addQuantity(item->quantity());
            return;
        }
    }
    insert(item);
}

bool ItemList::empty() const {
    return this->m_ItemList.size() == 0;
}

//removeItem
bool ItemList::removeItem(const QString& name) {
    //find item
    if(find(name) == nullptr) {
        //item doesn't exist
        return false;
    }

    //for each item in the item list
    for(auto& item : this->m_ItemList) {
        //if name matches
        if(item->name() == name) {
            //remove item
            this->m_ItemList.erase(std::find(this->m_ItemList.begin(), this->m_ItemList.end(), item));
            return true;
        }
    }
    //item doesn't exist
    return false;
}

//find
Item* ItemList::find(const QString& name) {
    //for each item in item list
    for(auto& item : this->m_ItemList) {
        //if the item names match
        if(item->name() == name) {
            return item;
        }
    }

    //item doesn't exist
    return nullptr;
}

//itemListString
QString ItemList::itemListString() const {
    if(this->m_ItemList.empty()) {
        return "";
    }

    QString str = "";
    QString name, price, quantity;
    for(size_t i = 0; i < this->m_ItemList.size(); i++) {
        //parse temp item
        Item* temp = this->m_ItemList[i];
        name = temp->name();
        price = QString::number(temp->price());
        quantity = QString::number(temp->quantity());

        //add to string
        if(i + 1 == this->m_ItemList.size()) {
            str += name + ", " + price + ", " + quantity + ", ";
            break;
        }
        else {
            str += name + ", " + price + ", " + quantity + ", ";
        }

        name = "";
        price = "";
        quantity = "";
    }
    return str;
}

void ItemList::sort() {
    std::sort(this->m_ItemList.begin(), this->m_ItemList.end(), std::less<Item*>());
}
//=============================================================================================================
