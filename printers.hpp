// Printers for Containers defined here

#pragma once

#include "stdafx.h"
#include "first.hpp"

namespace mydetails
{
  // Helper for std::tuple<> and std::pair<>
  template<size_t N> struct TuplePrinter
  {
    template<typename... Types>
    static void print(const std::tuple<Types...>& ar)
    {
      TuplePrinter<N-1>::print(ar);
      typedef typename std::remove_const<
	typename std::remove_reference<
	  decltype(std::get<N-1>(ar))>::type>::type TT;
      if(std::is_same<std::string,TT>::value)
	std::cout<<"\""<<std::get<N-1>(ar)<<"\",";
      else
	std::cout<<std::get<N-1>(ar)<<",";
    }
  };
  template<> struct TuplePrinter<0>
  {
    template<typename... Types>
    static void print(const std::tuple<Types...>&)
    {
      //Nothing here
    }
  };

  // printer for std::pair<T1,T2> : Checked
  template<typename T1,
	   typename T2> std::ostream&
  operator<<(std::ostream& xx, const std::pair<T1, T2>& pr)
  {
    constexpr size_t SZ = 2;
    std::cout<<"pr"<<SZ<<"(";
    TuplePrinter<SZ>::print(std::make_tuple(pr.first,pr.second));
    std::cout<<"\b)";
    return xx;
  }

  template<typename... Types> std::ostream&
  operator<<(std::ostream& xx,
	     const std::tuple<Types...>& ar)
  {
    constexpr size_t SZ = std::tuple_size<
      std::tuple<Types...>>::value;
    std::cout<<"tp"<<SZ<<"(";
    TuplePrinter<SZ>::print(ar);
    std::cout<<"\b)";
    return xx;
  }

  // printer for std::vector<T> : Checked
  template<typename T> std::ostream&
  operator<<(std::ostream& xx, const std::vector<T>& ar)
  {
    std::cout<<"vec"<<ar.size()<<"[";
    for(const auto& x : ar)
    {
      typedef typename std::remove_const<
	typename std::remove_reference<decltype(x)>::type>::type TT;
      if(std::is_same<std::string, TT>::value)
        std::cout<<"\""<<x<<"\",";
      else
        std::cout<<x<<",";
    }
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"]";
    return xx;
  }

    // printer for C-array
	template<typename T, size_t N>
		std::enable_if_t<!(std::is_same<char, T>::value ||
			std::is_same<wchar_t, T>::value), std::ostream&> operator<<(std::ostream& xx, const T(&ar)[N])
	{
		std::cout << "carr" << N << "[";
		for (const auto& x : ar)
		{
			typedef typename std::remove_const<
				typename std::remove_reference<decltype(x)>::type>::type TT;
			if (std::is_same<std::string, TT>::value)
				std::cout << "\"" << x << "\",";
			else
				std::cout << x << ",";
		}
		std::cout << "\b]";
		return xx;
	}
#ifdef INCLUDE_ALL

  // printer for std::array<T, N> : Checked
  template<typename T,
	   size_t N> std::ostream&
  operator<<(std::ostream& xx, const std::array<T,N>& ar)
  {
    std::cout<<"arr"<<N<<"[";
    for(const auto& x : ar)
    {
      typedef typename std::remove_const<
	typename std::remove_reference<decltype(x)>::type>::type TT;
      if(std::is_same<std::string, TT>::value)
        std::cout<<"\""<<x<<"\",";
      else
        std::cout<<x<<",";
    }
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"]";
    return xx;
  }

  // printer for std::list<T> : Checked
  template<typename T> std::ostream&
  operator<<(std::ostream& xx, const std::list<T>& ar)
  {
    std::cout<<"lst"<<ar.size()<<"[";
    for(const auto& x : ar)
    {
      typedef typename std::remove_const<
	typename std::remove_reference<decltype(x)>::type>::type TT;
      if(std::is_same<std::string, TT>::value)
        std::cout<<"\""<<x<<"\",";
      else
        std::cout<<x<<",";
    }
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"]";
    return xx;
  }

  // printer for std::unordered_set<T> : Checked
  template<typename T> std::ostream&
  operator<<(std::ostream& xx, const std::unordered_set<T>& ar)
  {
    std::cout<<"uset"<<ar.size()<<"{";
    for(const auto& x : ar)
    {
      typedef typename std::remove_const<
	typename std::remove_reference<decltype(x)>::type>::type TT;
      if(std::is_same<std::string, TT>::value)
        std::cout<<"\""<<x<<"\",";
      else
        std::cout<<x<<",";
    }
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"}";
    return xx;
  }

  // printer for std::set<T>
  template<typename T> std::ostream&
  operator<<(std::ostream& xx, const std::set<T>& ar)
  {
    std::cout<<"set"<<ar.size()<<"{";
    for(const auto& x : ar)
    {
      typedef typename std::remove_const<
	typename std::remove_reference<decltype(x)>::type>::type TT;
      if(std::is_same<std::string, TT>::value)
        std::cout<<"\""<<x<<"\",";
      else
        std::cout<<x<<",";
    }
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"}";
    return xx;
  }

  // printer for std::unordered_multiset<T>
  template<typename T> std::ostream&
  operator<<(std::ostream& xx,
	     const std::unordered_multiset<T>& ar)
  {
    std::cout<<"umset"<<ar.size()<<"{";
    for(const auto& x : ar)
    {
      typedef typename std::remove_const<
	     typename std::remove_reference<decltype(x)>::type>::type TT;
      if(std::is_same<std::string, TT>::value)
        std::cout<<"\""<<x<<"\",";
      else
        std::cout<<x<<",";
    }
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"}";
    return xx;
  }

  // printer for std::multiset<T>
  template<typename T> std::ostream&
  operator<<(std::ostream& xx, const std::multiset<T>& ar)
  {
    std::cout<<"mset"<<ar.size()<<"{";
    for(const auto& x : ar)
    {
      typedef typename std::remove_const<
	     typename std::remove_reference<decltype(x)>::type>::type TT;
      if(std::is_same<std::string, TT>::value)
        std::cout<<"\""<<x<<"\",";
      else
        std::cout<<x<<",";
    }
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"}";
    return xx;
  }

  // printer for std::map<T1, T2> : Checked
  template<typename T1, typename T2> std::ostream&
  operator<<(std::ostream& xx, const std::map<T1, T2>& ar)
  {
    std::cout<<"map"<<ar.size()<<"[";
    for(const auto& x : ar)
      std::cout<<x<<",";
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"]";
    return xx;
  }

  // printer for std::unordered_map<T1, T2>
  template<typename T1, typename T2> std::ostream&
  operator<<(std::ostream& xx, const std::unordered_map<T1, T2>& ar)
  {
    std::cout<<"umap"<<ar.size()<<"[";
    for(const auto& x : ar)
      std::cout<<x<<",";
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"]";
    return xx;
  }

  // printer for std::multimapmap<T1, T2>
  template<typename T1, typename T2> std::ostream&
  operator<<(std::ostream& xx, const std::multimap<T1, T2>& ar)
  {
    std::cout<<"mmap"<<ar.size()<<"[";
    for(const auto& x : ar)
      std::cout<<x<<",";
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"]";
    return xx;
  }

  // printer for std::unordered_multimap<T1, T2>
  template<typename T1, typename T2> std::ostream&
  operator<<(std::ostream& xx,
	     const std::unordered_multimap<T1, T2>& ar)
  {
    std::cout<<"ummap"<<ar.size()<<"[";
    for(const auto& x : ar)
      std::cout<<x<<",";
    if(ar.size() > 0 )
      std::cout<<"\b";
    std::cout<<"]";
    return xx;
  }

  // printer for std::shared_ptr<T>
  template<typename T> std::ostream&
  operator<<(std::ostream& xx,
	     const std::shared_ptr<T>& sp)
  {
    std::cout<<"sp["<<*sp<<"]";
    return xx;
  }

  // printer for std::unique_ptr<T>
  template<typename T> std::ostream&
  operator<<(std::ostream& xx,
	     const std::unique_ptr<T>& up)
  {
    std::cout<<"up["<<*up<<"]";
    return xx;
  }

#endif // INCLUDE_ALL

}
