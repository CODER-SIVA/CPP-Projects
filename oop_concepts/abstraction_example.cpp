#include <iostream>
#include <string>
#include <vector>

// Example 1: Music Player System
class MusicPlayer {
private:
    std::vector<std::string> playlist;
    int currentTrack;
    bool isPlaying;
    
    void initializeAudio() {
        // Complex audio initialization code here
        std::cout << "Audio system initialized\n";
    }
    
    void decodeAudioFile(std::string filename) {
        // Complex audio decoding logic here
        std::cout << "Decoding " << filename << "\n";
    }
    
    void sendToSoundCard(std::string audioData) {
        // Complex sound card interaction here
        std::cout << "Playing audio through sound card\n";
    }

public:
    MusicPlayer() : currentTrack(0), isPlaying(false) {
        initializeAudio();
    }

    // Simple interface for users
    void play() {
        if (!playlist.empty()) {
            decodeAudioFile(playlist[currentTrack]);
            sendToSoundCard(playlist[currentTrack]);
            isPlaying = true;
            std::cout << "Now playing: " << playlist[currentTrack] << std::endl;
        }
    }

    void pause() {
        isPlaying = false;
        std::cout << "Music paused\n";
    }

    void addToPlaylist(std::string song) {
        playlist.push_back(song);
    }
};

// Example 2: Car Engine System
class CarEngine {
private:
    bool engineRunning;
    int rpm;
    float fuelLevel;
    
    void initializeEngine() {
        // Complex engine initialization
        std::cout << "Engine systems initialized\n";
    }
    
    void checkFuelInjection() {
        // Complex fuel injection calculations
        std::cout << "Fuel injection checked\n";
    }
    
    void controlSparkPlugs() {
        // Complex spark plug timing logic
        std::cout << "Spark plugs fired\n";
    }
    
    void manageCoolingSystem() {
        // Complex cooling system management
        std::cout << "Cooling system managed\n";
    }

public:
    CarEngine() : engineRunning(false), rpm(0), fuelLevel(100.0) {
        initializeEngine();
    }

    // Simple interface for users
    void startEngine() {
        if (!engineRunning && fuelLevel > 0) {
            checkFuelInjection();
            controlSparkPlugs();
            engineRunning = true;
            rpm = 800; // Idle RPM
            std::cout << "Engine started successfully\n";
        }
    }

    void stopEngine() {
        if (engineRunning) {
            engineRunning = false;
            rpm = 0;
            std::cout << "Engine stopped\n";
        }
    }

    void accelerate() {
        if (engineRunning) {
            rpm += 1000;
            manageCoolingSystem();
            std::cout << "Speed increased, Current RPM: " << rpm << std::endl;
        }
    }
};

int main() {
    // Testing Music Player
    MusicPlayer player;
    player.addToPlaylist("Song1.mp3");
    player.addToPlaylist("Song2.mp3");
    player.play();
    player.pause();

    // Testing Car Engine
    CarEngine engine;
    engine.startEngine();
    engine.accelerate();
    engine.stopEngine();

    return 0;
}
