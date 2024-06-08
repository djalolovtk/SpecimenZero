
// New Esp Manager by Dark Team!
// Credit : Telegram @dark_fack
// Exclusive to everyone who meets in our community

//**********************************************

vector<void*> players;

void clearPlayers() {
    vector<void*> pls;
    for (int i = 0; i < players.size(); i++) {
        if (players[i] != NULL) {
            pls.push_back(players[i]);
        }
    }
    players = pls;
}

bool playerFind(void *pl) {
    if (pl != NULL) {
        for (int i = 0; i < players.size(); i++) {
            if (pl == players[i]) return true;
        }
    }
    return false;
}

//************************************************

