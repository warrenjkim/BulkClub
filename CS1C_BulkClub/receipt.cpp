#include "receipt.h"

//default constructor
Receipt::Receipt() {

}

//destructor
Receipt::~Receipt() {

}

//receipt
std::vector<std::pair<Date, ItemList>> Receipt::receipt() const {
    return m_Receipt;
}

//size
size_t Receipt::size() const {
    return m_Receipt.size();
}

//empty
bool Receipt::empty() const {
    return m_Receipt.size() == 0;
}

//receipt by date
ItemList Receipt::receiptByDay(const Date& key) {
    ItemList empty;
    for(auto& x : m_Receipt) {
        if(x.first == key) {
            return x.second;
        }
    }
    return empty;
}

//add item
bool Receipt::add(const Date& day, Item* item) {
    //for each element in receip
    for(auto& x : m_Receipt) {
        //add to date
        if(x.first == day) {
            x.second.insert(item);
            //not a new day
            return false;
        }
    }
    //else make a new item list with a new date and push it back to receipt
    ItemList temp;
    temp.insert(item);
    m_Receipt.push_back(std::make_pair(day, temp));

    return true;
}

//receipt string
QString Receipt::receiptString() const {
    if(m_Receipt.empty()) {
        return "";
    }

    QString str = "";
    QString date, list;
    for(size_t i = 0; i < m_Receipt.size(); i ++) {
        date = "#" + m_Receipt[i].first.dateString();
        list = m_Receipt[i].second.itemListString();

        if(i + 1 == m_Receipt.size()) {
            str += date + ", " + list + " ";
            break;
        }
        str += date + ", " + list + ", ";

        date = "";
        list = "";
    }

    return str;
}
