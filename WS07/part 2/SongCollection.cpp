// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 03/17/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "SongCollection.h"
#include <fstream>
#include <iomanip>
#include <optional>
#include <numeric>
#include <algorithm>

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

            song.m_title = trim(song.m_title);
            song.m_artist = trim(song.m_artist);
            song.m_album = trim(song.m_album);

            m_song.push_back(song);

        }

    }

    void SongCollection::display(std::ostream &out) const {
        for (auto &song : m_song)
            out << song << std::endl;

        out << "----------------------------------------------------------------------------------------\n";
        out << "|";
        printFormatted(out, "Total Listening Time:", " ", 77, ' ', Align::right);
//        out <<  std::right << std::setw(77) << "Total Listening Time:";
        auto totalLength = std::accumulate(m_song.begin(), m_song.end(), 0, [](unsigned int total, const Song& song) {
            return total + song.m_length;
        });
//        out << std::setw(2) << totalLength / 3600 << ":"
        printFormatted(out, totalLength / 3600, ":", 1, ' ', Align::right);
//            << std::setw(2) << (totalLength % 3600) / 60 << ":"
        printFormatted(out, (totalLength % 3600) / 60, ":", 2, '0', Align::right);
//            << std::setw(2) << totalLength % 60;
        printFormatted(out, totalLength % 60, " |", 2, '0', Align::right);
        out << std::endl;
    }

    void SongCollection::sort(const std::string &field) {
        if (field == "title") {
            std::sort(m_song.begin(), m_song.end(), [](const Song& a, const Song& b) {
                return a.m_title < b.m_title;
            });
        } else if (field == "album") {
            std::sort(m_song.begin(), m_song.end(), [](const Song& a, const Song& b) {
                return a.m_album < b.m_album;
            });
        } else if (field == "length") {
            std::sort(m_song.begin(), m_song.end(), [](const Song& a, const Song& b) {
//                if(a.m_length == b.m_length)
//                    return a.m_title < b.m_title;
                return a.m_length < b.m_length;
            });
        }
    }

    void SongCollection::cleanAlbum() {
        std::transform(m_song.begin(), m_song.end(), m_song.begin(), [](Song& song) {
            if (song.m_album == "[None]") {
                song.m_album = " ";
            }
            return song;
        });

    }

    bool SongCollection::inCollection(const std::string &artist) const {
         return std::any_of(m_song.begin(), m_song.end(), [&](const Song &song) {
            return (song.m_artist == artist);
        });
    }

    std::list<Song> SongCollection::getSongsForArtist(const std::string &artist) const {
std::list<Song> songs;
        std::copy_if(m_song.begin(), m_song.end(), std::back_inserter(songs), [&](const Song& song) {
            return song.m_artist == artist;
        });
        return songs;
    }


    std::ostream& operator<<(std::ostream& out, const Song& song) {
        //lambda expression to convert length in seconds into minutes and seconds
        auto lengthConvert = [](unsigned int length, std::ostream& out) {
            out << std::setw(1) << std::setfill('0') << length / 60 << ":"
                << std::setw(2) << std::setfill('0') << length % 60 << std::setfill(' ');

        };

        out << "| " << std::left << std::setw(20) << std::setfill(' ') << song.m_title
            << " | " << std::setw(15) << song.m_artist
            << " | " << std::setw(20) << song.m_album
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
        if (start == std::string::npos) {
            return str;
        }
        size_t end = str.find_last_not_of(' ');
        return str.substr(start, end - start + 1);
    }
} // seneca