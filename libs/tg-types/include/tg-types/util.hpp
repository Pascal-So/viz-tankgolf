#ifndef UTIL_HPP
#define UTIL_HPP

namespace tg {

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

} // namespace tg

#endif // UTIL_HPP