//
// Created by Amer on 14. 5. 2025..
//


#include "repository/UserRepository.h"
#include <dp/IStatement.h>
#include <crpt/SHA256.h>

const char* UserRepository::INSERT_USER_SQL = "INSERT INTO users (username, password) VALUES (?, ?)";
const char* UserRepository::FIND_USER_BY_USERNAME_AND_PASSWORD_SQL = "SELECT id FROM users WHERE username = ? AND password = ?";
const char* UserRepository::DELETE_USER_BY_ID = "DELETE FROM users WHERE id = ?";

td::String UserRepository::encryptPassword(const td::String &password) {
    crpt::SHA256 sha256;
    td::String encryptedPassword;
    sha256.calcToHex(password, encryptedPassword);
    return encryptedPassword;
}



void UserRepository::saveUser(const User &user) {
    dp::IStatementPtr saveStatPtr(_databasePtr->createStatement(INSERT_USER_SQL));

    td::Variant b_username(td::string8, td::nch, 30);
    td::Variant b_password(td::string8, td::nch, 64);


    dp::Params params(saveStatPtr->allocParams());
    params << b_username << b_password;

    dp::Transaction transaction(_databasePtr);
    b_username = user.username;
    b_password = encryptPassword(user.password);

    executeStatementAndThrowErrorIfExists(saveStatPtr, transaction);

    transaction.commit();
}

std::optional<User> UserRepository::findUserByUsernameAndPassword(const td::String& username, const td::String& password) {
    td::INT4 user_id;
    td::String encryptedPassword = encryptPassword(password);

    dp::IStatementPtr pStatPtr(_databasePtr->createStatement(FIND_USER_BY_USERNAME_AND_PASSWORD_SQL));

    td::Variant b_username(td::string8, td::nch, 30);
    td::Variant b_password(td::string8, td::nch, 64);

    dp::Columns columns(pStatPtr->allocBindColumns(1));
    columns << "id" << user_id;

    dp::Params params(pStatPtr->allocParams());
    params << b_username << b_password;

    b_username = username;
    b_password = encryptedPassword;

    if (!pStatPtr->execute() || !pStatPtr->moveNext())
        return std::nullopt;


    return User{user_id, username, encryptedPassword};
}

User UserRepository::findUserForDeletion(dp::Transaction& transaction, const td::String& username, const td::String& password) {
    auto userOptional = findUserByUsernameAndPassword(username,password);
    if (!userOptional.has_value()) {
        transaction.rollBack();
        throw std::logic_error("Incorrect Password");
    }
    return userOptional.value();
}

void UserRepository::deleteUserByUsernameAndPassword(const td::String& username, const td::String& password) {
    dp::Transaction transaction(_databasePtr);
    User userToDelete = findUserForDeletion(transaction, username, password);

    dp::IStatementPtr deleteStatPtr(_databasePtr->createStatement(DELETE_USER_BY_ID));

    dp::Params params(deleteStatPtr->allocParams());
    params << userToDelete.id;

    executeStatementAndThrowErrorIfExists(deleteStatPtr, transaction);
    transaction.commit();
}
