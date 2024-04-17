#ifndef DATABASE
#define DATABASE 
#include <sqlite3.h>
#include <string>
#include <vector>

struct Instrument{
    unsigned int id;
    std::string figi;
    std::string ticker;
    std::string name;
    std::string country_of_risk_name;
    std::string text;
};


class Database{
private:
    sqlite3 *db; //ссылка на таблицу
    int status;
    char* errorMessage; 

public:
    Database(const std::string& path="database.db");
    ~Database();
    void createTables();
    void addInstrument(
        const std::string& figi, 
        const std::string& ticker, 
        const std::string& name, 
        const std::string& country_of_risk_name, 
        const std::string& text);
    std::vector<Instrument> getInstruments();
};


Database::Database(const std::string& path)
{
    status = sqlite3_open(path.c_str(), &db); //возвращает 0 - без ошибок, 1 - ошибка
};

Database::~Database(){
    status = sqlite3_close(db);
}

void Database::createTables(){
    std::string queryInstrument = "CREATE TABLE IF NOT EXISTS instrument("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "figi TEXT, "
       " ticker TEXT, "
        "name TEXT,"
        "country_of_risk_name TEXT,"
        "sector TEXT);";
    status = sqlite3_exec(db, queryInstrument.c_str(), NULL, NULL, &errorMessage); //db - указатель на базу данных
}

void Database::addInstrument(
    const std::string& figi, 
    const std::string& ticker, 
    const std::string& name, 
    const std::string& country_of_risk_name, 
    const std::string& text)
    {
        std::string query = "INSERT INTO instrument(figi, ticker, name, country_of_risk_name, sector) "
            "VALUES ('" + figi + "', '" + ticker + "', '" + name + "', '" + country_of_risk_name + "', '" + text + "');"; //' ' - текстовые поля
        status = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorMessage); //db - указатель на базу данных
    }

int callback(void* data, int argc, char** argv, char** azColName) //argv - строки, azColName - названия колонок
{
    (*data)[0] = new Instrument[argc];
    for (int i = 0; i < argc; i++){
        std::cout << azColName[i] << " = " << argv[i] << std::endl;
    }
    return 0;
}


std::vector<Instrument> Database::getInstruments()
{
    Instrument** instruments = new Instrument*[1000];
    std::string query = "SELECT * FROM instrument"; //* все колонки таблицы 
    status = sqlite3_exec(db, query.c_str(), callback, (void*)instruments, &errorMessage); //callback обрабатывает каждую строчку, instruments.data() - ptr
    return std::vector<Instrument>();
}
#endif