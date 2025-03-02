#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

#include "page_s4.h"
#include "story_s4.h"
using namespace std;
void check_pagenumber(string str_page_num, story & mystory1) {
  int flag = 0;
  char * ptr;
  size_t page_number = std::strtol(str_page_num.c_str(), &ptr, 10);
  if (page_number == 0) {
    if (mystory1.getpagenum() == page_number && *ptr == '\0') {
      flag = 1;
    }
  }
  else {
    if (mystory1.getpagenum() + 1 == page_number && *ptr == '\0') {
      flag = 1;
    }
  }
  if (flag == 0) {
    cerr << str_page_num << "has wrong format" << endl;
    exit(EXIT_FAILURE);
  }
}

void check_dolar_pagenumber(string str_page_num,
                            string line,
                            story & mystory1,
                            string str_value) {
  int flag = 0;
  char * ptr1;
  char * ptr2;

  size_t page_number = std::strtol(str_page_num.c_str(), &ptr1, 10);
  size_t value_number = std::strtol(str_value.c_str(), &ptr2, 10);
  if (mystory1.getpagenum() >= page_number && *ptr1 == '\0' && *ptr2 == '\0' &&
      page_number >= 0) {
    flag = value_number + flag - value_number;
    flag = 1;
  }

  if (flag == 0) {
    cerr << str_page_num << line << endl;
    exit(EXIT_FAILURE);
  }
}

void check_type(string str_type, string line) {
  if (str_type != "N" || str_type != "L" || str_type != "N") {
    return;
  }
  cerr << line << "is not N or L or W" << endl;
  exit(EXIT_FAILURE);
}

void analyze(story & mystory, std::string line, std::string path) {
  size_t pos_at = line.find("@");
  size_t pos_at_colon = line.find(":");
  size_t pos_colon_1 = line.find(":");
  size_t pos_colon_2 = line.find(":", pos_colon_1 + 1);
  //12.1
  size_t pos_dolar = line.find("$");
  size_t pos_equal = line.find("=");
  size_t pos_l_bra = line.find("[");
  size_t pos_r_bra = line.find("]");
  char * ptr;
  if (pos_at != std::string::npos && pos_at_colon != std::string::npos) {
    std::string str_page_num = line.substr(0, pos_at);
    std::string str_type = line.substr(pos_at + 1, pos_at_colon - pos_at - 1);
    std::string str_file_name = line.substr(pos_at_colon + 1);
    size_t page_number = std::strtol(str_page_num.c_str(), &ptr, 10);
    //check format
    check_pagenumber(str_page_num, mystory);
    check_type(str_type, line);
    mystory.setpagenum(page_number);
    mystory.addPage(page_number, str_type[0], str_file_name, path);
  }
  else if (pos_colon_2 != std::string::npos && pos_colon_1 != std::string::npos &&
           pos_l_bra == string::npos && pos_r_bra == string::npos) {
    std::string str_page_num = line.substr(0, pos_colon_1);
    std::string str_destination_num =
        line.substr(pos_colon_1 + 1, pos_colon_2 - pos_colon_1 - 1);
    std::string str_choice = line.substr(pos_colon_2 + 1);
    size_t page_num = std::strtol(str_page_num.c_str(), &ptr, 10);
    char * ptr2;
    size_t destination_num = std::strtol(str_destination_num.c_str(), &ptr2, 10);
    if (*ptr2 != '\0' || *ptr != '\0') {
      cerr << line << "not valid pagenumber / destination number" << endl;
      exit(EXIT_FAILURE);
    }

    mystory.addChoices(page_num, destination_num, str_choice);
  }
  //12.1
  else if (pos_l_bra != string::npos && pos_r_bra != string::npos) {
    //get page num
    string str_page_num = line.substr(0, pos_l_bra);
    //get var, value
    string str_varname = line.substr(pos_l_bra + 1, pos_equal - pos_l_bra - 1);
    string str_value = line.substr(pos_equal + 1, pos_r_bra - pos_equal - 1);
    //get dest
    string str_destination_num =
        line.substr(pos_colon_1 + 1, pos_colon_2 - pos_colon_1 - 1);
    //get text
    string str_choice = line.substr(pos_colon_2 + 1);
    //convert str to nums
    char * ptr;
    size_t destination_num = std::strtol(str_destination_num.c_str(), &ptr, 10);
    size_t page_num = std::strtol(str_page_num.c_str(), &ptr, 10);
    long int value = strtol(str_value.c_str(), &ptr, 10);
    mystory.getpage(page_num).add_equipChoice(
        destination_num, str_choice, value, str_varname);
  }
  else if (pos_dolar != string::npos && pos_equal != string::npos) {
    string str_page_num = line.substr(0, pos_dolar);
    string str_varname = line.substr(pos_dolar + 1, pos_equal - pos_dolar - 1);
    string str_value = line.substr(pos_equal + 1);
    char * ptr2;
    size_t page_num = strtol(str_page_num.c_str(), &ptr, 10);
    long int value = strtol(str_value.c_str(), &ptr2, 10);

    check_dolar_pagenumber(str_page_num, line, mystory, str_value);
    //store valname = value into my story
    mystory.change_both_equip(page_num, value, str_varname);
  }
  else {
    cerr << line << "there is no such a format" << endl;
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  /*** check input number***/
  if (argc != 2) {
    std::cerr << "Wrong input number." << std::endl;
    return EXIT_FAILURE;
  }

  /*** Implement_filname***/
  const std::string filename = argv[1];
  //    const std::string filename = "story3";
  //  std::cout << filename << std::endl;

  /*** Open_file***/
  std::ifstream file(filename.c_str());
  std::ifstream storyFile((filename + "/story.txt").c_str());

  if (!storyFile) {
    std::cerr << "Error: Unable to open story.txt\n";
    return EXIT_FAILURE;
  }

  story mystory;

  /*** Analyze_line ***/

  std::string line;

  while (std::getline(storyFile, line)) {
    if (line.empty()) {
      // Skip empty lines
      continue;
    }
    analyze(mystory, line, filename);
  }

  mystory.checkWinLose();

  /*** Check pages correlation in story ***/

  for (size_t i = 0; i <= mystory.getpagenum(); i++) {
    for (size_t j = 0; j < mystory.getpage(i).sizeofmychoices(); j++) {
      size_t des_page = mystory.getpage(i).getmydes(j);
      mystory.getpage(des_page).setMarker();
    }
  }

  bool isWin = false;
  bool isLose = false;

  //des must be less than total num_page, greater or equal to 0
  size_t totalPage = mystory.getpagenum();
  for (size_t i = 0; i <= totalPage; i++) {
    size_t b = mystory.getpage(i).sizeofmychoices();
    for (size_t j = 0; j < b; j++) {
      size_t des_page = mystory.getpage(i).getmydes(j);
      //3a
      if (des_page > totalPage || des_page < 0) {
        std::cerr << "1Every page that is referenced by a choice is valid." << std::endl;
        EXIT_FAILURE;
      }
    }
    //3b
    if (i != 0 && mystory.getpage(i).getMarker() == 0) {
      std::cerr << "2Every page (except page 0) is referenced by at least one *other*\n"
                   "        page's choices."
                << std::endl;
      EXIT_FAILURE;
    }
    //3c
    if (mystory.getpage(i).getmychar() == 'L') {
      isLose = true;
    }
    if (mystory.getpage(i).getmychar() == 'W') {
      isWin = true;
    }
  }
  if (isWin == false || isLose == false) {
    std::cerr << "At least Win or Lose" << std::endl;
    EXIT_FAILURE;
  }

  mystory.interactUser();

  storyFile.close();
  return EXIT_SUCCESS;
}
