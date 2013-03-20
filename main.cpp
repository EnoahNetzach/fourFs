/*
 * main.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: Enoah Netzach
 */

#include <climits>
#include <iostream>
#include <string>
#include <unistd.h>

char m[10000],
     * n[99],
     * r = m,
     * p = m + 5000,
     ** s = n,
     d,
     c;

int main()
{
   std::string quine = "+[-<+]-ÿ<<<<<<<[.>]";
   std::string result = "";

   unsigned i = 0;
   for (read(0, r, 5000); c = * r; r++)
   {
      c - ']' || ((d > 1 || (r = * p ? * s : (--s, r)), ! d || d--), i++),
      c - '[' || d++ || (* ++s = r),
      d || ( * p += c == '+',
            * p -= c == '-',
            p += c == '>',
            p -= c == '<',
            c - '.' || write(1, p, 1),
            c - ',' || read(0, p, 1));

      //std::cout << "\t" << c << " : " << p << "\t\t- " << i << std::endl;
   };

   std::cout << std::endl;

   return 0;
}

