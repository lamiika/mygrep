#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void first_functionality();
void second_functionality(char *argv[]);

int search(string *search_ptr, string *input_ptr);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    first_functionality();
  } else {
    second_functionality(argv);
  }

  return 0;
}

int search(string *search_ptr, string *input_ptr) {
  string search_string = *search_ptr;
  string input_string = *input_ptr;
  int position = -1;

  for (size_t i = 0; i < input_string.length(); i++) {
    for (size_t j = 0; j < search_string.length(); j++) {
      if (i+j+1 > input_string.length()) {
        return -1;
      }
      char a_char = input_string[i+j];
      char b_char = search_string[j];
      if (a_char != b_char) {
        position = -1;
        break;
      }
      if (position == -1) {
        position = (int) i;
      }
      if (j == search_string.length() - 1) {
        return position;
      }
    }
  }
  return position;
}

void first_functionality() {
  string input_string;
  string search_string;
  string *input_ptr = &input_string;
  string *search_ptr = &search_string;

  cout << "Give a string from which to search for: ";
  getline(cin, input_string);
//  input_string = "Erkki Hietalahti";
  cout << "Give a search string: ";
  getline(cin, search_string);
//  search_string = "ti";

  int result = search(search_ptr, input_ptr);

  if (result == -1) {
    cout << search_string << " NOT found in \"" << input_string << "\"\n";
  } else {
    cout << "\"" << search_string << "\" found in \"" << input_string << "\" in position " << result << "\n";
  }
}

void second_functionality(char *argv[]) {
  cout << argv[1] << argv[2] << " Hi";
}