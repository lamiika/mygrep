#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using std::cout;
using std::cin;
using std::endl;
using std::string;

struct booleans {
  bool row_print;
  bool total_row_print;
  bool reverse_search;
  bool ignore_case;
};

void non_parameter_functionality();
void parameter_functionality(int argc, char *argv[]);

int search(string *search_ptr, string *input_ptr, bool ignore_case);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    non_parameter_functionality();
  } else {
    parameter_functionality(argc, argv);
  }

  return 0;
}

int search(string *search_ptr, string *input_ptr, bool ignore_case) {
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
      if (ignore_case) {
        a_char = std::tolower(a_char);
        b_char = std::tolower(b_char);
      }
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

void filter_options(string *parameters_ptr, booleans *options_ptr) {
  string parameters = *parameters_ptr;
  string char_l = "l";
  string char_o = "o";
  string char_r = "r";
  string char_i = "i";

  if (parameters.substr(0, 2) == "-o") {
    parameters = parameters.substr(2, parameters.length() - 2);
  } else {
    return;
  }

  if (search(&char_l, &parameters, true) != -1) {
    options_ptr->row_print = true;
  }

  if (search(&char_o, &parameters, true) != -1) {
    options_ptr->total_row_print = true;
  }

  if (search(&char_r, &parameters, true) != -1) {
    options_ptr->reverse_search = true;
  }

  if (search(&char_i, &parameters, true) != -1) {
    options_ptr->ignore_case = true;
  }
}

void non_parameter_functionality() {
  string input_string;
  string search_string;
  string *input_ptr = &input_string;
  string *search_ptr = &search_string;

  cout << "Give a string from which to search for: ";
  getline(cin, input_string);
  cout << "Give a search string: ";
  getline(cin, search_string);

  int result = search(search_ptr, input_ptr, false);

  if (result == -1) {
    cout << "\"" << search_string << "\" NOT found in \"" << input_string << "\"\n";
  } else {
    cout << "\"" << search_string << "\" found in \"" << input_string << "\" in position " << result << "\n";
  }
}

// g++ main.cpp -o mygrep.exe && ./mygrep -olo following man_grep_plain_ASCII.txt
void parameter_functionality(int argc, char *argv[]) {
  try {
    if (argc < 3) {
      throw "Too few parameters. Search term and file name required. Alternatively give no parameters at all.";
    }
  }
  catch(const char *error) {
    cout << "Exception: " << error << endl;
    return;
  }
  catch(...) {
    cout << "Generic error";
    return;
  }
  string parameters = argv[argc-3];
  string search_string = argv[argc-2];
  string filename = argv[argc-1];

  std::ifstream text_file(filename);

  booleans options;
  options.row_print = false;
  options.total_row_print = false;
  options.reverse_search = false;
  options.ignore_case = false;
  filter_options(&parameters, &options);

  try {
    std::ifstream value(filename, std::ifstream::ate | std::ifstream::binary);
    if (value.tellg() <= 0) {
      throw string("Exception Nr. -1 \nCould not find out the size of file \"" + filename + "\"");
    }
    if (!text_file.good()) {
      throw "File isn't readable or file doesn't exist.";
    }
  } 
  catch(string error) {
    cout << "An exception occurred. " << error << endl;
    return;
  }
  catch(const char *error) {
    cout << "Exception: " << error << endl;
    return;
  }
  catch(...) {
    cout << "Unknown error." << endl;
    return;
  }

  string line;
  int row_number = 0;
  int rows_total = 0;

  while(std::getline(text_file, line)) {
    int result = search(&search_string, &line, options.ignore_case);
    if (options.reverse_search) {
      if (result == -1) {
        result = 1;
      } else {
        result = -1;
      }
    }
    if (result != -1) {
      if (options.row_print) {
        cout << row_number << ": ";
      }
      cout << line << endl;
      rows_total++;
    }
    row_number++;
  }

  if (options.total_row_print && !options.reverse_search) {
    cout << "Occurrences of lines containing \"" << search_string << "\": " << rows_total << endl; 
  }
  
  if (options.total_row_print && options.reverse_search) {
    cout << "Occurrences of lines NOT containing \"" << search_string << "\": " << rows_total << endl; 
  }
}