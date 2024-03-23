//
// Created by Tomas  on 2024-03-17.
//

#include "SongCollection.h"
#include <fstream>
#include <iomanip>
#include <optional>

namespace seneca {
    SongCollection::SongCollection(const char *filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("File not found");
        }

        std::string line;
        while (std::getline(file, line)) {
            Song song;
            song.m_title = line.substr(0, 25);
            song.m_artist = line.substr(25, 25);
            song.m_album = line.substr(50, 25);
            try {
                song.m_releaseYear = std::stoi(line.substr(75, 5));
            } catch (std::exception& e) {
                song.m_releaseYear = std::nullopt; // or any default value
            }
            try {
                song.m_length = std::stoi(line.substr(80, 5));
            } catch (std::exception& e) {
                song.m_length = 0; // or any default value
            }
            try {
                song.m_price = std::stod(trim(line.substr(85, 5)));
            } catch (std::exception& e) {
                song.m_price = 0.0; // or any default value
            }
            m_song.push_back(song);
        }

    }

    void SongCollection::display(std::ostream &out) const {
        for (auto &song : m_song)
            out << song << std::endl;

    }

    std::ostream& operator<<(std::ostream& out, const Song& song) {
        //lambda expression to convert length in seconds into minutes and seconds
        auto lengthConvert = [](unsigned int length, std::ostream& out) {
            out << std::setw(1) << std::setfill('0') << length / 60 << ":"
                << std::setw(2) << std::setfill('0') << length % 60 << std::setfill(' ');

        };

        out << "| " << std::left << std::setw(20) << trim(song.m_title)
            << " | " << std::setw(15) << trim(song.m_artist)
            << " | " << std::setw(20) << trim(song.m_album)
            << " | ";

        if (song.m_releaseYear) {
            out << std::right << std::setw(6) << *song.m_releaseYear;
        } else {
            out << std::right << std::setw(6) << " ";
        }

        out << " | "; lengthConvert(song.m_length, out);
        out <<  " | " << std::fixed << std::setprecision(2) << song.m_price << " |";

        return out;
    }

    std::string trim(const std::string &str) {
        // Remove leading and trailing spaces
        size_t start = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ');
        return str.substr(start, end - start + 1);
    }
} // seneca