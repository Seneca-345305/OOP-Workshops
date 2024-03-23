//
// Created by Tomas Rochwerger on 2024-02-18.
//

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include <string>
namespace seneca {

    class Movie {
        std::string m_title;
        size_t m_year;
        std::string m_desc;

    public:
        // Default constructor
        Movie() = default;

        // Query returning the title of the movie
        const std::string& title() const;

        // Constructor that receives a string with the movie information and parses it to set the movie attributes
        Movie(const std::string& strMovie);

        // Template function that receives a spell checker and uses it to fix the spelling of the movie's title and description
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_desc);
        }

        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);

    };

} // seneca

#endif //SENECA_MOVIE_H
