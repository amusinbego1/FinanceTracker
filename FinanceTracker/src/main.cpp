#include <iostream>
#include "domain/User.h"
int main() {

    User user{1, "Nest", "Mest"};
    std::cout<<user.username;
    return 0;
}
