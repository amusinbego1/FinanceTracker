//
// Created by Amer on 13. 5. 2025..
//

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "BaseRepository.h"
#include <domain/User.h>

class UserRepository: public BaseRepository{
public:
    static UserRepository& getInstance() {
        static UserRepository instance;
        return instance;
    }

    UserRepository(const UserRepository&) = delete;
    UserRepository& operator=(const UserRepository&) = delete;
    UserRepository(UserRepository&&) = delete;
    UserRepository& operator=(UserRepository&&) = delete;

    void saveUser(const User&);
    std::optional<User> findUserByUsernameAndPassword(const td::String& username, const td::String& password);
    void deleteUserByUsernameAndPassword(const td::String& username, const td::String& password);

private:
    static const char * INSERT_USER_SQL;
    static const char * FIND_USER_BY_USERNAME_AND_PASSWORD_SQL;
    static const char * DELETE_USER_BY_ID;

    UserRepository() = default;

    td::String encryptPassword(const td::String&);
    User findUserForDeletion(dp::Transaction&, const td::String& username, const td::String& password);


};

#endif //USERREPOSITORY_H
