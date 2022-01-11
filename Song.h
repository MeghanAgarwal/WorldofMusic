//
// Created by Meghan Agarwal on 12/7/21.
//

#ifndef MUSICPROJECT_SONG_H
#define MUSICPROJECT_SONG_H
#include <iostream>

using namespace std;
class Song {
public:
    string title;
    string artist;
    string ranking;
    string region;
    string country, continent, duration;
    int rank;
    Song();
    Song(string songName, string songArtist);
    Song(string songName, string songArtist, string country_, string continent_, int rank_, string duration_);
};
#endif