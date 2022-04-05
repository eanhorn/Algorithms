/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Erik Anhorn and Jared Kronyak
 * Version     : 1.0
 * Date        : December 5, 2021
 * Description : Implementation of Floyd's Algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const long INF = numeric_limits<long>::max();
int num_vertices;

void Floyd(long (&weight_matrix)[26][26], long (&inter_vert)[26][26], size_t n) {
    for (size_t k = 0; k < n; k++) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (weight_matrix[i][k] != INF && weight_matrix[k][j] != INF) {
                    if (weight_matrix[i][j] > (weight_matrix[i][k] + weight_matrix[k][j])) {
                        weight_matrix[i][j] = weight_matrix[i][k] + weight_matrix[k][j];
                        inter_vert[i][j] = k;
                    }
                }
            }
        }
    }
}
long len(long num) {
    long length = 0;
    while (num > 0) {
        length++;
        num = num / 10;
    }
    return length;
}

void display_table(long const matrix[26][26], const string &label, const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        if (num_vertices == 1 && use_letters) {
            cout << " ";
        }
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

string make_path(long const inter[26][26], int first, int second) {
    if (inter[first][second] == INF) {
        string path = "";
        path = path + static_cast<char>(first + 'A') + " -> " + static_cast<char>(second + 'A');
        return path;
    }
    int middle = inter[first][second];
    string front = make_path(inter, first, middle);
    string back = make_path(inter, middle, second);
    if (front.back() == back.front()) {
        front.pop_back();
        return front + back;
    }
    return front + back;
}

void display_paths(long const dist[26][26], long const inter[26][26], long const paths[26][26], const char alphabet[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; j++) {
            cout << alphabet[i] << " -> " << alphabet[j] << ", distance: ";
            if (paths[i][j] == INF) {
                cout << "infinity, path: none" << endl;
            } else {
                cout << paths[i][j] << ", path: ";
                if (i == j) {
                    cout << alphabet[i];
                } else if (inter[i][j] == INF) {
                    cout << alphabet[i] << " -> " << alphabet[j];
                } else {
                    cout << make_path(inter, i, j);
                }
                cout << endl;
            }
        }
    }
}

bool inRange(char c, char alphabet[], int num_vert) {
    for (int i = 0; i < num_vert; i++) {
        if (c == alphabet[i])
            return true;
    }
    return false;
}

int index_of(char array[], char token) {
    for (int i = 0; i < 26; i++) {
        if (array[i] == token)
            return i;
    }
    return -1;
}

bool isNumber(string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) == false) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    ifstream input_file(argv[1]);
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        string token;
        unsigned int line_num = 1;
        long distance_matrix[26][26];
        long path_lengths[26][26];
        long intermediate_vertices[26][26];
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (i == j) {
                    distance_matrix[i][j] = 0;
                    path_lengths[i][j] = 0;
                } else {
                    distance_matrix[i][j] = INF;
                    path_lengths[i][j] = INF;
                }
                intermediate_vertices[i][j] = INF;
            }
        }
        while (getline(input_file, line)) {
            if (line_num == 1) {
                if (!isNumber(line)) {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    return 1;
                } else if (stoi(line) <= 0 || stoi(line) >= 26) {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    return 1;
                }
                num_vertices = stoi(line);
                line_num++;
                continue;
            }

            stringstream this_line(line);
            int this_line_count = 0;
            int first_index;
            int second_index;
            while (this_line >> token) {
                char tkn = token.front();

                if (this_line_count == 0) {
                    if (token.length() != 1 || isNumber(token) || !inRange(tkn, alphabet, num_vertices)) {
                        cerr << "Error: Starting vertex '" << token << "' on line " << line_num << " is not among valid values " << alphabet[0] << "-"
                             << alphabet[num_vertices - 1] << "." << endl;
                        return 1;
                    }
                    first_index = tkn - 65;
                } else if (this_line_count == 1) {
                    if (token.length() != 1 || isNumber(token) || !inRange(tkn, alphabet, num_vertices)) {
                        cerr << "Error: Ending vertex '" << token << "' on line " << line_num << " is not among valid values " << alphabet[0] << "-"
                             << alphabet[num_vertices - 1] << "." << endl;
                        return 1;
                    }

                    second_index = tkn - 65;
                    if (!getline(this_line, token, ' ')) {
                        cerr << "Error: Invalid edge data '" << line << "' on line " << line_num << "." << endl;
                        return 1;
                    }
                } else if (this_line_count == 2) {
                    long cur = -1;
                    if (isNumber(token))
                        cur = stol(token);

                    if (cur <= 0) {
                        cerr << "Error: Invalid edge weight '" << token << "' on line " << line_num << "." << endl;
                        return 1;
                    }

                    distance_matrix[first_index][second_index] = cur;
                }

                this_line_count++;
            }
            line_num++;
        }
        input_file.close();

        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                path_lengths[i][j] = distance_matrix[i][j];
            }
        }
        Floyd(path_lengths, intermediate_vertices, num_vertices);
        display_table(distance_matrix, "Distance matrix:");
        display_table(path_lengths, "Path lengths:");
        display_table(intermediate_vertices, "Intermediate vertices:", true);
        display_paths(distance_matrix, intermediate_vertices, path_lengths, alphabet, num_vertices);

    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}
