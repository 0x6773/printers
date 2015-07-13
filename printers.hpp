// New Printers

#pragma once

#include <bits/stdc++.h>

namespace printers
{
  namespace Helpers
  {
    std::string delimiter = ", ";

    std::unordered_map<std::string, std::string> Names =
    {
      {"array", "arr"},
      {"carray", "carr"},
      {"const_iterator", "citr"},
      {"const_pointer", "cptr"},
      {"iterator", "itr"},
      {"list", "lst"},
      {"map", "map"},
      {"multimap", "mmap"},
      {"multiset", "mset"},
      {"pair", "pr"},
      {"pointer", "ptr"},
      {"set", "set"},
      {"shared_ptr", "sp"},
      {"tuple", "tp"},
      {"unique_ptr", "up"},
      {"unordered_map", "umap"},
      {"unordered_multimap", "ummap"},
      {"unordered_multiset", "umset"},
      {"unordered_set", "uset"},
      {"vector", "vec"},
    };

    template<size_t N>
    struct TuplePrinter
    {
    	template<typename... Types>
      static void print(const std::tuple<Types...>& ar)
      {
      	TuplePrinter<N - 1>::print(ar);
      	typedef typename std::remove_const<
      		typename std::remove_reference<
      		  decltype(std::get<N - 1>(ar))>::type>::type TT;
      	if (std::is_same<std::string, TT>::value)
      		std::cout << "\"" << std::get<N - 1>(ar) << "\"" << delimiter;
      	else
      		std::cout << std::get<N - 1>(ar) << delimiter;
      }
    };

    template<>
    struct TuplePrinter<0>
    {
    	template<typename... Types>
    	static void print(const std::tuple<Types...>&) { }
    };

    class Printer
    {
    public:
      virtual ~Printer() { }
      virtual void printOpenBrace() = 0;
      virtual void printEndBrace() = 0;

      template<typename T>
      void printElementsCont(const T& ar, std::string&& _name, size_t N)
      {
        std::cout << Names[_name] << N;
        printOpenBrace();
        for (const auto& x : ar)
    		{
    			typedef typename std::remove_const_t<
    				typename std::remove_reference_t<decltype(x)>> TT;
    			if (std::is_same<std::string, TT>::value)
    				std::cout << "\"" << x << "\"" << delimiter;
    			else
    				std::cout << x << delimiter;
    		}
        if(N)
          for(size_t i = 0; i < delimiter.size(); ++i)
            std::cout << '\b';
        printEndBrace();
        return;
      }

      template<typename T>
      void printElementsPtr(const T& ptr, std::string&& _name)
      {
        std::cout << Names[_name];
        printOpenBrace();
        typedef typename std::remove_const_t<
          typename std::remove_reference_t<decltype(*ptr)>> TT;
        if (std::is_same<std::string, TT>::value)
          std::cout << "\"" << *ptr << "\"";
        else
          std::cout << *ptr;
        printEndBrace();
        return;
      }

      template<typename... TArgs>
      void printElementsTup(const std::tuple<TArgs...>& tup, std::string&& _name)
      {
        constexpr size_t SZ = std::tuple_size<
    			std::tuple<TArgs... >> ::value;
        std::cout << Names[_name] << SZ;
    		printOpenBrace();
    		TuplePrinter<SZ>::print(tup);
        for(size_t i = 0; i < delimiter.size(); ++i)
    		  std::cout << '\b';
        printEndBrace();
      }
    };

    class BoxBraces : public Printer
    {
    public:
      virtual void printOpenBrace() final { std::cout << "["; }
      virtual void printEndBrace() final { std::cout << "]"; }
    };

    class CurlyBraces : public Printer
    {
    public:
      virtual void printOpenBrace() final { std::cout << "{"; }
      virtual void printEndBrace()  final { std::cout << "}"; }
    };

    class ParaBraces : public Printer
    {
    public:
      virtual void printOpenBrace() final { std::cout << "("; }
      virtual void printEndBrace()  final { std::cout << ")"; }
    };

    class AngleBraces : public Printer
    {
    public:
      virtual void printOpenBrace() final { std::cout << "<"; }
      virtual void printEndBrace()  final { std::cout << ">"; }
    };
  }
  Helpers::BoxBraces    boxBraces;
  Helpers::CurlyBraces  curlyBraces;
  Helpers::ParaBraces   paraBraces;
  Helpers::AngleBraces  angleBraces;

  template<typename T1,
		typename T2> std::ostream&
		operator<<(std::ostream& xx, const std::pair<T1, T2>& pr)
	{
    curlyBraces.printElementsTup(std::make_tuple(pr.first, pr.second), "pair");
		return xx;
	}

  template<typename... Types> std::ostream&
		operator<<(std::ostream& xx,
			const std::tuple<Types...>& tup)
	{
		curlyBraces.printElementsTup(tup, "tuple");
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx, const std::vector<T>& ar)
	{
    boxBraces.printElementsCont(ar, "vector", ar.size());
		return xx;
	}

  template<typename T, size_t N>
	std::enable_if_t<!(std::is_same<char, T>::value ||
		std::is_same<wchar_t, T>::value), std::ostream&>
		operator<<(std::ostream& xx, const T(&ar)[N])
	{
    boxBraces.printElementsCont(ar, "carray", N);
    return xx;
	}

  template<typename T,
    typename S = typename std::iterator_traits<T>::reference>
    std::ostream& operator<<(std::ostream& xx, const T& it)
  {
    if(std::is_pointer<T>::value)
    {
      if(std::is_const<std::remove_reference_t<S>>::value)
        angleBraces.printElementsPtr(it, "const_pointer");
      else
        angleBraces.printElementsPtr(it, "pointer");
    }
    else
    {
      if(std::is_const<std::remove_reference_t<S>>::value)
        angleBraces.printElementsPtr(it, "const_iterator");
      else
        angleBraces.printElementsPtr(it, "iterator");
    }
    return xx;
  }

  template<typename T, size_t N> std::ostream&
		operator<<(std::ostream& xx, const std::array<T, N>& ar)
	{
    boxBraces.printElementsCont(ar, "array", N);
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx, const std::list<T>& ar)
	{
    curlyBraces.printElementsCont(ar, "list", ar.size());
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx, const std::unordered_set<T>& ar)
	{
    boxBraces.printElementsCont(ar, "unordered_set", ar.size());
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx, const std::set<T>& ar)
	{
    boxBraces.printElementsCont(ar, "set", ar.size());
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx, const std::unordered_multiset<T>& ar)
	{
    boxBraces.printElementsCont(ar, "unordered_multiset", ar.size());
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx, const std::multiset<T>& ar)
	{
    boxBraces.printElementsCont(ar, "multiset", ar.size());
		return xx;
	}

  template<typename T1, typename T2> std::ostream&
		operator<<(std::ostream& xx, const std::map<T1, T2>& ar)
	{
    boxBraces.printElementsCont(ar, "map", ar.size());
		return xx;
	}

  template<typename T1, typename T2> std::ostream&
		operator<<(std::ostream& xx, const std::unordered_map<T1, T2>& ar)
	{
    boxBraces.printElementsCont(ar, "unordered_map", ar.size());
		return xx;
	}

  template<typename T1, typename T2> std::ostream&
		operator<<(std::ostream& xx, const std::multimap<T1, T2>& ar)
	{
    boxBraces.printElementsCont(ar, "multimap", ar.size());
		return xx;
	}

  template<typename T1, typename T2> std::ostream&
		operator<<(std::ostream& xx, const std::unordered_multimap<T1, T2>& ar)
	{
    boxBraces.printElementsCont(ar, "unordered_multimap", ar.size());
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx,
			const std::shared_ptr<T>& sp)
	{
    angleBraces.printElementsPtr(sp, "shared_ptr");
		return xx;
	}

  template<typename T> std::ostream&
		operator<<(std::ostream& xx,
			const std::unique_ptr<T>& up)
	{
    angleBraces.printElementsPtr(up, "unique_ptr");
		return xx;
	}
}
