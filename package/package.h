#ifndef PACKAGE_H
#define PACKAGE_H

#include <variant>

#pragma pack(push, 1)

struct ServerIntro{
    char intro[2047];
} server_intro;

struct SearchFile{
    char filename[50];
} search_file;

struct PleaseWait{
    char plswait[30];
} please_wait;

struct ResultPath{
    char result[50];
} result_path;

std::variant<ServerIntro, SearchFile, PleaseWait, ResultPath> Package;
// using Package = std::variant<ServerIntro, SearchFile, PleaseWait, ResultPath>

static_assert(sizeof(Package) == 2048, "Package size != 2048");

#pragma pack(pop)

#endif // PACKAGE_H