#ifndef __STORY___
#define __STORY___

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "page.h"

class story {
 private:
  std::vector<page> pages;
  size_t total_page;

 public:
  story() : total_page(0) {}
  size_t getpagenum() const;
  void setpagenum(size_t x);

  void addPage(size_t page, char c, std::string filename, std::string path);
  page & getpage(size_t);
  void addChoices(size_t page_num, size_t destination_num, std::string str_choice);
  void test_choices();
  page & operator[](size_t index);
    void checkWinLose(void);
};
#endif
