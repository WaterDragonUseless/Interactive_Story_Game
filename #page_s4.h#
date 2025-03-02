#ifndef PAGE_H
#define PAGE_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class page {
 private:
  class choice {
   public:
    size_t des;
    std::string option;
    std::string equip_name;
    long int equip_value;
    bool mark;  //if mark == False, no equipment choice
    //if mark == True, equipment type choice
    choice(size_t x, std::string cho, long int t, string eq_na, bool m) :
        des(x), option(cho), equip_name(eq_na), equip_value(t), mark(m) {}
  };

  std::vector<choice> choices;
  size_t page_cur;
  char type;
  std::string file_txt;
  size_t marker_reference;
  //12.1
  std::vector<std::pair<long int, std::string> > equip;

 public:
  page() : page_cur(0), type('U') {}
  char getmychar() const;
  void set_cur_page(size_t x);
  void set_type(char x);
  void set_file_txt(std::string filename, std::string pathname);
  std::string getfile();
  void add_aChoice(size_t x, std::string choicei);
  void printChoices(vector<pair<string, long int> >);
  size_t sizeofmychoices();
  size_t getmydes(size_t i);
  void setDefaultMarker();
  void setMarker();
  size_t getMarker();

  //12.1
  friend class story;
  void add_equip(long int x, std::string text);
  void add_equipChoice(size_t x, std::string choi, long int t, string equip_name);
};

#endif
