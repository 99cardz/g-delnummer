#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <istream>
#include <map>
#include <regex>
#include <random>
#include "Primes.hpp"
#include "Translator.hpp"
#include "GNumber.hpp"

using namespace std;


template<typename T>
void assert_equal(const T& test, const T& expected,const string& comment = "")
{
    cout << setw(50) << left << comment;
    if (test == expected)
        cout << "PASSED";
    else
        cout << '"' << test << '"' << " is not equal to expected " << '"' << expected << '"';
    cout << endl;
}

string vector_to_string(std::vector<unsigned int> v)
{
    string ret;
    for (auto i : v)
        ret += i;
    return ret;
}

int main() 
{
    


    cout << "####### Testing Primes #######" << endl;

    istringstream primeRaw("2, 3, 5");
	Primes primes(primeRaw);

    assert_equal(primes.next(), 2U, "Primes.next()");
    assert_equal(primes.next(), 3U, "Primes.next()");
    assert_equal(primes.next(), 5U, "Primes.next()");
    assert_equal(primes.next(), 7U, "Primes.next() should calc");
    assert_equal(primes.next(), 11U, "Primes.next() should calc");

    primes.reset();
    assert_equal(primes.next(), 2U, "Primes.reset()");
    assert_equal(primes.next(), 3U, "Primes.next()");
    assert_equal(primes.next(), 5U, "Primes.next()");
    assert_equal(primes.next(), 7U, "Primes.next()");
    assert_equal(primes.next(), 11U, "Primes.next()");
    assert_equal(primes.next(), 13U, "Primes.next() should calc");
    assert_equal(primes.next(), 17U, "Primes.next() should calc");


    istringstream valueRaw("# comment\n+ 1\n- 2\n \n  #comment\n0 3\ns 4"); // 1:+ 2:- 3:0 4:s
	Translator t(valueRaw);

    cout << "####### Testing replace modified function #######" << endl;

    function<string(string)> mod1 = [](string s) { return "$$"; };
    function<string(string)> mod2 = [](string s) { return string(stoi(s), '$'); };
    regex r("\\d+");

    assert_equal(t.replace_modified("abc 123+456 980 abc", r, mod1), string("abc $$+$$ $$ abc"), "replace_mod1");
    assert_equal(t.replace_modified("a-2+3=c", r, mod2), string("a-$$+$$$=c"), "replace_mod2");





    cout << "####### Testing Translator #######" << endl;
    string error1;
    assert_equal(t.find_invalid_chars("+-0s", error1), false, "Constructor loaded correctly");
    assert_equal(error1, string("    "), "error string empty");
    assert_equal(t.find_invalid_chars("3/5", error1), true, "find_invalid_chars");
    assert_equal(error1, string(" ^ "), "error string content");

    string term1 = "a-    b*c";
    assert_equal(t.sanitise(term1), string("a-b*c"), "sanitise whitespaces");
    string term2 = "003-04*a-0";
    string term2clean = t.sanitise(term2);
    assert_equal(term2clean, string("3-4*a-0"), "sanitise leading spaces");
    assert_equal(t.prettify(term2clean), string("   3-    4*a-0"), "prettify numbers");

    string term3 = "a-10*b";
    assert_equal(t.prettify(term3), string("a-         10*b"), "prettify numbers > 10");


    string term4 = "2-3";
    assert_equal(t.convert_numbers(term4), string("ss0-sss0"), "convert numbers basic");
    string term5 = "001-10";
    assert_equal(t.convert_numbers(term5), string("s0-ssssssssss0"), "convert numbers > 9");


    string term6 = "+s0-ss0";
    vector<unsigned int> values6 = {1,4,3,2,4,4,3}; // 1:+ 2:- 3:0 4:s

    assert_equal(vector_to_string(t.term_to_values(term6)), vector_to_string(values6), "term to values");


    string term7 = "000102-04-a*0040";
    
    assert_equal(t.sanitise(term7), string("102-4-a*40"), "sanitise leading spaces, with multidigit numbers");


    string term8 = "0000-0001";
    assert_equal(t.sanitise(term8), string("0-1"), "sanitise leading 0");

    string term9 = "0000400-123";
    assert_equal(t.sanitise(term9), string("400-123"), "sanitise leading 0 > 100");

    string term10 = "400-123";
    assert_equal(t.sanitise(term10), string("400-123"), "sanitise > 100");


    istringstream valueRaw2("= 100\n # comment\n- 10\n s 1\n 0 9"); 
	Translator t2(valueRaw2);

    assert_equal(t2.allChars(), string("=-s0"), "allChars");
    assert_equal(t2.valueMaxWidth(), 3U, "maxWidthValue");

    cout << "####### Testing GNumber #######" << endl;

    GNumber g1(123512321);
    ostringstream oss1;
    oss1 << g1;
    assert_equal(oss1.str(), string("123512321"), "init GNumber1");

    GNumber g2(624573457);
    ostringstream oss2;
    oss2 << g2;
    assert_equal(oss2.str(), string("624573457"), "init GNumber2");

    ostringstream oss3;
    oss3 << g1 * g2;
    assert_equal(oss3.str(), string("77142517309063697"), "multiply GNumber");

    random_device rd; 
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0,numeric_limits<unsigned short>::max());
    ostringstream ossRd;
    unsigned long long a, b;

    for (unsigned int i = 0; i < 10; i++)
    {
        ossRd.str("");
        ossRd.clear();
        a = uni(rng);
        b = uni(rng);
        ossRd << (GNumber(a) *  GNumber(b));
        assert_equal(ossRd.str(), to_string(a * b), "Random multiplication");
    }

    cout << "####### Testing simple_pow method #######" << endl;

    ostringstream oss4;
    oss4 << GNumber::simple_pow(35, 7);
    assert_equal(oss4.str(), string("64339296875"), "pow1");
    ostringstream oss5;
    oss5 << GNumber::simple_pow(10, 2);
    assert_equal(oss5.str(), string("100"), "pow2");
    ostringstream oss6;
    oss6 << GNumber::simple_pow(11, 9);
    assert_equal(oss6.str(), string("2357947691"), "pow3");

}