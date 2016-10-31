// Binary_Search_Tree.cpp : Defines the entry point for the console application.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "binary_search_tree.h"

int main() {
   // 2014 Total Pay for some Foothill CS faculty from
   // http://transparentcalifornia.com/export/2014-community-colleges.csv
   // and
   // http://www.foothill.edu/cs/schedule.php?act=1&dept=C%20S

   std::vector<std::pair<int, std::string> > professors = {
      { 5089, "Rahul Agarwal" },
      { 15351, "Thomas Riordan" },
      { 20468, "Hadeel Ammari" },
      { 21617, "Viet Trinh" },
      { 36983, "Bita Mazloom" },
      { 38966, "David Harden" },
      { 46862, "Rula Khayrallah" },
      { 49732, "Jesse Cecil" },
      { 52952, "Anand Venkataraman" },
      { 97262, "Ladawn Meade" },
      { 130809, "Elaine Haight" },
      { 144740, "Michael Loceff" },
      { 180789, "William Murphy" },
   };
   BinarySearchTree<int, std::string> tree;

   std::random_shuffle(professors.begin(), professors.end());
   for (const auto& pay_name_pair : professors) {
      std::cout << "insert(" << pay_name_pair.first << ", "
         << pay_name_pair.second << ")" << std::endl;
      tree.insert(pay_name_pair.first, pay_name_pair.second);
   }
   std::cout << std::endl;

   for (const auto& pay_name_pair : professors) {
      const auto& key = pay_name_pair.first;
      auto value = tree.get(key);
      std::cout << "get(" << key << ") == " << value << std::endl;
   }
   return 0;
}