#ifndef PAGE_H
#define PAGE_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
class page {
  /* private:
  size_t page_cur;
  std::vector<std::pair<size_t, std::string> > choices;
  char type;
  std::string file_txt;
  */
 private:
  class choice {
   public:
    size_t des;
    std::string option;
    choice(size_t x, std::string cho) : des(x), option(cho) {}
  };

  std::vector<choice> choices;
  size_t page_cur;
  char type;
  std::string file_txt;
  size_t marker_reference;

 public:
  page() : page_cur(0), type('U') {}
  char getmychar() const;
  void set_cur_page(size_t x);
  void set_type(char x);
  void set_file_txt(std::string filename, std::string pathname);
  std::string getfile();
  void add_aChoice(size_t x, std::string choicei);
  void printChoices();
  size_t sizeofmychoices();
  size_t getmydes(size_t i);
  void setDefaultMarker();
  void setMarker();
  size_t getMarker();
};

#endif
