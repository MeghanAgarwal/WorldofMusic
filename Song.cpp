//
// Created by Meghan Agarwal on 12/7/21.
//
#include "Song.h"

Song::Song(){};

Song::Song(string songName, string songArtist) {
    title = songName;
    artist = songArtist;

}

Song::Song(string songName, string songArtist, string country_, string continent_, int rank_, string duration_) {
    title = songName;
    artist = songArtist;
    country = country_;
    continent = continent_;
    duration = duration_;
    rank = rank_;

}