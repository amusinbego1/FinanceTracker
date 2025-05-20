#include <iostream>
#include <domain/Category.h>
#include <repository/CategoryRepository.h>
#include <repository/TransactionRepository.h>
#include <service/TransactionService.h>

#include "domain/User.h"
#include "repository/UserRepository.h"
#include "gui/FTApplication.h"

int main(int argc, const char * argv[])
{
    FTApplication app(argc, argv);
    app.init("BA");
    return app.run();
}
