#include "story_s4.h"

#include <cstdlib>
#include <iostream>
#include <string>

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
  //new added
  newPage.setDefaultMarker();

  newPage.set_file_txt(filename, path);
  pages.push_back(newPage);
}

page & story::getpage(size_t x) {
  return pages[x];
}

page & story::operator[](size_t index) {
  return pages[index];
}

//12.1
void story::gainequip(size_t i) {
}

void story::addChoices(size_t page_num, size_t destination_num, std::string str_choice) {
  pages[page_num].add_aChoice(destination_num, str_choice);
}

void story::change_both_equip(size_t pagenum, long int value, string str_varname) {
  bool flag = true;
  getpage(pagenum).add_equip(value, str_varname);
  for (size_t i = 0; i < cur_equip.size(); i++) {
    if (str_varname == cur_equip[i].first) {
      flag = false;
      break;
    }
  }
  if (flag == true) {
    cur_equip.push_back(make_pair(str_varname, 0));
  }
}

void story::interactUser() {
  /*** Interact with inputs ***/
  size_t i = 0;
  size_t a;
  char * ptr;
  string user_choice;

  while (true) {
    //update equip
    vector<pair<long int, string> >::iterator it = getpage(i).equip.begin();
    while (it != getpage(i).equip.end()) {
      vector<pair<string, long int> >::iterator it2 = cur_equip.begin();
      while (it2 != cur_equip.end()) {
        if (it2->first == it->second) {  //if the string name is same
          it2->second = it->first;       //update the value in the cur_equip
          break;
        }
        ++it2;
      }
      ++it;
    }

    //print the background text only
    cout << (getpage(i)).getfile() << endl;
    if (getpage(i).getmychar() == 'W') {
      getpage(i).printChoices(cur_equip);
      break;
    }
    else if (getpage(i).getmychar() == 'L') {
      getpage(i).printChoices(cur_equip);
      break;
    }
    else {
      getpage(i).printChoices(cur_equip);
      while (true) {
        int flag = 0;
        cin >> user_choice;

        if (!isValidInput(user_choice, getpage(i))) {
          //exit(EXIT_FAILURE);
          cout << "That is not a valid choice, please try again" << endl;
          flag = 1;
        }
        else {
          size_t n_choice = strtol(user_choice.c_str(), &ptr, 10);
          long int t = find_equip(cur_equip, getpage(i).choices[n_choice - 1].equip_name);
          long int y = getpage(i).choices[n_choice - 1].equip_value;
          if (t != y && getpage(i).choices[n_choice - 1].mark == true) {
            cout << "That choice is not available at this time, please try again" << endl;
            flag = 1;
          }
          if (flag == 0) {
            break;
          }
        }

        //                if (getpage(i).choice[i].mark == false && flag == 0) {
        //                    break;
        //                }
      }
      a = strtol(user_choice.c_str(), &ptr, 10);
      i = getpage(i).getmydes(a - 1);
    }
  }
}

int story::isValidInput(string a, page mypage) {
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

long int story::find_equip(vector<pair<string, long int> > cur_equip, string var_name) {
  for (size_t i = 0; i < cur_equip.size(); i++) {
    if (cur_equip[i].first == var_name) {
      return cur_equip[i].second;
    }
  }
  return 0;
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
