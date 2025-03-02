#include "story.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
size_t story::getpagenum() const {
  return total_page;
}

void story::setpagenum(size_t x) {
  total_page = x;
}

void story::addPage(size_t pagenum, char c, std::string filename, std::string path) {
  page newPage;
  newPage.set_cur_page(pagenum);
  newPage.set_type(c);
  newPage.set_file_txt(filename, path);
  newPage.setDefaultMarker();
  pages.push_back(newPage);
}

page & story::getpage(size_t x) {
  return pages[x];
}

void story::addChoices(size_t page_num, size_t destination_num, std::string str_choice) {
  pages[page_num].add_aChoice(destination_num, str_choice);
}

page & story::operator[](size_t index) {
  return pages[index];
}

void story::test_choices() {
  std::vector<page>::iterator it = pages.begin();
  while (it != pages.end()) {
    it->printChoices();
    ++it;
  }
}

void story::checkWinLose() {
    for(size_t i = 0; i < total_page; i++) {
        if(getpage(i).getmychar() == 'W' || getpage(i).getmychar() == 'L') {
            if(getpage(i).sizeofmychoices() != 0) {
                cerr << i << "size of page is not 0 when page type is Win or Lose" << endl;
            }
        }
    }
}