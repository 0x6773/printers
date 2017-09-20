// New Printers

#ifndef __PRINTERS_HPP
#define __PRINTERS_HPP

// Comment out below line to show address of pointer
// instead of value in it.
//#define SHOW_ADDR

#include <unordered_map>
#include <utility>
#include <string>

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
			{ "const_reverse_iterator", "critr" },
			{ "deque", "deq" },
			{ "forward_list", "flst" },
			{ "iterator", "itr" },
			{ "list", "lst" },
			{ "map", "map" },
			{ "multimap", "mmap" },
			{ "multiset", "mset" },
			{ "pair", "pr" },
			{ "pointer", "ptr" },
			{ "reverse_iterator", "ritr" },
			{ "set", "set" },
			{ "shared_ptr", "sp" },
			{ "tuple", "tp" },
			{ "unique_ptr", "up" },
			{ "unordered_map", "umap" },
			{ "unordered_multimap", "ummap" },
			{ "unordered_multiset", "umset" },
			{ "unordered_set", "uset" },
			{ "valarray", "valarr"},
			{ "vector", "vec" },
		};

		template<size_t N>
		struct TuplePrinter
		{
			template<typename... Types>
			static void print(std::ostream& out, const std::tuple<Types...>& ar)
			{
				TuplePrinter<N - 1>::print(out, ar);
				using TT = std::remove_const_t<std::remove_reference_t<decltype(std::get<N - 1>(ar))>>;
				if (std::is_same<std::string, TT>::value)
					out << "\"" << std::get<N - 1>(ar) << "\"" << delimiter;
				else
					out << std::get<N - 1>(ar) << delimiter;
			}
		};

		template<>
		struct TuplePrinter<0>
		{
			template<typename... Types>
			static void print(std::ostream&, const std::tuple<Types...>&) { }
		};

		class Printer
		{
		public:
			virtual ~Printer() { }
			virtual void printOpenBrace(std::ostream&) = 0;
			virtual void printEndBrace(std::ostream&) = 0;

			template<typename T>
			void printElementsCont(std::ostream&, const T&, std::string&&, int);

			template<typename T>
			void printElementsPtr(std::ostream&, const T&, std::string&&);

			template<typename... TArgs>
			void printElementsTup(std::ostream&, const std::tuple<TArgs...>&, std::string&&);
		};

		template<typename T>
		void Printer::printElementsCont(std::ostream& out, const T& ar, std::string&& _name, int N)
		{
			out << Names[_name];
			if (N > -1)
				out << N;
			printOpenBrace(out);
			for (const auto& x : ar)
			{
				using TT = typename std::remove_const_t<std::remove_reference_t<decltype(x)>>;
				if (std::is_same<std::string, TT>::value)
					out << "\"" << x << "\"" << delimiter;
				else
					out << x << delimiter;
			}
			if (N)
				for (size_t i = 0; i < delimiter.size(); ++i)
					out << '\b';
			printEndBrace(out);
			return;
		}

		template<typename T>
		void Printer::printElementsPtr(ostream& out, const T& ptr, std::string&& _name)
		{
			out << Names[_name];
			printOpenBrace(out);
			using TT = std::remove_const_t<std::remove_reference_t<decltype(*ptr)>>;
			if (std::is_same<std::string, TT>::value)
				out << "\"" << *ptr << "\"";
			else
				out << *ptr;
			printEndBrace(out);
			return;
		}

		template<typename... TArgs>
		void Printer::printElementsTup(std::ostream& out, const std::tuple<TArgs...>& tup, std::string&& _name)
		{
			constexpr size_t SZ = std::tuple_size<
				std::tuple<TArgs... >> ::value;
			out << Names[_name] << SZ;
			printOpenBrace(out);
			TuplePrinter<SZ>::print(out, tup);
			for (size_t i = 0; i < delimiter.size(); ++i)
				out << '\b';
			printEndBrace(out);
		}

		class BoxBraces : public Printer
		{
		public:
			virtual void printOpenBrace(std::ostream& out) override final { out << "["; }
			virtual void printEndBrace(std::ostream& out) override final { out << "]"; }
		};

		class CurlyBraces : public Printer
		{
		public:
			virtual void printOpenBrace(std::ostream& out) override final { out << "{"; }
			virtual void printEndBrace(std::ostream& out) override final { out << "}"; }
		};

		class ParaBraces : public Printer
		{
		public:
			virtual void printOpenBrace(std::ostream& out) override final { out << "("; }
			virtual void printEndBrace(std::ostream& out) override final { out << ")"; }
		};

		class AngleBraces : public Printer
		{
		public:
			virtual void printOpenBrace(std::ostream& out) override final { out << "<"; }
			virtual void printEndBrace(std::ostream& out) override final { out << ">"; }
		};
	}
	Helpers::BoxBraces    boxBraces;
	Helpers::CurlyBraces  curlyBraces;
	Helpers::ParaBraces   paraBraces;
	Helpers::AngleBraces  angleBraces;

	template<typename T1,
		typename T2> std::ostream&
		operator<<(std::ostream& out,
			const std::pair<T1, T2>& pr)
	{
		curlyBraces.printElementsTup(out, std::make_tuple(pr.first, pr.second), "pair");
		return out;
	}

	template<typename... Types> std::ostream&
		operator<<(std::ostream& out,
			const std::tuple<Types...>& tup)
	{
		curlyBraces.printElementsTup(out, tup, "tuple");
		return out;
	}

	// for std::vector<>
#if defined(_GLIBCXX_VECTOR) || defined(_LIBCPP_VECTOR) || defined(_VECTOR_)

	template<typename T, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::vector<T, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "vector", ar.size());
		return out;
	}

#endif

// for std::valarray<>
#if defined(_GLIBCXX_VALARRAY) || defined(_LIBCPP_VALARRAY) || defined(_VALARRAY_)

template<typename T> std::ostream&
	operator<<(std::ostream& out,
		const std::valarray<T>& ar)
{
	boxBraces.printElementsCont(out, ar, "valarray", ar.size());
	return out;
}

template<typename T, typename R = typename T::value_type>
	std::enable_if_t<std::is_convertible<T,
		std::valarray<R>>::value, std::ostream&>
			operator<<(std::ostream& out, const T& ar)
{
	out << std::valarray<R>(ar);
	return out;
}

#endif

	// for std::deque<>
#if defined(_GLIBCXX_DEQUE) || defined(_LIBCPP_DEQUE) || defined(_DEQUE_)

	template<typename T, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::deque<T, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "deque", ar.size());
		return out;
	}

#endif

	template<typename T, size_t N>
	std::enable_if_t<!(std::is_same<char, T>::value ||
		std::is_same<wchar_t, T>::value), std::ostream&>
		operator<<(std::ostream& out, const T(&ar)[N])
	{
		boxBraces.printElementsCont(out, ar, "carray", N);
		return out;
	}

	template<typename T>
	struct is_reverse_iterator : std::false_type { };

	template<typename T>
	struct is_reverse_iterator<std::reverse_iterator<T>> : std::true_type{};

	template<typename T,
		typename S = typename std::iterator_traits<T>::reference>
#ifdef SHOW_ADDR
		std::enable_if_t<!std::is_pointer<T>::value, std::ostream&>
#else
		std::enable_if_t<!(std::is_same<T, char const*>::value ||
			std::is_same<T, wchar_t const*>::value ||
			std::is_same<T, wchar_t*>::value ||
			std::is_same<T, char*>::value), std::ostream&>
		//std::ostream&
#endif
		operator<<(std::ostream& out, const T& it)
	{
		if (std::is_pointer<T>::value)
		{
			if (std::is_const<std::remove_reference_t<S>>::value)
				angleBraces.printElementsPtr(out, it, "const_pointer");
			else
				angleBraces.printElementsPtr(out, it, "pointer");
		}
		else
		{
			if (printers::is_reverse_iterator<T>::value)
			{
				if (std::is_const<std::remove_reference_t<S>>::value)
					angleBraces.printElementsPtr(out, it, "const_reverse_iterator");
				else
					angleBraces.printElementsPtr(out, it, "reverse_iterator");
			}
			else
			{
				if (std::is_const<std::remove_reference_t<S>>::value)
					angleBraces.printElementsPtr(out, it, "const_iterator");
				else
					angleBraces.printElementsPtr(out, it, "iterator");
			}
		}
		return out;
	}

	// for std::array<>
#if defined(_GLIBCXX_ARRAY) || defined(_LIBCPP_ARRAY) || defined(_ARRAY_)
	template<typename T, size_t N> std::ostream&
		operator<<(std::ostream& out,
			const std::array<T, N>& ar)
	{
		boxBraces.printElementsCont(out, ar, "array", N);
		return out;
	}
#endif

	// for std::list<>
#if defined(_GLIBCXX_LIST) || defined(_LIBCPP_LIST) || defined(_LIST_)
	template<typename T, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::list<T, _Alloc>& ar)
	{
		curlyBraces.printElementsCont(out, ar, "list", ar.size());
		return out;
	}
#endif

	// for std::forward_list<>
#if defined(_GLIBCXX_FORWARD_LIST) || defined(_LIBCPP_FORWARD_LIST) || defined(_FORWARD_LIST_)
	template<typename T, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::forward_list<T, _Alloc>& ar)
	{
		std::string _del = Helpers::delimiter;
		Helpers::delimiter = "->";
		curlyBraces.printElementsCont(out, ar, "forward_list", -1);
		Helpers::delimiter = _del;
		return out;
	}
#endif

	// for std::unordered_set<> & std::unordered_multiset<>
#if defined(_GLIBCXX_UNORDERED_SET) || defined(_LIBCPP_UNORDERED_SET) || defined(_UNORDERED_SET_)
	template<typename T, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::unordered_set<T, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "unordered_set", ar.size());
		return out;
	}

	template<typename T, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::unordered_multiset<T, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "unordered_multiset", ar.size());
		return out;
	}
#endif

	// for std::set<> & std::multiset<>
#if defined(_GLIBCXX_SET) || defined(_LIBCPP_SET) || defined(_SET_)
	template<typename T, typename _Pr,
		typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::set<T, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "set", ar.size());
		return out;
	}

	template<typename T, typename _Pr,
		typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::multiset<T, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "multiset", ar.size());
		return out;
	}
#endif

	// for std::map<> & std::multimap<>
#if defined(_GLIBCXX_MAP) || defined(_LIBCPP_MAP) || defined(_MAP_)
	template<typename T1, typename T2,
		typename _Pr, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::map<T1, T2, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "map", ar.size());
		return out;
	}

	template<typename T1, typename T2,
		typename _Pr, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::multimap<T1, T2, _Pr, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "multimap", ar.size());
		return out;
	}
#endif

	// for std::unordered_map<> & std::unordered_multimap<>
#if defined(_GLIBCXX_UNORDERED_MAP) || defined(_LIBCPP_UNORDERED_MAP) || defined(_UNORDERED_MAP_)
	template<typename T1, typename T2, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::unordered_map<T1, T2, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "unordered_map", ar.size());
		return out;
	}

	template<typename T1, typename T2, typename _Hasher,
		typename _Key, typename _Alloc> std::ostream&
		operator<<(std::ostream& out,
			const std::unordered_multimap<T1, T2, _Hasher, _Key, _Alloc>& ar)
	{
		boxBraces.printElementsCont(out, ar, "unordered_multimap", ar.size());
		return out;
	}
#endif

	// for std::shared_ptr<> and std::unique_ptr<>
#if defined(_GLIBCXX_MEMORY) || defined(_LIBCPP_MEMORY) || defined(_MEMORY_)
	template<typename T> std::ostream&
		operator<<(std::ostream& out,
			const std::shared_ptr<T>& sp)
	{
		angleBraces.printElementsPtr(out, sp, "shared_ptr");
		return out;
	}

	template<typename T> std::ostream&
		operator<<(std::ostream& out,
			const std::unique_ptr<T>& up)
	{
		angleBraces.printElementsPtr(out, up, "unique_ptr");
		return out;
	}
#endif
}

#endif // __PRINTERS_HPP
