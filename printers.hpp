// New Printers

#ifndef __PRINTERS_HPP
#define __PRINTERS_HPP

// Comment out below line to show address of pointer
// instead of value in it.
#define SHOW_ADDR

#include <iostream>
#include <unordered_map>

namespace printers
{
	namespace Helpers
	{
		std::string delimiter = ", ";

		std::unordered_map<std::string, std::string> Names =
		{
			{ "array", "arr" },
			{ "carray", "carr" },
			{ "const_iterator", "citr" },
			{ "const_pointer", "cptr" },
			{ "forward_list", "flst" },
			{ "iterator", "itr" },
			{ "list", "lst" },
			{ "map", "map" },
			{ "multimap", "mmap" },
			{ "multiset", "mset" },
			{ "pair", "pr" },
			{ "pointer", "ptr" },
			{ "set", "set" },
			{ "shared_ptr", "sp" },
			{ "tuple", "tp" },
			{ "unique_ptr", "up" },
			{ "unordered_map", "umap" },
			{ "unordered_multimap", "ummap" },
			{ "unordered_multiset", "umset" },
			{ "unordered_set", "uset" },
			{ "vector", "vec" },
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
			void printElementsCont(const T& ar, std::string&& _name, int N)
			{
				std::cout << Names[_name];
				if (N > -1)
					std::cout << N;
				printOpenBrace();
				for (const auto& x : ar)
				{
					typedef typename std::remove_const_t<
						typename std::remove_reference_t<decltype(x) >> TT;
					if (std::is_same<std::string, TT>::value)
						std::cout << "\"" << x << "\"" << delimiter;
					else
						std::cout << x << delimiter;
				}
				if (N)
					for (size_t i = 0; i < delimiter.size(); ++i)
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
					typename std::remove_reference_t<decltype(*ptr) >> TT;
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
				for (size_t i = 0; i < delimiter.size(); ++i)
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
		operator<<(std::ostream& xx,
			const std::pair<T1, T2>& pr)
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

// for std::vector<>
#ifdef _GLIBCXX_VECTOR

	template<typename T, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::vector<T, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "vector", ar.size());
		return xx;
	}

#endif

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
#ifdef SHOW_ADDR
		std::enable_if_t<!std::is_pointer<T>::value, std::ostream&>
#else
		std::ostream&
#endif
	operator<<(std::ostream& xx, const T& it)
	{
		if (std::is_pointer<T>::value)
		{
			if (std::is_const<std::remove_reference_t<S>>::value)
				angleBraces.printElementsPtr(it, "const_pointer");
			else
				angleBraces.printElementsPtr(it, "pointer");
		}
		else
		{
			if (std::is_const<std::remove_reference_t<S>>::value)
				angleBraces.printElementsPtr(it, "const_iterator");
			else
				angleBraces.printElementsPtr(it, "iterator");
		}
		return xx;
	}

// for std::array<>
#ifdef _GLIBCXX_ARRAY
	template<typename T, size_t N> std::ostream&
		operator<<(std::ostream& xx,
			const std::array<T, N>& ar)
	{
		boxBraces.printElementsCont(ar, "array", N);
		return xx;
	}
#endif

// for std::list<>
#ifdef _GLIBCXX_LIST
	template<typename T, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::list<T, _Alloc>& ar)
	{
		curlyBraces.printElementsCont(ar, "list", ar.size());
		return xx;
	}
#endif

// for std::forward_list<>
#ifdef _GLIBCXX_FORWARD_LIST
	template<typename T, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::forward_list<T, _Alloc>& ar)
	{
		std::string _del = Helpers::delimiter;
		Helpers::delimiter = "->";
		curlyBraces.printElementsCont(ar, "forward_list", -1);
		Helpers::delimiter = _del;
		return xx;
	}
#endif

// for std::unordered_set<>
#ifdef _GLIBCXX_UNORDERED_SET
	template<typename T, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::unordered_set<T, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "unordered_set", ar.size());
		return xx;
	}
#endif

// for std::set<>
#ifdef _GLIBCXX_SET
	template<typename T, typename _Pr,
		typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::set<T, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "set", ar.size());
		return xx;
	}
#endif

// for std::unordered_multiset<>
#ifdef _GLIBCXX_UNORDERED_SET
	template<typename T, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::unordered_multiset<T, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "unordered_multiset", ar.size());
		return xx;
	}
#endif

// for std::multiset<>
#ifdef _GLIBCXX_SET
	template<typename T, typename _Pr,
		typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::multiset<T, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "multiset", ar.size());
		return xx;
	}
#endif

// for std::map<>
#ifdef _GLIBCXX_MAP
	template<typename T1, typename T2,
		typename _Pr, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::map<T1, T2, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "map", ar.size());
		return xx;
	}
#endif

// for std::unordered_map<>
#ifdef _GLIBCXX_UNORDERED_MAP
	template<typename T1, typename T2, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::unordered_map<T1, T2, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "unordered_map", ar.size());
		return xx;
	}
#endif

// for std::multimap<>
#ifdef _GLIBCXX_MAP
	template<typename T1, typename T2,
		typename _Pr, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::multimap<T1, T2, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "multimap", ar.size());
		return xx;
	}
#endif

// for std::unordered_multimap<>
#ifdef _GLIBCXX_UNORDERED_MAP
	template<typename T1, typename T2, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& xx,
			const std::unordered_multimap<T1, T2, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(ar, "unordered_multimap", ar.size());
		return xx;
	}
#endif

// for std::shared_ptr<> and std::unique_ptr<>
#ifdef _GLIBCXX_MEMORY
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
#endif

	template<typename T>
	void print_ptr(const T* ar, size_t N)
	{
		std::cout << "ptr[" << N << "][";
		for (size_t i = 0; i < N; ++i)
			std::cout << ar[i] << ", ";
		std::cout << "\b\b]" << std::endl;
	}
}

#endif // __PRINTERS_HPP
