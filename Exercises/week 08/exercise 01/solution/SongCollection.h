#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H
#include <vector>
#include <string>
#include <list>

namespace seneca
{
	struct Song
	{
		std::string m_artist{};
		std::string m_title{};
		std::string m_album{};
		double m_price{};
		int m_year{};
		size_t m_length{}; // in seconds
	};

	std::ostream& operator<<(std::ostream& out, const Song& theSong);


	class SongCollection
	{
		// data
		std::vector<seneca::Song> m_songs;

		// functions
		std::string& trim(std::string& token);
	public:
		SongCollection(const std::string& filename);
		void display(std::ostream& out) const;
		void sort(std::string field);
		void cleanAlbum();
		bool inCollection(std::string artist) const;
		std::list<Song> getSongsForArtist(std::string artist) const;
	};
}

#endif
