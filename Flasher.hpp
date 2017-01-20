//
// Flasher
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#ifndef BREWTROLLER_FLASHER_FLASHER_HPP
#define BREWTROLLER_FLASHER_FLASHER_HPP

typedef void (*FlashProgressCallback)(int, bool);

class Flasher {
public:
    FlashProgressCallback progressCallback;
};


#endif //BREWTROLLER_FLASHER_FLASHER_HPP
