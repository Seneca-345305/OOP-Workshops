// Workshop 3 - STL Containers and Algorithms
// 2024/11/03 - If this code works, it was created by Cornel
//            - If it doesn't work, I don't know who wrote it.

#include <iostream>
#include <iomanip>
#include <fstream>
#include "collection.h"
#include "collection.h"     // intentional
#include "spellChecker.h"
#include "spellChecker.h"   // intentional
#include "book.h"
#include "book.h"           // intentional
#include "movie.h"
#include "movie.h"          // intentional
#include "tvShow.h"
#include "tvShow.h"         // intentional
#include "mediaItem.h"
#include "mediaItem.h"      // intentional
#include "settings.h"
#include "settings.h"       // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_SETTINGS_H
    #error "The header guard for 'settings.h' doesn't follow the convention!"
#endif
#ifndef SENECA_MEDIAITEM_H
    #error "The header guard for 'mediaItem.h' doesn't follow the convention!"
#endif
#ifndef SENECA_BOOK_H
    #error "The header guard for 'book.h' doesn't follow the convention!"
#endif
#ifndef SENECA_MOVIE_H
    #error "The header guard for 'movie.h' doesn't follow the convention!"
#endif
#ifndef SENECA_TVSHOW_H
    #error "The header guard for 'tvShow.h' doesn't follow the convention!"
#endif
#ifndef SENECA_SPELLCHECKER_H
    #error "The header guard for 'spellChecker.h' doesn't follow the convention!"
#endif
#ifndef SENECA_COLLECTION_H
    #error "The header guard for 'collection.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
	RecordParsingError = 3, // Some unknown issue appeared when processing a record from file
};

// The observer function for adding media items to the collection:
//   should be called every time a new item is added to the collection
void itemAddedObserver(const seneca::Collection& theCollection, const seneca::MediaItem& theBook)
{
	std::cout << "Item \"" << theBook.getTitle() << "\" added!\n";
}


template<typename T>
void loadMedia(seneca::Collection& col, const char* filename);
void loadEpisodes(seneca::Collection& col, const char* filename);

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	seneca::Collection col("Movies and TV Shows");

	{
		std::cout << ">>>  T1: Loading TV Shows\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		::loadMedia<seneca::TvShow>(col, "tvShows.csv");
		::loadEpisodes(col, "episodes.csv");
		::loadMedia<seneca::TvShow>(col, "tvShows.csv");       // should have no effect since the shows are already loaded
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T2: Display TV Shows as Table\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = true;
		seneca::g_settings.m_maxSummaryWidth = 64;
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T3: Display 'The Fall of the House of Usher'\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = false;
		seneca::g_settings.m_maxSummaryWidth = 80;
		auto show = col["\"The Fall of the House of Usher\""];
		std::cout << *show;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T4: Load More Shows\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		::loadEpisodes(col, "got.csv");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T5: Display All TV Shows as Table\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = true;
		seneca::g_settings.m_maxSummaryWidth = 72;
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T6: Load Movies\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		::loadMedia<seneca::Movie>(col, "movies.csv");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T7: Display Shows and Movies as Table\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = true;
		seneca::g_settings.m_maxSummaryWidth = 80;
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T8: Load Books with an Observer Deployed\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		col.setObserver(itemAddedObserver);
		::loadMedia<seneca::Book>(col, "books.csv");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T9: Display Everything as Table\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = true;
		seneca::g_settings.m_maxSummaryWidth = 100;
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T10: Use the Spellckecker Functor\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::SpellChecker sp("words.txt");
		sp.showStatistics(std::cout);
		for (auto j = 0u; j < col.size(); ++j)
			col[j]->fixSpelling(sp);
		sp.showStatistics(std::cout);
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T11: Display Everything as Table\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = true;
		seneca::g_settings.m_maxSummaryWidth = 100;
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T12: Remove Quotes from Title and Summary (ALG)\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_maxSummaryWidth = 240;
		col.removeQuotes();
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T13: Sort by Title (ALG)\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = true;
		seneca::g_settings.m_maxSummaryWidth = 100;
		col.sort("title");
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T14: Sort by Year (ALG)\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = true;
		seneca::g_settings.m_maxSummaryWidth = 100;
		col.sort("year");
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T15: Average Episode Length (ALG)\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = false;
		seneca::g_settings.m_maxSummaryWidth = 100;
		seneca::TvShow* show = dynamic_cast<seneca::TvShow*>(col["Agatha All Along"]);
		std::cout << *show;
		std::cout << "Average size of an episode ["
			<< static_cast<int>(show->getEpisodeAverageLength() / 60) << "] minutes.\n";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T16: Get Long Episodes (ALG)\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::TvShow* show = dynamic_cast<seneca::TvShow*>(col["Game of Thrones"]);
		auto lst = show->getLongEpisodes();
		std::cout << "Episodes of 'Game of Thrones' of at least 60 minutes:\n";
		for (const auto& title : lst)
			std::cout << "- " << title << '\n';
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T17: Print Whole Collection\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::g_settings.m_tableView = false;
		seneca::g_settings.m_maxSummaryWidth = 80;
		std::cout << col;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	return cout;
}

template<typename T>
void loadMedia(seneca::Collection& col, const char* filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "ERROR: Cannot open file [" << filename << "].\n";
		std::exit(AppErrors::CannotOpenFile);
	}

	for (std::string record{}; std::getline(file, record); /* nothing */)
	{
		try
		{
			seneca::MediaItem* item = T::createItem(record);
			col += item;
		}
		catch (const char* msg)
		{
			std::cout << "ERROR: [" << record << "] " << msg << '\n';
		}
		catch (...)
		{
			std::cout << "ERROR: Unknown error when processing file record [" << record << "].\n";
			std::exit(AppErrors::RecordParsingError);
		}
	}
}

void loadEpisodes(seneca::Collection& col, const char* filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "ERROR: Cannot open file [" << filename << "].\n";
		std::exit(AppErrors::CannotOpenFile);
	}

	for (std::string record{}; std::getline(file, record); /* nothing */)
	{
		try
		{
			seneca::TvShow::addEpisode(col, record);
		}
		catch (const char* msg)
		{
			std::cout << "ERROR: [" << record << "] " << msg << '\n';
		}
		catch (const std::string& msg)
		{
			std::cout << "ERROR: " << msg << '\n';
		}
		catch (...)
		{
			std::cout << "ERROR: Unknown error when processing file record [" << record << "].\n";
			std::exit(AppErrors::RecordParsingError);
		}
	}
}
