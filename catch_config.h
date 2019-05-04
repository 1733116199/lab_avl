#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int c;
char** v;
int main(int argc, char** argv){
    c = argc;
    v = argv;
    Catch::Session session;
    return session.run();
}