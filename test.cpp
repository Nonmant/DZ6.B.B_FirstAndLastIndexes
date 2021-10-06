#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"4\n"
                  "1 2 2 3\n"
                  "4\n"
                  "4 3 2 1";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "0 0\n"
                            "4 4\n"
                            "2 3\n"
                            "1 1\n");
}

TEST_CASE("test 2", "[simple]"){
    std::stringstream input, output;
    input<<"10\n"
           "1 2 3 4 5 6 7 7 8 9\n"
           "10\n"
           "7 3 3 1 3 7 9 7 7 10";
    parseFile(input,output);
    REQUIRE(output.str() == "7 8\n"
                            "3 3\n"
                            "3 3\n"
                            "1 1\n"
                            "3 3\n"
                            "7 8\n"
                            "10 10\n"
                            "7 8\n"
                            "7 8\n"
                            "0 0\n");
}

TEST_CASE("test 3", "[simple]"){
    std::stringstream input, output;
    input<<"10\n"
           "1 3 3 3 3 6 8 8 9 10\n"
           "10\n"
           "2 9 6 4 2 9 3 7 9 7";
    parseFile(input,output);
    REQUIRE(output.str() == "0 0\n"
                            "9 9\n"
                            "6 6\n"
                            "0 0\n"
                            "0 0\n"
                            "9 9\n"
                            "2 5\n"
                            "0 0\n"
                            "9 9\n"
                            "0 0\n");
}

TEST_CASE("all smaller", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 2 3\n"
           "1\n"
           "4";
    parseFile(input,output);
    REQUIRE(output.str() =="0 0\n");
}

TEST_CASE("all bigger", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 2 3\n"
           "1\n"
           "0";
    parseFile(input,output);
    REQUIRE(output.str() =="0 0\n");
}

TEST_CASE("all array", ""){
    std::stringstream input, output;
    input<<"3\n"
           "3 3 3\n"
           "1\n"
           "3";
    parseFile(input,output);
    REQUIRE(output.str() =="1 3\n");
}

TEST_CASE("in range, but not equal", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 2 4\n"
           "1\n"
           "3";
    parseFile(input,output);
    REQUIRE(output.str() =="0 0\n");
}

TEST_CASE("one first", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 2 4\n"
           "1\n"
           "1";
    parseFile(input,output);
    REQUIRE(output.str() =="1 1\n");
}

TEST_CASE("one last", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 2 4\n"
           "1\n"
           "4";
    parseFile(input,output);
    REQUIRE(output.str() =="3 3\n");
}

TEST_CASE("multiple first", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 1 4\n"
           "1\n"
           "1";
    parseFile(input,output);
    REQUIRE(output.str() =="1 2\n");
}

TEST_CASE("multiple last", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 4 4\n"
           "1\n"
           "4";
    parseFile(input,output);
    REQUIRE(output.str() =="2 3\n");
}

TEST_CASE("one middle", ""){
    std::stringstream input, output;
    input<<"3\n"
           "1 2 4\n"
           "1\n"
           "2";
    parseFile(input,output);
    REQUIRE(output.str() =="2 2\n");
}

TEST_CASE("multiple middle", ""){
    std::stringstream input, output;
    input<<"5\n"
           "1 2 2 2 4\n"
           "1\n"
           "2";
    parseFile(input,output);
    REQUIRE(output.str() =="2 4\n");
}
