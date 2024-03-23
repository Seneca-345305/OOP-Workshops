// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 03/17/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H
#include <iostream>
#include <vector>
#include <optional>
#include <list>

namespace seneca {
    enum class Align {
        left,
        right
    };

    struct Song {
        std::string m_title;
        std::string m_artist;
        std::string m_album;
        double m_price;
        std::optional<int> m_releaseYear;
        unsigned int m_length;
    };
    class SongCollection {
        std::vector<Song> m_song;
    public:
        explicit SongCollection(const char* filename);
        void display(std::ostream& out) const;
        void sort(const std::string& field);
        void cleanAlbum();
        bool inCollection(const std::string& artist) const;
        std::list<Song> getSongsForArtist(const std::string& artist) const;
    };

    std::ostream& operator<<(std::ostream& out, const Song& theSong);
    std::string trim(const std::string &str);

    template <typename T>
    const std::ostream& printFormatted(std::ostream& os, T item, const char* delim, unsigned int width = 0, char fill = ' ', Align direction = Align::right){
        // Set alignment based on direction parameter
        switch (direction) {
            case Align::left:
                os.unsetf(std::ios::right);
                os.setf(std::ios::left);
                break;
            case Align::right:
                os.unsetf(std::ios::left);
                os.setf(std::ios::right);
                break;
        }

        // Set fill and width
        os.fill(fill);
        os.width(width);

        // Print item and delimiter if not nullptr
        os << item;
        if(delim != nullptr){
            os << delim;
        }
        return os;
    }

} // seneca


#endif //SENECA_SONGCOLLECTION_H
