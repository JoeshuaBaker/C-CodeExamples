#include <iostream>
const int SIZE = 1000;
int tape[SIZE] = {0};
int *dp = tape;

void *__gxx_personality_v0;

int main() {
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   while (*dp) {
      --*dp;
      ++dp;
      ++*dp;
      ++dp;
      ++*dp;
      --dp;
      --dp;
      }
   ++dp;
   ++dp;
   --*dp;
   while (*dp) {
      --*dp;
      --dp;
      --dp;
      ++*dp;
      ++dp;
      ++dp;
      }
   --dp;
   --dp;
   while (*dp) {
      ++dp;
      while (*dp) {
         --*dp;
         --dp;
         while (*dp) {
            --*dp;
            ++dp;
            ++dp;
            ++*dp;
            ++dp;
            ++*dp;
            --dp;
            --dp;
            --dp;
            }
         ++dp;
         ++dp;
         ++dp;
         while (*dp) {
            --*dp;
            --dp;
            --dp;
            --dp;
            ++*dp;
            ++dp;
            ++dp;
            ++dp;
            }
         --dp;
         --dp;
         }
      ++dp;
      while (*dp) {
         --*dp;
         --dp;
         ++*dp;
         ++dp;
         }
      --dp;
      --dp;
      --*dp;
      }
   ++dp;
   while (*dp) {
      --*dp;
      --dp;
      ++*dp;
      ++dp;
      }
   --dp;
   std::cout << *dp;
   ++dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   ++*dp;
   std::cout << ((char) *dp);

}