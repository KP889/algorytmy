#include "compression.hpp"
std::vector<std::pair<uint8_t, uint8_t>>
compressGrayscale(std::array<std::array<uint8_t, width>, height> &A) {

  std::vector<std::pair<uint8_t, uint8_t>> V; //(A.size());
  V.reserve(A.size());

  std::transform(A.begin(), A.end(), A.begin(), [&V](auto element) mutable {
    auto lenghtE = std::distance(element.begin(), element.end());
    auto pos = 1;
    std::transform(element.begin(), element.end(), element.begin(),
                   [index = 0, prevVar = *element.begin(), &V, &lenghtE,
                    &pos](uint8_t e) mutable {
                     if (e == prevVar) {
                       index++;
                       if (pos == lenghtE) {
                         V.push_back(std::make_pair(prevVar, index));
                       }
                     } else {
                       V.push_back(std::make_pair(prevVar, index));
                       prevVar = e;
                       index = 1;
                     }
                     pos++;
                     return e;
                   });

    return element;
  });

  V.shrink_to_fit();

  return V;
};
std::array<std::array<uint8_t, width>, height>
decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>> &V) {
  std::array<std::array<uint8_t, width>, height> A;
  auto it = A.begin()->begin();
  std::transform(V.begin(), V.end(), V.begin(),
                 [&A, &it](std::pair<uint8_t, uint8_t> element) {
                   std::fill_n(it, element.second, element.first);
                   std::advance(it, element.second);
                   return element;
                 });

  return A;
}; /*
 void printMap(std::array<std::array<uint8_t, width>, height> &A) {
   int index = 0;
   std::transform(A.begin()->begin(), A.end()->end(), A.begin()->begin(),
                  [&index](auto element) mutable {
                    //if (element != '\0') {
                     std::copy()
       std::cout << element;
                    //};
                    index++;
                    if (index == width) {
       std::cout << "\n";
       index = 0;
                    }
                    return element;
                  });
 };
 */
/*
void printMap(std::array<std::array<uint8_t, width>, height> &A) {

  std::transform(A.begin(), A.end(), A.begin(), [](auto element) mutable {
    auto index = 0;
    index = std::count_if(element.begin(), element.end(),
                          [](char c) { return c == char(0); });

    // if (index != std::distance(element.begin(), element.end())) {
    std::copy_if(std::find_if(element.begin(), element.end(),
                              [](auto element) { return element > char(33); }),
                 element.end(),
                 std::ostream_iterator<char>(std::cout << std::setw(16), ""),
                 [](char c) {
                   if (c < char(33)) {
                     std::cout << char(0xFFFD);
                   } else if (c > char(126)) {
                     std::cout << char(0xFFFD);
                   }
                   return (c > char(32) && c < char(126));
                 });

    //});
    std::cout << "\n";
    //};//if

    return element;
  });
};
*/
void printMap(std::array<std::array<uint8_t, width>, height> &A) {

  std::transform(A.begin(), A.end(), A.begin(), [](auto element) mutable {
    auto it1 = std::find_if(element.begin(), (element.begin() + (width / 2)),
                            [](auto e) { return e > char(31); });

    auto it2 = element.begin() +
               (width - std::distance(
                            element.rbegin(),
                            std::find_if(element.rbegin(), element.rend(),
                                         [](auto e) { return e > char(31); })));

    std::fill_n(std::ostream_iterator<char>(std::cout, " "),
                (std::distance(element.begin(), it1)), char(31));
    std::copy_if(it1, it2, std::ostream_iterator<char>(std::cout, ""),
                 [](unsigned char c) {
                   if (c < char(0x20) ) {
                     std::cout << char(0x20);
                     return false;
                   } 
                   else {
                     return true;
                   }
                 });

    std::cout << "\n";

    return element;
  });
};
