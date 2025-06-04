#ifndef DOCTEST_H
#define DOCTEST_H
#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
namespace doctest {
    struct TestCase { const char* name; void(*func)(); };
    inline std::vector<TestCase>& getTests(){ static std::vector<TestCase> t; return t; }
    struct Reg{ Reg(const char* name, void(*func)()){ getTests().push_back({name, func}); } };
}
#define TEST_CASE(name) \
    static void name(); \
    static doctest::Reg reg_##name(#name, name); \
    static void name()
#define CHECK(expr) do{ if(!(expr)) throw std::runtime_error("Check failed: " #expr); }while(0)
#ifdef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
int main(){
    int failures = 0;
    for(auto& tc: doctest::getTests()){
        try{ tc.func(); std::cout << tc.name << " - OK" << std::endl; }
        catch(const std::exception& e){ failures++; std::cout << tc.name << " - FAILED: " << e.what() << std::endl; }
        catch(...){ failures++; std::cout << tc.name << " - FAILED" << std::endl; }
    }
    if(failures) std::cout << failures << " test(s) failed" << std::endl;
    return failures ? 1 : 0;
}
#endif
#endif // DOCTEST_H
