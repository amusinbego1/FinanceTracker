//
// Created by Amer on 14. 5. 2025..
//


#include "repository/UserRepository.h"
#include <dp/IStatement.h>
#include <crpt/SHA256.h>

const char* UserRepository::INSERT_USER_SQL = "INSERT INTO users (username, password) VALUES (?, ?)";

td::String UserRepository::encryptPassword(const td::String &password) {
    crpt::SHA256 sha256;
    td::String encryptedPassword;
    sha256.calcToHex(password, encryptedPassword);
    return encryptedPassword;
}



void UserRepository::saveUser(const User &user) {
    dp::IStatementPtr pStatPtr(_databasePtr->createStatement(INSERT_USER_SQL));

    td::Variant b_username(td::string8, td::nch, 30);
    td::Variant b_password(td::string8, td::nch, 64);


    dp::Params params(pStatPtr->allocParams());
    params << b_username << b_password;

    dp::Transaction transaction(_databasePtr);
    b_username = user.username;
    b_password = encryptPassword(user.password);
    if(!pStatPtr -> execute()) {
        transaction.rollBack();
        td::String strErr;
        pStatPtr->getErrorStr(strErr);
        throw std::exception(strErr.c_str());
    }

    transaction.commit();
}