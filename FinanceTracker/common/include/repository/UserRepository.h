//
// Created by Amer on 13. 5. 2025..
//

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "BaseRepository.h"

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


private:
    UserRepository() = default;

};

#endif //USERREPOSITORY_H
