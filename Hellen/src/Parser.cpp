#include "Parser.h"

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

World* Parser::readWorld(string file){
    log("Loading world : "+file,INFO);
    ifstream worldFile(file.c_str());
    if(! worldFile.is_open())
        log("UNABLE TO LOAD "+file, ERROR);

    string line;
    bool ignore;
    int phase = -1; // FIle part
    vector<Tile*> *tiles = new vector<Tile*>();
    map<int,sf::Texture*> *textures = new map<int,sf::Texture*>();

    while(true){
        ignore = true;
        if(!getline(worldFile,line)) // S'il n'y a plus rien a lire ...
            break;
        if(line.compare("--TEXTURES--")== 0)
            phase = 0;
        else if (line.compare("--TILES--") == 0)
            phase = 1;
        else
            ignore = false;

        if(! ignore){
            switch(phase){
                case 0 :
                    textures = Parser::getTexture(line,file,textures);
                    break;
                case 1:
                    tiles->push_back(Parser::getTile(line,file,worldFile,textures));
                    break;
                default:
                    log("POSSIBLE CORRUPTION ON "+file,WARNING);
            }
        }

    }
    World* world = new World(textures,tiles);
    log("World "+file+" loaded !", INFO);
    return world;
}

sf::Sprite* Parser::readSprite(string file, map<int,sf::Texture*> *textures){
    log("Loading tilefile : "+file, INFO);
    ifstream tileFile (file.c_str());
    string line;
    sf::Sprite* sprite = new sf::Sprite();
    int h,w,d_x,d_y,texture;

    if(! tileFile.is_open()){ // Si le fichier n'existe pas on ne peut etre ouvert
        log("UNABLE TO LOAD "+file,ERROR);
    }
    for(int i = 0; i<5;i++){
        if(! getline(tileFile,line))
            log("MALFORMED FILE : "+file, ERROR);
        switch(i){
            case 0 :
                if (! str2int(texture,line))
                    log("MALFORMED FILE (texture incorrect)"+file, ERROR);
                break;
            case 1:
                if (! str2int(d_x,line))
                    log("MALFORMED FILE (dx incorrect) : "+file, ERROR);
                break;
            case 2:
                if (! str2int(d_y,line))
                    log("MALFORMED FILE (dy incorrect) : "+file, ERROR);
                break;
            case 3:
                if (! str2int(w,line))
                    log("MALFORMED FILE (w incorrect) : "+file,ERROR);
                break;
            case 4:
                if (! str2int(h,line))
                    log("MALFORMED FILE (h incorrect) : "+file,ERROR);
                break;
            default:
                log("WTF ?!?",WARNING);
        }
    }
    tileFile.close();
    if(textures->find(texture) == textures->end())
        log("INVALID TEXTURE "+texture, ERROR);
    sprite->setTexture(*(textures->find(texture)->second));
    sprite->setTextureRect(sf::IntRect(d_x,d_y,h,w));

    log("Sprite "+file+" loaded ...", INFO);
    return sprite;
}

map<int,sf::Texture*>* Parser::getTexture(string line, string file, map<int,sf::Texture*> *textures){
    int t_id;
    unsigned long index = line.find_first_of(":"); // On cherche le caractere separateur
    if(index == line.npos) // S'il n'est pas dans la ligne
        log("WRONG TEXTURE DESCRIPTOR"+file, ERROR);


    string texturePath = Parser::getPath(file)+line.substr(index+1);

    if(! str2int(t_id,line.substr(0,index))) // On cast le nombre (string) découpé en int
        log("ERROR : WRONG TID"+file, ERROR);

    textures->insert(pair<int,sf::Texture*>(t_id, new sf::Texture()));

    if(! textures->find(t_id)->second->loadFromFile(texturePath))
        log("ERROR : CANNOT LOAD TEXTURE FROM FILE : "+texturePath, ERROR);
    log("LOADING TEXTURE : "+texturePath ,INFO);
    return textures;
}

Tile* Parser::getTile(string line, string file, ifstream &descFile, map<int,sf::Texture*> *textures){
    string filename = line;
    string path = Parser::getPath(file);
    int pos_x, pos_y;
    if(! getline(descFile,line) || ! str2int(pos_x,line))
        log("MALFORMED FILE (pos_x): "+file, ERROR);
    if(! getline(descFile,line) || ! str2int(pos_y,line))
        log("MALFORMED FILE (pos_y): "+file, ERROR);

    path = path + "sprites/"+filename;

    return new Tile(Parser::readSprite(path,textures),pos_x, pos_y);
}

string Parser::getPath(string file){ // Donne le chemin d'acces du fichier
    unsigned long index = file.find_last_of("/\\"); // On cherche l'index du dernier caractere separateur

    if(index != file.npos) // Fichier à la racine ?
        return file.substr(0,index+1); // et on coupe (YEAH !)
    else
        return "";
}

