#include <iostream>
#include <string>
#include "GenericLinkedList.h"
#include "GenericLinkedList.cpp"
#include <sstream>
#include <vector>
#include <random>
//gnere class with a name
struct Genre {
	Genre() : name{ "" } {};
	Genre(std::string newname) : name{ newname } {};
	Genre(Genre* newgenre) : name{ newgenre->name } {};
	std::string name;
	bool operator ==(const Genre& g) {
		if (name == g.name) {
			return true;
		}
		else
			return false;
	}
};

// Basic structure of a song here, a name,file path, and a pointer to a genre class
struct Song {
	Song() : Name{ "" }, Filepath{ "" }, genre{ nullptr }{};
	Song(std::string name, std::string file, Genre *gen): Name{ name }, Filepath{ file }, genre{ gen } {};
	Song(Song *newsong) : Name{ newsong->Name }, Filepath{ newsong->Filepath }, genre{ newsong->genre } {};
	std::string Name;
	std::string Filepath;
	Genre* genre;
	bool operator ==(const Song & song) {
		if (Name == song.Name && genre == song.genre) {
			return true;
		}
		else {
			return false;
		}
	};
};

void Control_loop(LinkedList<Song>& songlist, LinkedList<Genre>& genre);
void Display_songs(LinkedList<Song>& songslist, std::string mygenre);
void Display_Genres(LinkedList<Genre>& genre);
Genre* Make_Genre_array();
Song* Make_Song_array(Genre genrelist[]);
void Play(LinkedList<Song>& songlist);
void Select_Genre(LinkedList<Song>& songslist);

int main() {

	Genre *currentgenres= Make_Genre_array();
	Song *currentsongs=  Make_Song_array( currentgenres) ;

	LinkedList<Song> songlist;
	LinkedList<Genre> genre;
	songlist.Add_Range(currentsongs, 12);
	genre.Add_Range(currentgenres, 4);

	Control_loop(songlist, genre);
	system("pause");
	return 0;
}
// This function is the main I/O interaction with the console, gives the choice of viewing genres, viewing songs by genres, or playing the list
void Control_loop(LinkedList<Song>& songlist, LinkedList<Genre>& genre) {
	while (true) {
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Welcome to this song database, Here are your options " << std::endl;
		std::cout << "1. Display all available Genres" << std::endl;
		std::cout << "2. Display all songs in a particular Genre" << std::endl;
		std::cout << "3. Play the song database" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
		std::string input;
		std::cin >> input;
		int myinput;
		std::stringstream(input) >> myinput;
		switch (myinput) {
		case 1:
			Display_Genres(genre);
			break;
		case 2:
			Select_Genre(songlist);
			break;
		case 3:
			Play(songlist);
			break;
		case 4:
			return;
		default:
			std::cout << "Not a valid option" << std::endl;
			break;
		}
	}
};
// takes in a song list and a genre stirng, and displays all the songs given that genre
void Display_songs(LinkedList<Song>& songslist, std::string mygenre) {
	int size = songslist.get_size();
	for (int i = 1; i < size+1; ++i) {
		Song song{ songslist.Find(i)->item };
		if (song.genre->name == mygenre) {
			std::cout << song.Name << std::endl;
		}
	}
};
//the function that allows you to display songs by genre
void Select_Genre(LinkedList<Song>& songslist) {
	std::cin.ignore();
	std::cout << "Please enter the genre" << std::endl;
	std::string genrename;
	std::getline(std::cin, genrename);
	Display_songs(songslist, genrename);
};
//the function that outputs all items in the genre list 
void Display_Genres(LinkedList<Genre>& genre) {
	int size = genre.get_size();
	for (int i = 1; i < size+1; ++i) {

		Genre curgenre{ genre.Find(i)->item };
		std::cout << curgenre.name << std::endl;
	}
};
// this function pre creates my genre array that is then passed to the make song array
Genre* Make_Genre_array() {
	Genre rock{ "Rock" };
	Genre classicrock{ "Classic Rock" };
	Genre edm{ "EDM" };
	Genre classical{ "Classical" };
	static Genre genrelist[4] = { rock, classicrock, edm, classical };
	return  genrelist;
};

// This takes in the genre array and pre creates around 12 songs that get put into the song list 
Song* Make_Song_array(Genre  genrelist[]) {
	Song rock1{ "Know your enemy","music/greenday1", &genrelist[0] };
	Song rock2{ "New Divide", "music/linkinpark", &genrelist[0] };
	Song rock3{ "Wheels", "music/wheels", &genrelist[0] };
	Song classicrock1{ "Stairway to Heaven", "music/Stairwaytoheaven", &genrelist[1] };
	Song classicrock2{ "Hey Jude","music/HeyJude", &genrelist[1] };
	Song classicrock3{ "All Along the Watchtower", "music/myboyjimmi", &genrelist[1] };
	Song EDM1{"Oceans", "music/awesomeedm", &genrelist[2] };
	Song EDM2{"Alone", "music/marshmellow", &genrelist[2] };
	Song EDM3{"Aftergold", "music/Aftergold", &genrelist[2] };
	Song Classical1{"spring allegro", "music/pretentious1", &genrelist[3] };
	Song Classical2{"Ride of the Valkyries","music/notasprentious2", &genrelist[3] };
	Song Classical3{"Requiem","music/Mozart", &genrelist[3] };

	static Song songlist[12] = { rock1, rock2, rock3, classicrock1, classicrock2 ,classicrock3, EDM1, EDM2, EDM3, Classical1, Classical2, Classical3 };
	return songlist;
};

//takes all the songs in the song lists, puts them in a vector, shuffles it ,and then outputs them 
void Play(LinkedList<Song> &songlist){
	int size = songlist.get_size();
	std::vector<Song> playlist;
	for (int i = 1; i < size + 1; ++i) {
		playlist.push_back(songlist.Find(i)->item);
	}
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(playlist), std::end(playlist), rng);
	for (int i = 0; i < size; ++i) {
		std::cout << playlist[i].Name << " " << playlist[i].genre->name << std::endl;
	}
	return;
};
