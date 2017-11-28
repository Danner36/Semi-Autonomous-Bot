#include "music.h"

void play_songs(int i)
{
    unsigned char notes[] = { 69, 69, 69, 69, 65, 67, 69, 0, 67, 69 };
    unsigned char lengths[] = { 12, 12, 12, 24, 24, 24, 12, 12, 12, 40 };
    oi_loadSong(i, 10, notes, lengths);
    oi_play_song(i);
}
