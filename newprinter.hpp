// New Printers

#pragma once

#include "stdafx.h"
#include "first.hpp"

namespace mydetails
{
  std::unordered_map<std::string, std::string> Names =
  {
    {"array", "arr"},
    {"carray", "carr"},
    {"const_iterator", "citr"},
    {"const_pointer", "cptr"},
    {"iterator", "itr"},
    {"list", "lst"},
    {"map", "map"},
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

  class IPrinter
  {
  public:
    virtual void printName() = 0;
    virtual void printOpenBrace() = 0;
    virtual void printEndBrace() = 0;
    void printDelimiter()
    {
      cout << ",";
    }
  };

  class BoxBraces : public IPrinter
  {
  public:
    virtual void printName() = 0;
    virtual void printOpenBrace() final
    {
      cout << "[";
    }
    virtual void printEndBrace() final
    {
      cout << "]";
    }
  };

  class CurlyBraces : public IPrinter
  {
  public:
    virtual void printName() = 0;
    virtual void printOpenBrace() final
    {
      cout << "{";
    }
    virtual void printEndBrace() final
    {
      cout << "}";
    }
  };

  class ParaBraces : public IPrinter
  {
  public:
    virtual void printName() = 0;
    virtual void printOpenBrace() final
    {
      cout << "(";
    }
    virtual void printEndBrace() final
    {
      cout << ")";
    }
  };

  class AngleBraces : public IPrinter
  {
  public:
    virtual void printName() = 0;
    virtual void printOpenBrace() final
    {
      cout << "<";
    }
    virtual void printEndBrace() final
    {
      cout << ">";
    }
  };



}
