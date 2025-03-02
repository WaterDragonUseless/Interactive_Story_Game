#include "page.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

char page::getmychar() const {
  return type;
}
void page::set_cur_page(size_t x) {
  page_cur = x;
}

void page::set_type(char x) {
  type = x;
}

void page::set_file_txt(std::string filename, std::string pathname) {
  //char * ss  = ;
  std::ifstream file((pathname + "/" + filename).c_str());
  std::string line;
  file_txt.clear();
  while (std::getline(file, line)) {
    if (!file) {
      std::cerr << "Error: Unable to open" << filename << std::endl;
      exit(EXIT_FAILURE);
    }
    file_txt += line + "\n";
  }
  file.close();
}

std::string page::getfile() {
  return file_txt;
}

void page::add_aChoice(size_t x, std::string choi) {
  //  choices.push_back(std::make_pair(x, choice));
  choices.push_back(choice(x, choi));
}
void page::printChoices() {
  // std::vector<std::pair<size_t, std::string> >::iterator it = choices.begin();
  std::vector<choice>::iterator it = choices.begin();
  if (getmychar() == 'L') {
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
  else if (getmychar() == 'W') {
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else if (getmychar() == 'N') {
    size_t i = 1;
    std::cout << "What would you like to do?" << std::endl;
    while (it != choices.end()) {
      std::cout << i << ". " << it->option << std::endl;
      ++it;
      i++;
    }
  }
  else {
    std::cerr << "type" << getmychar() << "is wrong" << std::endl;

    exit(EXIT_FAILURE);
  }
}

size_t page::sizeofmychoices() {
  return choices.size();
}

size_t page::getmydes(size_t i) {
  return choices[i].des;
}
//setdefult marker
void page::setDefaultMarker() {
  marker_reference = 0;
}

void page::setMarker() {
  marker_reference = 1;
}
size_t page::getMarker() {
  return marker_reference;
}
