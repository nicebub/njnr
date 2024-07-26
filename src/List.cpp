#include <config.h>
#include <memory>
#include <string>

#include "debug.hpp"
#include "List.hpp"
#include "ListNode.hpp"
#include "type.hpp"
#include "compiler.hpp"
using njnr::BasicListNode;
using njnr::ListNode;
using njnr::ReturnPacketListNode;
using njnr::PListNode;
using njnr::TranslationUnitListNode;

   List::List() : list(3,nullptr) {}

   List::List(const List& cp) : list{cp.list} {}

   List::~List()
   {
       report(njnr::logType::debug, "running List() Destructor on List(): " + std::to_string((long)this));
       report(njnr::logType::debug, this->toString());

       list.clear();
   }

   std::vector<std::shared_ptr<BasicListNode>>::iterator List::begin()
   {
       return list.begin();
   }

   std::vector<std::shared_ptr<BasicListNode>>::iterator List::end()
   {
       return list.end();
   }

   int List::size() const
   {
       return static_cast<int>(list.size());
   }
/*
   List& List::operator=(const List& in)
   {
      List* xx= const_cast<List*>(&in);
      if(&in != this)
      {
         this->list.clear();
         for(std::vector<std::shared_ptr<BasicListNode>>::iterator x = xx->begin();x != xx->end();x++)
         {
            this->list.push_back(*x);
         }
      }
      return *this;
   }
*/
   void List::push_back(std::shared_ptr<BasicListNode> in)
   {
       list.push_back(in);
   }

   std::shared_ptr<List> List::mklist(njnr::type inType)
   {
      std::shared_ptr<List> spL {nullptr};
      spL = std::make_shared<List>();
      spL->appendList(inType);
      return spL;
   }

   std::shared_ptr<List> List::mklist(std::string inVal)
   {

      std::shared_ptr<List> spL {nullptr};
      spL = std::make_shared<List>();
      spL->appendList(inVal);
      return spL;
   }

   std::shared_ptr<List> List::mklist(std::string inVal, type inType)
   {
      std::shared_ptr<List> spL {nullptr};
      spL = std::make_shared<List>();
      spL->appendList(inType);
      return spL;
   }

   std::shared_ptr<List> List::mklist(std::shared_ptr<ReturnPacket> inExpr)
   {
      std::shared_ptr<List> spL {nullptr};
      spL = std::make_shared<List>();
      spL->appendList(inExpr);
      return spL;
   }

   std::shared_ptr<List> List::mklist(std::shared_ptr<Statement> instmt)
   {
      std::shared_ptr<List> spL {nullptr};
      spL = std::make_shared<List>();
      spL->appendList(instmt);
      return spL;
   }

   std::shared_ptr<List> List::mklist(std::shared_ptr<Identifier> i)
   {
      std::shared_ptr<List> spL {nullptr};
      spL = std::make_shared<List>();
      spL->appendList(i);
      return spL;
   }

   std::shared_ptr<List> List::mklist(std::shared_ptr<Constant> c)
   {
      std::shared_ptr<List> spL {nullptr};
      spL = std::make_shared<List>();
      spL->appendList(c);
      return spL;
   }

   bool List::appendList(std::shared_ptr<Identifier> inVal)
   {
       std::shared_ptr<ReturnPacketListNode> nnode = std::make_shared<ReturnPacketListNode>(inVal);
       this->push_back(nnode);
       return true;
   }

   bool List::appendList(std::shared_ptr<Constant> inVal)
   {
       std::shared_ptr<ReturnPacketListNode> nnode = std::make_shared<ReturnPacketListNode>(inVal);
       this->push_back(nnode);
       return true;
   }

   bool List::appendList(std::string inVal)
   {
      std::shared_ptr<ListNode> nnode = std::make_shared<ListNode>(inVal);
      this->push_back(nnode);
      return true;
   }

   bool List::appendList(std::string inVal, type inType)
   {
       std::shared_ptr<PListNode> nnode = std::make_shared<PListNode>(inVal, inType);
       this->push_back(nnode);
       return true;
   }

   bool List::appendList(std::shared_ptr<ReturnPacket> inexpr)
   {
       std::shared_ptr<ReturnPacketListNode> nnode = std::make_shared<ReturnPacketListNode>(inexpr);
       this->push_back(nnode);
       return true;
   }

   bool List::appendList(njnr::type intype)
   {
       std::shared_ptr<TypeListNode> nnode = std::make_shared<TypeListNode>(intype);
       this->push_back(nnode);
       return true;
   }

   bool List::appendList(std::shared_ptr<Statement> instmt)
   {
       std::shared_ptr<StmtListNode> nnode = std::make_shared<StmtListNode>(instmt);
       this->push_back(nnode);
       return true;
   }

   std::vector<std::shared_ptr<BasicListNode>> List::getlist()
   {
       return list;
   }

   std::shared_ptr<List> List::mklist(std::shared_ptr<Funcb> expr)
   {
      std::shared_ptr<List> spl = std::make_shared<List>();
      spl->appendList(expr);
       return spl;
   }

   std::shared_ptr<List> List::mklist(std::shared_ptr<Varb> expr)
   {
      std::shared_ptr<List> spl = std::make_shared<List>();
      spl->appendList(expr);
       return spl;
   }  // place holder type -- needs changing

   bool List::appendList(std::shared_ptr<Funcb> expr)
   {
       std::shared_ptr<TranslationUnitListNode> nnode = std::make_shared<TranslationUnitListNode>(expr);
       this->push_back(nnode);
       return true;
   }

   bool List::appendList(std::shared_ptr<Varb> expr)
   {
       std::shared_ptr<TranslationUnitListNode> nnode = std::make_shared<TranslationUnitListNode>(expr);
       this->push_back(nnode);
       return true;
   }  // placeholder type -- needs changing

    const std::string List::toString() const
    {
       std::string r{"List: "};
       if (0 < list.size())
       {
          for (auto e : list)
          {
             if (e)
             {
                switch (e->get_nodeType())
                {
                  case njnr::eNodeType::EXPR:
                  case njnr::eNodeType::P:
                  case njnr::eNodeType::STANDARD:
                  case njnr::eNodeType::STMT:
                  case njnr::eNodeType::TRANSLATION_UNIT:
                  case njnr::eNodeType::TYPE:
                     r += e->toString();
                     break;
                  default:
                     // set as default "Invalid"
                     break;
                }
             }
          }
       }
       return r;
    }