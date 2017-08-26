#ifndef MRT_SP_MAIN
#define MRT_SP_MAIN

constexpr int FIRST_PARAM_POS = 1;
constexpr const char* SWITCH_LENGTH = "--length";
constexpr const char* SWITCH_SHORT_LENGTH = "-l";
constexpr const char* SWITCH_RULE = "--rule";
constexpr const char* SWITCH_SHORT_RULE = "-r";
constexpr const char* SWITCH_SPECIALS = "--specials";
constexpr const char* SWITCH_SHORT_SPECIALS = "-s";
constexpr const char* SWITCH_HELP = "--help";
constexpr const char* SWITCH_SHORT_HELP = "-h";

constexpr int RETCODE_ERROR = -1;
constexpr int RETCODE_SUCCESS = 0;

bool same(const char*, const char*) noexcept;
std::string execute_basic(const int, const bool);
std::string try_execute_rule(const int, const int, char**);
std::string execute_rule(const char*);
std::string help();

#endif