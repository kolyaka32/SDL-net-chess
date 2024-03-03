#include "include.hpp"
#include <fstream>
#include "define.hpp"
#include "values.hpp"

#include "initFile.hpp"
#include "pause.hpp"

std::string baseIP;  // Saved ip for better expirience
std::string basePort;     // Saved connection port for better expirience

// Loading initialasing settings in game
void loadInitFile(){
    // Reading file
    std::ifstream inSettings(SETTING_FILE); // Open file to read
    std::string line;  // Output string line

    // Setting standart values for variables
    language = LNG_ENGLISH;
    MusicVolume = MIX_MAX_VOLUME/2;
    EffectsVolume = MIX_MAX_VOLUME/2;
    drawFPS = 60;
    fieldWidth = 3;
    winWidth = 3;
    baseIP = "127.0.0.1";
    basePort = "2000";

    // Reading file until it end
    while(std::getline(inSettings, line)){  
        std::string first = line.substr(0, line.find('=')-1);
        // Switching between options
        if( first == "language" ){
            std::string lang = line.substr(line.rfind('=')+2);
            if(lang == "russian"){
                language = LNG_RUSSIAN;
            }
            else if(lang == "english"){
                language = LNG_ENGLISH;
            }
        }
        else if( first == "music" ){
            MusicVolume = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "effects" ){
            EffectsVolume = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "max FPS" ){
            drawFPS = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "width" ){
            fieldWidth = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "win width" ){
            winWidth = std::stoi( line.substr(line.rfind('=')+2) );
        }
        else if( first == "IP" ){
            baseIP = line.substr(line.rfind('=')+2);
        }
        else if( first == "port" ){
            basePort = line.substr(line.rfind('=')+2);
        }
    }
    // Checking of minimal posible values
    SET_MIN(drawFPS, 5);
    SET_MIN(fieldWidth, 3);
    SET_MAX(fieldWidth, 21);
    SET_MIN(winWidth, 3);
    SET_MAX(winWidth, fieldWidth);

    inSettings.close();  // Closing reading file
}

// Saving initialasing file
void saveInitFile(){
    // Creating output file
    FILE* outSettings = fopen(SETTING_FILE, "w");

    // Writing data to output
    fprintf(outSettings, "# Language type (english/russian):\n");// Extra comment
    switch (language)  // Writing language
    {
    case LNG_RUSSIAN:
        fprintf(outSettings, "language = russian\n");
        break;
    case LNG_ENGLISH:
    default:
        fprintf(outSettings, "language = english\n");
        break;
    }

    fprintf(outSettings, "\n# Technical part:\n");               // Extra comment
    fprintf(outSettings, "music = %u\n", MusicVolume);           // Writing music volume
    fprintf(outSettings, "effects = %u\n", EffectsVolume);       // Writing effects volume
    fprintf(outSettings, "max FPS = %u\n", drawFPS);             // Writing frames per seconds

    fprintf(outSettings, "\n# Sizes of game field:\n");          // Extra comment
    fprintf(outSettings, "width = %u\n", fieldWidth);            // Writing width of grid of field
    fprintf(outSettings, "win width = %u\n", winWidth);          // Writing width to win

    fprintf(outSettings, "\n# Intrnet base parameters\n");               // Extra comment
    fprintf(outSettings, "IP = %s\n", baseIP.std::string::c_str());      // Base connect IP
    fprintf(outSettings, "port = %s\n", basePort.std::string::c_str());  // Base connect port

    fclose(outSettings);
}