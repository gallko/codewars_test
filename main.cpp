#include <iostream>
#include <future>
#include <vector>
#include <regex>

#include <algorithm>
#include <numeric>
#include <cmath>
#include <set>
#include <unordered_set>

template <typename T>
class Q;

//template <typename T, typename = std::enable_if_t <
//        !std::is_same<
//                typename std::iterator_traits<typename T::const_iterator>::value_type,
//                void>::value
//    &&
//        !std::is_base_of<std::string, std::decay_t<T>>::value
//    >
//>
//std::ostream& operator<<(std::ostream& os, const T& a) {
//    for(const auto &it: a)
//        os << it << " ";
//    return os;
//}
//

void test() {

}


size_t duplicateCount(const char* in)
{
    std::map<char, int> acc;
    for(const char *i = in; *i != '\0'; ++i)
        acc[tolower(*i)]++;
    return static_cast<size_t>(std::count_if(acc.begin(), acc.end(),
            [](const std::pair<char, int> &p) {
        return p.second > 1;
    }));
}

std::vector<int> sqInRect(int lng, int wdth) {
    if (lng == wdth) return {};
    std::vector<int> acc;
    while (lng != 0 && wdth != 0) {
        if (lng > wdth) {
            acc.push_back(wdth);
            lng -= wdth;
            continue;
        } else {
            acc.push_back(lng);
            wdth -= lng;
        }
    }
    return std::move(acc);
}

std::string listSquared(long long m, long long n) {
    double c;
    std::vector<std::pair<long long, long long>> result;
    for (auto i = m; i <= n; ++i) {
        std::vector<int> div{1};
        long long dx = 1;
        for (int j = 2; j <= static_cast<int>(sqrt(i)); j++) {
            if (i % j) continue;
            div.push_back(j);
        }

        dx = std::accumulate(div.begin(), div.end(), 0, [&i](auto in_acc, auto elem) {
            int x = i / elem;
            x = x != elem ? x * x : 0;
            return (in_acc + elem * elem + x);
        });

        if (std::modf(std::sqrt(dx), &c) == static_cast<double>(0.0)) {
            result.push_back({i, dx});
        }
    }

    std::stringstream r;
    r << "{";
    for (auto it: result) {
        if (r.str().size() > 2) r << ", ";
        r << "{" << it.first << ", " << it.second << "}";
    }
    r << "}";

    return r.str();
}


std::string revrot(const std::string &strng, unsigned int sz) {
    if (sz <= 0 || strng.empty() || sz > strng.size()) return "";
    std::string result;
    using c_iterator = std::string::const_iterator;
    using iterator = std::string::iterator;

    for(c_iterator it = strng.cbegin(); (it + sz) <= strng.cend(); it += sz) {
        c_iterator begin = it, end = it + sz;
        auto sum = std::accumulate(begin, end, 0, [](auto acc, auto elem) {
            auto t = elem - 48;
            return acc + t*t*t;
        });
        if (sum % 2) {
            // rotate it to the left by one position
            result += std::string(begin + 1, end);
            result += std::string(begin, begin + 1);
        } else {
            // reverse
            for(c_iterator i = end - 1; i != begin - 1; --i) {
                result.push_back(*i);
            }
        }
    }
    return std::move(result);
}

bool valid_braces(std::string braces)
{
    // valid or not valid?
    std::map<char, char> close{{'}','{'}, {']','['}, {')','('}};
    std::vector<char> acc;
    for (auto &it: braces) {
        auto it_lose = close.find(it);
        if(it_lose == close.end()) {
            acc.push_back(it);
        } else {
            if (acc.empty()) return false;
            if (acc.back() == it_lose->second) acc.pop_back();
            else return false;
        }

    }
    return acc.empty();
}

long zeros(long n) {
    long long acc = 0, tmp = 0;

    for(long long i = 1; n > tmp; ++i) {
        tmp = static_cast<long long>(pow(5, i));
        acc += n / tmp;
    }

    return acc;
}

bool isPrime(int num) {
    if (num <= 0) return false;
    if (num == 1) return false;
    for (int i = 2; i <= sqrt(num); ++i) {
        if (!(num % i)) return false;
    }
    return true;
}

std::string pigIt2(const std::string &str) {
    std::regex reg{"(\\w)(\\w*)(\\s|$)"};
    return std::regex_replace(str, reg, "$2$1ay$3");
}
std::string pigIt(const std::string &str) {
    std::ostringstream ss_out;
    std::string out;
    std::cout << str << std::endl;
    char first = 0x00;
    for(auto it = str.begin(); it <= str.end(); ++it) {
        if(isalpha(*it)) {
            if (!first) first = *it;
            else ss_out << *it;
            continue;
        }
        if (first) ss_out << first << "ay";
        if (it != str.end()) ss_out << *it;
        first = 0x00;
    }
    return ss_out.str();
}

std::unordered_set<std::string> generate(char ch, const std::string &in) {
    std::unordered_set<std::string> acc{};
    acc.insert(std::string{ch} + in);
    for (auto it = in.begin(); it != in.end() ; ++it)
        acc.insert(
                std::string(in.cbegin(), it) +
                std::string{ch} + std::string(it, in.cend())
        );
    acc.insert(in + std::string{ch});
    return std::move(acc);
}

std::vector<std::string> permutations2(std::string s)
{
    std::sort(s.begin(), s.end());
    std::vector<std::string> result;
    do
    {
        result.push_back(s);
    }
    while (std::next_permutation(s.begin(), s.end()));
    return result;
}

std::vector<std::string> permutations(std::string s) {
    if (s.empty()) return {""};
    using set = std::unordered_set<std::string>;
    set d{std::string{s[0]}};

    for (auto ch = s.cbegin() + 1; ch != s.cend(); ++ch) {
        std::vector<set> vs{};
        for(const auto &item: d)
            vs.push_back(generate(*ch, item));
        d.clear();
        for(auto item: vs)
            d.insert(item.begin(), item.end());
    }
    return std::vector<std::string>(d.begin(), d.end());
}


//Expected: equal to 8757893018872981178457201150120117898112199399708766596604838159031972384445317104775645041857013092826100600084089885620245218538962774875195534941616771797563893371
//Actual:           08757893018872981178457201150120117898112199399708766596604838159031972384445317104775645041857013092826100600084089885620245218538962774875195534941616771797563893371
std::string sumStrings(std::string a, std::string b) {
    std::string &max = a.size() >= b.size() ? a : b;
    std::string &min = a.size() < b.size() ? a : b;
    std::string result;
    int tmp = 0;

    for(auto it_min = min.rbegin(), it_max = max.rbegin(); it_min != min.rend(); ++it_min, ++it_max) {
        auto sum = *it_min + *it_max - 96 + tmp;
        result.push_back(static_cast<char>(sum % 10 + 48));
        tmp = sum / 10;
    }

    for(auto it_max = max.rbegin() + min.size(); it_max != max.rend(); ++it_max) {
        auto sum = *it_max + tmp - 48;
        result.push_back(static_cast<char>(sum % 10 + 48));
        tmp = sum / 10;
    }
    if (tmp) result.push_back(static_cast<char>(tmp + 48));

    while (*(result.end() - 1) == 48 && result.size() != 1) result.pop_back();

    std::reverse(result.begin(), result.end());
    return result;
}

std::string mult(const std::string &a, std::uint8_t b) {
    std::string result;
    std::uint8_t carry = 0;
    if (!b || (a.size() == 1 && a[0] == '0')) return "0";
    for(auto ch = a.crbegin(); ch != a.crend(); ++ch) {
        auto sum = static_cast<std::uint8_t>((*ch - 48) * b + carry);
        result.push_back(static_cast<char>((sum % 10) + 48));
        carry = static_cast<std::uint8_t>(sum / 10);
    }
    if (carry) result.push_back(static_cast<char>(carry + 48));
    return std::move(result);
}

std::string sum(std::string a, std::string b) {
    auto max = a.size() >= b.size() ? a.size() : b.size();
    auto it_a = a.cbegin(), it_b = b.cbegin();
    std::string result;
    int carry = 0;
    for (auto i = 0; i < max; ++i) {
        auto _a = i < max ? *it_a++ : 0;
        auto _b = i < max ? *it_b++ : 0;
        auto sum = _a + _b - 96 + carry;
        result.push_back(static_cast<char>((sum % 10) + 48));
        carry = sum / 10;
    }
    if (carry) result.push_back(static_cast<char>(carry));
    return std::move(result);
}

std::string multiplication(std::string a, std::string b) {
    int i = 0;
    std::string sum;
    for (auto ch = b.crbegin(); ch != b.crend(); ++i, ++ch) {
        sum = mult(a, static_cast<std::uint8_t>(*ch - 48));
    }
}

int main() {
    auto y = multiplication("25", "25");

    auto y1 = sum("52", "52");

    int x = duplicateCount("aabbcde");

    auto gf = sqInRect(5, 3);

    auto d = listSquared(1, 250);

    auto d1 = revrot("73304991087281576455176044327690580265896", 8);
                                                                         // 1994033775182780067155464327690480265895

    auto d2 = zeros(1000);

    auto d3 = isPrime(-10);


    auto d4 = pigIt("Pig latin is cool"); // igPay atinlay siay oolcay
    d4 = pigIt("Hello, world  !\t\n");     // elloHay orldway !
    d4  = pigIt2("Hello world  !\t\n");

    auto d5 = permutations("");

    auto d6 = sumStrings("0","0");

    valid_braces("[({})](]");

    std::array<std::int32_t, 10> in{5,2,15,93,4,65,1,47,11,31};

    return 0;
}

