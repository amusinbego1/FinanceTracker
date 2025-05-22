//
// Created by Amer on 13. 5. 2025..
//

#ifndef BASEREPOSITORY_H
#define BASEREPOSITORY_H

#include <td/String.h>
#include <fo/Definitions.h>
#include <dp/IDatabase.h>
#include <stdexcept>
#include <mu/mu.h>

class BaseRepository {
public:
    BaseRepository(){
        // mu::getHomePath(_homePath);
        _dbFullPath = DB_PATH;
        _databasePtr = dp::create(dp::IDatabase::ConnType::CT_SQLITE, dp::IDatabase::ServerType::SER_SQLITE3);

        connect();
    }

    virtual ~BaseRepository() = default;


    virtual void connect() final{
        if (_databasePtr->isConnected())
            return;

        if (!_databasePtr.getPtr() || !_databasePtr->connect(_dbFullPath))
            throw std::exception("Couldn't connect to the Database");
    }

    virtual void disconnect() final{
        if (_databasePtr->isConnected())
            _databasePtr->release();
    }

    virtual bool isConnectionOK() const final
    {
        if (!_databasePtr->isConnected())
        {
            return false;
        }
        return true;
    }

protected:
    dp::IDatabasePtr _databasePtr;

    inline void executeStatementAndThrowErrorIfExists(dp::IStatementPtr& statementPtr, dp::Transaction& transaction) {
        if(!statementPtr -> execute()) {
            transaction.rollBack();
            td::String strErr;
            statementPtr->getErrorStr(strErr);
            throw std::exception(strErr.c_str());
        }
    }

private:

    fo::fs::path _homePath;
    fo::fs::path _dbFullPath;

};


#endif //BASEREPOSITORY_H
