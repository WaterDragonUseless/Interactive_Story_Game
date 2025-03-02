#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

#include "page.h"
#include "story.h"
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
    char * ptr;
    if (pos_at != std::string::npos && pos_at_colon != std::string::npos) {
        std::string str_page_num = line.substr(0, pos_at);
        std::string str_type = line.substr(pos_at + 1, pos_at_colon - pos_at - 1);
        std::string str_file_name = line.substr(pos_at_colon + 1);
        size_t page_number = std::strtol(str_page_num.c_str(), &ptr, 10);
        // std::cout << path << std::endl;
        //give value to mystory
        check_pagenumber(str_page_num, mystory);
        check_type(str_type, line);
        mystory.setpagenum(page_number);
        mystory.addPage(page_number, str_type[0], str_file_name, path);
    }
    else if (pos_colon_2 != std::string::npos && pos_colon_1 != std::string::npos) {
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
        //  std::cout << page_num << ":" << destination_num << ":" << str_choice << std::endl;
    }
    else {
        cerr << line << "there is no such a format" << endl;
        exit(EXIT_FAILURE);
    }
}

void printStory(story mystory) {
  for (size_t i = 0; i <= mystory.getpagenum(); i++) {
    //print the background text only
    std::cout << "Page " << i << "\n==========\n"
              << (mystory.getpage(i)).getfile() << std::endl;
    //print choices, only should exist in step1
    mystory.getpage(i).printChoices();
  }
}

int isValidInput(string a, page mypage) {
  int valid = 1;
  char * ptr;

  size_t user_choice = std::strtol(a.c_str(), &ptr, 10);
  if (*ptr != '\0') {
    valid = 0;
  }
  size_t num_story_choices = mypage.sizeofmychoices();
  if (user_choice > num_story_choices || user_choice < 1) {
    valid = 0;
  }
  return valid;
}

int main(int argc, char ** argv) {
  /*** check input number***/
  if (argc != 2) {
    std::cerr << "Wrong input number." << std::endl;
    return EXIT_FAILURE;
  }

  /*** Implement_filname***/
  const std::string filename = argv[1];
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


  /*** Check pages correlation in story ***/

  for (size_t i = 0; i <= mystory.getpagenum(); i++) {
    for (size_t j = 0; j < mystory.getpage(i).sizeofmychoices(); j++) {
      size_t des_page = mystory.getpage(i).getmydes(j);
      mystory.getpage(des_page).setMarker();
    }
  }

  //    for (size_t i = 0; i < mystory.getpagenum(); i++) {
  //        cout<<mystory.getpage(i).getMarker()<<endl;
  //    }
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
        std::cerr << "Every page that is referenced by a choice is valid." << std::endl;
        EXIT_FAILURE;
      }
    }
    //3b
    if (i != 0 && mystory.getpage(i).getMarker() == 0) {
      std::cerr << "Every page (except page 0) is referenced by at least one *other*\n"
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

  /*** Interact with inputs ***/
  size_t i = 0;
  string user_choice;

  while (true) {
    //print the background text only
    cout << (mystory.getpage(i)).getfile() << endl;
    if (mystory.getpage(i).getmychar() == 'W') {
      mystory.getpage(i).printChoices();
      break;
    }
    else if (mystory.getpage(i).getmychar() == 'L') {
      mystory.getpage(i).printChoices();
      break;
    }
    else {
      mystory.getpage(i).printChoices();
      while (true) {
        int flag = 0;
        cin >> user_choice;

        if (!isValidInput(user_choice, mystory.getpage(i))) {
          //exit(EXIT_FAILURE);
          cout << "That is not a valid choice, please try again" << endl;
          flag = 1;
        }
        if (flag == 0) {
          break;
        }
      }
      char * ptr;
      size_t a = strtol(user_choice.c_str(), &ptr, 10);
      i = mystory.getpage(i).getmydes(a - 1);
    }
  }

  /*** Print_story ***/

  storyFile.close();
  return EXIT_SUCCESS;
}
