//
// Created by Tomas  on 2024-03-17.
//
#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H
#include <iostream>
#include <vector>
#include <optional>

namespace seneca {
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


    };
    std::ostream& operator<<(std::ostream& out, const Song& theSong);
    std::string trim(const std::string &str);

} // seneca

#endif //SENECA_SONGCOLLECTION_H
