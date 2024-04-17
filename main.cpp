#include <iostream>
#include "database.h"

int main(){
    Database db;
    db.createTables();
    db.addInstrument("1", "2", "3", "4", "5");
    db.getInstruments();
}
