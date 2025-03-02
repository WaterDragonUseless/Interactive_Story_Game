#ifndef __STORY___
#define __STORY___

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "page_s4.h"

class story {
private:
    std::vector<page> pages;
    size_t total_page;
    //12.1
    vector<pair <string, long int> > cur_equip;

public:
    story() : total_page(0) {}
    size_t getpagenum() const;
    void setpagenum(size_t x);
    void addPage(size_t page, char c, std::string filename, std::string path);
    page & getpage(size_t);
    void addChoices(size_t page_num, size_t destination_num, std::string str_choice);
    void test_choices();
    page & operator[](size_t index);

    //12.1
    //update current_equip||Gain the equipment on the N th page
    void gainequip(size_t i);
    void interactUser(void);
    int isValidInput(string a, page mypage);
    void change_both_equip(size_t pagenum, long int value, string str_varname);
    long int find_equip (  vector<pair <string, long int> > cur_equip , string var_name);
    void checkWinLose(void);
};
#endif
