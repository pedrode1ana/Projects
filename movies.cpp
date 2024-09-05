/*
Name: Pedro De Lana
Date:4/20
Assignment: Homework 7
Due date: 4/25
About: this is a code that can read in movie files and show information about it
Assumptions: the files imported are in good order meaning 
file size genre, title, year runtime rating
All work below was performed by Pedro De Lana
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <string>
using namespace std;

// Structure to store movie information
struct Movie {
    string genre;
    string title;
    string rating;
    int year;
    int runtime;
};

// Functions, those that send movie to allow to make null if needed or checks
void loadMovieFile(Movie*& movieArr, int& size);
void viewTotalRuntime(const Movie* movieArr, int size);
void viewMoviesByRating(const Movie* movieArr, int size);
void exportMoviesByGenre(const Movie* movieArr, int size);
void clearMovieDatabase(Movie*& movieArr, int& size);
void sortMoviesByYear(Movie* movieArr, int size);
void printMoviesYearSorted(const Movie* movieArr, int size);


int main() {
    Movie* movieArr = 0;
    int size = 0;
    char choice;

//always show the menu
    do {
        cout << "\n1 - Load Movie File\n"
             << "2 - View Total Movie Database Runtime\n"
             << "3 - View Movies by Rating\n"
             << "4 - Export Movies by Genre\n"
             << "5 - Clear Currently Loaded Database\n"
             << "6 - Print Database Sorted by Year - EXTRA CREDIT\n"
             << "Q - Quit\n"
             << "Enter choice > ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice) {
            case '1':
                loadMovieFile(movieArr, size);
                break;
            case '2':
                viewTotalRuntime(movieArr, size);
                break;
            case '3':
                viewMoviesByRating(movieArr, size);
                break;
            case '4':
                exportMoviesByGenre(movieArr, size);
                break;
            case '5':
                clearMovieDatabase(movieArr, size);
                break;
            case '6':
                if (size > 0) {
                    sortMoviesByYear(movieArr, size);
                    printMoviesYearSorted(movieArr, size);
                } else {
                    cout << "Load movie file first! Use option 1.\n";
                }
                break;
            case 'Q':
                cout << "Thanks for using the Movie Database Organizer!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 'Q');

    // Clean up allocated memory
    delete[] movieArr;

    return 0;
}

// Function to validate file name and open the file
bool openFile(ifstream& inFile, const string& prompt) {
    string filename;
    do {
        cout << prompt;
        cin >> filename;
        inFile.open(filename);
        if (!inFile) {
            cout << "That is not a valid file. Try again!\n";
        }
    } while (!inFile);
    return true;
}

// Function to load movie file
void loadMovieFile(Movie*& movieArr, int& size) {
    ifstream inFile;
    bool overwrite = false;

    if (size > 0) {
        char input;
        cout << "There is a database already loaded. This will overwrite the current database.\n"
             << "Continue? (y/n) > ";
        cin >> input;
        input = tolower(input);

        //check for correct response
        while (input != 'y' && input != 'n') {
            cout << "Enter y or n > ";
            cin >> input;
            input = tolower(input);
        }

        if (input == 'y') {
            overwrite = true;
            delete[] movieArr;
            movieArr = 0;
            size = 0;
        }
    }

    if (overwrite || size == 0) {
        if (openFile(inFile, "Which movie file would you like to open? > ")) {
            int numMovies;
            inFile >> numMovies;

            movieArr = new Movie[numMovies];
            size = numMovies;

            inFile.ignore(); // Ignore the newline character after reading numMovies

            for (int i = 0; i < numMovies; ++i) {
                getline(inFile, movieArr[i].genre, ':');
                getline(inFile, movieArr[i].title, ',');
                inFile >> movieArr[i].year >> movieArr[i].runtime >> movieArr[i].rating;
                inFile.ignore(); // Ignore the newline character after reading movie details
            }

            inFile.close();
        }
    }
}

// Function to view total runtime of the movie database
void viewTotalRuntime(const Movie* movieArr, int size) {
    int totalRuntime = 0;
    for (int i = 0; i < size; ++i) {
        totalRuntime += movieArr[i].runtime;
    }

    int hours = totalRuntime / 60;
    int minutes = totalRuntime % 60;

    if (size > 0) {
        cout << "Total Movie Database Runtime: " << hours << "hrs " << minutes << " mins\n";
    } else {
        cout << "Total Movie Database Runtime: 0hrs 0 mins\n";
    }
}

// Function to view movies by rating
void viewMoviesByRating(const Movie* movieArr, int size) {
    if (size > 0) {
        string rating;
        cout << "View movies with which rating? (G, PG, PG-13, R) > ";
        cin >> rating;

        bool found = false;
        cout << "MOVIES RATED " << rating << endl;

        for (int i = 0; i < size; ++i) {
            if (movieArr[i].rating == rating) {
                cout << movieArr[i].title << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No movies with rating " << rating << endl;
        }
    } else {
        cout << "Load movie file first! Use option 1.\n";
    }
}

// Function to export movies by genre
void exportMoviesByGenre(const Movie* movieArr, int size) {
    if (size > 0) {
        cout << "Exporting database by genre...\n";

        ofstream actionFile("action.txt");
        ofstream dramaFile("drama.txt");
        ofstream comedyFile("comedy.txt");
        ofstream scifiFile("scifi.txt");

        for (int i = 0; i < size; ++i) {
            const Movie& movie = movieArr[i];
            if (movie.genre == "ACTION") {
                actionFile << movie.title << " (" << movie.year << ")" << endl;
           
            } else if (movie.genre == "DRAMA") {
                dramaFile << movie.title << " (" << movie.year << ")" << endl;
           
            } else if (movie.genre == "COMEDY") {
                comedyFile << movie.title << " (" << movie.year << ")" << endl;
            
                
            } else if (movie.genre == "SCIENCE FICTION") {
                scifiFile << movie.title << " (" << movie.year << ")" << endl;
            }
        }

        actionFile.close();
        dramaFile.close();
        comedyFile.close();
        scifiFile.close();

        cout << "... export complete.\n";
    } else {
        cout << "Load movie file first! Use option 1.\n";
    }
}

// Function to clear the movie database
void clearMovieDatabase(Movie*& movieArr, int& size) {
    if (size > 0) {
        delete[] movieArr;
        movieArr = nullptr;
        size = 0;
        cout << "Movie database cleared successfully.\n";
    } else {
        cout << "Movie database already empty.\n";
    }
}

// Function to sort movies by year using bubble sort
void sortMoviesByYear(Movie* movieArr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (movieArr[j].year > movieArr[j + 1].year) {
                swap(movieArr[j], movieArr[j + 1]);
            }
        }
    }
}

// Function to print movies sorted by year seperate for cleaner code
void printMoviesYearSorted(const Movie* movieArr, int size) {
    cout << "Movie Database Sorted by Year\n";
    for (int i = 0; i < size; i++) {
        cout << movieArr[i].year << " : " << movieArr[i].title << endl;
    }
}